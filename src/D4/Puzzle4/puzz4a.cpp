#include <iostream>

int main() {
    int encapsulateCount = 0;  // How many encapsulations occur

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

        // If first range encapsulates second,
        // or second range encapsulates first
        if (
            (lower1 <= lower2 && upper1 >= upper2) ||
            (lower2 <= lower1 && upper2 >= upper1)
        ) {
            ++encapsulateCount;
        }
    }

    printf("Total Encapsulations: %d\n", encapsulateCount);

    return 0;
}