#include <stdio.h>
#include <vector>
#include <set>
#include <bits/stdc++.h>

using namespace std;

#define max_dist 10001
#define max_sums 1000000001
#define mp std::make_pair


int N, dk = max_dist;
unsigned long Q;
std::vector<unsigned long> distances, sums(max_dist, INT_MAX);
map<unsigned long, int> discovered;

void Dijkstra()
{
	while (!discovered.empty())
	{
		pair<unsigned long, int> head = *discovered.begin();
		unsigned long current = head.second;
		int sum = head.first;
		discovered.erase(sum);

		for (auto distance : distances)
		{
			int node = (current + distance) % dk;
			int dist = sum + distance;

			if (dist < sums[node])
			{
				discovered.erase(sums[node]);
				sums[node] = dist;
				discovered[sums[node]] = node;
			}
		}
	}
}

int main()
{
	scanf("%d %lu", &N, &Q);
	unsigned long distance;
	for (int i = 1; i <= N; i++)
	{
		scanf("%lu", &distance);
		distances.push_back(distance);
		dk = (distance < dk) ? distance : dk;
	}

	sums[0] = 0;
	discovered[sums[0]] = 0;
	Dijkstra();

		unsigned long query;
	for (int i = 0; i < Q; i++)
	{
		scanf("%lu", &query);
		(sums[query % dk] > query) ? printf("NO\n") : printf("YES\n");
	}
}
