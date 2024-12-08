#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>

using namespace std;

int sumEvents(const unordered_set<uint>& eventsId, const vector<vector<int>>& events) {

    int tot = 0;
    for(const uint& eventId : eventsId) {
        tot += events.at(eventId).at(2);
        cout << "sumEvents tot " << tot << " eventId " << eventId << " value " << events.at(eventId).at(2) << endl;
    }
    return tot;
}

void insertEvent(map<int, uint>& map, uint index, const vector<int>& event) {

    for(int a=event.at(0); a <= event.at(1); a++) {
        map[a] = index;
        cout << "insertEvent map[" << a << "] = " << index << endl;
    }
}

void removeEvents(map<int, uint>& map, const unordered_set<uint>& eventsId, const vector<vector<int>>& events) {

    for(const uint& eventId : eventsId) {

        const vector<int>& event = events.at(eventId);
        for(int a=event.at(0); a <= event.at(1); a++) {

            if(map.at(a) == eventId) {
                map.erase(a);
                cout << "removeEvents map[" << a << "]" << endl;
            }
        }
    }
}


int maxTwoEvents(vector<vector<int>>& events) {

    map<int, uint> analized; // Vamos utilizar um mapeamento identificando 'Times' analisados (key: Time, value: Id do Evento)
    int tot = 0; // Vamos utilizar uma variável para identificar o valor total
    uint preventDuplicateEventId = -1; // Vamos inicializar preventDuplicateEventId com valor inválido

    // Vamos inserir o primeiro evento
    insertEvent(analized, 0, events.at(0));

    // Vamos analisar os demais casos
    for(uint i=1; i < events.size(); i++) {

        // Vamos criar os facilitadores necessários
        const vector<int>& event = events.at(i);
        const int& start = event.at(0);
        const int& end = event.at(1);
        const int& value = event.at(2);

        // Vamos identificar o evento corrente
        cout << "eventId " << i << endl;

        // Vamos criar um vetor auxiliar com o IDs dos eventos que tem conflito
        unordered_set<uint> conflitEvents;

        // Vamos percorrer todos os eventos já analisados
        for(const auto& pair : analized) {

            const int& time = pair.first;
            const int& eventId = pair.second;

            if(time >= start && time <= end) {

                if(!conflitEvents.contains(eventId)) {

                    conflitEvents.insert(eventId);

                    cout << "time " << time << " start " << start << " end " << end << endl;
                    cout << "conflitEvents.insert(" << eventId << ")" << endl;
                }
            }
        }

        // Se houverem conflitos
        if(!conflitEvents.empty()) {

            // Se os eventos antigos possuem um valor menor, vamos removê-los
            if(value > sumEvents(conflitEvents, events)) {

                removeEvents(analized, conflitEvents, events);
                insertEvent(analized, i, event);
            }
        }
        else {

            insertEvent(analized, i, event);
        }
    }

    // Vamos imprimir mapeamento obtido
    for(auto value : analized) {
        cout << "analized[" << value.first << "] eventId = " << value.second << " value = " << events.at(value.second).at(2) << endl;
    }

    // Vamos percorrer o mapeamento e evitar as duplicações de incrementos com o mesmo Id de evento
    for(auto value : analized) {

        if(preventDuplicateEventId != value.second) {

            tot += events.at(value.second).at(2);
            preventDuplicateEventId = value.second;
        }
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
    vector<vector<int>> vects = {{1,10,62},{1,5,3},{1,5,1},{6,6,5},{1,3,7},{2,4,8},{1,10,13},{1,2,60},{4,9,9},{1,10,61}};
    cout << maxTwoEvents(vects);
    cout << endl;
    return 0;
}
