//
// Created by beans on 2017/12/21.
//
//

#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <iomanip>
#include <cmath>
#include <sstream>
#include "Priority_Queue_BinaryHeap.h"

using namespace std;

const int Max_Distance = 100;
class Graph_SP{
private:
    int num_vertex;
    vector<list<pair<int,int>>> AdjList;
    vector<int> predecessor, distance;
    vector<bool> visited;
public:
    Graph_SP():num_vertex(0){};
    Graph_SP(int n):num_vertex(n){
        AdjList.resize(num_vertex);
    }
    void AddEdge(int from, int to, int weight);
    void PrintDataArray(vector<int> array);
    void PrintIntArray(int *array);

    void InitializeSingleSource(int Start);     // Start as root
    void Relax(int X, int Y, int weight);       // from X to Y

    void Dijkstra(int Start = 0);
    friend class BinaryHeap;
};
void Graph_SP::Dijkstra(int Start){

    InitializeSingleSource(Start);

    BinaryHeap minQueue(num_vertex);   // object of min queue
    minQueue.BuildMinHeap(distance);

    visited.resize(num_vertex, false);   // initializa visited[] as {0,0,0,...,0}

    while (!minQueue.IsHeapEmpty()) {
        int u = minQueue.ExtractMin();
        for (list<pair<int, int>>::iterator itr = AdjList[u].begin();
             itr != AdjList[u].end(); itr++) {
            Relax(u, (*itr).first, (*itr).second);
            minQueue.DecreaseKey((*itr).first, distance[(*itr).first]);
        }

    }
    cout << "final res:\n\n";
    cout << "print predecessor:\n";
    PrintDataArray(predecessor);
    cout << "\nprint distance:\n";
    PrintDataArray(distance);
    cout  << "*********************************\n\n";

}
void Graph_SP::InitializeSingleSource(int Start){

    distance.resize(num_vertex);
    predecessor.resize(num_vertex);

    for (int i = 0; i < num_vertex; i++) {
        distance[i] = Max_Distance;
        predecessor[i] = -1;
    }
    distance[Start] = 0;
}
void Graph_SP::Relax(int from, int to, int weight){

    if (distance[to] > distance[from] + weight) {
        distance[to] = distance[from] + weight;
        if( predecessor[to] == -1)
           printf("includeing vertex: %d\n\n",to);

        predecessor[to] = from;
        cout << "print predecessor:\n";
        PrintDataArray(predecessor);
        cout << "\nprint distance:\n";
        PrintDataArray(distance);
        cout  << "*********************************\n\n";
    }
}
void Graph_SP::AddEdge(int from, int to, int weight){//// directed graph!!!!!!!!!!

    AdjList[from].push_back(make_pair(to,weight));
}
void Graph_SP::PrintDataArray(vector<int> array){
    for (int i = 0; i < num_vertex; i++)
        cout << setw(4) << i;
    cout << endl;
    for (int i = 0; i < num_vertex; i++)
        cout << setw(4) << array[i];
    cout << endl;
}
int main(){

    stringstream ss;
    string s;
    int numOfVertex,tmp,cntVertex = 0;
    cin >> numOfVertex;
    Graph_SP g9(numOfVertex);
    getline(cin,s);
    while(getline(cin,s)){
        cout  << s <<endl;
        ss.clear();
        ss << s;
        for(int i = 0;i<numOfVertex;i++){
            ss >> tmp;
            if(tmp!=Max_Distance&&tmp!=0) {
                printf("AddEdge(%d, %d, %d)\n",cntVertex, i, tmp);
                g9.AddEdge(cntVertex, i, tmp);
            }
        }
        if(cntVertex == numOfVertex -1)
            break;
        cntVertex++;
    }
    cout  << "*********************************\n\n";
        /*
    Graph_SP g9(7);
    g9.AddEdge(0,1,5);g9.AddEdge(0,4,4);g9.AddEdge(0,5,8);
    g9.AddEdge(1,2,7);
    g9.AddEdge(2,3,9);g9.AddEdge(2,4,5);g9.AddEdge(2,5,12);
    g9.AddEdge(3,6,6);
    g9.AddEdge(4,6,11);
    g9.AddEdge(5,6,10);
         */


    g9.Dijkstra(0);

    return 0;
}