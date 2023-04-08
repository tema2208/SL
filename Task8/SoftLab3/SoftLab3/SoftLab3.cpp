#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

//DFS with visited vector
void FindCycles(map<string, string> m, map<string, bool>& visited, string vertex, int& answer) {
    string chosenEdges = m.at(vertex);
    for (char vertexTo : chosenEdges)
    {
        if (!visited.at(string(1, vertexTo))) {
            visited.at(string(1, vertexTo)) = true;
            FindCycles(m, visited, string(1, vertexTo), answer);
        }
        else 
        {
            answer = 1;
            return;
        }
    }
}

void ReadRoads(map<string, string>& myMap, const string& road) {
    string first = string(1, road[0]);
    string second = string(1, road[2]);
    if (!myMap.count(first)) {
        myMap.emplace(pair<string, string>(first, second));
    }
    else {
        myMap[first] += second;
    }
    if (!myMap.count(second)) {
        myMap.emplace(pair<string, string>(second, ""));
    }
}

map<string, bool> CreateVesetedMap(const map<string, string>& myMap) {
    map<string, bool> visited;
    for (auto it = myMap.begin(); it != myMap.end(); ++it)
    {
        visited.emplace(pair<string, bool>(it->first, false));
    }
    return visited;
}

int main()
{
    ifstream in("input.txt");
    int testsCount = 0; 
    in >> testsCount;

    while (testsCount--) {
        map<string, string> myMap;
        int cityCount = 0;
        in >> cityCount;
        string road; 
        while (cityCount-- > 0 && in >> road) {
            ReadRoads(myMap, road);
        }
        map<string, bool> visited = CreateVesetedMap(myMap);
        int answer = 0;
        FindCycles(myMap, visited, myMap.begin()->first, answer);
        cout << answer << " ";
    }
    in.close();
}