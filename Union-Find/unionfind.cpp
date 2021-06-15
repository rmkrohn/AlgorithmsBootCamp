//Disjoint Set Union-Find
//Rachel Krohn, 2016

//Demo program for disjoint set union-find
//Example builds sets by indicating that certain elements
//belong to the same set, then queries pairs of elements

#include <cstdio>
#include <vector>
using namespace std;

//union-find struct for disjoint sets of integers
struct union_find
{
	vector<int> parent;		//parent is representative item from set
	
	//constructor
	union_find(int n)
	{
		parent = vector<int>(n);		//create vector
		
		//initialize sets - each number 0 to n-1 in separate set
		for (int i = 0; i < n; i++)
			parent[i] = i;
	}

	//find
	int find(int x)
	{
		//if parent is same as item, return item
		if (parent[x] == x) return x;
		
		//otherwise, recursively find parent of x until reach base case
		parent[x] = find(parent[x]);
		return parent[x];
	}
	
	//union
	void unite(int x, int y)
	{
		//update top parent of x to be top parent of y
		parent[find(x)] = find(y);
	}
	
	//determines if two items belong to same set
	bool share_set(int x, int y)
	{
		return find(x) == find(y);
	}
};

//short implementation - 5 lines!
#define MAXN 1000
int p[MAXN];
int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
void unite(int x, int y) { p[find(x)] = find(y); }
//for (int i = 0; i < MAXN; i++) p[i] = i;		//do initialization in main

int main()
{
	int n, q;
	char c;
	int a, b;
	
	scanf("%d %d", &n, &q);
	
	//create union-find structure (initialized in constructor)
	union_find sets = union_find(n);
	
	//read and process queries
	for (int i = 0; i < q; i++)
	{
		scanf(" %c %d %d", &c, &a, &b);
		
		//find
		if (c == '?')
		{
			printf("are %d and %d in the same set?  ", a, b);
			printf(sets.share_set(a, b) ? "yes\n" : "no\n");
		}
		
		//union
		else
			printf("performing union of sets containing %d and %d\n", a, b);
			sets.unite(a, b);
	}
}
