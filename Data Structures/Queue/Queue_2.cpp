///////////////////////////////////////////////////
//
//		Creator : Sara Baradaran
//		Create Date : Fall 2018
//		Consept : Data Structures (Queue)
//
///////////////////////////////////////////////////

#include<iostream>

using namespace std;

class Queue
{
	int front;
	int rear;
	int* array;
	int MaxSize;

public:	
	Queue(int MaxSize):MaxSize(MaxSize),front(-1),rear(-1)
	{
		array = new int[MaxSize];
	}
	
	void Push(int index)
	{
		if(rear-front < MaxSize)
			array[++rear] = index;
		else
			cout<<"Queue is fuul";
	}
	int Pop()
	{
		int index = array[front+1];
		for(int i=front+2; i<=rear; i++)
			array[i-1]=array[i];
		rear--;	
		return index;
	}
	int size()
	{
		return rear-front;
	}
	bool IsEmpty()
	{
		if(rear==front)
			return 1;
		return 0;
	}
	bool IsFull()
	{
		if(rear == MaxSize-1)
			return 1;
		return 0;	
	}
	int Front()
	{
		return array[front+1];
	}
	~Queue()
	{
		delete [] array;		
	}		
};


bool SearchIndex(Queue* que, int index)
{
	for(int i=0; i<que->size(); i++)
	{
		int temp = que->Pop();
		que->Push(temp);
		if(temp == index)
			return 1;
	}
	return 0;
}
void AddIndex(Queue* que, int index)
{
	if(que->IsFull())
		que->Pop();
		
	que->Push(index);
}

bool CheckPageFault(Queue* que, int index)
{
	if (SearchIndex(que, index))
		return 0;
	else
		AddIndex(que, index);
	return 1;
}

int main()
{
	
	int index, size = 0, pagefault = 0, MaxSize;
	cin >> MaxSize;
	Queue* que = new Queue(MaxSize);

	while (cin >> index)
	{
		pagefault += CheckPageFault(que ,index);
	}
	cout << pagefault;

}


