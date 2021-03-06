// SinonimsUT.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cassert>

using namespace std;

using Synonyms = map<string, set<string>>;

void AddSynonyms(Synonyms& synonyms, 
					const string& first_word, 
					const string& second_word) {
	synonyms[first_word].insert(second_word);
	synonyms[second_word].insert(first_word);
}

size_t GetSynonymsCount(Synonyms& synonyms,
					const string& word) {
	return synonyms[word].size();
}

bool AreSynonyms(Synonyms& synonyms,
					const string& first_word,
					const string& second_word) {
	return synonyms[first_word].count(second_word) == 1;
}

void TestAddSynonyms() {
	{
		Synonyms empty;
		AddSynonyms(empty, "a", "b");
		const Synonyms expected = {
			{"a", {"b"}},
			{"b", {"a"}},
		};
		assert(empty == expected);
	}
	{
		Synonyms synonyms = {
			{"a", {"b"}},
			{"b", {"a", "c"}},
			{"c", {"b"}}
		};
		AddSynonyms(synonyms, "a", "c");
		const Synonyms expected = {
			{ "a",{ "b", "c" } },
			{ "b",{ "a", "c" } },
			{ "c",{ "b", "a" } }
		};
		assert(synonyms == expected);
	}
	cout << "passed" << endl;
}

int main() {
	

	Synonyms synonyms;

	try {
		TestAddSynonyms();
	}
	catch (exception e) {
		cout << "Error " << endl;
	}
		
	int q;
	cin >> q;

	for (int i = 0; i < q; ++i) {
		string operation_code;
		cin >> operation_code;

		if (operation_code == "ADD") {

			string first_word, second_word;
			cin >> first_word >> second_word;

			AddSynonyms(synonyms, first_word, second_word);
		}
		else if (operation_code == "COUNT") {

			string word;
			cin >> word;
			cout << GetSynonymsCount(synonyms, word) << endl;
		}
		else if (operation_code == "CHECK") {

			string first_word, second_word;
			cin >> first_word >> second_word;

			if (AreSynonyms(synonyms, first_word, second_word)) {
				cout << "YES" << endl;
			} else {
				cout << "NO" << endl;
			}
		}
	}

	return 0;
}

