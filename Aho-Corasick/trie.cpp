//Trie
//Rachel Krohn, 2016

//Demo program for search (prefix) trie
//This contains the code necessary to build a trie of search terms,
//and a method to perform lookups in the trie
//The Aho-Corasick algorithm is based on this data structure

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

struct node
{
	map<char, node*> children;
	bool end;
	
	node()
	{
		end = false;
	}
	
	//insert string s starting from index idx
	void insert(string s, int idx = 0)
	{
		//have not inserted entire string
		if (idx < s.length())
		{
			//no edge for this character, create it
			if (this->children.find(s[idx]) == this->children.end())
				this->children[s[idx]] = new node();
				
			//recurse down to finish insert
			this->children[s[idx]]->insert(s, idx+1);
		}
		//entire string inserted, leaf node
		else
		{
			this->end = true;
		}
	}
	
	//determines if trie contains string s; idx is index of current character of s
	bool search(string s, int idx = 0)
	{
		//not done searching string
		if (idx < s.length())
		{
			//no edge for current character, return false
			if (this->children.find(s[idx]) == this->children.end())
				return false;
				
			//have matching edge, continue search
			return this->children[s[idx]]->search(s, idx+1);
		}
		//on last character of string, return true if at leaf node
		else
		{
			return this->end;
		}
	}
	
	//delete this node
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
	//testing the search trie
	node *trie = new node();
	trie->insert("banani");
	trie->insert("banana");
	trie->insert("bana");
	trie->insert("ana");
	cerr << "banani " << (trie->search("banani") ? "T" : "F") << endl;
	cerr << "banana " << (trie->search("banana") ? "T" : "F") << endl;
	cerr << "bana " << (trie->search("bana") ? "T" : "F") << endl;
	cerr << "ana " << (trie->search("ana") ? "T" : "F") << endl;
	cerr << "anan " << (trie->search("anan") ? "T" : "F") << endl;
	cerr << "banan " << (trie->search("banan") ? "T" : "F") << endl;
	
	trie->del();
}
