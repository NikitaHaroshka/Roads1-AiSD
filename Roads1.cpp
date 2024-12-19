#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class DSU {
private:
    vector<int> root;
    int amount;

public:
    DSU(int n) {
        root.resize(n, -1);
        amount = n;
    }

    int Leader(int node) {
        if (root[node] < 0) return node;
        return root[node] = Leader(root[node]);  // Сжатие пути
    }

    void Connect(int node1, int node2) {
        int element1 = Leader(node1);
        int element2 = Leader(node2);

        if (element1 != element2) {
            if (root[element1] > root[element2]) swap(element1, element2);
            root[element1] += root[element2];
            root[element2] = element1;
            amount--;
        }
    }

    int Amount() {
        return amount;
    }
};

int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    int towns, roads;
    inputFile >> towns >> roads;

    DSU dsu(towns);

    for (int i = 0; i < roads; i++) {
        int element1, element2;
        inputFile >> element1 >> element2;
        dsu.Connect(element1 - 1, element2 - 1);
        outputFile << dsu.Amount() << endl;
    }
}
