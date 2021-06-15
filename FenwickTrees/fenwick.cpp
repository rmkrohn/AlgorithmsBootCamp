//Fenwick Tree
//Rachel Krohn, 2016

//This program relies on scanf() and printf() for all input and output, 
//because this method is faster than cin and cout. Ties between the
//C++ and C output streams slow things down, and cout flushes the buffer 
//on endl;, creating further slowdown

#include <vector>
#include <cstdio>
using namespace std;

// FENWICK TREE

vector<long long> tree;		//Fenwick tree

//increase item at position i by delta d
void update(int i, long long d)
{
	while (i < tree.size())
	{ 
		tree[i] += d;
		i |= i+1;
	}
}

//find sum from index 0 to index i
long long sum(int i)
{
	long long sum = 0;
	while (i > 0)
	{
		sum += tree[i-1];
		i &= i - 1;
	}
	return sum;
}

//get sum from index left to index right
long long rangesum(int left, int right)
{
	return sum(right) - sum(left);
}

// END FENWICK TREE

int main()
{
	int n, q;

	scanf("%d %d", &n, &q);		//read number of items and number of operations	
	
	//create Fenwick tree (no need to initialize, all 0)
	tree.resize(n, 0);

	//read and process operations
	char op;
	int index;
	long long delta;
	for (int i = 0; i < q; i++)
	{
		scanf(" %c", &op);
		
		//increment
		if (op == '+')
		{
			scanf("%d %lld", &index, &delta);
			update(index, delta);
		}
		//sum query
		else
		{
			scanf("%d", &index);
			printf("%lld\n", sum(index));
		}
	}
	return 0;
}

