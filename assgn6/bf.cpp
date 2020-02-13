#include <iostream>
#include <stdint.h>
#include <map>
using namespace std;

int main()
{
    int vertices;
    int edges;
    int edge_array[edges][2];
    int vertex1;
    int vertex2;
    int source;
    int flag;
    string city;
    map<int, string> citymap;

    cout << "Enter the number of cities" << endl;
    cin >> vertices;

    for (int i = 0; i < vertices; i++)
    {
        cout << "Enter the name of the city" << endl;
        cin >> city;
        citymap[i] = city;
    }

    int adj[vertices][vertices]; //USING ADJACENCY MATRIX

    for (int i = 0; i < vertices; i++)
        for (int j = 0; j < vertices; j++)
            adj[i][j] = 0; //INITIALISATION OF ADJACENCY MATRIX

    int dist[vertices];       //DISTANCE OF VERTICES FROM SOURCE
    int path[vertices] = {0}; //PATH ARRAY TO DISPLAY SHORTEST PATH

    cout << "Enter the number of edges" << endl;
    cin >> edges;

    for (int i = 0; i < edges; i++)
    {
        cout << "Enter vertice 1" << endl;
        cin >> vertex1;
        cout << "Enter vertice 2" << endl;
        cin >> vertex2;
        cout << "Enter the length of edge " << vertex1 << " " << vertex2 << endl;
        cin >> adj[vertex1][vertex2];
        adj[vertex2][vertex1] = adj[vertex1][vertex2];
        edge_array[i][0] = vertex1; //INITIALISE EDGE ARRAY
        edge_array[i][1] = vertex2;
    }

    // cout << "ADJACENCY MATRIX" << endl;
    // for (int i = 0; i < vertices; i++)
    // {
    //     for (int j = 0; j < vertices; j++)
    //     {
    //         cout << adj[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    cout << "Enter the source vertex" << endl;
    cin >> source;

    for (int i = 0; i < vertices; i++)
        dist[i] = INT32_MAX;

    dist[source] = 0;

    cout << "SRRAY AFTER SOURCE" << endl;

    for (int i = 0; i < vertices; i++)
        cout << dist[i] << " ";

    cout << endl;
    for (int i = 0; i < vertices - 1; i++)
    {
        for (int j = 0; j < edges; j++)
        {
            if (dist[edge_array[j][0]] != INT32_MAX)
            {
                if (dist[edge_array[j][0]] + adj[edge_array[j][0]][edge_array[j][1]] < dist[edge_array[j][1]])
                {
                    flag = 1;
                    dist[edge_array[j][1]] = dist[edge_array[j][0]] + adj[edge_array[j][0]][edge_array[j][1]];
                    path[edge_array[j][1]] = edge_array[j][0];
                }
            }
        }
        // if (flag == 0)
        //     break;
    }

    // for (int i = 0; i < edges; i++)
    // {
    //     if (dist[edge_array[i][0]] + adj[edge_array[i][0]][edge_array[i][1]] < dist[edge_array[i][1]])
    //     {
    //         flag = 0;
    //         dist[edge_array[i][1]] = dist[edge_array[i][0]] + adj[edge_array[i][0]][edge_array[i][1]];
    //     }
    // }
    // if (flag == 0)
    //     cout << "ERROR: NO SHORTEST PATH AVAILABLE" << endl;

    cout << "THE SHORTEST DISTANCES FOR VERTICES ARE:-" << endl;
    for (int i = 0; i < vertices; i++)
    {
        if (i == source)
            cout << dist[i] << " ";
        else
            cout << dist[i] << " ";
    }
    // for (int i = 0; i < vertices; i++)
    // {
    //     if (dist[i] == INT32_MAX)
    //         cout << "Vertex " << i << " not reachable" << endl;
    // }

    // cout << "Path" << endl;
}