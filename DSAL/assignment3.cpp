//NO USE OF IMPLICIT OR EXPLIXIT STACK IN THE PROGRAM

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Node
{
public:
    int data;
    Node *lchild;
    Node *rchild;
    bool lbit,rbit;

    //constructor
    Node()
    {
        data = 0;
        lbit = false;
        rbit = false;
    }
};

// Queue class to facilitate input to the Binary tree
class Queue
{
private:
    int front;
    int rear;
    int size;
    Node **Q;

public:
    Queue()
    {
        front = rear = -1;
        size = 10;
        Q = new Node *[size];
    }
    Queue(int size)
    {
        front = rear = -1;
        this->size = size;
        Q = new Node *[size];
    }
    void enqueue(Node *x);
    Node *dequeue();
    int isEmpty()
    {return front == rear;}
};

// function to enqueue a pointer in the queue
void Queue::enqueue(Node *x)
{
    if (rear == size - 1)
        printf("Queue Full\n");
    else
    {
        rear++;
        Q[rear] = x;
    }
}

//function to dequeue a pointer in the queue
Node *Queue::dequeue()
{
    Node *x = NULL;
    if (front == rear)
        printf("Queue is Empty\n");
    else
    {
        x = Q[front + 1];
        front++;
    }
    return x;
}

class TBT
{
public:
    Node *header;
    TBT() // default constructor
    {
        createTree();
        return;
    }

    void createTree();
    void InorderTraversal(Node *);
    void PreorderTraversal(Node *);
};

void TBT ::createTree()
{
    // intro();
    Queue q(100);
    Node *p;
    int x;

    // creating header node
    header = new Node;
    // creating root node
    Node *temp = new Node;
    header->lchild = temp;
    header->lbit = true;
    header->rbit = true;
    cout << "Enter the value of the root node: ";
    cin >> temp->data;
    cout<<endl;
    temp->lchild = header;
    temp->rchild = header;
    q.enqueue(temp);
    header->data++;

    // creating the rest of the tree
    while (!q.isEmpty())
    {
        p = q.dequeue();
        cout << "Enter left child of " << p->data << " : ";
        cin >> x;
        // algorithm for left node
        if (x != -1)
        {
            temp = new Node;
            temp->data = x;
            temp->lchild = p->lchild;
            temp->rchild = p;
            p->lchild = temp;
            p->lbit = true;
            q.enqueue(temp);
            header->data++;
        }
        cout << "Enter right child of " << p->data << " : ";
        cin >> x;
        // algorithm for right node
        if (x != -1)
        {
            temp = new Node;
            temp->data = x;
            temp->lchild = p;
            temp->rchild = p->rchild;
            p->rchild = temp;
            p->rbit = true;
            q.enqueue(temp);
            header->data++;
        }
        cout<<endl;
    }
    cout << "The total number of nodes in the TBT is: " << header->data << endl;
    return;
}

void TBT ::InorderTraversal(Node *p)
{
    int count = header->data;
    p = p->lchild;
    while (p != header)
    {
        while (p->lbit)
        {
            p = p->lchild;
        }
        cout << p->data << ", ";
        count--;
        if (p->rbit)
        {
            p = p->rchild;
            continue;
        }
        else
        {
            while (!p->rbit && p->rchild != header)
            {
                p = p->rchild;
                cout << p->data << ", ";
                count--;
            }
            p = p->rchild;
        }
    }
    return;
}

void TBT :: PreorderTraversal(Node *p)
{
    int count = header->data;
    p = p->lchild;
    cout<< p->data << ", ";
    count--;
    while (p != header)
    {
        while (p->lbit)
        {
            p = p->lchild;
            cout << p->data << ", ";
            count--; 
        }
        if (p->rbit)
        {
            p = p->rchild;
            cout << p->data << ", ";
            count--;
            
            continue;
        }
        else
        {
            while (!p->rbit && p->rchild != header)
            {
                p = p->rchild;
            }
            p = p->rchild;
            if(p!=header)
            {
                cout << p->data << ", ";
                count--;
            }
        }
    }
    return;
}

int main()
{
    TBT t1;
    int opt = 0;
    while (opt != -1)
    {
        cout << "\n\n\t\t**************MENU***************\n\n";
        cout << "1. Inorder Traversal\n2.Preorder Traversal\n-1 to Exit\n\n";
        cout << "Enter your choice: ";
        cin >> opt;
        switch (opt)
        {
        case 1:
        {
            cout << "Inorder traversal is - [";
            t1.InorderTraversal(t1.header);
            cout << "\b\b]";
            break;
        }

        case 2:
        {
            cout << "Preorder traversal is -[";
            t1.PreorderTraversal(t1.header);
            cout<<"\b\b]";
            break;
        }

        case -1:
        {
            break;
        }

        default:
        {
            cout << "Please enter the correct option!" << endl;
            break;
        }
        }
    }
    cout << "Thank you!";
    return 0;
}

/*
6
0
10
-1
1
8
-1
-1
4
7
9
3
5
-1
-1
-1
-1
2
-1
-1
-1
-1
-1
*/