#include <bits/stdc++.h>
#include "include/DP_lcsq.h"
#include "include/Divide_lcsq.h"
#include "include/Backtrack_lcsq.h"
#include "include/Trie_lcsq.h"
#include "include/Greedy_lcsq.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

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

int main()
{
    vector<string> dnaSequences;
    vector<int> classLabels;

    // Step 0: Getting all the sequences from human DNA dataset
    loadDNAFromTxt("DNA_dataset/human.txt", dnaSequences, classLabels);

    // Step 1: Combine into vector of pairs
    vector<pair<string, int>> sequences;
    for (size_t i = 0; i < dnaSequences.size(); ++i)
    {
        sequences.push_back({dnaSequences[i], classLabels[i]});
    }

    // Step 2: Sort by class label (second of pair)
    sort(sequences.begin(), sequences.end(), [](const pair<string, int> &a, const pair<string, int> &b)
         { return a.second < b.second; });

    // Differentiate class by Sequence
    vector<vector<string>> Sequence_byClass(7);

    for( auto &i : sequences) {
        Sequence_byClass[i.second].push_back(i.first);
    }

    //Print all the class and their Respective DNA 
    // for (int i = 0; i < Sequence_byClass.size(); ++i)
    // {
    //     cout << "Class " << i << " has " << Sequence_byClass[i].size() << " sequences:\n";
    //     for (const auto &s : Sequence_byClass[i])
    //     {
    //         cout << "  " << s << endl;
    //     }
    //     cout << "-------------------\n";
    // }


    //Performing Dynamic Programming LCS method
    string dna1 = Sequence_byClass[1][10];
    string dna2 = Sequence_byClass[1][12];

    pair<int, string> result = lcsq_dp(dna1, dna2);
    int length = result.first;
    string lcsStr = result.second;

    cout << "LCS length: " << length << "\n";
    cout << "LCS string: " << lcsStr << "\n";

    return 0;
}
