#ifndef TRIE_H
#define TRIE_H
/*
Assignment: PA3
Description:Creates a simple word dictionary that
stored in the form of a trie tree. The user
has the ability to search through the tree
by any prefix and locate all words that match
the desired prefix
Author: Jeffrey Heredia
*/
#include "TrieNode.h"
#include <string>
#include <cctype>
using namespace std;

class Trie
{
private:
    TrieNode *_root = nullptr;

protected:

public:
    Trie()
    {
        _root = new TrieNode{};
    }

    virtual ~Trie()
    {
		deleter(_root);
		delete _root;
    }

	void deleter(TrieNode *node)
	{
		vector<TrieNode*> children = node->getChildren();
		for (int i = 0; i < children.size(); i++)
		{
			node = children[i];
			deleter(node);
			delete node;
		}
	}
	
	//TODO: implement
    void addWord(const string &word)
    {
		int index = 0;
		addWordHelper(word, index, _root);
    }
	
	void addWordHelper(const string &word, int index, TrieNode *node)
	{
		//base case end of word
		if(word.length() == index)
		{
			node->setChild('$', new TrieNode { '$' });
			return;
		}
		
		//adding a new letter when the node doesnt have a child
		if(node->hasChild(word.at(index)) == false)
		{
			node->setChild(word.at(index), new TrieNode { word.at(index) });
			node = node->getChild(word.at(index));
			index += 1;
			return addWordHelper(word, index, node);
		}
		
		//adding a letter when the node has a child
		if(node->hasChild(word.at(index)) == true)
		{
			//check if you need to branch
			//first test no branch
			if (node->getChild(word.at(index)) != nullptr)
			{
				node = node->getChild(word.at(index));
				index += 1;
				return addWordHelper(word, index, node);
			}
			//next for a branch branch
			else
			{
				node->setChild(word.at(index), node);
				node = node->getChild(word.at(index));
				index += 1;
				return addWordHelper(word, index, node);
			}
		}
	}
	vector<string> search(const string &prefix, vector<string> &words)
	{
		string current_word = "";
		searchHelper(_root, words, current_word, prefix);
		return words;
	}

	void searchHelper(TrieNode *node, vector<string> &words, string current_word, string prefix)
	{
		for (int i = 0; i < prefix.size(); i++)
		{
			//base case the letter isnt there
			if (node->getChild(prefix[i]) == nullptr)
				return;
			//if the letter is there then move node to that letter
			else
				node = node->getChild(prefix[i]);

		}
		walk(node, words, prefix);
	}

	void walk(TrieNode *node, vector<string> &words, string current_word)
	{
		//when we reach a $
		if (node->isSentinel())
		{
			current_word.pop_back();
			words.push_back(current_word);
			return;
		}

		vector<TrieNode*> children = node->getChildren();
		for (int i = 0; i < children.size(); i++)
		{
			//otherwise
			char index = children[i]->getValue();
			string temp_word = current_word + index;
			walk(node->getChild(index), words, temp_word);
		}
	}
};

#endif // !TRIE_H
