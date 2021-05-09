///////////////////////////////////////////////////
//
//		Creator : Sara Baradaran
//		Create Date : Fall 2018
//		Consept : Data Structures (Queue)
//
///////////////////////////////////////////////////

#include<iostream>

using namespace std;

class Node
{
	int energy;
	int distance;
	Node* next;
	
public:
	Node(int energy, int distance) :energy(energy), distance(distance) {	}
	
	friend class Queue;

};
class Queue
{
	Node* node;
	Node* front;
	Node* rear;
	int size;

public:
	Queue():size(0),front(0),rear(0)
	{
		
	}
	~Queue()
	{
		while(!this->IsEmpty())
		this->Pop();
	}
	void Push(int energy, int distance)
	{
		node = new Node(energy, distance);
		if(this->IsEmpty())
		{
			front = rear = node;
			rear->next = front;	
		}
		else
		{
			rear->next = node;
			rear = node;
			rear->next = front;
		}
		size++;
	}
	void Pop()
	{
		node = front;
		front = front->next;
		rear->next = front;
		delete(node);
		size--;
	}
	bool IsEmpty()
	{
		if(!size)
			return 1;
		return 0;	
	}
	int FindStart()
	{
		int Eremain, dis, s, s1;
		s1 = 0;
		for (Node* i = front; s1 < size; i = i->next, s1++)
		{
			s = 0;
			Eremain = 0;
			for (Node* j = i; s < size; j = j->next, s++)
			{
				Eremain += j->energy;
				if (j->distance>Eremain)
					break;

				if (s == size - 1)
					return s1;

				Eremain -= j->distance;
			}
		}
		return -1;
	}
};

int main()
{

	int num, energy, distance;
	Queue* queue;
	cin >> num;
	queue = new Queue();
	for (int i = 0; i<num; i++)
	{
		cin >> energy >> distance;
		queue->Push(energy, distance);
	}
	int a = queue->FindStart();
	if (a >= 0)
		cout << "You should start at " << a << "!";
	else
		cout << "There's no way the probe could make this trip!";
}


