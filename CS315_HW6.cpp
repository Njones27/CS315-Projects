/* Course: CS315-001
* Project: Homework 6
* Date: 12/09/2025
* Purpose: Maximum Prize Game
*	The program prompts the user to input a list of n integers (one per line; duplicates allowed; zero or negative to end
*   input). The program then finds the set of buttons to maximize the total prize value with the constraint that no two
*   adjacent buttons can be chosen. It then displays the list of chosen buttons and the maximum total prize the player
*   could collect.
* Authors: Nathan Jones, Ian Rowe Rojas, Hannah Laney
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to find maximum prize and print selected buttons
void solve_game(const vector<int>& prizes) {
    int n = prizes.size();
    if (n == 0) {
        cout << "The maximum total prize is: 0" << endl;
        return;
    }

    // dp[i] stores the max prize collectible considering buttons 0 to i
    vector<long long> dp(n); 
    
    // Base cases
    dp[0] = prizes[0];
    if (n > 1) {
        dp[1] = max(prizes[0], prizes[1]);
    }

    // DP table
    for (int i = 2; i < n; i++) {        
        long long include_current = prizes[i] + dp[i-2];
        long long exclude_current = dp[i-1];
        
        dp[i] = max(include_current, exclude_current);
    }
    
    cout << "The maximum total prize is: " << dp[n-1] << endl;

    // For our bonus points
    cout << "Optimal buttons are:" << endl;
    vector<int> selected_indices;
    // Backtrack from the last element
    int i = n - 1;
    while (i >= 0) {
        if (i == 0) {
            // If we are at the first element, we must have selected it
            selected_indices.push_back(i + 1); // +1 bc of 1-based indexing
            break; 
        }

        // Check if current button i was included in the optimal solution
        // It was included if dp[i] equals (prizes[i] + dp[i-2])
        long long val_if_included = prizes[i];
        if (i >= 2) val_if_included += dp[i-2];

        if (dp[i] == val_if_included) {
            selected_indices.push_back(i + 1);
            i -= 2; // Can't pick adjacent, so jump back 2
        } else {
            i -= 1; // Current wasn't picked, move to previous
        }
    }

    // Print in increasing order
    for (int k = selected_indices.size() - 1; k >= 0; k--) {        
        // selected_indices contains 1-based IDs, prizes is 0-based
        int idx = selected_indices[k] - 1; 
        cout << "Button " << selected_indices[k] << " : " << prizes[idx] << endl;
    }
}

int main() {
    cout << "Let's play the maximum prize game!" << endl;
    cout << "Enter possible prize values (one per line or space separated; <= 0 to stop): " << endl;

    vector<int> prizes;
    int val;
        
    while (cin >> val && val > 0) {
        prizes.push_back(val);
    }

    solve_game(prizes);

    return 0;
}