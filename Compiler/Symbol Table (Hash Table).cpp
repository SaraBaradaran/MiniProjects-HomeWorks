
#include <iostream> 
using namespace std; 
  
  
class Node { 
  
    string id;
	string scope;
	string type; 
    string line; 
    Node* next; 
  
public: 
    Node(string id):id(id),scope(" "),type(" "),line(" ") 
    { 
        this->next = NULL; 
    } 
  
    friend class SymbolTable; 
}; 
  
class SymbolTable { 

    Node* head[100]; 
  
public: 
    SymbolTable() 
    { 
        for (int i = 0; i < 100; i++) 
            head[i] = NULL; 
    } 
	      
	int hashf(string id) 
	{ 
	    int sum = 0; 
	  
	    for (int i = 0; i < id.length(); i++) { 
	        sum = sum + id[i]; 
	    } 
	  
	    return (sum % 100); 
	} 
    
    Node* insert(string id) 
	{ 
	    int index = hashf(id); 
	    Node* p = new Node(id); 
	  
	    if (head[index] == NULL) { 
	    
	        head[index] = p; 
	  
	        return p; 
	    } 
	  
	    else { 
	    
	        Node* start = head[index]; 
	        while (start->next != NULL) 
	            start = start->next; 
	  
	        start->next = p; 
	  
	        return p; 
	    } 
	  
	    return false; 
	} 
	void free(){
		
		for(int i = 0; i < 100; i++){
			
			while(head[i] != NULL){
				Node* start = head[i];
				head[i] = start->next;
				start->next = NULL;
				delete start;
				
			}	
		}
	}
	
    Node* lookup(string id) 
	{ 
	    int index = hashf(id); 
	    Node* start = head[index]; 

	    while (start != NULL) { 
	  
	        if (start->id == id) { 
	            return start;
	        } 
	  
	        start = start->next; 
	    } 
	  
	    return NULL; 
	}
	void setattribute(string id, string attribute, string value)
	{
		Node* p = lookup(id);
		
		if(attribute == "scope")
			p->scope = value;
			
		else if(attribute == "type")
			p->type = value;
			
			
		if(attribute == "line")
			p->line = value;		
			
	}	
	string getattribute(string id, string attribute)
	{
		Node* p = lookup(id);
		
		if(attribute == "scope")
			return p->scope;
			
		else if(attribute == "type")
			return p->type;
		
		else if(attribute == "line")
			return p->line;	
	}

    void print() // print symbol table
    { 
    	cout << "id\t type\t scope\t line\t" << endl;
    	for(int i = 0; i < 100; i++){
    		Node* start = head[i];
    		while(start != NULL){
    			
    			cout << start->id << "\t " << start->type << "\t " << start->scope << "\t " << start->line << endl;
    			start = start->next;
			}
		}
    	
    } 
}; 
  
int main() 
{ 
    SymbolTable st; // allocate symbol table
    Node* p = st.insert("var");
    st.setattribute("var", "scope", "local");
    st.setattribute("var", "line", "9");    
    st.setattribute("var", "type", "int");
    
 	p = st.insert("x");
    st.setattribute("x", "type", "char");
	st.setattribute("x", "scope", "global");
	st.setattribute("x", "line", "20");
    
    st.print();
  	st.free();
  	cout << "\n---------------------------------\n";
  	st.print();
  	
    return 0; 
} 

