#include <algorithm>
#include <iostream>
#include <limits>
#include <list>
#include <unordered_map>

struct position {
    int r;
    int c;
    
    bool operator==(const position& rhs) {
        return r == rhs.r && c == rhs.c;
    }
    bool operator!=(const position& rhs) {
        return !(*this == rhs);
    }

    position operator+(const position& rhs) {
        return {r + rhs.r, c + rhs.c};
    }
    position& operator+=(const position& rhs) {
        *this = *this + rhs;
        return *this;
    }

    position operator-(const position& rhs) {
        return {r - rhs.r, c - rhs.c};
    }
    position& operator-=(const position& rhs) {
        *this = *this - rhs;
        return *this;
    }
};

// Sensor object which knows its position and the position of the closest beacon
struct sensor {
    position sensorPos;
    position beaconPos;
};

// Defines a range of tiles where `start` and `finish` are its corners
struct range {
    position start;
    position finish;
};

// Constant undefined position value
const position UNDEFINED {-1, -1};

// const int MAX_DIM = 20;
const int MAX_DIM = 4'000'000;  // Maximum value of r/c in the tile map

/// @brief Standard absolute value function
///
/// @param a : The integer to retreive the absolute value of
///
/// @return the absolute value result of 'a'

inline int abs(int a) { return a < 0 ? -a : a; }

/// @brief Standard manhattan distance function
///
/// @param a : First position
/// @param b : Second position
///
/// @return the manhattan distance between 'a' and 'b'

inline unsigned manhattan(position a, position b) {
    return abs(a.r - b.r) + abs(a.c - b.c);
}

/// @brief Standard min/max function
///
/// @param a : First value in comparison
/// @param b : Second value in comparison
///
/// @return min/max between 'a' and 'b'

inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }

/// @brief Create ranges of related non-empty tiles for the current row based on
///   the sensors that interact with the current row
/// 
/// @param row : The row to query interactions on
/// @param sensors : List of sensors deployed
/// @param ranges : Maps a row to its existing ranges

void createRanges(
    int row, std::list<sensor> sensors,
    std::unordered_map<int, std::vector<range> >& ranges
);

/// @brief Determines if two ranges are (1) end-to-end or (2) overlapping
///
/// @param a : First range
/// @param b : Second range
///
/// @return whether the ranges are end-to-end or overlapping

inline bool overlap(const range& a, const range& b) {
    return !(a.start.c > b.finish.c || a.finish.c < b.start.c) ||
        a.finish.c + 1 == b.start.c ||
        b.finish.c + 1 == a.start.c;
}

/// @brief Attempts to combine all overlapping ranges for a given row
///
/// @param row : The row to merge within
/// @param ranges : Maps a row to its existing ranges

void mergeRanges(int row, std::unordered_map<int, std::vector<range> >& ranges);

/// @brief Determines whether a row has an empty tile in it based on its ranges
///
/// @param row : The current row to query for an empty tile's existence
/// @param ranges : Maps a row to its existing ranges
///
/// @return a position {r, c} which points at the empty tile, or 'UNDEFINED'
///   if no such empty tile exists in the row.

position hasEmpty(
    int row, std::unordered_map<int, std::vector<range> >& ranges
);

int main() {
    // Tile grid containing different tile characters
    std::unordered_map<int, std::vector<range> > ranges;
    std::list<sensor> sensors;  // List of given sensors

    int sensorR;  // Row position of a sensor
    int sensorC;  // Column position of a sensor
    int beaconR;  // Row position of a beacon
    int beaconC;  // Column position of a sensor

    /// Using scanf to more easily process formatted input
    while (
        scanf("Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d\n",
            &sensorC, &sensorR, &beaconC, &beaconR
        ) > 0
    ) {
        sensors.push_back({{sensorR, sensorC}, {beaconR, beaconC}});

        if (  // If sensor falls in valid bounding box
            sensorR >= 0 && sensorR <= MAX_DIM &&
            sensorC >= 0 && sensorC <= MAX_DIM
        ) {
            ranges[sensorR].push_back({
                sensors.back().sensorPos, sensors.back().sensorPos
            });
        }

        if (  // If beacon falls in valid bounding box
            beaconR >= 0 && beaconR <= MAX_DIM &&
            beaconC >= 0 && beaconC <= MAX_DIM
        ) {
            ranges[beaconR].push_back({
                sensors.back().beaconPos, sensors.back().beaconPos
            });
        }
    }

    // Vertical scan from row 0 through row MAX_DIM looking for the EMPTY tile
    position emptyPos = UNDEFINED;
    int r = 0;

    while (emptyPos == UNDEFINED && r <= MAX_DIM) {
        createRanges(r, sensors, ranges);  // Create ranges of non-empty tiles
        mergeRanges(r, ranges);            // Simplify ranges
        emptyPos = hasEmpty(r++, ranges);  // Query for an empty space in row
    }

    // Results
    printf("Tuning Frequency: %ld\n",
        // In-order array index of the empty tile in the bounding box's 2D grid
        (long)emptyPos.c * MAX_DIM + emptyPos.r
    );

    return 0;
}

void createRanges(
    int row, std::list<sensor> sensors,
    std::unordered_map<int, std::vector<range> >& ranges
) {
    for (auto& sens : sensors) {
        // Get manhattan distance between sensor and its closest beacon
        int manDist = manhattan(sens.sensorPos, sens.beaconPos);

        // Check if row intersects area of vacancies around sensor
        if (
            sens.sensorPos.r - manDist <= row &&
            sens.sensorPos.r + manDist >= row
        ) {
            // Get row offset between 'row' and sensor's row
            int rowDiff = row - sens.sensorPos.r;

            // Get arc radius of intersected segment
            int radius = manDist - abs(rowDiff);

            // Check if intersected segment range overlaps with the range
            // between valid columns
            if (
                sens.sensorPos.c - radius <= MAX_DIM &&
                sens.sensorPos.c + radius >= 0
            ) {
                // Place range of intersected segment into ranges list
                ranges[row].push_back({
                    {row, max(sens.sensorPos.c - radius, 0)},
                    {row, min(sens.sensorPos.c + radius, MAX_DIM)}
                });
            }
        }
    }
}

void mergeRanges(int row, std::unordered_map<int, std::vector<range> >& ranges) {
    std::sort(ranges[row].begin(), ranges[row].end(), [](range& a, range& b) {
        return a.start.c < b.start.c ||
            (a.start.c == b.start.c && a.finish.c > b.finish.c);
    });

    auto it = ranges[row].begin();
    auto next = it + 1;

    while (next != ranges[row].end()) {
        if (overlap(*it, *next)) {
            // Merge current and next ranges into one range
            it->finish.c = max(it->finish.c, next->finish.c);
            next = ranges[row].erase(next);
        } else {
            // Check next pair of ranges
            ++it;
            ++next;
        }
    }
}

position hasEmpty(
    int row, std::unordered_map<int,std::vector<range> >& ranges
) {
    position emptyPos = UNDEFINED;

    int rangeSize = ranges[row].front().finish.c
        - ranges[row].front().start.c + 1;

    if (ranges[row].size() == 1 && rangeSize != MAX_DIM + 1) {  // Gap on edge
        range leftEdge {{row, -1}, {row, -1}};

        if (overlap(ranges[row].front(), leftEdge)) {  // Range starts at 0
            emptyPos = {row, MAX_DIM};
        } else {  // Range starts at 1
            emptyPos = {row, 0};
        }
    } else if (ranges[row].size() > 1) {  // Gap between ranges
        emptyPos = {row, ranges[row].front().finish.c + 1};
    }

    return emptyPos;
}
