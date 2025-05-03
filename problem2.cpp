#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Enum for direction representation
enum class Direction { DOWN, RIGHT };

// Function to find the minimum cost path in a grid
pair<vector<Direction>, int> findMinimumCostPath(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    
    // DP table to store the minimum cost to reach each cell
    vector<vector<int>> dp(m, vector<int>(n, 0));
    // Direction table to store the direction from which we came to the cell
    vector<vector<Direction>> direction(m, vector<Direction>(n));
    
    // Initialize the DP table for the first cell
    dp[0][0] = grid[0][0];
    
    // Fill the first row (can only come from the left)
    for (int j = 1; j < n; ++j) {
        dp[0][j] = dp[0][j-1] + grid[0][j];
        direction[0][j] = Direction::RIGHT;
    }
    
    // Fill the first column (can only come from above)
    for (int i = 1; i < m; ++i) {
        dp[i][0] = dp[i-1][0] + grid[i][0];
        direction[i][0] = Direction::DOWN;
    }
    
    // Fill the rest of the DP table
    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            if (dp[i-1][j] < dp[i][j-1]) {
                dp[i][j] = dp[i-1][j] + grid[i][j];
                direction[i][j] = Direction::DOWN;
            } else {
                dp[i][j] = dp[i][j-1] + grid[i][j];
                direction[i][j] = Direction::RIGHT;
            }
        }
    }
    
    // Backtrack to find the path
    vector<Direction> path;
    int i = m - 1, j = n - 1;
    
    while (i > 0 || j > 0) {
        if (direction[i][j] == Direction::DOWN) {
            path.push_back(Direction::DOWN);
            i--;
        } else {
            path.push_back(Direction::RIGHT);
            j--;
        }
    }
    
    reverse(path.begin(), path.end());

    // Return the path and total cost
    return { path, dp[m - 1][n - 1] };
}

// Function to print the path directions
void printPath(const vector<Direction>& path) {
    for (const auto& dir : path) {
        if (dir == Direction::DOWN) {
            cout << "DOWN ";
        } else {
            cout << "RIGHT ";
        }
    }
    cout << endl;
}

int main() {
    // Example grid
    vector<vector<int>> grid = {
        {5, 1, 1},
        {8, 4, 7},
        {2, 4, 5},
        {5, 6, 3}
    };
    
    // Find the minimum cost path and its cost
    auto [path, cost] = findMinimumCostPath(grid);
    
    // Output the results
    cout << "Minimum cost path: ";
    printPath(path);
    cout << "Total cost: " << cost << endl;
    
    return 0;
}
