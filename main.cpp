/*
Assignment: PA3
Description:Creates a simple word dictionary that
	stored in the form of a trie tree. The user
	has the ability to search through the tree
	by any prefix and locate all words that match
	the desired prefix
Author: Jeffrey Heredia
*/
#include <string>
#include <iostream>
#include <fstream>
#include "Trie.h"
using namespace std;




int main(void)
{
    Trie dictionary{};

    string line = "";
	string file_name;

    //First, prompt the user for a file containing all of the words to look up
	cout << "Please enter file name of dictionary" << endl;
	getline(cin, file_name);

	//open file stream
	ifstream dictionary_file(file_name);

    //Next, add all words in the file into the Trie using the addWord() function
	while (dictionary_file >> line)
	{
		dictionary.addWord(line);
	}

    //Then, prompt the user for a list of partial words to look up.  Display all matches 
    //on the screen.

	char again = 'y';
	string prefix = "";
	while (again != 'n')
	{
		cout << "Enter the prefix to look up" << endl;
		cout << "Prefix: ";
		cin >> prefix;

		//call search
		vector<string> words{};
		dictionary.search(prefix, words);

		//print the results of search
		for (auto word : words)
		{
			cout << word << endl;
		}

		//ask if they user wants to look up another one

		cout << endl;
		cout << "Would you like to look up another prefix? y / n" << endl;
		cin >> again;
		cout << endl;
	}

	return 0;
}