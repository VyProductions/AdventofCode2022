#include <iostream>
#include <stack>

int main() {
    std::stack<char>* boxStacks;

    int numStacks;

    std::cin >> numStacks;

    boxStacks = new std::stack<char>[numStacks] {};

    for (int stack = 0; stack < numStacks; ++stack) {
        int numBoxes;
        std::cin >> numBoxes;
        for (int box = 0; box < numBoxes; ++box) {
            char boxValue;
            std::cin >> boxValue;
            boxStacks[stack].push(boxValue);
        }
    }

    int boxCount;
    int sourceStack;
    int destStack;

    std::cin.ignore(6);
    while (std::cin >> boxCount) {
        std::cin.ignore(6);
        std::cin >> sourceStack;
        std::cin.ignore(4);
        std::cin >> destStack;
        std::cin.ignore(6);

        for (int k = 0; k < boxCount; ++k) {
            char topBox = boxStacks[sourceStack-1].top();
            boxStacks[sourceStack-1].pop();
            boxStacks[destStack-1].push(topBox);
        }
    }

    std::cout << "Top of Each Stack:\n";
    for (int i = 0; i < numStacks; ++i) {
        std::cout << boxStacks[i].top();
    }
    std::cout << '\n';

    delete [] boxStacks;

    return 0;
}
