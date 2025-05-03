#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Interval {
    int start;
    int end;
};

// Returns minimum number of red intervals and prints out the selected intervals
int minimumRedIntervalsToCoverBlue(vector<Interval> blue, vector<Interval> red) {
    // Sort blue intervals by their end time
    sort(blue.begin(), blue.end(), [](const Interval &a, const Interval &b) {
        return a.end < b.end;
    });

    // Sort red intervals by their start time
    sort(red.begin(), red.end(), [](const Interval &a, const Interval &b) {
        return a.start < b.start;
    });

    int count = 0;
    int redIndex = 0;
    int n = blue.size();
    int m = red.size();

    vector<Interval> selectedRedIntervals; // Store chosen red intervals
    
    for (int i = 0; i < n; ) {
        int currentBlueEnd = blue[i].end;
        int lastRedEnd = -1;
        int chosenRedIdx = -1;

        // Find the red interval that can cover the current blue interval and extends coverage the furthest
        while (redIndex < m && red[redIndex].start <= currentBlueEnd) {
            if (red[redIndex].end > lastRedEnd) {
                lastRedEnd = red[redIndex].end;
                chosenRedIdx = redIndex;
            }
            redIndex++;
        }

        if (lastRedEnd < currentBlueEnd) {
            // No red interval covers this blue interval
            return -1;
        }

        count++;
        selectedRedIntervals.push_back(red[chosenRedIdx]);

        // Move to the next blue interval that is not covered by the chosen red interval
        while (i < n && blue[i].start <= lastRedEnd) {
            i++;
        }
    }

    cout << "Selected Red Intervals for coverage:\n";
    for (const auto& interval : selectedRedIntervals) {
        cout << "(" << interval.start << ", " << interval.end << ")\n";
    }

    return count;
}

int main() {
    vector<Interval> blue = {{0, 2}, {5, 5}, {7, 10}, {11, 13}};
    vector<Interval> red = {{0, 4}, {2, 5}, {4, 8}, {9, 10}, {9, 11}, {10, 12}, {11, 12}};
    
    /*vector<Interval> blue = {{1, 3}, {4, 6}, {7, 9}, {10, 15}, {16, 18}};
   vector<Interval> red = {{0, 2}, {2, 5}, {5, 8}, {9, 12}, {11, 17}, {14, 20}};*/      // other example for input 

    int result = minimumRedIntervalsToCoverBlue(blue, red);
    if(result == -1) {
        cout << "It is impossible to cover all blue intervals with the given red intervals.\n";
    } else {
        cout << "Minimum number of red intervals to cover blue: " << result << endl;
    }

    return 0;
}