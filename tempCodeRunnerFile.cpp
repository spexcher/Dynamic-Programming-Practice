#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_map<char, int> alphabetIndex;
unordered_map<int, vector<pair<char, int>>> transitions;
vector<vector<int>> epsilonClosure;
vector<vector<pair<char, int>>> StateTable;

void findClosure(int state, int current)
{
    if (epsilonClosure[current][state])
        return;

    epsilonClosure[current][state] = 1;

    if (alphabetIndex.count('#') && transitions[state].size() > 0)
    {
        for (auto &transition : transitions[state])
        {
            if (transition.first == '#')
            {
                findClosure(transition.second, current);
            }
        }
    }
}

void insertTransition(int fromState, char symbol, int toState)
{
    if (!alphabetIndex.count(symbol))
    {
        cout << "Error: Invalid alphabet '" << symbol << "'. Alphabet must be one of the defined alphabets." << endl;
        return;
    }

    int symbolIndex = alphabetIndex[symbol];
    transitions[fromState].push_back({symbol, toState});
    StateTable[fromState].push_back({symbol, toState});
}

void printStateTable(int numStates)
{
    cout << "State Table:" << endl;
    for (int state = 1; state <= numStates; ++state)
    {
        cout << "State " << state << ": {";
        for (int j = 1; j <= numStates; ++j)
        {
            if (epsilonClosure[state][j])
            {
                cout << "q" << j << " ";
            }
        }
        cout << "}" << endl;
    }
}

void printGeneralTable(int numStates)
{
    cout << "State Table:" << endl;
    for (int state = 1; state <= numStates; ++state)
    {
        cout << "State " << state << ": {";
        for (auto [symbol, tostate] : StateTable[state])
        {
            cout << "(" << symbol << " q" << tostate << ") ";
        }
        cout << "}" << endl;
    }
}

int main()
{
    int numAlphabets, numStates, numTransitions;
    cout << "Enter the number of alphabets: ";
    cin >> numAlphabets;
    cout << "Enter alphabets: ";
    for (int i = 1; i <= numAlphabets; ++i)
    {
        char alphabet;
        cin >> alphabet;
        alphabetIndex[alphabet] = i;
    }
    alphabetIndex['#'] = 0;

    cout << "Enter the number of states: ";
    cin >> numStates;

    cout << "Enter the number of transitions: ";
    cin >> numTransitions;

    epsilonClosure.resize(numStates + 1, vector<int>(numStates + 1, 0));
    StateTable.resize(numStates + 1);

    cout << "Enter transitions (fromState symbol toState):" << endl;
    for (int i = 0; i < numTransitions; ++i)
    {
        cout << "Press 1 to enter a transition (fromState symbol toState):" << endl;
        cout << "Press 2 to see the state table" << endl;
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            int fromState, toState;
            char symbol;
            cout << "Enter From_State symbol To_State seperated by space" << endl;
            cin >> fromState >> symbol >> toState;
            insertTransition(fromState, symbol, toState);
            break;
        case 2:
            printGeneralTable(numStates);
            break;
        default:
            cout << "Invalid INPUT" << endl;
            return 0;
        }
    }

    cout << "Epsilon closure for each state:" << endl;
    for (int state = 1; state <= numStates; ++state)
    {
        for (int j = 0; j < numStates; ++j)
        {
            epsilonClosure[state][j] = 0;
        }

        findClosure(state, state);

        cout << "State " << state << ": {";
        for (int j = 1; j <= numStates; ++j)
        {
            if (epsilonClosure[state][j])
            {
                cout << "q" << j << " ";
            }
        }
        cout << "}" << endl;
    }

    char option;
    cout << "Enter '?' to see the entire state table: ";
    cin >> option;

    if (option == '?')
    {
        printGeneralTable(numStates);
    }
    cout << "Thanks for using our program have a great day." << endl;
    return 0;
}
