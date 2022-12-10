#include <iostream>

unsigned countScenic(char** grid, unsigned row, unsigned col);

const unsigned GRID_SIDE = 99;

int main() {
    // Allocate Memory for Grid
    char** grid = new char*[GRID_SIDE];
    for (unsigned r = 0; r < GRID_SIDE; ++r) {
        grid[r] = new char[GRID_SIDE] {};
        for (unsigned c = 0; c < GRID_SIDE; ++c) {
            std::cin >> grid[r][c];
        }
    }

    unsigned maxScore = 0;  // Largest scenic score among any tree.
                            // Edge trees always have a scenic score of 0.

    for (unsigned r = 1; r < GRID_SIDE - 1; ++r) {
        for (unsigned c = 1; c < GRID_SIDE - 1; ++c) {
            unsigned score = countScenic(grid, r, c);
            maxScore = score > maxScore ? score : maxScore;
        }
    }

    printf("Maximum Scenic Score: %d\n", maxScore);

    // Free Memory of Grid
    for (unsigned r = 0; r < GRID_SIDE; ++r) {
        delete [] grid[r];
    }

    delete [] grid;

    return 0;
}

unsigned countScenic(char** grid, unsigned row, unsigned col) {
    unsigned scenicScoreU = 0;
    unsigned scenicScoreD = 0;
    unsigned scenicScoreL = 0;
    unsigned scenicScoreR = 0;
    
    // Check top direction
    bool lookTop = true;
    int r = row - 1;

    while (lookTop) {
        if (r < 0) {
            lookTop = false;
        } else if (grid[r][col] >= grid[row][col]) {
            lookTop = false;
            ++scenicScoreU;
        } else {
            ++scenicScoreU;
        }
        --r;
    }

    // Check top direction
    bool lookBottom = true;
    r = row + 1;

    while (lookBottom) {
        if (r >= (int)GRID_SIDE) {
            lookBottom = false;
        } else if (grid[r][col] >= grid[row][col]) {
            lookBottom = false;
            ++scenicScoreD;
        } else {
            ++scenicScoreD;
        }
        ++r;
    }

    // Check left direction
    bool lookLeft = true;
    int c = col - 1;

    while (lookLeft) {
        if (c < 0) {
            lookLeft = false;
        } else if (grid[row][c] >= grid[row][col]) {
            lookLeft = false;
            ++scenicScoreL;
        } else {
            ++scenicScoreL;
        }
        --c;
    }

    // Check right direction
    bool lookRight = true;
    c = col + 1;

    while (lookRight) {
        if (c >= (int)GRID_SIDE) {
            lookRight = false;
        } else if (grid[row][c] >= grid[row][col]) {
            lookRight = false;
            ++scenicScoreR;
        } else {
            ++scenicScoreR;
        }
        ++c;
    }

    return scenicScoreU * scenicScoreD * scenicScoreL * scenicScoreR;
}
