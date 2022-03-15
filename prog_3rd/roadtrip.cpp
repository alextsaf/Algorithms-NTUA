#include <cstdio>
#include <vector>
#include <tuple>
#include <stdlib.h>
#include <limits.h>
#include <algorithm>

#define Nmax 3001
#define Mmax 100001
#define pb push_back
#define mp std::make_pair
using namespace std;

long int N, M, Q;
long int adjarray[Nmax][Nmax];
int parent[Nmax], ranks[Nmax];

struct Edge
{
   long int src, dest, distance;
};

vector<Edge> roads, edges;

class Graph
{
public:
   vector<vector<pair<long int, long int>>> adjList;

   Graph(vector<Edge> const &edges, int N)
   {
      adjList.resize(2 * N);
      for (auto &edge : edges)
      {
         pair<long int, long int> child(edge.dest, edge.distance);
         adjList[edge.src].pb(child);
         child = mp(edge.src, edge.distance);
         adjList[edge.dest].pb(child);
         adjarray[edge.src][edge.dest] = edge.distance;
         adjarray[edge.dest][edge.src] = edge.distance;
      }
   }
};

//Figure out if there is a path between two vertivces using DFS, and store it 
bool isReachable(Graph const &graph, long int src, long int dest, vector<bool> &discovered, vector<long int> &path)
{
   // mark the current node as discovered
   discovered[src] = true;
   // printf("%ld    ", src);

   path.pb(src);
   // printf("Pushed %ld\n", src);

   // if destination vertex is found
   if (src == dest)
   {
      return true;
   }

   // do for every edge (src, i)
   for (auto i : graph.adjList[src])
   {

      // printf("Checking %ld\n", i.first);
      // if `u` is not yet discovered
      if (!discovered[i.first])
      {
         // return true if the destination is found
         if (isReachable(graph, i.first, dest, discovered, path))
         {
            path.pb(i.second);
            return true;
         }
      }
   }

   // backtrack: remove the current node from the path
   path.pop_back();

   // return false if destination vertex is not reachable from src
   return false;
}

// perform MakeSet operation
void makeSet(int const &i)
{
   parent[i] = i;
   ranks[i] = 0;
}

// Find the root of the set in which element `k` belongs
int Find(int k)
{
   // if `k` is not the root
   if (parent[k] != k)
   {
      // path compression
      parent[k] = Find(parent[k]);
   }

   return parent[k];
}

// Perform Union of two subsets
void Union(int a, int b)
{
   // Find the root of the sets in which elements `x` and `y` belongs
   int x = Find(a);
   int y = Find(b);

   // if `x` and `y` are present in the same set
   if (x == y)
   {
      return;
   }

   // Always attach a smaller depth tree under the root of the deeper tree.
   if (ranks[x] > ranks[y])
   {
      parent[y] = x;
   }
   else if (ranks[x] < ranks[y])
   {
      parent[x] = y;
   }
   else
   {
      parent[x] = y;
      ranks[y]++;
   }
}

bool compareDistance(const Edge &p1, const Edge &p2)
{
   return p1.distance < p2.distance;
}

//Kruskal Algorithm Implementation
void Kruskal()
{
   long int i = 0, e = 0;
   for (long int v = 0; v < Nmax; v++)
   {
      parent[v] = v;
      ranks[v] = 0;
   }
   while ((e < N - 1) && (i < M - 1))
   {
      long int x = roads[i].src;
      long int y = roads[i].dest;
      if (Find(x) != Find(y))
      { 
         edges.pb(roads[i]);
         Union(x, y);
         e++;
      }
      i++;
   }
}

int main()
{
   scanf("%ld %ld", &N, &M);
   struct Edge temp;
   long x, y, d;
   for (int i = 1; i <= M; i++)
   {
      scanf("%li %li %li", &x, &y, &d);
      temp.src = x;
      temp.dest = y;
      temp.distance = d;
      roads.pb(temp);
   }
   sort(roads.begin(), roads.end(), compareDistance);

   Kruskal();

   Graph graph(edges, N);

   scanf("%ld", &Q);
   for (int i = 0; i < Q; i++)
   {
      scanf("%ld %ld", &x, &y);
      vector<bool> discovered(N);
      vector<long int> path;
      long int size, max = 0;
      if (isReachable(graph, x, y, discovered, path))
      {
         size = path.size() / 2;
         for (int i = 0; i < size; i++)
         {
            max = (adjarray[path[i]][path[i + 1]] > max) ? adjarray[path[i]][path[i + 1]] : max;
         }
         printf("%ld\n", max);
      }
      else
         printf("-1\n", i);
   }
   return 0;
}
