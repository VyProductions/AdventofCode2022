#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <limits>
#include <list>
#include <unordered_map>

struct position {
    unsigned r;
    unsigned c;
    bool operator==(const position& rhs) {
        return r == rhs.r && c == rhs.c;
    }
    bool operator!=(const position& rhs) {
        return !(*this == rhs);
    }
};

const unsigned GRID_HEIGHT = 41;
const unsigned GRID_WIDTH = 173;

inline int manhattan(position a, position b) {
    return std::abs((int)a.r - (int)b.r) + std::abs((int)a.c - (int)b.c);
}

/// @brief Collects neighbors navigating backwards from the end position in the
///   height map.
///
/// @param p : The position to query neighbors from
/// @param heightMap : The height map to determine the neighbors from
///
/// @return a list of the collected neighbors

std::list<position> neighbors(
    position p, char heightMap[][GRID_WIDTH]
);

/// @brief Find the shortest path from a starting node to a given target value.
///
/// @param start : The starting node's coordinates in the height map
/// @param heightMap : The heightmap to construct the path within
/// @param weights : The current weights of each node in the height map
/// @param pred: The predeccesors in the minimum weight path for all nodes
///
/// @returns shortest path between point and 'a' height in map

std::list<position> AStar(
    position start, position finish, char heightMap[][GRID_WIDTH]
);

/// @brief Standard bubble down implementation for a max heap
/// @param nodes : List of nodes to bubble down in
/// @param pos : Index of node in the heap to bubble down from
/// @param size : How large the heap is
/// @param weights : Weights of each node in the list

void bubbleDownMax(
    std::vector<position>& nodes, unsigned pos, unsigned size,
    int weights[][GRID_WIDTH]
);

/// @brief Standard build heap implementation for a max heap
/// @param nodes : List of nodes to build a heap from
/// @param weights : Weights of each node in the list

void buildHeapMax(std::vector<position>& nodes, int weights[][GRID_WIDTH]);

/// @brief Standard ascending heap sort implementation using a max heap
/// @param nodes : List of nodes to sort
/// @param weights : Weights of each node in the list

void heapSort(std::vector<position>& nodes, int weights[][GRID_WIDTH]);

int main() {
    /// Height map data for all nodes
    char heightMap[GRID_HEIGHT][GRID_WIDTH] {};

    // All starting 'a' paths
    std::vector<position> startPoints;
    int mWeight[GRID_HEIGHT][GRID_WIDTH];

    // Position in the height map with the best signal
    position signalPos;

    // Store height map data to array
    for (unsigned r = 0; r < GRID_HEIGHT; ++r) {
        for (unsigned c = 0; c < GRID_WIDTH; ++c) {
            std::cin >> heightMap[r][c];
            if (heightMap[r][c] == 'a' || heightMap[r][c] == 'S') {
                heightMap[r][c] = 'a';
                startPoints.push_back({r, c});
            } else if (heightMap[r][c] == 'E') {
                heightMap[r][c] = 'z';
                signalPos = {r, c};
            }
        }
    }

    for (unsigned r = 0; r < GRID_HEIGHT; ++r) {
        for (unsigned c = 0; c < GRID_WIDTH; ++c) {
            mWeight[r][c] = manhattan({r, c}, signalPos);
        }
    }

    // Sort starting points in ascending order by their distance to the finish
    heapSort(startPoints, mWeight);

    unsigned minDist = (unsigned)-1;

    for (auto pos : startPoints) {
        if (manhattan(signalPos, pos) <= minDist) {
            std::list<position> path = AStar(pos, signalPos, heightMap);

            if (!path.empty()) {
                path.pop_front();

                if (path.back() == signalPos) {
                    minDist = path.size() < minDist ? path.size() : minDist;
                }
            }
        }
    }

    // Results
    printf("Path Length: %u\n", minDist);

    return 0;
}

std::list<position> neighbors(
    position p, char heightMap[][GRID_WIDTH]
) {
    int offR[] {-1, 0, 0, 1};
    int offC[] {0, -1, 1, 0};

    char curr = heightMap[p.r][p.c];

    std::list<position> neigh;

    for (unsigned i = 0; i < 4; ++i) {
        unsigned nRow = p.r + offR[i];
        unsigned nCol = p.c + offC[i];

        if (nRow < GRID_HEIGHT && nCol < GRID_WIDTH) {
            char n = heightMap[nRow][nCol];

            if (curr + 1 >= n) {
                neigh.push_back({nRow, nCol});
            }
        }
    }

    return neigh;
}

