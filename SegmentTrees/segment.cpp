//Segment Trees
//Rachel Krohn, 2016

//Demo program for segment trees
//Implements prefix sums

#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
 
int *tree;
int arr[6] = {1, 3, 5, 7, 9, 11};
int n = 6;
 
//Builds segment tree in array tree from array arr
//node = curr node index in tree
//start = beginning of range covered by node
//end = end of range covered by node
void build(int node, int start, int end)
{
	//leaf node, copy value from array
	if (start == end)
		tree[node] = arr[start];
	//recurse on children
	else
	{
		int mid = (start + end) / 2;
		build(2*node, start, mid);		//left child
		build(2*node+1, mid+1, end);	//right child
		
		//set value of current node as sum of children
		tree[node] = tree[2*node] + tree[2*node+1];		
	}
}
 
//Updates item at index idx by adding diff and updates segment tree to match
//node = curr node index in tree
//start = beginning of range covered by node
//end = end of range covered by node
//idx = index of item to update
//diff = amount to update item by
void update(int node, int start, int end, int idx, int diff)
{
	//leaf node: update node
	if (start == end)
		tree[node] += diff;

	//recurse children
	else
	{
		int mid = (start + end) / 2;	//split point
		
		//left child
		if(start <= idx && idx <= mid)
			update(2*node, start, mid, idx, diff);
		//right child
		else
			update(2*node+1, mid+1, end, idx, diff);
			
		//update current node to be sum of children
		tree[node] = tree[2*node] + tree[2*node+1];
	}
}

//Returns sum of array item from index l to index r using segment tree
//node = curr node index in tree
//start = beginning of range covered by node
//end = end of range covered by node
//l = beginning of query range
//r = end of query range (inclusive)
int query(int node, int start, int end, int l, int r)
{
	//node range completely outside query range, return 0
    if (r < start || end < l)
        return 0;
        
	//node range completely within query range, return node value
    if(l <= start && end <= r)
        return tree[node];
        
    //node range overlaps query range, recurse children
    int mid = (start + end) / 2;
    return query(2*node, start, mid, l, r) + query(2*node+1, mid+1, end, l, r);
}

//Updates items at in range l to r by adding diff
//node = curr node index in tree
//start = beginning of range covered by node
//end = end of range covered by node
//l = beginning of update range
//r = end of query update (inclusive)
//diff = amount to update item by
void updateRange(int node, int start, int end, int l, int r, int diff)
{
    //node range completely outside query range, return
    if (start > end || start > r || end < l)
        return;

    //leaf node: update node
    if (start == end)
    {
        tree[node] += diff;
        return;
    }

    //recurse children
    int mid = (start + end) / 2;
    updateRange(2*node, start, mid, l, r, diff);
    updateRange(2*node+1, mid+1, end, l, r, diff);

    //update current node to be sum of children
    tree[node] = tree[node*2] + tree[node*2+1];
}

//Utility function to print tree as list of values
void printTree(int size)
{
    for (int i = 1; i < size; i++)
    	printf("%d ", tree[i]);
    printf("\n\n");
}

int main()
{
	//allocate tree
	int x = (int)(ceil(log2(n))); 	//height
    int size = 2*(int)pow(2, x); 	//size of array
    tree = new int[size];

	int root = 1;			//root of tree at tree[1]

    //build segment tree from array
    build(root, 0, n-1);
    
    printf("tree after build: ");
    printTree(size);    
 
    //print sum of values in array from index 1 to 3
    printf("Sum of values in given range = %d\n\n", query(root, 0, n-1, 1, 3));
 
    //update: set arr[1] = 10 (+7) and update corresponding segment tree nodes
    update(root, 0, n-1, 1, 7);
    
    printf("tree after update: ");
    printTree(size);  
 
    //find sum after the value is updated
    printf("Updated sum of values in given range = %d\n\n", query(root, 0, n-1, 1, 3));
    
    //update range 2-3 by 4
    updateRange(root, 0, n-1, 2, 3, 4);
    
    printf("tree after range update: ");
    printTree(size); 
    
    //find sum for 1-3 after range update 
    printf("Updated sum of values in given range = %d\n\n", query(root, 0, n-1, 1, 3));
    
    return 0;
}
