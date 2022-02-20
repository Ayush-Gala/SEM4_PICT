//============================================================================
// Name        : Assignment2.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
// Date		   : 7th Feb 2022
//============================================================================

/* Problem statement
 */
#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
using namespace std;

//class for defining Node struct
class Node
{
public:
    string word;
    string meaning;
    Node *left_child;
    Node *right_child;

	Node()
	{
		left_child = nullptr;
		right_child = nullptr;
	}
    //parameterized constructor
    Node(string word, string meaning)
    {
        this->word = word;
        this->meaning = meaning;
        left_child = nullptr;
        right_child = nullptr;
    }
    friend class Dictionary;
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
};

class Dictionary
{
public:
    Node *root,*p;
    Dictionary()
    {
        root = nullptr;
        p = nullptr;
    }
    void insert(Node*, string, string);
	bool exists(Node*, string);
    void displayAscending(Node *);
    void displayDescending(Node *);
    void count(Node *,string);
    void updateMeaning(Node *, string);
    Node* SearchWord(Node *,string);
    Node* Successor(Node *);
    Node* DeleteWord(Node *, string);

};

Node* Dictionary :: SearchWord(Node* p, string key)
{
	while(p!= nullptr)
		{
			if(key<p->word)
			{
				p = p->left_child;
			}
			else if(key>p->word)
			{
				p = p->right_child;
			}
			else
			{
				return p;
			}
		}
	return nullptr;
}
void Dictionary :: insert(Node* p, string key, string keyMeaning)
{
    if(key < p->word)
	{
		if(p->left_child != NULL)
			insert(p->left_child, key, keyMeaning);
		else
			p->left_child = new Node(key, keyMeaning);
	}
	else if(key > p->word)
	{
		if(p->right_child != NULL)
			insert(p->right_child, key, keyMeaning);
		else
			p->right_child = new Node(key, keyMeaning);
	}
}

bool Dictionary :: exists(Node* p, string key)
{
	if(p!=nullptr)
	{
		while(p!= nullptr)
		{
	        if(key<p->word)
	        {
	            p = p->left_child;
	        }
	        else if(key>p->word)
	        {
	            p = p->right_child;
	        }
	        else if(key == p->word)
	        {
				return true;
	        }
	    }
		return false;
	}
	else
	{
		return false;
	}
}
void Dictionary :: displayAscending(Node * p)
{
    if(p->left_child!=nullptr)
		displayAscending(p->left_child);
	cout<<endl<<p->word << " : " <<p->meaning;
	if(p->right_child!=nullptr)
		displayAscending(p->right_child);
}

void Dictionary :: displayDescending(Node * p)
{

	if(p->right_child!=nullptr)
		displayDescending(p->right_child);
    cout<<endl<< p->word << "  :  "<<p->meaning;
    if(p->left_child!=nullptr)
		displayDescending(p->left_child);
}

void Dictionary :: count(Node *p,string key)
{
    int comparison = 0;
    while(p!= nullptr){
        if(key<p->word){
            comparison++;
            p = p->left_child;
        }
        else if(key>p->word){
            comparison++;
            p = p->right_child;
        }
        else if(key == p->word){
            comparison++;
			cout<<"Number of comparisons to find the word "<< key <<" is  :  " << comparison<<endl;
			return ;
        }
    }
    cout<<key<<" is not present in this Dictionary"<<endl;
}

void Dictionary :: updateMeaning(Node *p, string key)
{
	string updatedMeaning;
	while(p!= nullptr)
	{
	        if(key<p->word)
	        {
	            p = p->left_child;
	        }
	        else if(key>p->word)
	        {
	            p = p->right_child;
	        }
	        else if(key == p->word)
	        {
	        	cout<<endl<<"Enter the new meaning of the word: ";
	        	cin>>updatedMeaning;
	        	p->meaning = updatedMeaning;
				cout<<"Meaning of word "<< key <<" has been updated to:  " <<p->meaning<<endl;
				return ;
	        }
	    }
	    cout<<key<<" is not present in this Dictionary"<<endl;
}

Node* Dictionary :: Successor(Node *cur)
{
	while(cur->left_child != nullptr) {  
        cur = cur->left_child;  
    }  
    return cur;  
}

