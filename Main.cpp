#include <bits/stdc++.h>
#include "include/DP_lcsq.h"
#include "include/Divide_lcsq.h"
#include "include/Backtrack_lcsq.h"
#include "include/Trie_lcsq.h"
#include "include/Greedy_lcsq.h"
#include "include/utils.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<string> dnaSequences,chimpanzee;
    vector<int> classLabels, chim_labels;

    // Step 0: Getting all the sequences from human DNA dataset
    loadDNAFromTxt("DNA_dataset/human.txt", dnaSequences, classLabels);
    loadDNAFromTxt("DNA_dataset/chimpanzee.txt", chimpanzee, chim_labels);

    // Step 1: Combine and sort into vector of pairs
    vector<pair<string, int>> sequences;
    combineAndSort(sequences, dnaSequences, classLabels);

    // Differentiate class by Sequence
    vector<vector<string>> Sequence_byClass(7);
    differentiateBySequence( Sequence_byClass, sequences);

    // Performing Dynamic Programming LCS method
    startTheAnalysis(Sequence_byClass);

    return 0;
}
