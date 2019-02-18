#include <iostream>
#include <vector>
#include <map>
#include <iostream>
#include <string>


using namespace std;

struct trienode {
	map<char, trienode> children;
	int size;
};

void add(trienode& root, string word, int index) {
	if (index == word.size()) {
		return;
	}
	if (root.children.count(word[index]) > 0) {
		root.size = root.size + 1;
		return add(root.children[word[index]], word, index + 1);
	}
	trienode newnode;
	newnode.size = 0;
	root.children[word[index]] = newnode;
	root.size = root.size + 1;
	return add(root.children[word[index]], word, index + 1);
}
int find(trienode& root, string word, int index) {
	if (index == word.size()) {
		return root.size;
	}
	return find(root.children[word[index]], word, index + 1);
}

vector<int> contacts(vector<vector<string>> queries) {
	trienode root;
	vector<int> numberofcontacts;
	root.size = 0;
	for (int i = 0; i < queries.size(); i++) {
		if (queries[i][0] == "add") {
			add(root, queries[i][1], 0);
		}
		else {
			numberofcontacts.push_back(find(root, queries[i][1], 0));
		}
	}
	return numberofcontacts;
}


int main()
{
	int queries_rows;
	cin >> queries_rows;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	vector<vector<string>> queries(queries_rows);
	for (int queries_row_itr = 0; queries_row_itr < queries_rows; queries_row_itr++) {
		queries[queries_row_itr].resize(2);

		for (int queries_column_itr = 0; queries_column_itr < 2; queries_column_itr++) {
			cin >> queries[queries_row_itr][queries_column_itr];
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	vector<int> result = contacts(queries);

	for (int result_itr = 0; result_itr < result.size(); result_itr++) {
		cout << result[result_itr];

		if (result_itr != result.size() - 1) {
			cout << "\n";
		}
	}

	return 0;
}

