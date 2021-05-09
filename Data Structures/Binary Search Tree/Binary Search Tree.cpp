///////////////////////////////////////////////////
//
//		Creator : Sara Baradaran
//		Create Date : Fall 2018
//		Consept : Data Structures (Binary Seach Tree)
//
///////////////////////////////////////////////////

#include<iostream>

using namespace std;

class Node{

public:	

	Node(int data):data(data),leftchild(NULL),rightchild(NULL)
	{
		
	}
	int data;
	Node* leftchild;
	Node* rightchild;
	
	friend class Tree;
};

class Tree{

public:
	Node* root;
	Node* temp;
	
	Tree(int data){
		root = new Node(data);		
	}
	
	void Add(int data)
	{
		
		Node* p = root;
		Node* parent;
		
		while(p)
		{
			parent = p;
			
			if(data < p->data)
			p = p->leftchild;
			else
			p = p->rightchild;
			
		}
		temp = new Node(data);
		
		if(data < parent->data)
			parent->leftchild = temp;
		else
			parent->rightchild = temp;
			
	}
		
};

void print(Node* root)
{
	if(root)
	{
		print(root->leftchild);
		print(root->rightchild);
		cout << root->data << endl;	
	}

}


int main()
{
	int root_data, data;
	cin >> root_data;
	Tree* tree = new Tree(root_data);
	
	while(cin>>data)
	{
		tree->Add(data);
	}
	print(tree->root);
}

