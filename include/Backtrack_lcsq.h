#ifndef Backtrack_LCSQ_H
#define Backtrack_LCSQ_H
#include<bits/stdc++.h>
#include <string>
using namespace std;

void backtrackAllLCS(const vector<vector<int>> &dp, const string &X, const string &Y, int i, int j, string lcs, set<string> &all_lcs);
set<string> getAllLCS(const string &X, const string &Y);


#endif
