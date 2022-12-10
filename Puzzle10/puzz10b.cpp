#include <iostream>
#include <list>
#include <string>

// Contains information about current clock cycle and register value
struct runtime_info {
    long cycle;
    long info;
};

/// @brief Draw a pixel to the CRT screen based on the clock cycle and x value
///
/// @param cycle : The clock cycle of the CPU
/// @param x : The x register value
/// @param screen : The CRT screen pixel array

void draw(long cycle, long x, char screen[][40]);

int main() {
    char screen[6][40] {};  // 2D pixel grid simulating a CRT screen

    std::string op;  // String for operation name
    long num;        // Parameter of addx operation

    long clockCycle = 0;  // Current clock cycle (0 when program hasn't started)
    long x = 1;           // Current X register value (initally set to 1)

    while (std::cin >> op) {
        if (op == "addx") {
            std::cin >> num;

            // Update clock value and draw pixel to CRT
            ++clockCycle;
            draw(clockCycle, x, screen);

            // Update clock value and draw pixel to CRT
            ++clockCycle;
            draw(clockCycle, x, screen);

            // Modify x register after two clock cycles
            x += num;
        } else {  // no-op
            // Update clock value and draw pixel to CRT
            ++clockCycle;
            draw(clockCycle, x, screen);

            // Do nothing after one clock cycle
        }
    }

    // Results
    std::cout << "CRT CONTENT:\n------------\n";
    for (unsigned r = 0; r < 6; ++r) {
        for (unsigned c = 0; c < 40; ++c) {
            std::cout << screen[r][c];
        }
        std::cout << std::endl;
    }

    return 0;
}

void draw(long cycle, long x, char screen[][40]) {
    unsigned r = (cycle - 1) / 40;  // CRT row derived from clock cycle
    unsigned c = (cycle - 1) % 40;  // CRT column derived from clock cycle

    if (c >= x - 1 && c <= x + 1) {  // Sprite and clock align
        screen[r][c] = '#';
    } else {
        screen[r][c] = ' ';
    }
}
