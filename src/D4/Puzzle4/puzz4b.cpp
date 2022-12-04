#include <iostream>

int main() {
    int overlapCount = 0;  // How many overlaps occur

    int lower1;  // lower bound of first range
    int upper1;  // upper bound of first range
    int lower2;  // lower bound of second range
    int upper2;  // upper bound of second range

    while (std::cin >> lower1) {
        std::cin.ignore();
        std::cin >> upper1;
        std::cin.ignore();
        std::cin >> lower2;
        std::cin.ignore();
        std::cin >> upper2;

        // If first range touches second range at all
        overlapCount += !(lower1 > upper2 || upper1 < lower2);
    }

    printf("Total Overlaps: %d\n", overlapCount);

    return 0;
}