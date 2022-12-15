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

const char EMPTY = '\0';  // Represents an unmarked spot in the tile grid
const char VACANT = '.';  // A spot where a beacon cannot be in the tile grid
const char SENSOR = 'S';  // Sensor symbol in the tile grid
const char BEACON = 'B';  // Beacon symbol in the tile grid

const int ROW_QUERY = 2'000'000;  // Which row to count vacancies in

/// @brief Standard absolute value function
/// @param a : The integer to retreive the absolute value of
/// @return the absolute value result of 'a'

inline int abs(int a) { return a < 0 ? -a : a; }

/// @brief Standard manhattan distance function
/// @param a : First position
/// @param b : Second position
/// @return the manhattan distance between 'a' and 'b'

inline unsigned manhattan(position a, position b) {
    return abs(a.r - b.r) + abs(a.c - b.c);
}

/// @brief Create a normalized position offset pointing from 'a' to 'b'
/// @param a : The starting position
/// @param b : The target posiition
/// @return a position object with a look vector length of 1

position normalize(position a, position b);

/// @brief Draw a line of characters between two points in the tile grid
/// @param start : The starting position
/// @param finish : The ending position
/// @param tileMap : The tile grid to draw to
/// @param fill : The character to draw with

void drawLine(
    position start, position finish,
    std::unordered_map<int, std::unordered_map<int, char> >& tileMap,
    char fill
);

/// @brief Draw and mask a diamond around a sensor with radius
///   `manhattan(sens.sensorPos, sens.beaconPos)` for a given row
/// @param sens : The sensor at the center of the diamond
/// @param row : The row to mask the diamond in
/// @param tileMap : The tile map to draw to

void fillDiamond(
    sensor& sens, int row,
    std::unordered_map<int, std::unordered_map<int, char> >& tileMap
);

/// @brief Count how many spaces are `VACANT` in the tile map for a given row
/// @param row : The row to check
/// @param tileMap : The tile map to count vacancies in
/// @return how many spaces in the row are vacant

int countVacancies(
    int row,
    std::unordered_map<int, std::unordered_map<int, char> >& tileMap
);

int main() {
    // Tile grid containing different tile characters
    std::unordered_map<int, std::unordered_map<int, char> > tileMap;

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
        tileMap[sensorR][sensorC] = SENSOR;  // Place sensor placeholder in grid
        tileMap[beaconR][beaconC] = BEACON;  // Place beacon placeholder in grid

        sensor sens = {{sensorR, sensorC}, {beaconR, beaconC}};

        fillDiamond(sens, ROW_QUERY, tileMap);
    }

    // Results
    printf("Number of vacancies in row %d: %d\n",
        ROW_QUERY, countVacancies(ROW_QUERY, tileMap)
    );

    return 0;
}

position normalize(position a, position b) {
    position tmp = b - a;

    int r = abs(tmp.r);
    int c = abs(tmp.c);
    int larger = r > c ? r : c;

    if (larger != 0) {
        tmp.r /= larger;
        tmp.c /= larger;
    }

    return tmp;
}

void drawLine(
    position start, position finish,
    std::unordered_map<int, std::unordered_map<int, char> >& tileMap,
    char fill
) {
    bool done = false;

    if (tileMap[start.r][start.c] == EMPTY) {
        tileMap[start.r][start.c] = fill;
    }

    while (!done) {
        start += normalize(start, finish);

        if (start == finish) {
            done = true;
        }

        if (tileMap[start.r][start.c] == EMPTY) {
            tileMap[start.r][start.c] = fill;
        }
    }
}

void fillDiamond(
    sensor& sens, int row,
    std::unordered_map<int, std::unordered_map<int, char> >& tileMap
) {

    // Get manhattan distance between sensor and beacon
    int manDist = manhattan(sens.sensorPos, sens.beaconPos);

    // Detect if `row` intersects the vacancy area around the sensor
    if (
        sens.sensorPos.r - manDist <= row &&
        sens.sensorPos.r + manDist >= row
    ) {
        // Find the offset from the sensor's row to the intersection's row
        int interDist = row - sens.sensorPos.r;

        // Get arc radius of intersecting line
        int radius = manDist - abs(interDist);

        // Draw vacancies onto the tile map along the intersected tiles
        drawLine(
            {row, sens.sensorPos.c - radius},
            {row, sens.sensorPos.c + radius},
            tileMap, VACANT
        );
    }

}

int countVacancies(
    int row,
    std::unordered_map<int, std::unordered_map<int, char> >& tileMap
) {
    int vacancies = 0;

    for (auto& [_, space] : tileMap[row]) {
        vacancies += space == VACANT;
    }

    return vacancies;
}