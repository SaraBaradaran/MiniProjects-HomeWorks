#include<iostream>
#include<string>
using namespace std;

class Node{

	string name;
	string type;
	string scope;
	
	Node* next;
	
public:		
	Node(string name):next(NULL),name(name),type("undef"),scope("undef"){

	}
	void set_type(string type){
		this->type = type;
	}
	void set_scope(string scope){
		this->scope = scope;
	}
	string get_scope(){
		return this->scope;
	}
	string get_type(){
		return this->type;
	}
	friend class SymbolTable;
};

class SymbolTable{
	
	Node* first;
	Node* last;
public:
	SymbolTable():first(NULL),last(NULL){
		
	}
	Node* insert(string name){
			
		Node* _new = new Node(name);
		if(first){
			
			last->next = _new;
			last = _new;
		}
		else{
			first = last = _new;
			
		}
		
		return _new;	
	}
	
	Node* lookup(string name){
		
		for(Node* t = first; t; t = t->next){
			if(t->name == name)
				return t;
		}
		return NULL;
	}
	void free(){
		
		while(first){
			
			Node* t = first;
			first = first->next;
			t->next = NULL;
			delete(t);
			
		}	
	}
	
	void print(){
		
		cout << "\n\n name\t| type\t| scope\t\n-------------------------\n ";
		for(Node* t = first; t; t = t->next){
			cout << t->name << "\t";
			cout << "| " << t->type << "\t| " << t->scope << "\t\n-------------------------\n ";
		}
	}

	void set_arrtibute(string attribute_name, string attribute_value, string symbol_name){
		
		Node* t = lookup(symbol_name);
		
		if(attribute_name == "type")
			t->set_type(attribute_value);
			
		else if(attribute_name == "scope")
			t->set_scope(attribute_value);
			
	}
	string get_arrtibute(string attribute_name, string symbol_name){
		
		Node* t = lookup(symbol_name);
		
		if(attribute_name == "type")
			return t->get_type();
			
		else if(attribute_name == "scope")
			return t->get_scope();
			
	}

	
};


int main(){
	
	SymbolTable s;//allocate symbol table
	
	Node* ptr = s.insert("x");
	ptr = s.insert("var");// insert to symbol table
	s.set_arrtibute("type","int","var");// set attribute of a symbol
	s.set_arrtibute("scope","global","var");
	ptr = s.insert("rate");
	s.set_arrtibute("scope","local","rate");
	ptr = s.insert("ch");
	s.set_arrtibute("type","char","ch");
	
	ptr = s.lookup("var"); // lookup a symbol in symbol table
	cout << "type of *var* : " << ptr->get_type() << endl;
	
	cout << "scope of *rate* : " << s.get_arrtibute("scope","rate");//get attribute of a symbol
	s.print();
	s.free();//free symbol table
	s.print();
	
}
