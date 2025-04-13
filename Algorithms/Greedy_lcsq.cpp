

#include "../include/Greedy_lcsq.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Helper to calculate max overlap between two strings
int calc_overlap(const string &a, const string &b, string &merged) {
    int maxOverlap = 0;
    merged = a + b;

    for (int i = 1; i <= min(a.size(), b.size()); ++i) {
        if (a.substr(a.size() - i) == b.substr(0, i)) {
            if (i > maxOverlap) {
                maxOverlap = i;
                merged = a + b.substr(i);
            }
        }
    }
    return maxOverlap;
}

// Greedy superstring builder
string greedy_dna_assembly(vector<string> &fragments) {
    while (fragments.size() > 1) {
        int maxOverlap = -1;
        int l = 0, r = 0;
        string bestMerge = "";

        for (int i = 0; i < fragments.size(); ++i) {
            for (int j = 0; j < fragments.size(); ++j) {
                if (i != j) {
                    string merged;
                    int overlap = calc_overlap(fragments[i], fragments[j], merged);
                    if (overlap > maxOverlap) {
                        maxOverlap = overlap;
                        bestMerge = merged;
                        l = i;
                        r = j;
                    }
                }
            }
        }

        if (maxOverlap == -1) break;

        fragments[l] = bestMerge;
        fragments.erase(fragments.begin() + r);
    }

    return fragments.empty() ? "" : fragments[0];
}