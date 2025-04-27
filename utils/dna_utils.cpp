#include <bits/stdc++.h>
#include "../include/utils.h"
#include "../include/DP_lcsq.h"
#include "../include/Divide_lcsq.h"
#include "../include/Backtrack_lcsq.h"
#include "../include/Trie_lcsq.h"
#include "../include/Greedy_lcsq.h"
#include <vector>
#include <algorithm>
using namespace std;

pair<int, int> values;
pair<int, MutationSummary> result;
vector<string> class_Description = {
    "G protein coupled receptors",
    "Tyrosine kinase",
    "Tyrosine phosphatase",
    "Synthetase", "Synthase",
    "Ion channel",
    "Transcription factor"};

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
    vector<int> &classLabels)
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

void startTheAnalysis(vector<vector<string>> &Sequence_byClass)
{
    cout << "\nWelcome to the Human DNA Analysis Tool\n";
    cout << "Analyzing 7 biological DNA classes using advanced algorithms.\n";
    cout << "\n";
    for (int i = 0; i < 7; i++)
    {
        cout << i << ". " << class_Description[i] << endl;
    }

    int choice;
    do
    {
        cout << "\n-----------------------------------------" << endl;
        cout << "\n--- DNA Sequence Analysis Tool ---\n";
        cout << "1. Intra-Class Similarity Comparison\n";
        cout << "2. Inter-Class Similarity Comparison\n";
        cout << "3. View Mutation Summary Between Two Sequences\n";
        cout << "4. Discover Common Patterns (Motifs)\n";
        cout << "5. Simulate DNA Assembly\n";
        cout << "6. Analyze Common Prefix/Suffix\n";
        cout << "7. Advanced: Fast Comparison for Long Sequences\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "\n[INFO] Intra-Class LCS Comparison: Comparing sequences *within* the same class using Dynamic Programming.\n";
            Intra_Class_Comparison(Sequence_byClass);
            break;
        }
        case 2:
        {
            cout << "\n[INFO] Inter-Class LCS Comparison: Comparing sequences *between* different classes using DP.\n";
            Inter_Class_Comparison(Sequence_byClass);
            break;
        }
        case 3:
        {
            cout << "\n[INFO] Mutation Analysis: Showing number and type of mutations between two sequences.\n";
            values = chooseBaseClasses(Sequence_byClass);
            printLimitedMutations(Sequence_byClass[values.first][20], Sequence_byClass[values.second][20]);
            cout << "\n";
            result = mutation_summary(Sequence_byClass[values.first][20], Sequence_byClass[values.second][20]); // wrapper that calls both printLimitedMutations + mutation_summary
            cout << "Edit Distance: " << result.first << endl;
            cout << "Insertions: " << result.second.insertions << endl;
            cout << "Deletions: " << result.second.deletions << endl;
            cout << "Substitutions: " << result.second.substitutions << endl;
            break;
        }
        case 4:
        {
            cout << "\n[INFO] Exhaustive LCS Search: Finding *all* possible longest common subsequences (backtracking based).\n";
            values = chooseBaseClasses(Sequence_byClass);

            const string &A = Sequence_byClass[values.first][20];
            const string &B = Sequence_byClass[values.second][20];

            set<string> motifs = getAllLCS(A, B);
            cout << "Number of motifs (LCS variants): " << motifs.size() << "\n";
            cout << "Sample motifs:\n";

            int shown = 0;
            for (const string &motif : motifs)
            {
                cout << "- " << motif << "\n";
                if (++shown == 10)
                    break;
            }
            cout << "[Only first 10 shown]\n";
            break;
        }

        case 5:
        {
            cout << "\n[INFO] DNA Assembly Simulation: Approximating full DNA from fragments using a greedy strategy.\n";
            int c;
            cout << "Enter class number to simulate assembly (0-6): ";
            cin >> c;

            if (c < 0 || c > 6 || Sequence_byClass[c].size() < 20)
            {
                cout << "Invalid class number or not enough sequences in class.\n";
                break;
            }

            // Use only the first 20 sequences
            vector<string> fragments(Sequence_byClass[c].begin(), Sequence_byClass[c].begin() + 20);
            random_shuffle(fragments.begin(), fragments.end()); // simulate unordered fragments

            string assembled = greedy_dna_assembly(fragments);
            cout << "Assembled DNA sequence:\n"
                 << assembled << "\n";
            cout << "Length: " << assembled.length() << "\n";
            break;
        }
        case 6:
        {
            cout << "\n[INFO] Pattern Detection: Using Trie for common prefix/suffix and repeat finding in sequences.\n";
            int c1, c2;
            cout << "Enter first class number (0-6): ";
            cin >> c1;
            cout << "Enter second class number (0-6): ";
            cin >> c2;

            if (c1 < 0 || c1 > 6 || c2 < 0 || c2 > 6 || Sequence_byClass[c1].empty() || Sequence_byClass[c2].empty())
            {
                cout << "Invalid class numbers or sequences not found.\n";
                break;
            }

            vector<string> combined = Sequence_byClass[c1];
            combined.insert(combined.end(), Sequence_byClass[c2].begin(), Sequence_byClass[c2].end());

            analyzeCommonPrefixSuffix(combined);
            break;
        }

        case 7:
        {
            cout << "\n[INFO] Efficient LCS (Divide and Conquer): Calculating LCS using less memory and better performance on long sequences.\n";
            values = chooseBaseClasses(Sequence_byClass);
            pair<int, string> result = lcsq_divide_conquer(Sequence_byClass[values.first][20], Sequence_byClass[values.second][20]);
            cout << "LCS Length: " << result.first << "\n";
            cout << "LCS String: " << result.second << "\n";
            break;
        }
        case 0:
            cout << "Exiting.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);
}