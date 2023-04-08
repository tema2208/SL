#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;
void CountSort(std::vector<int>& input)
{
    std::map<int, int> freq;
    for (int x : input) {
        freq[x]++;
    }
    int i = 0;
    for (auto p : freq)
    {
        while (p.second--) {
            input[i++] = p.first;
        }
    }
}

int HexToInt(char ch) {
	switch (toupper(ch))
	{
	case 'A': return 10;
	case 'B': return 11;
	case 'C': return 12;
	case 'D': return 13;
	case 'E': return 14;
	case 'F': return 15;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	case '0': return 0;
	}
}

string IntToHex(int a)
{
	string tmp("");
	do
	{
		int r(a % 16);
		if (r > 9) { r += (int)'A' - 10; }
		else { r += (int)'0'; };
		tmp = (char)r + tmp;
		a /= 16;
	} while (a);
	return tmp;
}

int FindIndex1(const vector<int>& vec, const vector<int>& sortedDigits) {
	int index1 = 0;
	int k = 0;
	for (int i = 0; i < vec.size(); ++i) {
		if (vec[i] != sortedDigits[i]) {
			index1 = i;
			break;
		}
	}
	return index1;
}

int FindIndex2ForMax(const vector<int>& vec, const vector<int>& numbers, int index1) {
	int index2 = 0;
	for (int i = index1 + 1; i < vec.size(); ++i) {
		if (numbers[index1] == vec[i]) {
			index2 = i;
			break;
		}
	}
	return index2;
}

int FindIndex2ForMin(const vector<int>& vec, const vector<int>& numbers, int index1) {
	int index2 = 0;
	for (int i = vec.size() - 1; i >= 0; --i) {
		if (numbers[index1] == vec[i]) {
			index2 = i;
			break;
		}
	}
	return index2;
}

//indexVec - index of digit, which we will change
//indexDigit - index of digit in sorted array, which we will find in original number
void FindIndexes(const vector<int>& vec, const vector<int>& sortedDigits, int zeroCount, int& indexVec, int& indexDigit) {
	// case 2 (1)
	//check for first digit in number
	if (vec[0] != sortedDigits[zeroCount]) {
		indexVec = 0;
		indexDigit = zeroCount;
		return;
	}
	for (int i = 1; i < vec.size(); ++i) {
		// case 2 (2)
		if (zeroCount-- > 0 && vec[i] != 0) {
			indexVec = i;
			indexDigit = 0;
			return;
		}
		// case 2 (3)
		if (zeroCount <= 0 && vec[i] > sortedDigits[i]) {
			indexVec = i;
			indexDigit = i;
			return;
		}
	}
}

string CreateAnswer(const vector<int>& vec) {
	string answer = "";
	for (int i = 0; i < vec.size(); ++i) {
		answer += IntToHex(vec[i]);
	}
	return answer;
}

string FindMinNumber(vector<int> vec, const vector<int>& sortedDigits) {
	vector<int> zeroIndexes;
	//this indexes of elements, which we want to change
	int index1 = 0;
	int index2 = 0;
	//this auxiliary index
	int indexDigit = 0;
	for (int i = 0; i < vec.size(); ++i) {
		if (vec[i] == 0)
			zeroIndexes.push_back(i);
	}
	//case 1
	//if number doesn't have zero
	if (zeroIndexes.empty()) {
		index1 = FindIndex1(vec, sortedDigits);
		index2 = FindIndex2ForMin(vec, sortedDigits, index1);
	}
	else {
		FindIndexes(vec, sortedDigits, zeroIndexes.size(), index1, indexDigit);
		index2 = FindIndex2ForMin(vec, sortedDigits, indexDigit);
	}
	if(index1 != 0 || vec[index2] != 0)
		swap(vec[index1], vec[index2]);

	return CreateAnswer(vec);
}

string FindMaxNumber(vector<int> vec, const vector<int>& numbers) {
	int index1 = FindIndex1(vec, numbers);
	int index2 = FindIndex2ForMax(vec, numbers, index1);
	swap(vec[index1], vec[index2]);
	return CreateAnswer(vec);
}


void StartTest(vector<int>& vec) {
	vector<int> digits = vec;
	CountSort(digits);
	cout << hex << FindMinNumber(vec, digits) << hex << " ";
	reverse(digits.begin(), digits.end());
	cout << hex << FindMaxNumber(vec, digits) << hex << endl;
}

int main()
{	
	ifstream in("input.txt");

	int testsCount = 0;
	vector<int> vec;
	vector<char> tmpVector;
	char ch;
	in >> testsCount;
	while (in.is_open() && testsCount >= 0) {
		while (in.get(ch))
		{
			if (ch != '\n' && ch != ' ')
				tmpVector.push_back(ch);
			if (ch == '\n')
				break;
		}
		for (auto it = tmpVector.begin(); it != tmpVector.end(); ++it) {
			vec.push_back(HexToInt(*it));
		}
		if(!tmpVector.empty())
			StartTest(vec);
		if (ch == '\n') {
			tmpVector.clear();
			vec.clear();
			testsCount--;
		}
	}
	in.close();
    return 0;
}