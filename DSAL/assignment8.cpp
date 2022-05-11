// 8
// write a cpp or java program to implement topological sorting on graph using object oriented programming features
// design necessary class. Use a graph

// 301 staff room

#include <iostream>
using namespace std;

class Queue
{
    int queue[100];
    int n = 100;
    int rear = -1;
    int front = -1;

public:
    Queue()
    {
    }

    void Insert(int val)
    {

        if (rear == n - 1)
            cout << "Queue Overflow" << endl;
        else
        {
            if (front == -1)
                front = 0;
            rear++;
            queue[rear] = val;
        }
    }
    int Delete()
    {
        if (front == -1 || front > rear)
        {
            cout << "Queue Underflow ";
            return -1;
        }
        else
        {
            return queue[front++];
        }
    }

    bool NotEmpty()
    {
        return front != -1 && front <= rear;
    }
    void Display()
    {
        if (front == -1)
            cout << "Queue is empty" << endl;
        else
        {
            cout << "Queue elements are : ";
            for (int i = front; i <= rear; i++)
                cout << queue[i] << " ";
            cout << endl;
        }
    }
};

class Graph
{

    int **matrix;
    int max_ver = 0;
    string *NodeList;
    static int index;
    int *visited;
    int *indegree;

public:
    Graph(int max_vertices)
    {

        matrix = new int *[max_vertices];
        for (int i = 0; i < max_vertices; i++)
        {
            matrix[i] = new int[max_vertices];
        }
        for (int i = 0; i < max_vertices; i++)
        {
            for (int j = 0; j < max_vertices; j++)
            {
                matrix[i][j] = 0;
            }
        }
        max_ver = max_vertices;
        NodeList = new string[max_ver];
        visited = new int[max_ver];
        indegree = new int[max_ver];
    }
    ~Graph()
    {

        for (int i = 0; i < max_ver; i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    void insertNode(string name)
    {
        if (index < max_ver)
        {
            NodeList[index++] = name;
        }
        else
        {
            cout << "No more nodes can be added" << endl;
        }
    }
    int refValuefromName(string name)
    {
        for (int i = 0; i < max_ver; i++)
        {
            if (NodeList[i] == name)
            {
                return i;
            }
        }
        return -1;
    }

    void addConnection(string name1, string name2)
    {
        int index1 = refValuefromName(name1);
        int index2 = refValuefromName(name2);
        if (index1 == -1 || index2 == -1)
        {
            if (index1 == -1)
            {
                cout << "No node named " << name1 << " found" << endl;
                return;
            }
            cout << "No node named " << name2 << " found" << endl;
        }
        matrix[index1][index2] = 1;
    }

    void indegree_calculator(Queue *q)
    {

        for (int i = 0; i < max_ver; i++)
        {
            visited[i] = 0;
            indegree[i] = 0;
            for (int j = 0; j < max_ver; j++)
            {
                if (matrix[j][i] != 0)
                    indegree[i] += 1;
            }
            if (indegree[i] == 0)
            {
                visited[i] = 1;
                q->Insert(i);
            }
        }
    }
    // using adjecency list for graph representation is always preferable since otherwise
    // you need to keep a visited list to make sure you do not queue back a node you have already printed
    // using kahns (BFS:queue) algo , can be done using DFS:stack too
    void topological_sort()
    {
        Queue q;
        int j = 0;
        indegree_calculator(&q);
        while (q.NotEmpty())
        {
            j = q.Delete();
            cout << NodeList[j] << endl;
           

            for (int m = 0; m < max_ver; m++)
            {
                if (matrix[j][m] != 0)
                    indegree[m] -= 1;
                if (indegree[m] == 0 and visited[m] == 0)
                {
                    visited[m] = 1;	// mark as visited
                    q.Insert(m);
                }
            }
        }
    }

    void printAdjacencyMatrix()
    {
        cout << "Adjacency Matrix" << endl;
        for (int i = 0; i < max_ver; i++)
        {
            for (int j = 0; j < max_ver; j++)
            {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};
int Graph::index = 0;

int main()
{
    int vertexnum;
    cout<<"Enter the number of vertices in the graph: ";
    cin>>vertexnum;
    Graph g(vertexnum);
    // these nodes can be any name too
    for(int i=0;i<vertexnum;i++)
    {
        string name;
        cout<<"Enter the name of vertex "<<i<<" : ";
        cin>>name;
        g.insertNode(name);
    }

    int choice = 0;
    while(choice!=-1)
    {
        cout<<"\n\nMENU\n\n1. Make a connection.\n2. Execute Topological sort\nEnter -1 to exit the program\n\nEnter your choice: ";
        cin>>choice;
        
        switch(choice)
        {

            case 1:
            {
                string A,B;
                cout<<"Enter the starting node: ";
                cin>>A;
                cout<<"Enter the ending node: ";
                cin>>B;
                g.addConnection(A,B);
                cout<<"Connection added!";
                break;
            }

            case 2:
            {
                g.topological_sort();
                break;
            }

            case -1:
            {
                break;
            }

            default:
            {
                cout<<"Please enter the correct choice from the menu!";
                break;
            }
        }
    }
    
    cout<<"Thank you";
    return 0;
}


/*
Testcase

6
0
1
2
3
4
5
1
5
0
1
5
3
1
3
2
1
2
1
1
4
0
1
4
1
2
-1


        5          4
        |\    /    |
        |  \/      |
        v   0      V
        2 -> 3 -> 1


*/
