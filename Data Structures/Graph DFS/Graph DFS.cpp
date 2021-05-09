///////////////////////////////////////////////////
//
//		Creator : Sara Baradaran
//		Create Date : Fall 2018
//		Consept : Data Structures (Depth First Search On Graph)
//
///////////////////////////////////////////////////

#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
	Node(int key):key(key){}
	int key;
	Node* next;

};

class Graph {

	Node* temp1,*temp2;
	Node** arr;
	bool* visited;
	int size;
public:

	Graph(int node_number) :size(node_number+1)
	{
		arr = new Node*[size];
		visited = new bool[size];
		for (int i = 1; i < size; i++)
		{
			arr[i] = NULL;
			visited[i] = false;
		}
	}
	void Add(int sourse, int distination)
	{
		temp1 = new Node(sourse);
		temp2 = new Node(distination);
		if (arr[sourse] == NULL)
		{
			arr[sourse] = temp2;
			temp2->next = NULL;
		}
		else
		{
			temp2->next = arr[sourse];
			arr[sourse] = temp2;
		}
		if (arr[distination] == NULL)
		{
			arr[distination] = temp1;
			temp1->next = NULL;
		}
		else
		{
			temp1->next = arr[distination];
			arr[distination] = temp1;
		}
		
	}

	void DFS(int vertex)
	{
		Node* p;
		visited[vertex] = true;

		for (p = arr[vertex] ; p; p = p->next)
		{
			if (visited[p->key] == false)
			{
				DFS(p->key);
			}
		}

	}

	int checkDFS()
	{
		int num = 1;
		for (int i = 1; i < size; i++)
		{
			if (visited[i] == false)
			{
				DFS(i);
				num += 1;
			}
		}
		return num;
	}


};

int main()
{

	int i, j, n;
	cin >> n;
	Graph* dominos = new Graph(n);
	cin >> i >> j;
	while (i != 0 && j != 0)
	{
		dominos->Add(i, j);
		cin >> i >> j;
	}
	dominos->DFS(1);
	cout << dominos->checkDFS();
}
