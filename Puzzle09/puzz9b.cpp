#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>

// General integer Vec2 object for each snake segment
struct position {
    long x;
    long y;
    bool operator==(const position rhs) {
        return rhs.x == x && rhs.y == y;
    }
    position operator+(const position& rhs) {
        position tmp = *this;
        tmp.x += rhs.x;
        tmp.y += rhs.y;
        return tmp;
    }
    position& operator+=(const position& rhs) {
        position tmp = *this + rhs;
        *this = tmp;
        return *this;
    }
    position operator-(const position& rhs) {
        position tmp = *this;
        tmp.x -= rhs.x;
        tmp.y -= rhs.y;
        return tmp;
    }
    position& operator-=(const position& rhs) {
        position tmp = *this - rhs;
        *this = tmp;
        return *this;
    }
    bool operator!=(const position rhs) {
        return !(*this == rhs);
    }
};

/// @brief Normalize the x and y value of a position.
/// @param a : The position to normalize.
/// @return Normalized position.

position normalize(position a) {
    // Largest absolute magnitude between x and y
    long maxMag = std::abs(a.y) - std::abs(a.x) > 0 ?
        std::abs(a.y) : std::abs(a.x);
    a.x = a.x / maxMag;
    a.y = a.y / maxMag;
    return a;
}

static const unsigned SNAKE_LENGTH = 10;

/// @brief Update each segment in the snake after the head has moved.
/// @param snake : The snake to update the segments in.

void update(position snake[]) {
    // Loop until distance is smaller than 1.5
    bool cont = true;
    for (unsigned s = 0; cont && s + 1 < SNAKE_LENGTH; ++s) {
        if (
            std::abs(snake[s].y - snake[s + 1].y) == 2 ||
            std::abs(snake[s].x - snake[s + 1].x) == 2
        ) {
            snake[s + 1] = snake[s] + normalize(snake[s + 1] - snake[s]);
        } else {
            cont = false;
        }
    }
}

int main() {
    // Simulate a segmented snake
    position snake[SNAKE_LENGTH] {};
    // Map a position string (ie, "-1,2") to if it has been visited
    std::unordered_map<std::string, bool> tileMap;

    char dir;  // U,D,L,R, direction input
    int dist;  // Distance traveled by head in direction

    position& hPos = snake[0];                 // Reference to head of snake
    position& tPos = snake[SNAKE_LENGTH - 1];  // Reference to tail of snake

    while (std::cin >> dir >> dist) {
        switch (dir) {
        case 'U':
            while (dist-- > 0) {
                hPos += {0, 1};
                update(snake);
                tileMap[std::to_string(tPos.x)+","+std::to_string(tPos.y)] = 1;
            }
            break;
        case 'D':
            while (dist-- > 0) {
                hPos -= {0, 1};
                update(snake);
                tileMap[std::to_string(tPos.x)+","+std::to_string(tPos.y)] = 1;
            }
            break;
        case 'L':
            while (dist-- > 0) {
                hPos -= {1, 0};
                update(snake);
                tileMap[std::to_string(tPos.x)+","+std::to_string(tPos.y)] = 1;
            }
            break;
        case 'R':
            while (dist-- > 0) {
                hPos += {1, 0};
                update(snake);
                tileMap[std::to_string(tPos.x)+","+std::to_string(tPos.y)] = 1;
            }
            break;
        }
    }

    int visited = 0;  // Number of tiles visited by tail segment
    for (auto& [key, value] : tileMap) {
        visited += value;
    }

    printf("Total tiles covered by tail: %d\n", visited);

    return 0;
}
