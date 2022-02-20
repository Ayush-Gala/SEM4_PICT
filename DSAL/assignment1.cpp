/*
                                        PROBLEM STATEMENT

Beginning with an empty binary BT, Construct binary BT by inserting the values in the order given. After constructing a binary BT perform following operations on it-

1.Perform inorder /preorder and post order traversal
2.Change a BT so that the roles of the left and right pointers are swapped at every node
3.Find the height of BT
4.Copy this BT to another [operator=]
5.Count number of leaves, number of internal nodes. 
6.Erase all nodes in a binary BT.
(implement both recursive and non-recursive methods)

*/

#include <bits/stdc++.h>
using namespace std;

//class for implementing a node
class Node
{
public:
    int data;
    Node *lchild; //pointer to left child of node
    Node *rchild;

    Node()
    {
        lchild = nullptr;
        rchild = nullptr;
    }
};

//class for implementing stack using LL
class Stack
{
private:
    int size;
    int top;
    Node **S;

public:
    // default constructor
    Stack()
    {
        size = 100;
        top = -1;
        S = new Node *[100];
    }

    //pushing into stack
    void push(Node *x)
    {
        if (top == size - 1)
        {
            cin.clear();
            cout << "Stack Overflow" << endl;
            return;
        }
        else
        {
            top++;
            S[top] = x;
        }
    }

    //popping from stack
    Node *pop()
    {
        Node *x;
        if (top == -1)
        {
            cout << "Stack UnderFlow" << endl;
        }
        else
        {
            x = S[top--];
        }
        return x;
    }

    // function that returns if stack is empty or not
    int isEmpty()
    {
        if (top == -1)
            return 1;
        return 0;
    }

    //function for peeking into the top element of the stack
    Node *peek()
    {
        if (isEmpty())
        {
            return nullptr;
        }
        return S[top];
    }
};

//class for implementing Queue using LL
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
    int isEmpty() { return front == rear; }
};

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

class Tree
{
public:
    Node *root;
    Tree()
    {
        root = nullptr;
    }
    void CreateTree();
    void Inorder(Node *p);
    void IInorder(Node *root);
    void Preorder(Node *p);
    void IPreorder(Node *root);
    void Postorder(Node *p);
    void IPostorder(Node *root);
    int Height(Node *root);
    int internalNodes(Node *root);
    int externalNodes(Node *root);
    void delete_tree(Node *root);
    Node *copy_tree(Node *root1, Node* root2);
    void swap_nodes(Node *root);
};

void Tree::CreateTree()
{

    Node *p, *t;
    int x;
    Queue q(100);
    cout << "Enter the root value : ";
    cin >> x;
    root = new Node;
    root->data = x;
    root->lchild = root->rchild = nullptr;
    q.enqueue(root);

    while (!q.isEmpty())
    {
        p = q.dequeue();
        cout << "Enter left child of " << p->data << " : ";
        cin >> x;
        if (x != -1)
        {
            t = new Node;
            t->data = x;
            t->lchild = t->rchild = nullptr;
            p->lchild = t;
            q.enqueue(t);
        }
        cout << "Enter right child of " << p->data << " : ";
        cin >> x;
        if (x != -1)
        {
            t = new Node;
            t->data = x;
            t->lchild = t->rchild = NULL;
            p->rchild = t;
            q.enqueue(t);
        }
    }
}

void Tree ::IPostorder(Node *t)
{
    Node *temp; //garbage variable
    Stack stk;
    cout << "[ ";
    while (t || !stk.isEmpty())
    {
        while (t)
        {
            if (t->rchild != nullptr)
            {
                stk.push(t->rchild);
            }
            stk.push(t);
            t = t->lchild;
        }

        if (t)
        {
            stk.push(t);
            t = t->lchild;
        }

        t = stk.pop();

        if (t->rchild != nullptr && stk.peek() == t->rchild)
        {
            temp = stk.pop();
            stk.push(t);
            t = t->rchild;
        }
        else
        {
            cout << t->data << " ";
        }
    }

    cout << " ]" << endl;
}

