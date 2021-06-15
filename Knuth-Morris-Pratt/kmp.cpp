//Knuth-Morris-Pratt String Matching
//Rachel Krohn, 2016

//Demo program for KMP String Matching

#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> T;

//Build prefix table for KMP algorithm
//remember to clear and resize T before calling
void buildTable(string pat)
{
    int i = 0, j = -1;
    T[i] = j;
    while (i < pat.size())
    {
        while (j >= 0 && pat[i] != pat[j]) 
        	j = T[j];
        i++; 
        j++;
        T[i] = j;
    }
}

//Finds position of first match of pat in txt
//if no match, returns length of txt
//not used int this problem, but still useful
int kmp(string txt, string pat)
{
	int m = 0;		//beginning of current match in txt
	int i = 0;		//position in pat
	
	while (m + i < txt.length())		//search to end of txt
	{
		//characters match
		if (pat[i] == txt[m+i])
		{
			//reached end of pattern, return position of current match
			if (i == pat.length()-1)
				return m;
		
			i++;		//move to next character of pat			
		}
		//characters do not match, keep searching
		else
		{
			//valid border, skip ahead
			if (T[i] != -1)
			{
				m = m + i - T[i];	//current pos + length of match - known matched
				i = T[i];			//start just after known matched
			}
			//no valid border, try next character
			else
			{
				i = 0;
				m++;
			}
		}		
	}
	
	//no matches, return length of txt
	return txt.length();
}

//Returns list of all match positions of pat in txt
//if no matches, returns empty vector
vector<int> kmpAll(string txt, string pat)
{
	int m = 0;		//beginning of current match in txt
	int i = 0;		//position in pat
	vector<int> matches;		//list of matches
	
	while (m + i < txt.length())		//search to end of txt
	{
		//characters match
		if (pat[i] == txt[m+i])
		{
			//add match to list
			if (i == pat.length()-1)
			{
				matches.push_back(m);
				
				//move forward to continue searching
				m = m + i - T[i];
				i = T[i];
			}
		
			i++;		//move to next character of pat			
		}
		//characters do not match, keep searching
		else
		{
			//valid border, skip ahead
			if (T[i] != -1)
			{
				m = m + i - T[i];	//current pos + length of match - known matched
				i = T[i];			//start just after known matched
			}
			//no valid border, try next character
			else
			{
				i = 0;
				m++;
			}
		}		
	}
	
	//return list of matches
	return matches;
}

int main()
{
	string pattern, text;
	
	while (getline(cin, pattern))	//read pattern
	{
		getline(cin, text);		//read text
		
		cerr << endl << text << endl << pattern << endl;
		
		//allocate prefix table
		T.clear();
		T.resize(pattern.length()+1);
		
		//build prefix table
		buildTable(pattern);
		
		//debug: print table
		
		cerr << "Prefix Table: ";
		for (int i = 0; i < T.size(); i++)
			cerr << T[i] << " ";
		cerr << endl;
		
		
		//find matches
		vector<int> matches = kmpAll(text, pattern);
		
		//print results
		cerr << "Matches: ";
		if (matches.size() != 0)
			cout << matches[0];
		for (int i = 1; i < matches.size(); i++)
			cout << " " << matches[i];
		cout << endl;
		
	}
}
