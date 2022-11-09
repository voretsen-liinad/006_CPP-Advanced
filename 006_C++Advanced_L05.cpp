// C++ advanced - Lesson 5 (07.11.2022)
// Homework 
// Created by Daniil Neserov (e-mail: maidanov1991@yandex.ru)

#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

//Task 1------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
void OriginalWords(T start, T end) {
	set<string> words;
	while (start != end) {
		words.insert(*start++);
	}
	copy(words.begin(), words.end(), ostream_iterator<string>(cout, "\n")); 
}

//End of task 1-----------------------------------------------------------------------------------------------------------------------------

//Task 2------------------------------------------------------------------------------------------------------------------------------------

void Sentences() {
	multimap<int, string> storage;
	string sentence;
	string word;
	int counter{ 0 };
	char ch;
	cout << "Please, enter sentences, and then input \"STOP\":\n";
	while (cin) {
		cin >> word;
		if (word.length() == 1) ch = word[0]; 
		if (word.length() > 1 || isalpha(ch)) {
			if (word != "STOP") {
				sentence += word;
				counter++;
			}
			if (word[word.length() - 1] == '.' || word == "STOP") {
				storage.insert({ counter, sentence });
				sentence.clear();
				counter = 0;
				if (word == "STOP") break;
			}
			else sentence += " ";
		}
		else continue;	
	}
	cout << "\n---Result---\n";
	for_each(storage.begin(), storage.end(), [](pair<int, string> sentence) {	
		cout << sentence.second << " (" << sentence.first << " words)" << endl; });
}

//End of task 2-----------------------------------------------------------------------------------------------------------------------------


int main() {
	
	cout << "Tasks 1-------------------------------------------------------------------------------------------\n";
	string arr[] = { "banana", "apple", "pineapple", "orange", "pear", "apple", "kiwi", "banana", "apple", "aiwa"};
	vector<string> vec = { "banana", "apple", "pineapple", "orange", "pear", "apple", "kiwi", "banana", "apple", "aiwa"};
	set<string> set = { "banana", "apple", "pineapple", "orange", "pear", "apple", "kiwi", "banana", "apple", "aiwa" };
	multiset<string> mset = { "banana", "apple", "pineapple", "orange", "pear", "apple", "kiwi", "banana", "apple", "aiwa" };

	cout << "  ---array---\n";
	OriginalWords(begin(arr), end(arr));
	cout << endl;
	
	cout << "  ---vector---\n";
	OriginalWords(vec.begin(), vec.end());
	cout << endl;

	cout << "  ---set---\n";
	OriginalWords(set.begin(), set.end());
	cout << endl;

	cout << "  ---multiset---\n";
	OriginalWords(mset.begin(), mset.end());
	cout << endl;

	cout << "\n";
	cout << "End of tasks 1------------------------------------------------------------------------------------\n" << endl;


	cout << "Tasks 2-------------------------------------------------------------------------------------------\n";

	Sentences();

	cout << "\n";
	cout << "End of tasks 1------------------------------------------------------------------------------------\n" << endl;

	return 0;
}
