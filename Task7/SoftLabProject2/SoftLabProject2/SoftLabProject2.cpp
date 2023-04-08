#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

int FindCount(const vector<pair<string, string>>& words, const string& word) {
    int count = 0;
    for (const auto& wordPair : words) {
        if (wordPair.second == word) {
            count++;
        }
    }
    return count == 0 ? count : count - 1;
}

int main()
{
    ifstream in("words.txt");
    vector<pair<string, string>> words;
    string str;

    while (getline(in, str, '\n')) {
        pair<string, string> word;
        word.first = str;
        word.second = str;
        sort(word.second.begin(), word.second.end());
        words.push_back(word);
    }
    in.close();

    ifstream fin("input.txt");
    int wordsCount = 0;
    fin >> wordsCount;
    while(wordsCount--){
        string str;
        if (fin >> str) {
            int myAnswer = 0;
            sort(str.begin(), str.end());
            myAnswer = FindCount(words, str);

            cout << myAnswer << " ";
        }
    }
    fin.close();

    return 0;
}
