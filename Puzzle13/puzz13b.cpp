#include <algorithm>
#include <iostream>
#include <vector>

// Classification for what an item is
enum ITEM_TYPE {LIST, LITERAL};

// Represents either a literal value or a list of items
struct item {
    ITEM_TYPE which;
    int val;
    std::vector<item> vals;
    bool operator==(const item rhs) const {
        bool equal = val == rhs.val;
        return equal && vals == rhs.vals;
    }
};

// Constant codes for the correct() function
#define LESS 0
#define EQUAL 1
#define MORE 2

/// @brief Parses a literal value from stdin into an item
/// @param it : The item to store the literal to

void readNum(item& it);

/// @brief Parses a list from stdin into an item
/// @param it : The item to store the list to

void readList(std::vector<item>& it);

/// @brief Convert a literal item to a list item with one element
/// @param it : The item to convert

void convertLiteral(item& it);

/// @brief Test whether a and b are in the right order relative to each other
/// @param a : The first item of the comparison
/// @param b : The second item of the comparison
/// @return LESS, EQUAL, or MORE as a result of the comparison

int correct(item a, item b);

int main() {
    // List of all packets received
    std::vector<item> packetList;

    while (std::cin.peek() == '[') {
        item packet1 {LIST, 0, {}};  // 1st packet of pair
        item packet2 {LIST, 0, {}};  // 2nd packet of pair

        // -----
        //  Read first packet of pair
        readList(packet1.vals);
        std::cin.ignore();  // Ignore trailing newline

        // -----
        //  Read second packet of pair
        readList(packet2.vals);
        std::cin.ignore(2);  // Ignore trailing newline and buffer newline

        // Add packets to list
        packetList.push_back(packet1);
        packetList.push_back(packet2);
    }

    // "[[2]]" packet
    const item divider2 = {
        LIST, 0, {
            {LIST, 0, {
                {LITERAL, 2, {}}
            }}
        }
    };

    // "[[6]]" packet
    const item divider6 = {
        LIST, 0, {
            {LIST, 0, {
                {LITERAL, 6, {}}
            }}
        }
    };

    // Add divider packets to list
    packetList.push_back(divider2);
    packetList.push_back(divider6);

    // Sort packets into the right order
    std::sort(packetList.begin(), packetList.end(), [](item& a, item& b) {
        return correct(a, b) == LESS;
    });

    // Locate the indices of "[[2]]" and "[[6]]" in the packet list
    std::vector<item>::iterator iter = packetList.begin();
    bool found2 = false;
    bool found6 = false;
    unsigned idx = 1;
    unsigned idx2 = 0;
    unsigned idx6 = 0;

    while ((!found2 || !found6) && iter != packetList.end()) {
        if (*iter == divider2) {
            found2 = true;
            idx2 = idx;
        } else if (*iter == divider6) {
            found6 = true;
            idx6 = idx;
        }

        ++idx;
        ++iter;
    }

    // Results
    printf("Decoder Key: %u\n", idx2 * idx6);

    return 0;
}

void readNum(item& it) {
    std::cin >> it.val;
}

void readList(std::vector<item>& it) {
    std::cin.ignore();  // Ignore leading '['
    while (std::cin.peek() != ']') {
        if (std::cin.peek() == '[') {  // list
            item tmp {LIST, 0, {}};
            readList(tmp.vals);
            it.push_back(tmp);
        } else {
            item tmp {LITERAL, 0, {}};
            readNum(tmp);
            it.push_back(tmp);
        }

        if (std::cin.peek() == ',') {
            std::cin.ignore();
        }
    }
    std::cin.ignore();  // Ignore trailing ']';
}

void convertLiteral(item& it) {
    if (it.which == LITERAL) {
        it.which = LIST;
        it.vals.push_back({LITERAL, it.val, {}});
    }
}

int correct(item a, item b) {
    int state = EQUAL;

    if (a.which == LITERAL && b.which == LITERAL) {   // Both literals
        state = a.val == b.val ? EQUAL : a.val < b.val ? LESS : MORE;
    } else if (a.which == LIST && b.which == LIST) {  // Both lists
        auto iterA = a.vals.begin();
        auto iterB = b.vals.begin();
        
        while (
            state == EQUAL &&
            iterA != a.vals.end() && iterB != b.vals.end()
        ) {
            state = correct(*iterA, *iterB);

            ++iterA;
            ++iterB;
        }

        // A ran out of items first
        if (state == EQUAL && iterA == a.vals.end() && iterB != b.vals.end()) {
            state = LESS;
        // B ran out of items first
        } else if (state == EQUAL && iterA != a.vals.end() && iterB == b.vals.end()) {
            state = MORE;
        }
    } else {  // One is a list and the other is a literal
        item& k = a.which == LITERAL ? a : b;
        convertLiteral(k);     // Convert
        return correct(a, b);  // Try again
    }

    return state;
}
