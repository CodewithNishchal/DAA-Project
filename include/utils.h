#ifndef UTILS_H
#define UTILS_H

#include<bits/stdc++.h>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

using namespace std;

void loadDNAFromTxt(
    const string &filename,
    vector<string> &sequences,
    vector<int> &classes);

void combineAndSort(
    vector<pair<string, int>> &sequences,
    vector<string> &dnaSequences,
    vector<int> &classLabels
);

void differentiateBySequence(
    vector<vector<string>> &Sequence_byClass,
    vector<pair<string, int>> &sequences);

#endif // UTILS_H