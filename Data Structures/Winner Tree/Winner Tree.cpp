///////////////////////////////////////////////////
//
//		Creator : Sara Baradaran
//		Create Date : Fall 2018
//		Consept : Data Structures (Winner Tree)
//
///////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Node {

public:
	Node(int key, Node* parent) :key(key), left_child(NULL), right_child(NULL), parent(parent)
	{
	}
	int key;
	Node* right_child;
	Node* left_child;
	Node* parent;
};

class WinnerTree {

	Node* root;
	Node* temp1, *temp2;
	int leaves;

public:
	vector <Node*> leaves_pointer;

	WinnerTree(int n) :leaves(n)
	{
		root = new Node(200000000, NULL);
		rec_treecreate(root, 1, 2 * n - 1);
	}
	int deletee()
	{
		int temp = root->key;
		root->key = 200000000;
		Node* node = root;
		while (node->left_child != node->right_child != NULL)
		{

			if (node->left_child->key == temp)
				node = node->left_child;
			else
				node = node->right_child;

			node->key = 200000000;
		}
		return temp;
	}
	void rec_treecreate(Node* root, int n, int mux)
	{
		Node* parent = root;
		if (2 * n - 1 < mux)
		{
			temp1 = new Node(200000000, parent);
			temp2 = new Node(200000000, parent);
			parent->left_child = temp1;
			parent->right_child = temp2;
			//cout << temp1->key << endl;
			//cout << temp2->key << endl;
			n *= 2;

			rec_treecreate(parent->left_child, n, mux);
			rec_treecreate(parent->right_child, n + 1, mux);
		}
		else
			leaves_pointer.push_back(parent);

	}

	void rec_comp(Node* node)
	{
		if (node->parent == NULL)
			return;

		Node * parent = node->parent;
		if (parent->left_child == node)
		{
			if (node->key < parent->right_child->key)
				parent->key = node->key;
			else
				parent->key = parent->right_child->key;
		}
		else
		{
			if (node->key < parent->left_child->key)
				parent->key = node->key;
			else
				parent->key = parent->left_child->key;
		}

		rec_comp(parent);

	}

};


int main()
{
	int n, f, x;
	cin >> n >> x;
	WinnerTree * a = new WinnerTree(n);

	queue<int>* stk;
	stk = new queue<int>[n];
	for (int i = 0; i < n; i++)
	{
		cin >> f;
		while (f != 0)
		{
			stk[i].push(f);
			cin >> f;
		}
	}
	int r = a->leaves_pointer.size();

	for (int j = 0; j < r; j++)
	{
		if (stk[j].empty())
			continue;
		a->leaves_pointer[j]->key = stk[j].front();
		stk[j].pop();
		for (int i = 0; i < r; i++)
		{
			a->rec_comp(a->leaves_pointer[i]);
		}
	}

	for (int i = 0; i < r; i++)
	{
		a->rec_comp(a->leaves_pointer[i]);
	}

	for (int i = 0; i < x - 1; i++)
	{
		a->deletee();
		for (int j = 0; j < r; j++)
			if (a->leaves_pointer[j]->key == 200000000)
			{
				if (stk[j].empty())
				{
					a->rec_comp(a->leaves_pointer[j]);
					continue;
				}
				a->leaves_pointer[j]->key = stk[j].front();
				stk[j].pop();
				a->rec_comp(a->leaves_pointer[j]);
				break;
			}
		
	}
	cout << a->deletee();


}
