//============================================================================
// Name        : Assignment4.cpp
// Author      : Ayush Gala
// Version     : 2.1.1
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#define size 5
using namespace std;

class HashEntry
{
	private:
	long int telephone;
	string name;

	public:
	//default constructor
	HashEntry()
	{
		telephone = 0;
		name = "";
	}

	//parameterized constructor
	HashEntry(long int telephone, string name)
	{
		this->telephone = telephone;
		this->name = name;
	}

	//function to set value of object data members
	void set(long int telephone, string name)
	{
		this->telephone = telephone;
		this->name = name;
	}

	long int get()
	{
		return this->telephone;
	}
	//function to check if object is empty or not
	bool isempty()
	{
		if(this->telephone == 0)
			return true;
		else
			return false;
	}

	//function to display object data
	void display()
	{
		cout<<telephone<<"\t\t";
		cout<<name<<endl;
	}

	//function to compare telephone values
	bool compare(long int unknown)
	{
		if(telephone == unknown)
			return true;
		else
			return false;

	}
	void swap(HashEntry &obj)
	{
		long int tempt = this->telephone;
		string tempn = this-> name;
		this->telephone = obj.telephone;
		this->name = obj.name;
		obj.telephone = tempt;
		obj.name = tempn;
		return;
	}
	//friend class HashTable;
};

class HashTable
{
private:
	HashEntry table[size];
	static int countEntry;

public:
	//default constructor
	HashTable()
	{
		cout<<"A telephone directory has been created!\n";
	}

	//function to insert a value in the hashtable without replacement
	void insert(long int key,string value)
	{
		if(countEntry == size)
		{
			cout<<"HashTable FULL!"<<endl;
			return;
		}
		int hi = hashfunc(key);
		while(!table[hi].isempty())
		{
			hi = (hi+1)%size;
		}
		table[hi].set(key,value);
		cout<<"NUMBER ADDED TO DIRECTORY!\n";
	}

	//function to insert a value in the hashtable with replacement
	void insertr(long int key,string value)
	{
		if(countEntry == size)
		{
			return;
		}
		int hi = hashfunc(key);
		bool replace = false;
		int temp = hi;
		if(!table[hi].isempty() && hashfunc(table[hi].get())!= hi )
		{
			replace = true;
		}
		while(!table[hi].isempty())
		{
			hi = (hi+1)%size;
		}
		table[hi].set(key,value);
		if(replace)
		{
			table[hi].swap(table[temp]);
		}
		countEntry++;
	}

	//Hash function to return hash index
	int hashfunc(long int key)
	{
		return key%size;
	}

	void displayTable()
	{
		cout<<"Index\tTelephone\tName\n";
		for(int i=0;i<size;i++)
		{
			if(!table[i].isempty())
			{
				cout<<i<<".\t";
				table[i].display();

			}
		}
	}

	void search(long int unknown)
	{
		int hi = hashfunc(unknown);
		int count = 1;
		int temp = hi;
		while(!table[hi].compare(unknown))
		{
			count++;
			hi = (hi+1)%size;
			if(hi == temp)
			{
				cout<<"Number not present in the directory!\n";
				return;
			}
		}
		cout<<"Index\tTelephone\tName\n";
		cout<<hi<<"\t";
		table[hi].display();
		cout<<"No of comparisions: "<<count<<endl;
	}
};

int HashTable::countEntry = 0;

int main()
{
	HashTable h1,h2;
	int choice = 0;
	//main loop
	while(choice!=-1)
	{
		cout<<"\n**********MENU**********\n";
		cout<<"1. Insert value into table\n2. Display table\n3. Search Number\n-1. Exit program\nEnter your choice: ";
		cin>>choice;
		cout<<endl;
		switch(choice)
		{

		case 1:
		{
			long int tele = 0;
			string name = "";
			cout<<"Enter telephone number: ";
			cin>>tele;
			cout<<"Enter name on number: ";
			cin>>name;
			h1.insert(tele,name);
			h2.insertr(tele,name);
			break;
		}

		case 2:
		{
			cout<<"Without replacement:\n";
			h1.displayTable();
			cout<<"\nWith replacement:\n";
			h2.displayTable();
			break;
		}

		case 3:
		{
			cout<<"Enter the number you want to search: ";
			long int unknown = 0;
			cin>>unknown;
			cout<<"Search without replacement:\n";
			h1.search(unknown);
			cout<<"\nSearch with replacement:\n";
			h2.search(unknown);
			break;
		}

		case -1:
			break;

		default:
		{
			cout<<"Please enter valid choice from the MENU!\n";
		}
		}
	}

	cout<<"Thank you!";
	return 0;
}
