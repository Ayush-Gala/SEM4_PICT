//============================================================================
// Name        : Assignment5.cpp
// Author      : Ayush Gala
// Version     : 1
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#define size 10
using namespace std;

class Node
{
private:
	string word,meaning;

public:
	Node* next;
	Node()
	{
		word = "";
		meaning = "";
		next = nullptr;
	}

	Node(string word, string meaning)
	{
		this->word = word;
		this->meaning = meaning;
		next = nullptr;
	}

	void set(string word, string meaning)
	{
		this ->word = word;
		this->meaning = meaning;
	}

	string get()
	{
		return this->meaning;
	}

//	bool isEmpty()
//	{
//		if(word == "")
//		{
//			return true;
//		}
//		else
//			return false;
//	}

	bool compare(string key)
	{
		if(key== word)
			return true;
		else
			return false;
	}
};

class LL
{
private:
	Node* head;
	Node* tail;
	int count;

public:
	Node* temp;
	LL()
	{
		head = nullptr;
		tail = nullptr;
		temp = nullptr;
		count = 0;
	}

	void append(string word, string meaning)
	{
		temp = new Node(word,meaning);
		if(head != nullptr)
		{
			tail = head;
			if(tail->compare(word))
			{
				cout<<"Word already exists!\n\n";
				return;
			}
			while(tail->next!=nullptr)
			{
				if(tail->compare(word))
				{
					cout<<"Word is already present!\n\n";
					return;
				}
				else
				{
					tail = tail->next;
				}
			}
			tail->next = temp;
		}
		else
		{
			head = temp;
			tail = temp;
		}
		count++;
		cout<<"Word has been added to the dictionary!\n\n";
		return;
	}

	void search(string key)
	{
		int iter = 0;
		if(head!=nullptr)
		{
			temp = head;
			while(temp != nullptr)
			{
				if(temp->compare(key))
				{
					cout<<"Meaning: "<<temp->get();
					cout<<"\nNo. of comparisons = "<<iter+1<<endl<<endl;
					return;
				}
				else
				{
					temp=temp->next;
				}
				iter++;
			}
			if(temp==nullptr)
			{
				cout<<"NO such word in the dictionary!\n";
				cout<<"No. of comparisons : "<<iter<<endl<<endl;
			}
		}
		else
		{
			cout<<"No such word in the dictionary!\n";
		}
	}

	void deleteword(string key)
	{
		if(head!=nullptr)
		{
			temp = head;
			Node* prev;
			while(temp != nullptr)
			{
				if(temp->compare(key))
				{
					if(temp == head)
					{
						head = temp->next;
						temp->next = nullptr;
						delete temp;
					}
					else if(temp->next == tail)
					{
						tail = prev;
						prev->next = nullptr;
						delete temp;
					}
					else
					{
						prev->next = temp->next;
						temp->next = nullptr;
						delete temp;
					}
					cout<<"The word has been removed from the dictionary!\n\n";
					return;
				}
				else
				{
					prev = temp;
					temp=temp->next;
				}

			}
			if(temp==nullptr)
			{
				cout<<"NO such word in the dictionary!\n";
			}
		}
		else
		{
			cout<<"No such word in the dictionary!\n";
		}
	}
};

class HashTable
{
	LL table[size];
	static int entryCount;

public:
	HashTable()
	{
		cout<<"A hash table has been created!\n\n";
	}

	int Func(string key)
	{
		int hi = 0;
		for(int i=0; i<key.length(); i++)
		{
			hi += int(key[i]);
		}
		return hi%size;
	}

	void Search(string key)
	{
		int index = Func(key);
		table[index].search(key);

	}

	void add(string word, string meaning)
	{
		int index = Func(word);
		table[index].append(word,meaning);
	}

	void deleteword(string key)
	{
		int index = Func(key);
		table[index].deleteword(key);
	}
};

int HashTable :: entryCount = 0;

int main()
{
	HashTable t1;
	int choice = 0;
	while(choice!= -1)
	{
		cout<<"MENU\n";
		cout<<"1. Add word to dictionary.\n2. Find word in dictionary.\n3. Delete word from dictionary.\n-1 Exit program.\n\n";
		cout<<"Enter your choice: ";
		cin>>choice;

		switch(choice)
		{

		case 1:
		{
			string word,meaning;
			cout<<"Enter the word: ";
			cin>>word;
			cout<<"Enter it's meaning: ";
			cin>>meaning;
			t1.add(word,meaning);
			break;
		}

		case 2:
		{
			string word;
			cout<<"Enter the word you want to search: ";
			cin>>word;
			t1.Search(word);
			break;
		}

		case 3:
		{
			string word;
			cout<<"Enter the word you want to delete: ";
			cin>>word;
			t1.deleteword(word);
			break;
		}

		case -1:
		{
			break;
		}

		default:
		{
			cout<<"Please enter the correct option from the Menu!\n\n";
			break;
		}
		}
	}
	cout<<"THANK YOU!";
	return 0;
}
