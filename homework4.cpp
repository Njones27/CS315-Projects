#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <random>
#include <vector>

using namespace std; 
constexpr int kBucketCount = 50;

// Generates a trial of kBucketCount random integers between [0, 999]
vector<int> generate_trial(mt19937& rng) {
    uniform_int_distribution<int> dist(0, 999);
    vector<int> values(kBucketCount);

    for(int& value : values) {
        value = dist(rng);
    }

    return values;
}

// Bucket histogram for a single trial
vector<int> populate_buckets(const vector<int>& values) {
    vector<int> bucket_counts(kBucketCount, 0);

    const int max_value = *max_element(values.begin(), values.end());
    const int divisor = max_value + 1;  // Guard division when max_value == 0.

    for (int value : values) {
        const int bucket_index = (value * kBucketCount) / divisor;
        bucket_counts[bucket_index]++;
    }
    return bucket_counts;
}

struct Statistics {
    double mean = 0.0;
    double standard_deviation = 0.0;
};

Statistics compute_statistics(double sum, double sum_of_squares, int trials) {
    const double mean = sum / trials;
    double variance = (sum_of_squares / trials) - (mean * mean);
    if (variance < 0.0) {
        variance = 0.0;  // Guard small negative values
    }
    const double std_dev = sqrt(variance);

    return Statistics{mean, std_dev};
}


int main() {
    cout << "Enter the number of trials: ";
    int trials = 0;
    if (!(cin >> trials) || trials <= 0) {
        cerr << "Number of trials must be a positive integer.\n";
        return 1;
    }

    mt19937 rng(random_device{}());
    vector<double> sum_counts(kBucketCount, 0.0);
    vector<double> sum_of_squares(kBucketCount, 0.0);

    for(int trial = 0; trial < trials; ++trial) {
        const vector<int> values = generate_trial(rng);
        const vector<int> bucket_counts = populate_buckets(values);

        for(int i = 0; i < kBucketCount; ++i) {
            const double count = static_cast<double>(bucket_counts[i]);
            sum_counts[i] += count;
            sum_of_squares[i] += count * count;
        }
    }

    cout << fixed << setprecision(4);

    vector<Statistics> bucket_stats(kBucketCount);
    for(int i = 0; i < kBucketCount; ++i) {
        bucket_stats[i] = compute_statistics(sum_counts[i], sum_of_squares[i], trials);
    }

    cout << "****** Mean of the count for each bucket across " << trials << " trials:\n";

    double mean_total = 0.0;
    for(int i = 0; i < kBucketCount; ++i) {
        mean_total += bucket_stats[i].mean;
        cout << "Mean of the count in bucket " << i << ": " << bucket_stats[i].mean << '\n';
    }

    cout << "****** Standard deviation of the count for each bucket across " << trials << " trials:\n";

    double std_dev_total = 0.0;
    for(int i = 0; i < kBucketCount; ++i) {
        std_dev_total += bucket_stats[i].standard_deviation;
        cout << "Standard deviation of the count in bucket " << i << ": "
                  << bucket_stats[i].standard_deviation << '\n';
    }

    const double mean_average = mean_total / kBucketCount;
    const double std_dev_average = std_dev_total / kBucketCount;

    cout << "****** Average of means: " << mean_average << '\n';
    cout << "****** Average of standard deviations: " << std_dev_average << '\n';

    return 0;
}
