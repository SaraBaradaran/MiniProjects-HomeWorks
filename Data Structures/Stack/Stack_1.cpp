///////////////////////////////////////////////////
//
//		Creator : Sara Baradaran
//		Create Date : Fall 2018
//		Consept : Data Structures (Stack)
//
///////////////////////////////////////////////////

#include<iostream>

using namespace std;

class Node
{
	int key;
	Node* next;
public:
	Node(int key) :key(key){	}
	
	friend class Stack;
};

class Stack
{
	Node* node;
	Node* top;
	int size;

public:
	Stack():size(0),top(0)	{	}
	~Stack() 
	{
		while(!this->IsEmpty())
			this->Pop();
	}
	
	void Push(int key)
	{
		node = new Node(key);
		node->next = top;
		top = node;
		size++;
	}
	int Pop()
	{
		int value;
		value = top->key;
		node = top;
		top = top->next;
		delete(node);
		size--;
		return value;
	}
	bool IsEmpty()
	{
		if(!size)
			return 1;
		return 0;	
	}
	int Top()
	{
		return top->key;
	}
	int Size()
	{
		return size;
	}

};

Stack stc;
int** a;
int n;

int FamousPerson()
{
	int i, j, temp;
	for (int i = 0; i<n; i++)
		stc.Push(i);
	while (stc.Size() != 1 || stc.IsEmpty())
	{
		if(stc.IsEmpty())
			return -1;
			
		i = stc.Pop();
		j = stc.Top();
		stc.Push(i);

		if (a[i][j] == a[j][i])
		{
			stc.Pop();
			stc.Pop();
		}
		else if (a[i][j] == 1)
			stc.Pop();

		else
		{
			temp = stc.Pop();
			stc.Pop();
			stc.Push(temp);
		}
	}
	for (int i = 0; i<n ; i++)
	{
		if (a[i][stc.Top()] == 0 && i != stc.Top())
			return -1;
	}
	for (int i = 0; i<n; i++)
	{
		if (a[stc.Top()][i] == 1)
			return -1;
	}
	return stc.Top();
}

int main()
{
	cin >> n;
	a = new int*[n];
	for (int i = 0; i<n; i++)
		a[i] = new int;

	for (int i = 0; i<n; i++)
		for (int j = 0; j<n; j++)
			cin >> a[i][j];
	int f = FamousPerson();

	if (f >= 0)
		cout << "Person " << f << " " << "is a celebrity!";
	else
		cout << "There's no celebrity in this party!";
}


