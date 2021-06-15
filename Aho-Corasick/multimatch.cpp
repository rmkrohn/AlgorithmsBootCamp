//Aho-Corasick String Matching
//Rachel Krohn, 2016

//Demo program for Aho-Corasick String Multi-Matching
//This contains the code necessary to build the trie, along with
//the string search process

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;

struct node
{
	map<char, node*> children;
	node* fail;		//points to longest proper suffix of this node that is
					//a prefix of another pattern (ie go somewhere assuming
					//we have already matched some characters)
	set<int> out;	//list of patterns recognized by entering this node
	
	node()
	{
		fail = 0;
	}
	
	//insert string s starting from index idx
	void insert(string s, int id, int idx = 0)
	{
		//have not inserted entire string
		if (idx < s.length())
		{
			//no edge for this character, create it
			if (this->children.find(s[idx]) == this->children.end())
				this->children[s[idx]] = new node();
				
			//recurse down to finish insert
			this->children[s[idx]]->insert(s, id, idx+1);
		}
		//entire string inserted, leaf node
		else
		{
			out.insert(id);
		}
	}
	
	void del()
	{
		for (map<char, node*>::iterator it = children.begin(); 
			it != children.end(); it++)
		{
			if (it->second != this)
				(it->second)->del();
		}
		delete(this);
	}
};

int main()
{
	int n;		//number of patterns to match
	string alpha = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int alpha_size = 53;
	
	while (cin >> n)
	{
		cin.ignore();
		
		vector<string> patterns;
		string text;
		node *trie = new node();
		
		//read in patterns, add to trie
		patterns.resize(n);
		for (int i = 0; i < n; i++)
		{
			getline(cin, patterns[i]);
			trie->insert(patterns[i], i);
		}
			
		//read text to search
		getline(cin, text);
		
		//cerr << text << endl;		
		
		//complete goto function for root: any character without edge points
		//back to root (loop the alphabet)
		for (int c = 0; c < alpha_size; c++)	//loop alphabet
		{
			//no edge for this character, create a self-loop
			if (trie->children.find(alpha[c]) == trie->children.end())
				trie->children[alpha[c]] = trie;
		}
		
		//create failure edges and output list for trie
		//start at root, loop all characters in alphabet
		queue<node*> q;
		for (int c = 0; c < alpha_size; c++)	//loop alphabet
		{
			//if this character has edge from root, push destination in queue
			if (trie->children[alpha[c]] != trie)
			{
				trie->children[alpha[c]]->fail = trie;		//fail for this node is root
				q.push(trie->children[alpha[c]]);
			}
		}
		
		//now, process nodes until the queue is empty (bfs)
		while (!q.empty())
		{
			node* curr = q.front();
			q.pop();
			node* v;			
			
			for (int i = 0; i < alpha_size; i++)	//loop alphabet
			{
				char c = alpha[i];
			
				//if node has edge for this character, put destination in queue
				if (curr->children.find(c) != curr->children.end())
				{
					q.push(curr->children[c]);	//destination in queue
					v = curr->fail;		//set pointer for traversal
					
					//traverse up failure edges until find valid edge for c
					//this finds the deepest node corresponding to a proper
					//suffix of current node 
					while (v->children.find(c) == v->children.end())
					{
						if (v->fail == 0)
							v = trie;
						else
							v = v->fail;
					}
					
					//set failure of current node to deepest suffix node
					curr->children[c]->fail = v->children[c];
					
					//union output sets of destination c of current node and
					//failure of that node
					//this is because any output strings at failure node 
					//are suffixes of the node reached by c from curr, so
					//we need to register those matches at node reached by c
					//as well as at failure node
					for (set<int>::iterator it = v->children[c]->out.begin();
						it != v->children[c]->out.end(); it++)
					{
						curr->children[c]->out.insert(*it);
					}
				}
			}
		}
		
		//finally, search patterns!
		node* curr = trie;		//start at root
		vector<vector<int> > matches;	//list of matches for each pattern
		matches.resize(n);		
		for (int i = 0; i < text.length(); i++)		//loop text
		{
			//while no matching edge, follow fail edges
			while (curr->children.find(text[i]) == curr->children.end())
			{
				if (curr->fail == 0)
					curr = trie;
				else
					curr = curr->fail;
			}
				
			//now follow valid edge
			curr = curr->children[text[i]];
			
			//store locations in text of any matches found here
			//note that i will be location of end of match, use
			//length of string matched to determine starting location
			for (set<int>::iterator it = curr->out.begin(); 
				it != curr->out.end(); it++)
			{
				matches[*it].push_back(i-(patterns[*it].length()-1));
			}
		}
		
		//print results
		for (int i = 0; i < n; i++)
		{
			if (matches[i].size() != 0)
				cout << matches[i][0];
			for (int j = 1; j < matches[i].size(); j++)
				cout << " " << matches[i][j];
			cout << endl;
		}
		
		//free memory
		trie->del();
	}
}
