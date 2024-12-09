#include <iostream>
#include <vector>
#include <chrono>

//#include "CaseTests.h"

using namespace std;

int maxTwoEvents(vector<vector<int>>& events) {

    uint tot = 0;
    uint result = 0;
    vector<uint> analized;

    vector<int>* fEvent = nullptr;
    int* fStart = nullptr;
    int* fEnd = nullptr;
    //int* fValue = nullptr;

    vector<int>* sEvent = nullptr;
    int* sStart = nullptr;
    int* sEnd = nullptr;
    int* sValue = nullptr;

    int* oldValue = nullptr;

    for(uint first=0; first < events.size(); first++) {

        fEvent = &events[first];
        fStart = &fEvent->at(0);
        fEnd = &fEvent->at(1);

        analized.push_back(first);

        oldValue = nullptr;
        for(uint second=first+1; second < events.size(); second++) {

            sEvent = &events[second];
            sStart = &sEvent->at(0);
            sEnd = &sEvent->at(1);
            sValue = &sEvent->at(2);

            // Conflito do first com second
            if((*fStart >= *sStart && *fStart <= *sEnd) || (*fEnd >= *sStart && *fEnd <= *sEnd))
                continue;

            // Conflito do second com first
            if((*sStart >= *fStart && *sStart <= *fEnd) || (*sEnd >= *fStart && *sEnd <= *fEnd))
                continue;

            // Valor novo é menor que o antigo
            if(oldValue && *sValue < *oldValue)
                continue;

            oldValue = sValue;
            analized[first] = second;
        }

        if(analized[first] != first)
            result = events[first][2] + events[analized[first]][2];
        else
            result = events[first][2];

        if(tot < result)
            tot = result;
    }

    return tot;
}

int main()
{
    //vector<vector<int>> vects = {{1,3,2},{4,5,2},{2,4,3}};
    //vector<vector<int>> vects = {{1,3,2},{4,5,2},{1,5,5}};
    //vector<vector<int>> vects = {{1,5,3},{1,5,1},{6,6,5}};
    //vector<vector<int>> vects = {{1,5,3},{1,5,1},{6,6,5},{1,3,7},{2,4,8}};
    //vector<vector<int>> vects = {{1,5,3},{1,5,1},{6,6,5},{1,3,7},{2,4,8},{1,10,13}};
    //vector<vector<int>> vects = {{1,5,3},{1,5,1},{6,6,5},{1,3,7},{2,4,8},{1,10,13},{1,2,60}};
    //vector<vector<int>> vects = {{1,5,3},{1,5,1},{6,6,5},{1,3,7},{2,4,8},{1,10,13},{1,2,60},{4,9,9}};
    //vector<vector<int>> vects = {{1,5,3},{1,5,1},{6,6,5},{1,3,7},{2,4,8},{1,10,13},{1,2,60},{4,9,9},{1,10,61}};
    //vector<vector<int>> vects = {{1,5,63},{1,5,1},{6,6,5},{1,3,7},{2,4,8},{1,10,13},{1,2,60},{4,9,9},{1,10,61}};
    vector<vector<int>> vects = {{1,10,62},{1,5,63},{1,5,1},{6,6,5},{1,3,7},{2,4,8},{1,10,13},{1,2,60},{4,9,9},{1,10,61}};

    uint result = 0;
    auto inicio = std::chrono::high_resolution_clock::now();
    for(int a=0; a < 1000000; a++)
        result = maxTwoEvents(vects);
    auto fim = std::chrono::high_resolution_clock::now();
    auto duracao = std::chrono::duration_cast<std::chrono::milliseconds>(fim - inicio);
    cout << result << " tempo " << duracao;

    //cout << maxTwoEvents(vectTests);
    cout << endl;
    return 0;
}
