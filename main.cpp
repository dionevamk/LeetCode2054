#include <iostream>
#include <vector>
#include <map>

using namespace std;

int maxTwoEvents(vector<vector<int>>& events) {

    uint tot = 0;
    map<uint, uint> analized;

    for(uint first=0; first < events.size(); first++) {

        const vector<int>& fEvent = events.at(first);
        const int& fStart = fEvent.at(0);
        const int& fEnd = fEvent.at(1);
        // const int& fValue = fEvent.at(2);

        int oldValue = 0;

        analized[first] = first;

        for(uint second=first+1; second < events.size(); second++) {

            const vector<int>& sEvent = events.at(second);
            const int& sStart = sEvent.at(0);
            const int& sEnd = sEvent.at(1);
            const int& sValue = sEvent.at(2);

            // Conflito do first com second
            if((fStart >= sStart && fStart <= sEnd) || (fEnd >= sStart && fEnd <= sEnd))
                continue;

            // Conflito do second com first
            if((sStart >= fStart && sStart <= fEnd) || (sEnd >= fStart && sEnd <= fEnd))
                continue;

            // Valor novo é menor que o antigo
            if(sValue < oldValue)
                continue;

            oldValue = sValue;
            analized[first] = second;
        }
    }

    // Vamos calcular os valores obtidos
    for(auto value : analized) {

        uint result;
        if(value.first != value.second)
            result = events.at(value.first).at(2) + events.at(value.second).at(2);
        else
            result = events.at(value.first).at(2);

        cout << "analized firstEvent " << value.first << " secondEvent " << value.second << " result = " << result << endl;

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
    cout << maxTwoEvents(vects);
    cout << endl;
    return 0;
}