std::list<position> AStar(
    position start, position finish, char heightMap[][GRID_WIDTH]
) {
    const position defPred {
        std::numeric_limits<int>::max(), std::numeric_limits<int>::max()
    };

    // h = dist from node to finish
    // g = path length from node back to start
    // f = overall weight of node

    int g[GRID_HEIGHT][GRID_WIDTH];
    int h[GRID_HEIGHT][GRID_WIDTH];
    int f[GRID_HEIGHT][GRID_WIDTH];
    position pred[GRID_HEIGHT][GRID_WIDTH];

    std::vector<position> open;  // Priority Queue for all open nodes
    std::list<position> closed;  // List of closed nodes

    // Initialize start information
    for (unsigned r = 0; r < GRID_HEIGHT; ++r) {
        for (unsigned c = 0; c < GRID_WIDTH; ++c) {
            g[r][c] = std::numeric_limits<int>::max();
            h[r][c] = std::numeric_limits<int>::max();
            f[r][c] = std::numeric_limits<int>::max();
        }
    }

    g[start.r][start.c] = 0;
    h[start.r][start.c] = manhattan(start, finish);
    f[start.r][start.c] = manhattan(start, finish);
    pred[start.r][start.c] = defPred;

    open.push_back(start);

    while (!open.empty()) {
        position u = open.front();

        if (u == finish) {
            std::list<position> path;

            while (u != defPred) {
                path.push_front(u);
                u = pred[u.r][u.c];
            }

            return path;
        }

        open.erase(open.begin());
        closed.push_back(u);

        std::list<position> neighList = neighbors(u, heightMap);

        for (auto n : neighList) {
            if (std::find(closed.begin(), closed.end(), n) == closed.end()) {
                int w = g[u.r][u.c] + manhattan(u, n);

                if (w < g[n.r][n.c] || std::find(open.begin(), open.end(), n) == open.end()) {
                    g[n.r][n.c] = w;
                    h[n.r][n.c] = manhattan(n, finish);
                    f[n.r][n.c] = g[n.r][n.c] + h[n.r][n.c];
                    pred[n.r][n.c] = u;

                    if (std::find(open.begin(), open.end(), n) == open.end()) {
                        open.push_back(n);
                        heapSort(open, f);
                    }
                }
            }
        }
    }

    return {};  // No path was found -- empty list
}

void bubbleDownMax(
    std::vector<position>& nodes, unsigned pos, unsigned size,
    int weights[][GRID_WIDTH]
) {
    position curr = nodes.at(pos);          // Node at given position
    int cWeight = weights[curr.r][curr.c];  // Weight of given node

    unsigned leftChild = pos * 2 + 1;   // Index in list of possible left child
    unsigned rightChild = pos * 2 + 2;  // Index in list of possible right child

    // if right child exists
    if (rightChild < size) {
        position left = nodes.at(leftChild);      // Position of left child
        position right = nodes.at(rightChild);    // Position of right child
        int lWeight = weights[left.r][left.c];    // Weight of left child
        int rWeight = weights[right.r][right.c];  // Weight of right child

        if (
            (lWeight > cWeight && rWeight > cWeight) ||
            lWeight > cWeight || rWeight > cWeight
        ) {
            // Conditional index based on which child is largest
            unsigned swapPos = lWeight > rWeight ? leftChild : rightChild;

            // Swap node at "swapPos" with node at "pos"
            position tmp = nodes.at(swapPos);
            nodes.at(swapPos) = nodes.at(pos);
            nodes.at(pos) = tmp;

            // Recursive call to continue updating towards leaves
            bubbleDownMax(nodes, swapPos, size, weights);
        }
    } else if (leftChild < size) {
        position left = nodes.at(leftChild);    // Position of left child
        int lWeight = weights[left.r][left.c];  // Weight of left child

        if (lWeight > cWeight) {
            // Swap root with root's left child
            position tmp = nodes.at(leftChild);
            nodes.at(leftChild) = nodes.at(pos);
            nodes.at(pos) = tmp;

            // Recursive call to continue updating towards leaves
            bubbleDownMax(nodes, leftChild, size, weights);
        }
    }
}

void buildHeapMax(std::vector<position>& nodes, int weights[][GRID_WIDTH]) {
    // Bubble down from all positions (starting at last, working towards front)
    unsigned pos = nodes.size();
    while (pos > 0) {
        bubbleDownMax(nodes, pos - 1, nodes.size(), weights);
        --pos;
    }
}

void heapSort(std::vector<position>& nodes, int weights[][GRID_WIDTH]) {
    // Build a max heap
    buildHeapMax(nodes, weights);

    // While sorted index size is > 0
    unsigned sortedIdx = nodes.size() - 1;

    while (sortedIdx > 0) {
        // Swap root of heap with node at sortedIdx
        position tmp = nodes.at(0);
        nodes.at(0) = nodes.at(sortedIdx);
        nodes.at(sortedIdx) = tmp;

        // Bubble down from root
        bubbleDownMax(nodes, 0, sortedIdx, weights);

        // Decrease sorted index
        --sortedIdx;
    }
}
