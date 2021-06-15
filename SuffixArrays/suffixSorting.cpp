//Suffix Arrays (and suffix sorting)
//Rachel Krohn, 2016

//Demo program for Suffix Arrays
//Example of sorting suffixes to answer order queries

#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
using namespace std;
 
//store suffix info
struct suffix
{
    int index;		//index of beginning of suffix in txt
    int rank[2]; 	//first and second rank
};
 
//comparison function used by sort() to compare two suffixes
//compares two suffixes by rank pairs
int compare(suffix a, suffix b)
{
	if (a.rank[0] != b.rank[0])
		return a.rank[0] < b.rank[0];
	return a.rank[1] < b.rank[1];
}
 
//builds suffix array for string txt with length n
int *buildSuffixArray(string txt, int n)
{
    struct suffix suffixes[n];		//suffix storage
    
    //index is index in txt of beginning of suffix
    //first rank is equal to value of first character
    //second rank is equal to value of second character, or -1 if first char is last in txt
    for (int i = 0; i < n; i++)
    {
        suffixes[i].index = i;
        suffixes[i].rank[0] = txt[i];
        suffixes[i].rank[1] = i+1 < n ? txt[i+1] : -1;
    }

    //sort suffixes - sorts on first 2 characters of each suffix
    sort(suffixes, suffixes+n, compare);
 
 	//suffixes now sorted by first 2 characters
 	//to continue, sort by first 4 chars, then first 8, etc

    int ind[n]; 	//mapping array to get next suffix
    				//ind[i] = index of suffix beginning at txt[i] in suffixes array 
    
    //sort by larger chunks of characters
    //first rank assigned in this loop will be rank (including ties) resulting
    //from previous sort
    //second rank will be equal to first rank of 
    for (int k = 4; k < 2*n; k = k*2)
    {
        //assign first rank to first suffix
        int rank = 0;		//current rank being assigned
        int prev_rank = suffixes[0].rank[0];		//rank of previous suffix
        suffixes[0].rank[0] = rank;		//first suffix has rank 0
        ind[suffixes[0].index] = 0;		//index mapping for first suffix
 
        //assign first ranks to all remaining suffixes
        for (int i = 1; i < n; i++)
        {
            //if ranks for current suffix are same as ranks of previous suffixes,
            //rank does not change (current gets same rank as previous)
            if (suffixes[i].rank[0] == prev_rank &&
                    suffixes[i].rank[1] == suffixes[i-1].rank[1]) { }
            //not an exact match, this suffix gets new rank
            else
            	rank++;                
            
            prev_rank = suffixes[i].rank[0];		//update previous rank
            suffixes[i].rank[0] = rank;				//set new rank of current suffix
            ind[suffixes[i].index] = i;				//index mapping
        }
 
        //assign second rank to every suffix
        //second rank is rank of suffix starting at current suffix index + k/2
        //if no suffix there (overstep txt), rank is -1
        for (int i = 0; i < n; i++)
        {
            int nextindex = suffixes[i].index + k / 2;	 //index in txt of next suffix
            
            //use index mapping created earlier to find rank of next suffix
            suffixes[i].rank[1] = nextindex < n ? suffixes[ind[nextindex]].rank[0] : -1;
        }
 
        //sort the suffixes according to first k characters
        sort(suffixes, suffixes+n, compare);
    }
    //now all suffixes are sorted correctly
 
    //store indexes of all sorted suffixes in the suffix array
    int *suffixArr = new int[n];		//allocate
    for (int i = 0; i < n; i++)
        suffixArr[i] = suffixes[i].index;		//store index of suffix start in rank order
 
    //return the suffix array
    return  suffixArr;
}
 
// A utility function to print an array of given size
void printArr(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        cerr << arr[i] << " ";
    cerr << endl;
}
 
// Driver program to test above functions
int main()
{
    string txt;
    
    while (getline(cin, txt))
    {
    	cerr << endl << txt << endl;
    
    	//build suffix array
    	int *suffixArr = buildSuffixArray(txt,  txt.length());
    	
    	cerr << "Suffix Array: ";
    	printArr(suffixArr, txt.length());
    
    	//get number of queries
    	long long n;
    	cin >> n;
    	
    	//process queries
    	int q;
    	cin >> q;
    	cout << suffixArr[q];
    	for (long long i = 1; i < n; i++)
    	{
    		cin >> q;
    		cout << " " << suffixArr[q];
    	}
    	cout << endl;
    	
    	cin.ignore();		//clear newline char
    }
}


