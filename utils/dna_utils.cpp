#include <bits/stdc++.h>
#include "../include/utils.h"
#include <vector>
#include <algorithm>
using namespace std;

void loadDNAFromTxt(
    const string &filename,
    vector<string> &sequences,
    vector<int> &classes)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Could not open the file!" << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header: "sequence\tclass"

    while (getline(file, line))
    {
        stringstream ss(line);
        string sequence, classStr;

        getline(ss, sequence, '\t'); // assuming tab-separated
        getline(ss, classStr, '\t');

        if (!sequence.empty() && !classStr.empty())
        {
            sequences.push_back(sequence);
            classes.push_back(stoi(classStr));
        }
    }

    file.close();
}

void combineAndSort(
    vector<pair<string, int>> &sequences,
    vector<string> &dnaSequences,
    vector<int> &classLabels
) 
{
    for (size_t i = 0; i < dnaSequences.size(); ++i)
    {
        sequences.push_back({dnaSequences[i], classLabels[i]});
    }

    sort(sequences.begin(), sequences.end(), [](const pair<string, int> &a, const pair<string, int> &b)
         { return a.second < b.second; });
    
}

void differentiateBySequence(
    vector<vector<string>> &Sequence_byClass,
    vector<pair<string, int>> &sequences)
{
    for (auto &i : sequences)
    {
        Sequence_byClass[i.second].push_back(i.first);
    }
}