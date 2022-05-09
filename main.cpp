#include <iostream>
#include <limits.h>
#include <string>
#include <math.h>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <time.h>
#include <windows.h>
#include <conio.h>

using namespace std;

const int V=248;   //no of stations
COORD coord;        //for goto

struct station_code
{
    string station_name;
    int code;
    string color;
};
struct station_code station[V];
float graph[V][V];

struct node1
    {
        vector <float>p;
    }P[V];

string capitalize(string str)
{
    for(int i=0;i<str.length();++i)
    {
        if(str[i]>96&&str[i]<123)
            str[i]=str[i]-32;
    }
    return str;
}

void createbox(int, int, int, int, int);
void window2();
void clrscreen();
void delay(unsigned int ms);
void go_x_y(int x,int y);
int timeconsumed(float distance);
int cost(float distance);
void Path(float distance,int e,int st,int inter);
int distance_min(float distance[], bool visited[]);
void dijkstra(float graph[V][V], int src,int targ);
void take_input();
void dmrc(int x, int y);
void intro();
void initialize();

int main()
{
           int x,num;
           while(1)
           {
                    system("cls");
                    cout<<"\t\t   |================================|";
                    cout<<"\n\t\t\tCUSTOMIZED TRAVEL PLANNER";
                    cout<<"\n\t\t   |================================|";
                    cout<<"\nUSE:\n1.Shortest Path\n2.Plan Journey\n3.Feedback/Ratings\n4.Exit";
                    cout<<"\nEnter your choice:";
                    cin>>x;
                    switch(x)
                    {
                               case 1://shortest_path();
                                            initialize();
                                            break;
                               case 2://shortest_path();
                                            while(1)
                                            {
                                                       system("cls");
                                                       cout<<"Choose your preference:\n1.Time-Effective\n2.Cost-Effective\n3.Exit";
                                                       cout<<"\nEnter your choice:";
                                                       cin>>num;
                                                       switch(num)
                                                       {
                                                                  case 1://time_effective(); 
                                                                               break;
                                                                  case 2://cost_effective();
                                                                               break;
                                                                  case 3://exit_program();
                                                                               break;
                                                                  default:cout<<"Please enter a valid number!!";
                                                       }
                                                       getch();
                                            }
                                            break;
                               case 3://feedback();
                                            break;
                               case 4://exit_program();
                                            break;
                               default:cout<<"Please enter a valid number!!";
                    }
                    getch();
           }
        initialize();
           return 0;
}

void initialize(){
    // GRAPH construction
    int temp,n1,n2; 
    float dis;
    ifstream fin;
    ifstream code;
    ifstream color;
    code.open("stationname.txt");
    color.open("colorcodes.txt");
    fin.open("distvalues.txt");
    for(int i=0;i<248;++i)
    {
       for(int j=0;j<248;++j)
        graph[i][j]=0;
    }
    for(int i=1;i<=V;++i)
    {
        fin>>temp;
        fin>>n1;
        for( int j=0;j<temp;++j)
        {
           fin>>n2;
           fin>>dis;
           //cout<<" "<<n2<<" "<<dis<<endl;
           graph[n1-1][n2-1]=dis;
        }
        //cout<<endl;
    }
    //filing structure info
        string line,col;
        for(int i=0;i<V;++i)
        {
            getline(color,col);
            station[i].color=col;
            getline(code, line);
            station[i].code=i;
            station[i].station_name=line;
        }
        intro();
}

void clrscreen()
{
    system("cls");
    createbox(1,0,117,29,0);
}

void delay(unsigned int msec)
{
    clock_t time = msec + clock();
    while( time > clock() );        //loop makes the delay(presentation)
}

