#include <iostream>
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

const position UNDEFINED = {-1, -1};  // Undefined position constant
const char EMPTY = '\0';              // Empty space in tile grid
const char STATIC_BLOCK = '#';        // Static block space in tile grid
const char SAND = '.';                // Sand space in tile grid

/// @brief Draw a line of STATIC_BLOCK between two points in the tile grid
/// @param start : The starting position
/// @param finish : The ending position
/// @param tileMap : The tile grid to draw to

void drawLine(
    position start, position finish,
    std::unordered_map<int, std::unordered_map<int, char> >& tileMap
);

/// @brief Create a normalized position offset pointing from 'a' to 'b'
/// @param a : The starting position
/// @param b : The target posiition
/// @return a position object with a look vector length of 1

position normalize(position a, position b);

/// @brief Standard absolute value function
/// @param a : The integer to retreive the absolute value of
/// @return the absolute value result of 'a'

inline int abs(int a) { return a < 0 ? -a : a; }

/// @brief Simulate dropping sand until the sand falls into the void
/// @param spawnPos : Where to spawn the sand from
/// @param tileMap : The current tile grid content
/// @return how many tiles of sand were spawned until sand fell into the void

int dropSand(
    position spawnPos,
    std::unordered_map<int, std::unordered_map<int, char> >& tileMap
);

/// @brief Determine whether a sand particle is settled
/// @param sandPos : The sand particle's position
/// @param tileMap : The current tile grid content
/// @return TRUE if the sand particle is  settled, FALSE otherwise

bool settleSand(
    position& sandPos,
    std::unordered_map<int, std::unordered_map<int, char> >& tileMap
);

static int maxR = 0;  // Max height of the scan

std::ostream& operator<<(
    std::ostream& output,
    std::unordered_map<int, std::unordered_map<int, char> >& tileMap
) {
    for (unsigned r = 0; r < maxR + 3; ++r) {
        for (unsigned c = 400; c < 600; ++c) {
            output << (tileMap[r][c] == '\0' ? ' ' : tileMap[r][c]);
        }
        output << '\n';
    }

    return output;
}

int main() {
    std::unordered_map<int, std::unordered_map<int, char> > tileMap;

    int prevR = -1;  // Previous row coordinate for line draw
    int prevC = -1;  // Previous col coordinate for line draw
    int currR;       // Current  row coordinate for line draw
    int currC;       // Current  col coordinate for line draw

    while (std::cin >> currC) {
        std::cin.ignore();
        std::cin >> currR;

        if (currR > maxR) {
            maxR = currR;
        }

        if (position{prevR, prevC} != UNDEFINED) {
            drawLine({prevR, prevC}, {currR, currC}, tileMap);
        }

        prevR = currR;
        prevC = currC;

        if (std::cin.peek() == ' ') {
            std::cin.ignore(4);  // Ignore " -> "
        } else {
            prevR = -1;  // Re-initialize previous row to undefined
            prevC = -1;  // Re-initialize previous col to undefined
        }
    }

    // How much sand was dropped until sand fell into the void
    int sandDropped = dropSand({0, 500}, tileMap);

    // Finalize and print the tile map content to the screen
    tileMap[0][500] = '+';
    std::cout << tileMap << std::flush;

    // Results
    printf("\nSand Dropped: %d\n", sandDropped);

    return 0;
}

void drawLine(
    position start, position finish,
    std::unordered_map<int, std::unordered_map<int, char> >& tileMap
) {
    bool done = false;
    tileMap[start.r][start.c] = STATIC_BLOCK;
    while (!done) {
        start += normalize(start, finish);

        if (start == finish) {
            done = true;
        }

        tileMap[start.r][start.c] = STATIC_BLOCK;
    }
}

position normalize(position a, position b) {
    position tmp = b - a;

    int r = abs(tmp.r);
    int c = abs(tmp.c);
    int larger = r > c ? r : c;

    tmp.r /= larger;
    tmp.c /= larger;

    return tmp;
}

int dropSand(
    position spawnPos,
    std::unordered_map<int, std::unordered_map<int, char> >& tileMap
) {
    int sandDropped = 0;
    bool voided = false;

    while (!voided) {
        // Spawn sand at spawn position
        position sandPos = spawnPos;
        tileMap[sandPos.r][sandPos.c] = SAND;

        // While sand is not yet settled
        while (!voided && !settleSand(sandPos, tileMap)) {
            // If sand falls into the void
            if (sandPos.r == maxR) {
                tileMap[sandPos.r][sandPos.c] = 'O';
                voided = true;
            }
        }

        sandDropped += !voided;
    }

    return sandDropped;
}

bool settleSand(
    position& sandPos,
    std::unordered_map<int, std::unordered_map<int, char> >& tileMap
) {
    bool settled = false;

    // -----
    //  Check for an available spot to move the sand to

    if (tileMap[sandPos.r + 1][sandPos.c] == EMPTY) {  // Directly below
        // Swap sand into new position
        char tmp = tileMap[sandPos.r][sandPos.c];
        tileMap[sandPos.r][sandPos.c] = tileMap[sandPos.r + 1][sandPos.c];
        tileMap[sandPos.r + 1][sandPos.c] = tmp;
        sandPos.r++;
    } else if (
        tileMap[sandPos.r + 1][sandPos.c - 1] == EMPTY  // Left corner
    ) {
        // Swap sand into new position
        char tmp = tileMap[sandPos.r][sandPos.c];
        tileMap[sandPos.r][sandPos.c] = tileMap[sandPos.r + 1][sandPos.c - 1];
        tileMap[sandPos.r + 1][sandPos.c - 1] = tmp;
        sandPos.r++;
        sandPos.c--;
    } else if (
        tileMap[sandPos.r + 1][sandPos.c + 1] == EMPTY  // Right corner
    ) {
        // Swap sand into new position
        char tmp = tileMap[sandPos.r][sandPos.c];
        tileMap[sandPos.r][sandPos.c] = tileMap[sandPos.r + 1][sandPos.c + 1];
        tileMap[sandPos.r + 1][sandPos.c + 1] = tmp;
        sandPos.r++;
        sandPos.c++;
    } else {
        settled = true;
    }

    return settled;
}
