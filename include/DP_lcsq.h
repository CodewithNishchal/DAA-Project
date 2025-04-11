#ifndef DP_LCSQ_H
#define DP_LCSQ_H

#include <string>
using namespace std;

struct MutationSummary
{
    int substitutions = 0;
    int insertions = 0;
    int deletions = 0;
};

pair<int, string> lcsq_dp(const string &a, const string &b);
void Intra_Class_Comparison(vector<vector<string>> Sequence_byClass);
void Inter_Class_Comparison(vector<vector<string>> Sequence_byClass);
void printLimitedMutations(const string &A, const string &B, int maxStepsToPrint = 20);
pair<int, MutationSummary> mutation_summary(const string &A, const string &B);

#endif
