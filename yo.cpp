#define MOD 1000000007
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using pbds = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template <typename T>
using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;
#define ll long long
#define ull unsigned long long
#define lld long double
#define mod MOD
#define eb emplace_back
#define pb push_back
#define ppb pop_back

#define int long long
// disable this to storage constrained problems
// now int behaves as it
// but if you need long long then use ll
#define sqrt(x) sqrtl((x))
#define ceil(x) ceill((x))
#define floor(x) floorl((x))
#define ceildiv(a, b) ((a + b - 1) / b)
#define vi vector<int>
#define vll vector<ll>
#define vvb vector<vector<bool>>
#define vvc vector<vector<char>>
#define vb vector<bool>
#define vc vector<char>
#define vs vector<string>
#define vvi vector<vector<int>>
#define vvll vector<vector<ll>>
#define vvb vector<vector<bool>>
#define vvpii vector<vector<pii>>
#define vvpll vector<vector<pll>>
#define vpii vector<pii>
#define vpll vector<pll>
#define si set<int>
#define sll set<ll>
#define sc set<char>
#define mii map<int, int>
#define mll map<ll, ll>
#define mci map<char, int>
#define mcll map<char, ll>
#define pqi priority_queue<int>
#define pqll priority_queue<ll>

#define lb lower_bound
#define ub upper_bound
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define sortall(x) sort(all(x))
#define ff first
#define ss second
#define spre(x) cout << fixed << setprecision(x)
#define PI 3.1415926535897932384626
#define py cout << "YES\n"
#define pm cout << "-1\n"
#define pn cout << "NO\n"
#define pm cout << "-1\n"
#define pl cout << "\n"
#define nl "\n"
#define sp " "
#define print(x) cout << x << endl
#define deb(x) cout << #x << "=" << x << endl
#define upper(s1) transform(s1.begin(), s1.end(), s1.begin(), ::toupper)
#define lower(s1) transform(s1.begin(), s1.end(), s1.begin(), ::tolower)
#define maxe(v) *max_element(v.begin(), v.end())
#define mine(v) *min_element(v.begin(), v.end())
#define unq(v) v.resize(distance(v.begin(), unique(all(v))))
// sort v or it will remove consecutive duplicates only
#define getunique(v)                      \
    {                                     \
        sort(all(v));                     \
        v.erase(unique(all(v)), v.end()); \
    }
#define sum(v) accumulate(all(v), 0)
#define sz(x) (ll) x.size()
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << endl
#define gc getchar_unlocked
#define fo(i, n) for (int i = 0; i < n; i++)
#define forr(i, n) for (int i = n - 1; i >= 0; i--)
#define Fo(i, k, n) for (int i = k; k < n ? i < n : i > n; k < n ? i += 1 : i -= 1)
#define setbits(n) __builtin_popcountll(n)
#define counttz(n) __builtin_ctzll(n)
#define countlz(n) __builtin_clzll(n)
clock_t startTime;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
//-----------------------------End Snippet--------------------------

unordered_map<char, int> alphabetIndex;
unordered_map<int, vector<pair<char, int>>> transitions;
vector<vector<int>> epsilonClosure;
vector<vector<pair<char, int>>> StateTable;

void findClosure(int state, int current)
{
    if (epsilonClosure[current][state])
        return;
    epsilonClosure[current][state] = 1;
    if (alphabetIndex.count('#') and transitions[state].size() > 0)
        for (auto &transition : transitions[state])
            if (transition.ff == '#')
                findClosure(transition.ss, current);
}

void insertTransition(int fromState, char symbol, int toState)
{
    if (!alphabetIndex.count(symbol))
    {
        print("Error: Invalid alphabet '" << symbol << "'. Alphabet must be one of the defined alphabets.");
        exit(1);
    }

    int symbolIndex = alphabetIndex[symbol];
    transitions[fromState].pb({symbol, toState});
    StateTable[fromState].pb({symbol, toState});
}

void printStateTable(int numStates)
{
    print("State Table:");
    for (int state = 1; state <= numStates; ++state)
    {
        cout << "State q" << state << ": {" << sp;
        for (int j = 1; j <= numStates; ++j)
        {
            if (epsilonClosure[state][j])
            {
                cout << "q" << j << sp;
            }
        }
        print("}");
    }
}

void printGeneralTable(int numStates)
{
    print("State Table:");
    for (int state = 1; state <= numStates; ++state)
    {
        cout << "State q" << state << ": {" << sp;
        for (auto [symbol, tostate] : StateTable[state])
            cout << "(" << symbol << ", q" << tostate << "), ";
        print("}");
    }
}

signed main()
{
    int numAlphabets, numStates, numTransitions;
    print("Enter the number of alphabets: ");
    cin >> numAlphabets;
    print("Enter alphabets: ");
    for (int i = 1; i <= numAlphabets; ++i)
    {
        char alphabet;
        cin >> alphabet;
        alphabetIndex[alphabet] = i;
    }
    alphabetIndex['#'] = 0;

    cout << ("Enter the number of states: ") << sp;
    cin >> numStates;

    cout << ("Enter the number of transitions: ") << sp;
    cin >> numTransitions;

    epsilonClosure.resize(numStates + 1, vector<int>(numStates + 1, 0));
    StateTable.resize(numStates + 1);

    print("Enter transitions (fromState symbol toState):");
    for (int i = 0; i < numTransitions; ++i)
    {
        print("Press 1 to enter a transition (fromState symbol toState):\nPress 2 to see the state table");
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            int fromState, toState;
            char symbol;
            print("Enter \"From_State symbol To_State\" seperated by space (without quotes)");
            cin >> fromState >> symbol >> toState;
            insertTransition(fromState, symbol, toState);
            break;
        case 2:
            printGeneralTable(numStates);
            i--;
            break;
        default:
            print("Invalid INPUT");
            return 0;
        }
    }

    print("Epsilon closure for each state:");
    for (int state = 1; state <= numStates; ++state)
    {
        for (int j = 0; j < numStates; ++j)
        {
            epsilonClosure[state][j] = 0;
        }

        findClosure(state, state);

        cout << "State q" << state << ": { ";
        for (int j = 1; j <= numStates; ++j)
        {
            if (epsilonClosure[state][j])
            {
                cout << "q" << j << ", "[j != (numStates + 1)] << sp;
            }
        }
        print("}");
    }

    printGeneralTable(numStates);
    print("Thanks for using our program have a great day.");
    return 0;
}
