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

void GetClassSequence(vector<vector<string>> &arr,
                      vector<string> &class0,
                      vector<string> &class1,
                      vector<string> &class2,
                      vector<string> &class3,
                      vector<string> &class4,
                      vector<string> &class5,
                      vector<string> &class6)
{
    for (auto &i : arr[0])
    {
        class0.push_back(i);
    }
    for (auto &i : arr[1])
    {
        class1.push_back(i);
    }
    for (auto &i : arr[2])
    {
        class2.push_back(i);
    }
    for (auto &i : arr[3])
    {
        class3.push_back(i);
    }
    for (auto &i : arr[4])
    {
        class4.push_back(i);
    }
    for (auto &i : arr[5])
    {
        class5.push_back(i);
    }
    for (auto &i : arr[5])
    {
        class6.push_back(i);
    }
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

    for (auto &i : sequences)
    {
        Sequence_byClass[i.second].push_back(i.first);
    }

    // Performing Dynamic Programming LCS method

    vector<string> human_class0, human_class1, human_class2, human_class3, human_class4, human_class5, human_class6;

    GetClassSequence(Sequence_byClass, human_class0, human_class1, human_class2, human_class3, human_class4, human_class5, human_class6);

    cout << human_class1.size();

    return 0;
}