void Tree::IInorder(Node *p)
{
    Stack stk;
    cout << "[";
    while (p || !stk.isEmpty())
    {
        if (p)
        {

            stk.push(p);
            p = p->lchild;
        }
        else
        {
            p = stk.pop();
            cout << p->data << " ";
            p = p->rchild;
        }
    }
    cout << "]";
}

void Tree::IPreorder(Node *p)
{
    Stack stk;
    cout << "[";
    while (p || !stk.isEmpty())
    {
        if (p)
        {
            cout << p->data << " ";
            stk.push(p);
            p = p->lchild;
        }
        else
        {
            p = stk.pop();
            p = p->rchild;
        }
    }
    cout << "]";
}

void Tree::Preorder(Node *p)
{
    if (p)
    {

        cout << p->data << " ";
        Preorder(p->lchild);
        Preorder(p->rchild);
    }
}

void Tree::Inorder(Node *p)
{
    if (p)
    {

        Inorder(p->lchild);
        cout << p->data << " ";
        Inorder(p->rchild);
    }
}

void Tree::Postorder(Node *p)
{
    if (p!=nullptr)
    {
        Postorder(p->lchild);
        Postorder(p->rchild);
        cout << p->data << " ";
    }
    return;
}

int Tree::Height(Node *root)
{
    int x = 0, y = 0;
    if (root == 0)
    {
        return 0;
    }
    x = Height(root->lchild);
    y = Height(root->rchild);
    if (x > y)
        return x + 1;
    else
        return y + 1;
}

int Tree ::internalNodes(Node *p)
{
    int x, y;
    if (p)
    {
        x = internalNodes(p->lchild);
        y = internalNodes(p->rchild);
        if (p->lchild || p->rchild)
            return x + y + 1;
        else
        {
            return x + y;
        }
    }
    return 0;
}

int Tree ::externalNodes(Node *p)
{
    int x, y;
    if (p)
    {
        x = externalNodes(p->lchild);
        y = externalNodes(p->rchild);
        if (!p->lchild && !p->rchild)
            return x + y + 1;
        else
        {
            return x + y;
        }
    }
    return 0;
}

//recursive function to delete the tree
void Tree ::delete_tree(Node *p)
{
    if (p == nullptr)
    {
        return;
    }
    else
    {
        delete_tree(p->lchild);
        delete_tree(p->rchild);
        cout << "\nDeleting nodes : " << p->data;
        p->lchild = nullptr;
        p->rchild = nullptr;
        delete p;
        return;
    }
}

//function to swap nodes
void Tree ::swap_nodes(Node *p)
{
    if (p == NULL)
    {
        return;
    }
    else
    {
        Node *temp;
        swap_nodes(p->lchild);
        swap_nodes(p->rchild);
        temp = p->lchild;
        p->lchild = p->rchild;
        p->rchild = temp;
    }
}

//function to copy tree recursively
Node *Tree ::copy_tree(Node *t, Node *p)
{
    if (t == NULL)
    {
        return NULL;
    }
    else
    {
        p = new Node;
        p->data = t->data;
        p->lchild = copy_tree(t->lchild, p->lchild);
        p->rchild = copy_tree(t->rchild, p->rchild);
        return p;
    }
}

