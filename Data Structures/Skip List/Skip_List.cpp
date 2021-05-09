///////////////////////////////////////////////////
//
//		Creator : Sara Baradaran
//		Create Date : Fall 2018
//		Consept : Data Structures (Skip List)
//
///////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std; 
  
class Node 
{ 
    int key; 
    Node** forward;
public: 	 
    Node(int key, int level):key(key)
    {
    	forward = new Node* [level+1];
    	for(int i=0; i<=level; i++)
    		forward[i] = 0;
	}
	friend class SkipList;
}; 
   
class SkipList 
{ 
    int MaxLevel;
    float P;  
    int level;  
    Node *head;
	 
public: 
	  
	SkipList(int MaxLevel, float P):MaxLevel(MaxLevel), P(P), level(0)
	{ 
	    head = new Node(-1, MaxLevel); 
	} 
	
	int randomLevel() 
	{ 
	    float r = (float)rand()/MaxLevel; 
	    int lvl = 0; 
	    while (r < P && lvl < MaxLevel) 
	    { 
	        lvl++; 
	        r = (float)rand()/MaxLevel; 
	    } 
	    return lvl; 
	} 
	  
	   
	void insertElement(int key) 
	{ 
	
	    Node *current = head; 
	  
	    Node *update[MaxLevel+1]; 
	    for(int i=0; i<=MaxLevel; i++)
	    	update[i]=0;
	  
	    for (int i = level; i >= 0; i--) 
	    { 
	        while (current->forward[i] != NULL && current->forward[i]->key < key) 
	            current = current->forward[i]; 
	            
	        update[i] = current; 
	    } 
	  

	    current = current->forward[0]; 

	    if (current == NULL || current->key != key) 
	    { 
	        int rlevel = randomLevel(); 
	   
	        if (rlevel > level) 
	        { 
	            for (int i=level+1;i<rlevel+1;i++) 
	                update[i] = head; 

	            level = rlevel; 
	        } 
	  
	        Node *newnode = new Node(key, rlevel); 

	        for (int i=0;i<=rlevel;i++) 
	        { 
	            newnode->forward[i] = update[i]->forward[i]; 
	            update[i]->forward[i] = newnode; 
	        } 
	        cout << "Successfully Inserted key " << key << "\n"; 
	    } 
	}
	void deleteElement(int key) 
	{ 
	  	Node *current = head; 
		  
	    Node *update[MaxLevel+1]; 
	    for(int i=0; i<=MaxLevel; i++)
	    	update[i]=0; 
	
	    for(int i = level; i >= 0; i--) 
	    { 
	        while(current->forward[i] != NULL  && current->forward[i]->key < key) 
	            current = current->forward[i];
				 
	        update[i] = current; 
	    } 
	
	    current = current->forward[0]; 
	
	    if(current != NULL && current->key == key) 
	    { 
	    
	        for(int i=0;i<=level;i++) 
	        { 
	            if(update[i]->forward[i] != current) 
	                break; 
	  
	            update[i]->forward[i] = current->forward[i]; 
	        } 
	 
	        while(level>0 && head->forward[level] == 0) 
	            level--; 
	        cout<<"Successfully deleted key "<<key<<"\n"; 
	    } 
	}
	bool searchElement(int key) 
	{ 
	    Node *current = head; 
	  
	    for(int i = level; i >= 0; i--) 
	    { 
	        while(current->forward[i] != NULL && current->forward[i]->key < key) 
	            current = current->forward[i];  
	    } 
	  
	    current = current->forward[0]; 
	
	    if(current != NULL && current->key == key)  
	        return 1;
	    
		return 0;    
	}
}; 
int main()
{
	srand(time(0));
	int n;
	SkipList a(4, 1);
	while(cin>>n)
	{
		a.insertElement(n);
	}
	
	cout<<a.searchElement(2);
}

