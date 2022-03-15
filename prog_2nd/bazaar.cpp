#include <stdio.h>
#include <stdlib.h>
#include <vector>

#define limit 16000000000

using namespace std;

int N, M, A;
long long P;

vector <pair <int, long long> > offers[4][4];
vector <long long> cheapest[4][4];
long long cost_array[1502][5002];

//DP function computing the minimum cost needed to survive X (all in between) days
//by only buying given the piece of equipment and the merchant
//Used to fill cost_array and cheapest
void cost(int merchant, int equipment){
    int maxI = offers[merchant][equipment].size();
    int maxJ = N;
    
    //column 0 initialized to 0
    for (int i = 0; i <= maxI; i++) cost_array[i][0] = 0;
    //line 0 initialized to limit
    for (int j = 1; j <= maxJ; j++) cost_array[0][j] = limit;
    //computing the cheapest sequence of purchases
    for(int i = 1; i <= maxI; i++){
        int A = offers[merchant][equipment][i-1].first;
        long long P = offers[merchant][equipment][i-1].second;
        //i is the number of offers we consider, j is the days of survival
        for(int j = 1; j <= maxJ; j++) 
            cost_array[i][j] = min(cost_array[i-1][max(0, j-A)] + P, cost_array[i-1][j]);
    }
    //the last row contains the cheapest sequence of purchases
    for (int j = 0; j <= maxJ; j++)
        cheapest[merchant][equipment].push_back(cost_array[maxI][j]);
}

int main(){
    scanf("%d %d\n", &N, &M);
    int merchant, equipment;
    char ret;
    for (int i = 0; i < M; i++){
        scanf("%d%c %d %lld\n", &merchant, &ret, &A, &P);
        switch (ret){
        case 'A':
            equipment = 1;
            break;
        case 'B':
            equipment = 2;
            break;
        case 'C':
            equipment = 3;
            break;
        }
        offers[merchant][equipment].push_back(make_pair(A,P));
    }

    //call cost function for all types of equipment
    for (int i = 1; i <= 3; i++){
        for (int j = 1; j <= 3; j++){
            cost(i, j);
        }
    }
    //sum up, so the total cost of the set is contained one row
    for (int i = 1; i <= 3; i++){
        for (int j = 0; j <= N; j++){
        cheapest[i][1][j] += cheapest[i][2][j] + cheapest[i][3][j];
        }
    }
    long long result = limit;
    for (int i = 0; i <= N; i++){
        for (int j = 0; j <= N; j++){
            if (N >= i + j){
                result = min(result, cheapest[1][1][i] + cheapest[2][1][j] + cheapest[3][1][N-i-j]);
            }
            else{
                result = min(result, cheapest[1][1][i] + cheapest[2][1][j]);
            }
        }
    }
    if (result == limit) printf("%d\n", -1);

    else printf("%lld\n", result);
}

