/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <iostream>
#include <string>
#include<list>

using namespace std;
#include "Map.h"


class Territory {
public:
    list<int>* Borders;
    int n;
    Territory(int v) {
        Borders = new list<int>[v];
        n = v;
    }

    void addedge(int u, int v, bool bi) {
        Borders[u].push_back(v);
        if (bi) {
            Borders[v].push_back(u);
        }
    }

    void print() {
        for (int i = 0; i < n; i++) {
            cout << i << "-->";
            for (auto it : Borders[i]) {
                cout << it << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};