Node* Dictionary :: DeleteWord(Node *p, string key)
{
	if(p==nullptr)
	{
		return nullptr;
	}
	// else if(key<p->word)
	// {
	// 	p->left_child = DeleteWord(p->left_child, key);
	// }
	// else if(key>p->word)
	// {
	// 	p->right_child = DeleteWord(p->right_child,key);
	// }
	else
	{
		Node* temp;

		if(p->left_child == nullptr)
		{
			p->word = p->right_child->word;
			p->meaning = p->right_child->meaning;
			p->left_child = p->right_child->left_child;
			p->right_child = p->right_child->right_child;
			p = p->right_child;
			p->left_child = nullptr;
			p->right_child = nullptr;
			delete p;
			return temp;
		}

		else if(p->right_child == nullptr)
		{
			p->word = p->left_child->word;
			p->meaning = p->left_child->meaning;
			p->left_child = p->left_child->left_child;
			p->right_child = p->left_child->right_child;
			p = p->left_child;
			p->left_child = nullptr;
			p->right_child = nullptr;
			delete p;
			return temp;
		}
		else
		{
			temp = Successor(p->right_child);
			DeleteWord(temp,temp->word);
			p->word = temp->word;
			p->meaning = temp->meaning;
		}
	}
	return p;
}


int main()
{

    Dictionary d;
    int n;
    string newWord, newMeaning,searchWord;
    int opt;
    char ans;
    do{
        cout << "\n\n<------Menu ------>" << endl;
        cout<<"\n1. Insert new words\n2. Display the dictionary in ascending order\n3. Display the dictionary in descending order\n4. Number of Comparisons\n5. Update meaning of a word\n6. Delete Word and meaning.\n-1 Exit the program"<<endl;
        cout << "\nEnter option : ";
        cin >> opt;
        cout<<endl;
        switch(opt)
        {
            case 1:
                    cout<<"\nEnter the word to be inserted: ";
                    cin>>newWord;
                    newWord[0] = toupper(newWord[0]);
                    for(int i=1;i<newWord.length();i++)
					{
                        newWord[i] = tolower(newWord[i]);
                    }
					if(d.exists(d.root,newWord))
					{
						cout<<"This word already exists!"<<endl;
					}
					else
					{
						cout<<"Enter its meaning: ";
						cin>>newMeaning;
						newMeaning[0] = toupper(newMeaning[0]);
						for(int i=1;i<newMeaning.length();i++)
						{
							newMeaning[i] = tolower(newMeaning[i]);
						}
						if(d.root == NULL)
						{
							d. root = new Node(newWord, newMeaning);
						}
						else
						{
							d.insert(d.root, newWord, newMeaning);
						}
					}
                break;
            case 2:
            	if(d.root == NULL)
            	{cout<<"BST does not exist! Please add words to dictionary first!"<<endl;}
            	else
            	{
                cout<<"****The order of words in dictionary are as follows : ******"<<endl;
                d.displayAscending(d.root);
            	}
                break;
            case 3:
            	if(d.root == NULL)
            	{cout<<"BST does not exist! Please add words to dictionary first!"<<endl;}
            	else
            	{
                cout<<"****The order of words in dictionary are as follows : ******"<<endl;
                d.displayDescending(d.root);
            	}
                break;
            case 4:
            	if(d.root == NULL)
            	{cout<<"BST does not exist! Please add words to dictionary first!"<<endl;}
            	else
            	{
                cout<<"\nEnter the word whose comparison for search is to be found out : ";
                cin>>searchWord;
                searchWord[0] = toupper(searchWord[0]);
                for(int i=1;i<searchWord.length();i++){
                    searchWord[i] = tolower(searchWord[i]);
                }
                d.count(d.root,searchWord);
            	}
                break;

            case 5:
            	if(d.root == NULL)
              	{cout<<"BST does not exist! Please add words to dictionary first!"<<endl;}
               	else
               	{
            	cout<<"\nEnter the word you want to update: ";
            	cin>>searchWord;
            	searchWord[0] = toupper(searchWord[0]);
            	for(int i=1;i<searchWord.length();i++)
            	{
            		searchWord[i] = tolower(searchWord[i]);
            	}
            	d.updateMeaning(d.root,searchWord);
               	}
            	break;
            
            case 6:
            	if(d.root == nullptr)
            	{
            		cout<<"BST Does not exist!"<<endl;
            	}
            	else
            	{
            		cout<<"\nEnter the word you want to delete: ";
            		cin>>searchWord;
            		searchWord[0] = toupper(searchWord[0]);
            		for(int i=1;i<searchWord.length();i++)
            		{
            			searchWord[i] = tolower(searchWord[i]);
            		}
            		Node *temp = d.SearchWord(d.root,searchWord);
            		if(temp!= nullptr)
            			d.DeleteWord(temp,searchWord);
            		else
            			cout<<"The word does not exist in BST!"<<endl;
            	}
            	break;
			
			case -1:
				break;

            default:
                cout << "Wrong option entered!" << endl;
        }
    }while (opt!=-1);
    cout<<"THANK YOU!";
    return 0;
}