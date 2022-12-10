#include <iostream>
#include <list>
#include <string>

// Contains information about current clock cycle and register value
struct runtime_info {
    long cycle;
    long regVal;
};

int main() {
    std::string op;  // String for operation name
    long num;        // Parameter of addx operation

    std::list<runtime_info> ri;  // Info polls at important clock cycles
    long clockCycle = 0;  // Current clock cycle (0 when program hasn't started)
    long x = 1;           // Current X register value (initally set to 1)

    while (std::cin >> op) {
        if (op == "addx") {
            std::cin >> num;

            ++clockCycle;

            // Log important polling periods (clock: 20, 60, 100, etc)
            if ((clockCycle - 20) % 40 == 0) {
                // Push information (current clock, current x register value)
                ri.push_back({clockCycle, x});
            }

            ++clockCycle;

            // Log important polling periods (clock: 20, 60, 100, etc)
            if ((clockCycle - 20) % 40 == 0) {
                // Push information (current clock, current x register value)
                ri.push_back({clockCycle, x});
            }

            // Modify x register after two clock cycles
            x += num;
        } else {
            ++clockCycle;

            // Log important polling periods (clock: 20, 60, 100, etc)
            if ((clockCycle - 20) % 40 == 0) {
                // Push information (current clock, current x register value)
                ri.push_back({clockCycle, x});
            }

            // Do nothing after one clock cycle
        }
    }

    auto infoIt = ri.begin();  // Iterator to first info poll
    long signalSum = 0;        // Signal strength sum

    while (infoIt != ri.end() && infoIt->cycle <= 220) {
        signalSum += infoIt->cycle * infoIt->regVal;
        ++infoIt;
    }

    // Results
    printf("Signal Sum: %ld\n", signalSum);

    return 0;
}
