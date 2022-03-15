#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

int N, K;

vector <pair <int, int>  > LDSnorm, LISnorm;

// Binary search (note boundaries in the caller)
int CeilIndexInc(vector<int>& v, int l, int r, int key)
{
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (v[m] >= key)
            r = m;
        else
            l = m;
    }

    return r;
}

void LIS(vector<int>& v)
{
    vector<int> tail(v.size(), 0);
    int length = 1; // always points empty slot in tail
    
    LISnorm.push_back(make_pair(v[0], 1));

    tail[0] = v[0];
    for (int i = 1; i < v.size(); i++) {

        // new smallest value
        if (v[i] < tail[0]){
            tail[0] = v[i];
            if (length == 1) LISnorm.push_back(make_pair(v[i], 1)); //New best subsequence
            else LISnorm.push_back(LISnorm[i-1]); //Still the same normal LIS
        }
        // v[i] extends largest subsequence
        else if (v[i] > tail[length - 1]){
            tail[length++] = v[i];
            LISnorm.push_back(make_pair(v[i], length));
        }
        //find the right stack for v[i]
        else{
            int index = CeilIndexInc(tail, -1, length - 1, v[i]);
            tail[index] = v[i];
            LISnorm.push_back(make_pair(tail[length-1], length));
        }
    }
}

// Binary search (note boundaries in the caller)
int CeilIndexDec(vector<int>& v, int l, int r, int key)
{
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (v[m] <= key)
            r = m;
        else
            l = m;
    }

    return r;
}

void LDS(vector<int>& v)
{
    vector<int> tail(v.size(), 0);
    int length = 1; // always points empty slot in tail
    
    LDSnorm.push_back(make_pair(v[0], 1));

    tail[0] = v[0];
    for (int i = 1; i < v.size(); i++) {

        // new largest value
        if (v[i] > tail[0]){
            tail[0] = v[i];
            if (length == 1) LDSnorm.push_back(make_pair(v[i], 1)); //New best subsequence
            else LDSnorm.push_back(LDSnorm[i-1]); //Still the same normal LIS
        }
        // v[i] extends largest subsequence
        else if (v[i] < tail[length - 1]){
            tail[length++] = v[i];
            LDSnorm.push_back(make_pair(v[i], length));
        }

        //find the right stack for v[i]
        else{
            int index = CeilIndexDec(tail, -1, length - 1, v[i]);
            tail[index] = v[i];
            LDSnorm.push_back(make_pair(tail[length-1], length));
        }
    }
}


int main(int argc, char const *argv[]) {

    scanf("%d %d\n",&N ,&K);
    vector<int> input(N, 0), inputRev(N, 0);

    for (int i = 0; i < N; i++) {
        cin >> input[i];
        inputRev[N-1-i] = input[i] + K; 
    }

    LIS(input);
    LDS(inputRev);

    int max_length = 0;
    if (LISnorm[N-1].second == input.size()) printf("%d\n", LISnorm[N-1].second);
    else {
        for(int i = 0; i < N; i++){
            if (LISnorm[i].first < LDSnorm[N-i-1].first){
                if ((LISnorm[i].second == i-1) && (LDSnorm[N-i-1].second == N-i)) {
                    max_length = max(max_length, LISnorm[i].second+LDSnorm[N-i-1].second-1);
                }
                else if ((LISnorm[i].second == i+1) && (LDSnorm[N-i-1].second == N-i-2)) {
                    max_length = max(max_length, LISnorm[i].second+LDSnorm[N-i-1].second-1);
                }
                else {
                    max_length = max(max_length, LISnorm[i].second+LDSnorm[N-i-1].second);
                }
            }
    }
    max_length = max(max_length, LISnorm[N-1].second);
    printf("%d\n", max_length);
    }
}
