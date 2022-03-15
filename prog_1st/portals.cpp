#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int N, M, parent[1000000], ranks[1000000];


  // perform MakeSet operation
  void makeSet(int const &i){
    parent[i] = i;
    ranks[i] = 0;
  }

  // Find the root of the set in which element `k` belongs
  int find(int k){
    // if `k` is not the root
    if (parent[k] != k)
    {
      // path compression
      parent[k] = find(parent[k]);
    }

    return parent[k];
  }

  // Perform Union of two subsets
  void Union(int a, int b){
    // find the root of the sets in which elements `x` and `y` belongs
    int x = find(a);
    int y = find(b);

    // if `x` and `y` are present in the same set
    if (x == y) {
      return;
    }

    // Always attach a smaller depth tree under the root of the deeper tree.
    if (ranks[x] > ranks[y]) {
      parent[y] = x;
    }
    else if (ranks[x] < ranks[y]) {
      parent[x] = y;
    }
    else {
      parent[x] = y;
      ranks[y]++;
    }
  }

bool compareWidth(const vector<int>& p1, const vector<int>& p2){
  return p1[2] < p2[2];
}


vector<int> morty;

bool has_path(int i){

  int x = find(i);
  int y = find(morty[i-1]);

  return (x == y);
}

int main(){

  scanf("%d %d\n", &N, &M);
  int i, ret;
  vector<int> lost;
  vector<vector<int> > portals;

  for (i = 0; i < N; i++) {
    cin >> ret;
    morty.push_back(ret);
    if (morty[i] != i+1) lost.push_back(i+1);
    makeSet(i+1);
  }
  scanf("\n");

  int u1, u2, w;

  for (i = 0; i < M; i++){
    vector<int> row;
    cin >> u1;
    cin >> u2;
    cin >> w;
    row.push_back(u1);
    row.push_back(u2);
    row.push_back(w);
    portals.push_back(row);
  }

  if (!is_sorted(portals.begin(), portals.end(), compareWidth)) {
    sort(portals.begin(), portals.end(), compareWidth);
  }

  int flag, end = lost.size();

  int low, high, half, down = 0;
  high = M-1;
  low = 0;


  while(high > low){

    if (low == half + 1){ //only need to instanciate when moving up
      for (i = 1; i <= N; i++){
        makeSet(i);
      }

      half = (low+high)/2;

      for (i = M-1; i > half; i--){
        Union(portals[i][0], portals[i][1]);
      }
    }
    else{
      half = (low+high)/2;

      for (i = high; i > half; i--){
        Union(portals[i][0], portals[i][1]);
      }
    }

    flag = 1;
    for (int j = 0; j < end; j++) {
      if (!has_path(lost[j])){
        flag = 0;
        break;
      }
    }

    if (flag) low = half + 1;
    else high = half;

  }

  cout << portals[high][2] << '\n';





  return 0;
}
