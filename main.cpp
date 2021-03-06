#include <bits/stdc++.h>

using namespace std;

const int V = 248; 

struct station_code
{
    string station_name;
    int code;
};
struct station_code station[V];
float graph[V][V];

struct node1
{
    vector<float> p;
} P[V];

string capitalize(string str)
{
    for (int i = 0; i < str.length(); ++i)
    {
        if (str[i] > 96 && str[i] < 123)
            str[i] = str[i] - 32;
    }
    return str;
}

void Path(float distance, int e, int st, int inter);
int distance_min(float distance[], bool visited[]);
void dijkstra(float graph[V][V], int src, int targ);
void take_input();

int main()
{
    int temp, n1, n2;
    float dis;
    ifstream fin;
    ifstream code;
    code.open("citiesname.txt");
    fin.open("distvalues.txt");
    for (int i = 0; i < 248; ++i)
    {
        for (int j = 0; j < 248; ++j)
            graph[i][j] = 0;
    }
    for (int i = 1; i <= V; ++i)
    {
        fin >> temp;
        fin >> n1;
        for (int j = 0; j < temp; ++j)
        {
            fin >> n2;
            fin >> dis;
            graph[n1 - 1][n2 - 1] = dis;
        }
    }

    string line, col;
    for (int i = 0; i < V; ++i)
    {
        getline(code, line);
        station[i].code = i;
        station[i].station_name = line;
    }
    take_input();
    code.close();
    fin.close();
}

int j;

void Path(float dis, int dest, int st, int inter)
{
    int t = dest, s;
    static float distance = 0;
    distance += dis;

    cout << "THE SHORTEST PATH IS : ";

    static int pos_x = 12;
    static int pos_y = 15;
    vector<int> path;
    path.push_back(t);
    while (t != st)
    {
        s = P[t].p.size();
        t = P[t].p[s - 1];
        path.push_back(t);
    }
    vector<int>::iterator i = path.end();
    string str;
    if (!inter)
    {
        cout << "****** ROUTE FOUND ******";
    }
    vector<int>::iterator i2 = path.end();
    i2--;
    int n_of_stations = 0;
    while (i != path.begin())
    {
        i--;
        str = station[*i].station_name;
        if (pos_x + 5 + str.size() < 106)
        {

            cout << " ->> " << str;
        }
        else
        {

            cout << " ->> " << str;
        }
    }

    if (inter)
    {
    }

    if (inter)
    {

        cout << "\nWANT TO SEARCH AGAIN ?  ";
        string choice;

        cin >> choice;
        choice = capitalize(choice);
        if (choice == "Y" || choice == "YES")
        {
            take_input();
        }
        char ch;
        scanf("%c", &ch);
        cout << endl;
    }
    return;
}

int distance_min(float distance[], bool visited[])
{
    float min = INT_MAX;
    int min_index;

    for (int v = 0; v < V; v++)
        if (visited[v] == false && distance[v] <= min)
            min = distance[v], min_index = v;

    return min_index;
}

void dijkstra(float graph[V][V], int src, int targ, int inter)
{
    float distance[V];
    bool visited[V];
    for (int i = 0; i < V; i++) 
        distance[i] = INT_MAX, visited[i] = false;
    distance[src] = 0;
    for (int count = 0; count < V - 1; count++)
    {
        int u = distance_min(distance, visited);
        visited[u] = true;
        for (int v = 0; v < V; v++)
            if (!visited[v] && graph[u][v] && distance[u] != INT_MAX && distance[u] + graph[u][v] < distance[v])
            {
                distance[v] = distance[u] + graph[u][v];
                P[v].p.push_back(u);
            }
    }
    Path(distance[targ], targ, src, inter);
}

void take_input()
{
    char ch;
    string startStation, endStation, line, col;
    int startcode, endcode;
    cout << "ENTER THE STARTING POINT:";

    getline(cin, startStation);
    cout << "ENTER THE DESTINATION POINT:";
    getline(cin, endStation);

    startStation = capitalize(startStation);
    endStation = capitalize(endStation);

    int flag_start = 0, flag_end = 0;

    for (int i = 0; i < 248; i++)
    {
        if (station[i].station_name == startStation)
        {
            startcode = station[i].code;
            flag_start = 1;
        }
        if (station[i].station_name == endStation)
        {
            endcode = station[i].code;
            flag_end = 1;
        }
    }
    int fault = 0;
    if (flag_start == 0)
    {
        cout << "WRONG STARTING STATION NAME ENTERED";
        fault = 1;
    }
    if (flag_end == 0)
    {
        cout << "WRONG DESTINATION STATION NAME ENTERED";
        fault = 1;
    }

    scanf("%c", &ch);
    if (fault)
    {
        take_input();
        return;
    }

    dijkstra(graph, startcode, endcode, 1);
}