//main part of the program
int main()
{
    Tree t, copy;
    bool copy_created = false, use_copy = false;
    int opt, opt1;
    char ans;
    t.CreateTree();
    do
    {   
        if(copy_created)
        {
            cout<<"Do you want to use the copied tree (y/n): ";
            cin>>ans;
            if(ans == 'y')
            {
                use_copy = true;
            }
            else{use_copy = false;}
        }
        cout << "\n\n<------Menu ------>" << endl;
        cout << "1. Inorder Traversal\n2. Preorder Traversal\n3. Postorder Traversal\n4. Height of Tree\n5. Number of Leaf/External nodes\n6. Number of Internal Nodes\n7. Delete Tree\n8. Swap Nodes\n9. Copy Tree" << endl;
        cout << "Enter option : ";
        cin >> opt;
        switch (opt)
        {
        // Case for inorder traversal
        case 1:
            cout << "\n\nBy which method you wish to perform Inorder Traversal\n1. Iterative\n2. Recursive\n"
                 << endl;
            cout << "Enter Option : ";
            cin >> opt1;
            switch (opt1)
            {
            case 1:
                cout << "The Inorder Traversal of the generated Binary tree through Iterative method is : ";
                if(use_copy)
                {copy.IInorder(copy.root);}
                else{t.IInorder(t.root);}
                break;
            case 2:
                cout << "The Inorder Traversal of the generated Binary tree through Recursive method is : [ ";
                if(use_copy){copy.Inorder(copy.root);}
                else{t.Inorder(t.root);}
                cout << "]";
                break;
            default:
                cout << "Wrong option entered!" << endl;
            }
            break;
        // Case for Preorder traversal
        case 2:
            cout << "\n\nBy which method you wish to perform Preorder Traversal\n1. Iterative\n2. Recursive" << endl;
            cout << "Enter Option : ";
            cin >> opt1;
            switch (opt1)
            {
            case 1:
                cout << "The Preorder Traversal of the generated Binary tree through Iterative method is : ";
                if(!use_copy)
                {t.IPreorder(t.root);}
                else{copy.IPreorder(copy.root);}
                break;
            case 2:
                cout << "The Preorder Traversal of the generated Binary tree through Recursive method is : [ ";
                if(!use_copy)
                {t.Preorder(t.root);}
                else{copy.Preorder(copy.root);}
                cout << "]";
                break;
            default:
                cout << "Wrong option entered!" << endl;
            }
            break;

        // Case for postorder traversal
        case 3:
            cout << "\n\nBy which method you wish to perform Postorder Traversal\n1. Iterative\n2. Recursive" << endl;
            cout << "Enter Option : ";
            cin >> opt1;
            switch (opt1)
            {
            case 1:
                cout << "The Postorder Traversal of the generated Binary tree through Iterative method is : ";
                if(!use_copy)
                {t.Postorder(t.root);}
                else{copy.Postorder(copy.root);}
                break;
            case 2:
                cout << "The Postorder Traversal of the generated Binary tree through Recursive method is : [ ";
                if(!use_copy)
                {t.Postorder(t.root);}
                else{copy.Postorder(copy.root);}
                cout << "]";
                break;
            default:
                cout << "Wrong option entered!" << endl;
            }
            break;

        //To print the height of a Binary tree
        case 4:
            cout << "The Height of the Generated Binary Tree is : ";
            if(!use_copy)
            {cout << t.Height(t.root);}
            else
            {cout<<copy.Height(copy.root);}
            break;

        // To print no of external nodes
        case 5:
            cout << "The number of Leaf/External nodes is : ";
            if(!use_copy)
            {cout << t.externalNodes(t.root);}
            else{cout<<copy.externalNodes(copy.root);}
            break;

        // To print number of internal nodes
        case 6:
            cout << "The number of Internal nodes is : ";
            if(!use_copy)
            {cout << t.internalNodes(t.root);}
            else{cout<<copy.internalNodes(copy.root);}
            break;

        // Case to delete the entire tree
        case 7:
            t.delete_tree(t.root);
            t.root = nullptr;
            cout << "\n ------------------------ Tree Successfully Deleted ------------------------";
            break;

        //Case to swap all left and right nodes
        case 8:
            if(!use_copy)
            {t.swap_nodes(t.root);}
            else{copy.swap_nodes(copy.root);}
            cout << "\n ------------------------ NODES SWAPPED SUCCESSFULLY -----------------------";
            break;

        // Case to copy the tree
        case 9:
            if(!use_copy)
            {copy.root = copy.copy_tree(t.root, copy.root);}
            else{t.root = t.copy_tree(copy.root, t.root);}
            cout << "\n ------------------------ TREE COPIED SUCCESSFULLY ------------------------";
            copy_created = true;
            break;

        // Default case for wrong option entered
        default:
            cout << "Wrong option entered!" << endl;
        }
        cout << "\n\nDo you want to continue? (y/n) : ";
        cin >> ans;
    } while (ans == 'y');

    cout<<"Thank You for running the program !";
    return 0;
}
