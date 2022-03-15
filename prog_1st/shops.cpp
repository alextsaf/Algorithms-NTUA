#include <iostream>
#include <cstdio>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int N, K;
vector<int> residents;
vector< vector<int> > sums;

int find(int k, int bound);

int main(int argc, char const *argv[]) {

  scanf("%d %d\n",&N ,&K);

  int ret, i, j;
  vector<int> row;

  scanf("%d \n", &ret);
  residents.push_back(ret);
  row.push_back(ret);

  for (i = 1; i < N; i++) {
    scanf("%d \n", &ret);
    residents.push_back(ret);
    row.push_back(ret + row[i-1]);
  }

  sums.push_back(row);

  for (i = 1; i < N; i++) {
    vector<int> row;
    row.push_back(residents[i]);
    for(j = i+1; j < N; j++){
      row.push_back(residents[j]+row[j-i-1]);
    }
    sums.push_back(row);
  }

  int minimum = INT_MAX, second;

  for (i = 0; i < N; i++) {
    for (j = 0; j < N - i; j++){
       if (sums[i][j] > K) break;
       if (sums[i][j] == K){
         //cout << "OK" << '\n';
         minimum = ((j + 1) < minimum) ? (j + 1) : minimum;
         continue;
       }
       second = find((K - sums[i][j]), j + i);
       if (second != INT_MAX) minimum = ((j + second + 1) < minimum) ? (j + second + 1) : minimum;
    }
  }
  minimum = (minimum == INT_MAX) ? -1 : minimum;
  cout << minimum << '\n';

  return 0;
}



//used to find sub array with sum k
//that's not overlapping [lower, uppper]
//returns length of array if found, N+1 if not
// int find(int k, int bound){
//   int minimum = INT_MAX, low, high, mid;
//   for (int i = bound + 1; i < N; i++){
//     low = 0;
//     high = N - i - 1;
//
//     while (low < high){
//       mid = (low + high) / 2;
//       if (sums[i][mid] < k) low = mid + 1;
//       else high = mid;
//     }
//
//     if (sums[i][low] == k) minimum = ((high + 1) < minimum) ? (high + 1) : minimum;
//
//     //cout << bound << ' ' << k << ' ' << i << ' ' << low << ' ' << minimum << '\n';
//   }
//   return minimum;
// }

int find(int k, int bound){
  int minimum = INT_MAX, current = 0, left = bound + 1;

  for (int right = bound + 1; right < N; right++){
    current += residents[right];

    while(current > k){
      current -= residents[left];
      left++;
    }

    if (current == k) minimum = min(minimum, right - left + 1);
  }
  //cout << bound << ' ' << k << ' ' << minimum << '\n';
  return minimum;

}