void go_x_y(int a,int b)
{
  coord.X = a;
  coord.Y = b;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void createbox(int x1, int y1, int x2, int y2, int d)
{
    go_x_y(x1,y2);
    printf("+");
    go_x_y(x2,y1);
    printf("+");
    int j;
    for(j=1;j<y2-y1;++j)
        {
            go_x_y(x2,y1+j);
            printf("|");
            delay(d);
            go_x_y(x1,y2-j);
            printf("|");
            delay(d);
        }
    go_x_y(x1,y1);
    printf("+");
    delay(d);
    go_x_y(x2,y2);
    printf("+");
    delay(d);
    int i;
    for(i=1;i<x2-x1;i++)
        {   go_x_y(x1+i,y1);
            printf("-");
            delay(d);
            go_x_y(x2-i,y2);
            printf("-");
            delay(d);
        }
}

void Path(float dis,int dest,int st,int inter)
{
    int t=dest,s;
    static float distance=0;
    distance+=dis;

    go_x_y(16,11);
    cout<<"THE SHORTEST PATH IS : ";

    static int pos_x=12;
    static int pos_y=15;
    vector <int> path;
    path.push_back(t);
    while(t!=st)
    {
        s=P[t].p.size();
        t=P[t].p[s-1];
        path.push_back(t);
    }
    vector <int>::iterator i=path.end();
    string str;
    string color;
    if(!inter){
    go_x_y(42,13);
    cout<<"****** ROUTE FOUND ******";
    }
    vector<int>::iterator i2=path.end();
    i2--;
    //int n_of_stations=0;
    while(i!=path.begin())
    {
        i--;
        color=station[*i].color;
        if(color=="BLUE")
            system("color 09");
        else if(color=="PINK")
            system("color 0D");
        else if(color=="YELLOW")
            system("color 06");
        else if(color=="AQUA")
            system("color 03");
        else if(color=="RED")
            system("color 04");
        else if(color=="GREEN")
            system("color 02");
        else if(color=="ORANGE")
            system("color 0C");
        else if(color=="MAGENTA")
            system("color 05");
        else if(color=="VOILET")
            system("color 01");


        if(i!=i2)
        {
        if(station[*(i2)].color!=station[*(i)].color)
        {
            pos_x=8;
            pos_y++;
            go_x_y(pos_x,pos_y);
            cout<<"{change from "<<station[*i2].color<<" to "<<station[*i].color<<"}";
            pos_x=12;
            pos_y++;
            go_x_y(pos_x,pos_y);
        }
        i2--;
        }
        str=station[*i].station_name;
        if(pos_x+5+str.size()<106)
        {
            go_x_y(pos_x,pos_y);
            cout<<" ->> "<<str;
            pos_x=pos_x+str.size()+5;
        }
        else
        {
            pos_x=12;
            pos_y++;
            go_x_y(pos_x,pos_y);
            cout<<" ->> "<<str;
            pos_x=pos_x+str.size()+5;
        }
        //n_of_stations++;
        delay(700);
    }
    if(inter){
    delay(2500);
    go_x_y(44,9);
    cout<<"WANT TO SEARCH AGAIN ?  ";
    string choice;
    pos_x=12; pos_y=15;
    cin>>choice;
    choice=capitalize(choice);
    if(choice=="Y"||choice=="YES")
        window2();
    go_x_y(5,30);
    char ch;
    scanf("%c",&ch);
    cout<<endl;
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

void dijkstra(float graph[V][V], int src,int targ,int inter)
{
     float distance[V];
     bool visited[V];
     for (int i = 0; i < V; i++)        //initilization
        distance[i] = INT_MAX, visited[i] = false;
     distance[src] = 0;
     for (int count = 0; count < V-1; count++)
     {
         int u = distance_min(distance, visited);
       visited[u] = true;
       for (int v = 0; v < V; v++)
         if (!visited[v] && graph[u][v] && distance[u] != INT_MAX
                                       && distance[u]+graph[u][v] < distance[v])
            {
                distance[v] = distance[u] + graph[u][v];
                P[v].p.push_back(u);
            }
    }
    Path(distance[targ],targ,src,inter);
}

void take_input()
{
        char ch;
        //scanf("%c",&ch);
        string startStation,endStation,line,col;
        int startcode,endcode;
        go_x_y(16,3);
        cout<<"ENTER THE STARTING POINT:";
        go_x_y(20,5);
    
        getline(cin,startStation);
        go_x_y(72,3);
        cout<<"ENTER THE DESTINATION POINT:";
        go_x_y(76,5);
        getline(cin,endStation);
        go_x_y(42,6);


        startStation=capitalize(startStation);
        endStation=capitalize(endStation);

        int flag_start=0,flag_end=0;

        for(int i=0;i<248;i++)
        {
            if(station[i].station_name==startStation)
            {
                startcode=station[i].code;
                flag_start=1;
            }
            if(station[i].station_name==endStation)
            {
                endcode=station[i].code;
                flag_end=1;
            }
        }
        int fault=0;
        if(flag_start==0)
        {
            go_x_y(42,10);
            cout<<"WRONG STARTING STATION NAME ENTERED";
            fault=1;
        }
        if(flag_end==0)
        {
            go_x_y(40,11);
            cout<<"WRONG DESTINATION STATION NAME ENTERED";
            fault=1;
        }

        scanf("%c",&ch);
        if(fault)
        {
          window2();
          return;
        }

        dijkstra(graph, startcode,endcode,1);
}

void dmrc(int x, int y)
{
    go_x_y(x,y);
    printf("   ___                     ___       ____");
    go_x_y(x,y+1);
    printf(" ||   \\\\   ||\\\\    //||  ||   \\\\   //    \\\\");
    go_x_y(x,y+2);
    printf(" ||    ||  || \\\\  // ||  ||    || ||");
    go_x_y(x,y+3);
    printf(" ||    ||  ||  \\\\//  ||  ||___//  ||");
    go_x_y(x,y+4);
    printf(" ||    ||  ||        ||  ||  \\\\   ||");
    go_x_y(x,y+5);
    printf(" ||___//   ||        ||  ||   \\\\   \\\\____//");
    }

void window2()
{
    clrscreen();
    go_x_y(48,19);
    system("color 0C");
    delay(90);
    take_input();
}

void intro(){

    system("color 0A");
    createbox(1,0,117,29,4);
    system("color 0C");
    delay(90);
    system("color 0A");
    delay(90);
    dmrc(37,4);
    system("color 0C");
    delay(90);
    createbox(30,3,87,11,4);
    createbox(28,2,89,12,4);
    system("color 0C");
    delay(90);
    system("color 0A");
    delay(90);
    go_x_y(42,14);
    cout<<"WELCOME TO DELHI METRO";
    system("color 0C");
    delay(90);
    system("color 0D");
    delay(90);
    go_x_y(47,18);
    printf("PRESS ENTER TO CONTINUE");
    char ch;
    scanf("%c",&ch);
    window2();
}