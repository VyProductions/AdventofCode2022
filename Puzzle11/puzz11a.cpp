#include <algorithm>
#include <iostream>
#include <vector>

// Which monkey number should be thrown to for a "true" or "false" test result
struct MonkeyThrow {
    int t;
    int f;
};

// Simulates an individual monkey's properties
struct Monkey {
    // Items the monkey has in its possession
    std::vector<unsigned long> items;

    // Calls operation function via assigned raw pointer
    void operate(unsigned long& item) { operation(item, this); }

    // Placeholder for desired operation per-monkey
    void (*operation)(unsigned long&, const Monkey*);

    int argument;  // RHS argument of operation

    bool test(unsigned long item) { return item % factor == 0; }
    int factor;  // Divisibility factor value

    MonkeyThrow throwsTo;  // Where the monkey throws
    int numThrows;         // How many times the monkey has thrown
};

// Possible operations (old + #, old * #, old * old)
void add(unsigned long& a, const Monkey* m) { a += m->argument; }
void multi(unsigned long& a, const Monkey* m) { a *= m->argument; }
void square(unsigned long& a, const Monkey* m) { a *= a; }

/// @brief Simulate the "keep away" among the monkeys over 20 rounds
///
/// @param monkeys : The list of monkeys

void simulate(std::vector<Monkey>& monkeys);

int main() {
    // List of the monkeys participating
    std::vector<Monkey> monkeys;

    unsigned long item;     // Current item being read in per-monkey
    char operate;           // Current operation (+, *, ^) per-monkey
    int argument;           // Argument of operation
    int factor;             // Factor of divisibility
    int targetMonkey;       // Where the monkey throws if test is true/false

    // For each monkey's information:
    while (std::cin.ignore(20, '\n')) {
        Monkey m;  // The current monkey

        std::cin.ignore(17);  // Ignore "  Starting items:"

        // Collect item values into monkey's item list
        while (std::cin.get() == ' ' && std::cin.peek() != ' ') {
            std::cin >> item;
            std::cin.ignore(1);  // Ignore ',' or '\n'
            m.items.push_back(item);
        }

        std::cin.ignore(22);  // Ignore " Operation: new = old "

        // Collect operator and argument of operator
        std::cin >> operate;
        if (std::cin.get() && std::cin.peek() != 'o') {
            std::cin >> argument;
            m.argument = argument;
        } else {
            operate = '^';       // Squaring operation
            std::cin.ignore(3);  // Ignore "old"
        }

        // Assign placeholder function its definition via a function pointer
        switch (operate) {
        case '+': m.operation = add; break;
        case '*': m.operation = multi; break;
        case '^': m.operation = square; break;
        default: printf("Invalid operator\n"); break;
        }

        std::cin.ignore(22);  // Ignore "\n  Test: divisible by "

        // Collect divisibility factor
        std::cin >> factor;
        m.factor = factor;

        std::cin.ignore(30);  // Ignore "\n    If true: throw to monkey "

        // Collect "true" monkey target
        std::cin >> targetMonkey;
        m.throwsTo.t = targetMonkey;

        std::cin.ignore(31);  // Ignore "\n    If false: throw to monkey "

        // Collect "false" monkey target
        std::cin >> targetMonkey;
        m.throwsTo.f = targetMonkey;

        std::cin.ignore(2);  // Ignore two newlines at end of info text block

        m.numThrows = 0;  // The monkey hasn't thrown at all

        monkeys.push_back(m);
    }

    // Run simulation
    simulate(monkeys);

    // Sort monkeys by throw number (descending order)
    std::sort(monkeys.begin(), monkeys.end(), [](Monkey a, Monkey b) {
        return a.numThrows > b.numThrows;
    });

    // Results
    printf("Monkey Business: %ld\n",
        (unsigned long)monkeys.at(0).numThrows * monkeys.at(1).numThrows
    );

    return 0;
}

void simulate(std::vector<Monkey>& monkeys) {
    // Simulate 20 rounds
    for (int round = 1; round <= 20; ++round) {
        for (auto& m : monkeys) {
            auto itemIter = m.items.begin();  // Iterator to current item
            while (itemIter != m.items.end()) {
                unsigned long& item = *itemIter;  // Reference to current item
                m.operate(item);

                item /= 3;

                if (m.test(item)) {
                    monkeys.at(m.throwsTo.t).items.push_back(item);
                } else {
                    monkeys.at(m.throwsTo.f).items.push_back(item);
                }

                itemIter = m.items.erase(itemIter);

                m.numThrows++;
            }
        }
    }
}
