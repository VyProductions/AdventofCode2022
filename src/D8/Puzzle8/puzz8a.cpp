#include <iostream>

bool isVisible(char** grid, unsigned row, unsigned col);

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

    unsigned visibleCount = 4 * GRID_SIDE - 4;  // Perimiter is always visible

    for (unsigned r = 1; r < GRID_SIDE - 1; ++r) {
        for (unsigned c = 1; c < GRID_SIDE - 1; ++c) {
            visibleCount += isVisible(grid, r, c);
        }
    }

    printf("Number of Visible Trees: %d\n", visibleCount);

    // Free Memory of Grid
    for (unsigned r = 0; r < GRID_SIDE; ++r) {
        delete [] grid[r];
    }

    delete [] grid;

    return 0;
}

bool isVisible(char** grid, unsigned row, unsigned col) {
    // check in row direction
    bool visibleTop = true;
    int r = row - 1;
    while (visibleTop && r >= 0) {
        visibleTop = grid[r][col] < grid[row][col];
        --r;
    }

    bool visibleBottom = true;
    r = row + 1;
    while (visibleBottom && r < (int)GRID_SIDE) {
        visibleBottom = grid[r][col] < grid[row][col];
        ++r;
    }

    // check in col direction
    bool visibleLeft = true;
    int c = col - 1;
    while (visibleLeft && c >= 0) {
        visibleLeft = grid[row][c] < grid[row][col];
        --c;
    }

    bool visibleRight = true;
    c = col + 1;
    while (visibleRight && c < (int)GRID_SIDE) {
        visibleRight = grid[row][c] < grid[row][col];
        ++c;
    }


    return visibleTop || visibleBottom || visibleLeft || visibleRight;
}
