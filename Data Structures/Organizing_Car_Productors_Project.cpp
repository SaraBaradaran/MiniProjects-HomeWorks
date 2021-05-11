/////////////////////////////////////////////////////////////////////////
//
//		Creator : Sara Baradaran
//		Create Date : Fall 2019
//		Consept : Data Structures (Organizing Car Productors Project)
//
/////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <string.h>
#define node GenListNode
using namespace std;


class Service{
public:
	char name[10];
	string model;
	string describtion_customer;
	string describtion_agency;
	long int cost;
};


class Order{
public:
	Order(){
		Immediacy_level = new char [15];
		customer_name = new char [15];
	}
	Service* s;
	char* Immediacy_level;
	char* customer_name;
	
};

class MaxHeap{
	

	
public:
	Order* heap;
	int size;
	
	MaxHeap():size(0){
		heap = new Order[10];
	}
	void add(char* Immediacy_level, Service* s, char* customer_name){
		
		
		int i = (++size);
		while( (i != 1)  && (strcmp(Immediacy_level,heap[i/2].Immediacy_level) > 0)){
			
			strcpy(heap[i].Immediacy_level,heap[i/2].Immediacy_level);
			heap[i].s = heap[i/2].s;
			strcpy(heap[i].customer_name, heap[i/2].customer_name);
			i /= 2;
		}
		
		strcpy(heap[i].Immediacy_level,Immediacy_level);
		heap[i].s = s;
		strcpy(heap[i].customer_name, customer_name);
	}
	
	void remove(){
		
		
		
		if( size == 0 ){
			cout << "________heap is empty________\n";
			return;
		}
			
			
		int parent = 1, child = 2;
		Order i, temp;
		i = heap[1];

		temp = heap[size--];
		while(child <= size){
			if(child < size && (strcmp(heap[child].Immediacy_level, heap[child + 1].Immediacy_level) < 0))
				child++;
			if(strcmp(temp.Immediacy_level, heap[child].Immediacy_level) >= 0) 
				break;
				
			heap[parent] = heap[child];
			parent = child;
			child *= 2;
		}
		heap[parent] = temp;

		cout << i.s->name  << " for "<< i.customer_name << " done " << endl;

	}
		
};
class GenListNode{
public:
	GenListNode(char* name):next(NULL), sub_service(NULL), agency_num(0){
		s = new Service;
		strcpy(s->name, name);
	}
	
	GenListNode *next;
	GenListNode *sub_service;
	Service *s;
	int agency_num;
};


	
node* search(char* name, node* root){
	if(root == NULL) 
		return NULL;
	if(!strcmp(root->s->name, name))
		return root;
	if(search(name, root->sub_service) != NULL)
		return search(name, root->sub_service);
	else	
		return search(name, root->next);
}

class GenLinkedList{


	GenListNode* last;
public:
	GenListNode* first;
	
	GenLinkedList():first(NULL), last(NULL){
	}

	void add_service(char* name){
		
		GenListNode *new_service = new GenListNode(name);
		
		if(first == NULL){
			
			first = last = new_service;
		}
		else{
			
			last->next = new_service;
			last = new_service;
		}
		
		cout << "________added successfully________\n";
	}
	void remove_service(char* name){
		
		
		if(!strcmp(first->s->name, name)){
			
			first = first->next;
			cout << "________service deleted successfully________\n";
			return;
			
		}
		else{
			
			node* prev = first;
			for(node* i = first->next; i; i = i->next, prev = prev->next){
				if(!strcmp(i->s->name, name)){
					if(i == last){
						last = prev;
						last->next = NULL;
					
						
					}
					else{
						prev->next = i->next;
						i->next = NULL;
					}
					cout << "________service deleted successfully________\n";
					return;
				}
				
			}
		}
			cout << "________service not found________\n";
		
	}
	void add_subservice(char* sub_name, char* name){

		node* root = first;
		node* parent = search(name, root);
		
		if(parent != NULL){

			GenListNode *new_service = new GenListNode(sub_name);
			
			if(parent->sub_service == NULL){
				parent->sub_service =  new_service;
			}
			else{
				node* i;
				
				for(i = parent->sub_service; i->next; i = i->next);
				
				i->next = new_service;
			}
			
			cout << "________added successfully________\n";
		}
		else
			cout << "________service not found________\n";
	}
	
	void list_subservices(char* parent_name){
		
		node* root = first;
		node* parent = search(parent_name, root);
		if(parent != NULL){
			for(node* i = parent->sub_service; i; i = i->next){
				cout << i->s->name << endl;
				if(i->sub_service != NULL){
					cout << i->s->name << "'s subservices : " << endl;
					list_subservices(i->s->name);
				}
			}
			cout << "_________________________________\n";
		}
		else 
			cout << "________service not found________\n";
	}
	
	void list_services(){
		if(first == NULL)
			cout << "________list is empty________\n";
			
		for(node* i = first; i; i = i->next){
				cout << "<<<" << i->s->name << ">>>" << endl;
			if(i->sub_service != NULL){
				cout << i->s->name << "'s subservices : " << endl;
				list_subservices(i->s->name);
			}
		}
		
		cout << "_________________________________\n";
	}
	
};

class ListNode{

public:
	ListNode(char* name):next(NULL){
		queue = new MaxHeap();
		agency_name = new char[10];
		strcpy(agency_name, name);
	}
	ListNode *next;
	char* agency_name;
	vector <node*> sevices;
	MaxHeap* queue;
};

class LinkedList{
	
	ListNode* first;
	ListNode* last;
	GenLinkedList* service_list;
public:
	LinkedList(GenLinkedList* list):first(NULL), last(NULL), service_list(list){
		
	}
	
	void add_agency(char* name){
		ListNode *new_agency = new ListNode(name);

		if(first == NULL){

			first = last = new_agency;
		}
		else{
			last->next = new_agency;
			last = new_agency;
		}
		
		cout << "________added successfully________\n";

	}
	void list_agencies(){
		
		for(ListNode* i = first; i; i = i->next)
			cout << i->agency_name << endl;
			
		cout << "__________________________________\n";
	}
	void list_orders(char* agency_name){
		
		if(first == NULL)
			cout << "________list is empty________\n";
		for(ListNode* i = first; i; i = i->next){
			if(!strcmp(i->agency_name, agency_name)){
				int n = i->queue->size;
				for(int j=1; j <=n; j++){
					i->queue->remove();
				}
				break;
			}
		}
		cout << "__________________________________\n";
		
	}
	
	void make_order(char* service_name, char* agency_name, char* customer_name, char* immediacy_level){
		
		node* root = service_list->first;
		node* p = search(service_name, root);
		
		if( p != NULL){
			for(ListNode* i = first; i; i = i->next){
				if(!strcmp(i->agency_name, agency_name)){
					i->queue->add(immediacy_level, p->s,  customer_name);
					cout << "________added successfully________\n";
					break;
				}
			}
		}
		else
			cout << "________service not found________\n";
		
	}
	void add_offer(char* service_name, char* agency_name){
		
		node* root = service_list->first;
		node* p = search(service_name, root);

		if( p != NULL ){
			for(ListNode* i = first; i; i = i->next){
				if(!strcmp(i->agency_name, agency_name)){
					i->sevices.push_back(p);
					(p->agency_num)++;
					
					cout << "________added successfuly________\n";
					break;
					
				}		
			}
		}
		else
			cout << "________service not found________\n";
		
	}
	
	void delete_service(char* service_name, char* agency_name){
		node* root = service_list->first;
		node* p = search(service_name, root);
		
		if( p != NULL){
			
			for(ListNode* i = first; i; i = i->next){
				
				if(!strcmp(i->agency_name, agency_name)){
					int j;
					for(j = 0; j < i->sevices.size(); j++)
						if(!strcmp(i->sevices[j]->s->name, service_name)){
						
							i->sevices.erase(i->sevices.begin()+j);
							(p->agency_num)--;
							if(p->agency_num == 0)
								service_list->remove_service(p->s->name);
								
							cout << "________deleted successfuly________\n";
							break;
						}
			
				}
			}
		}
		else
			cout << "________service not found________\n";
	}

};
void split_command(char* command, char** sub_command){
	
	for(int i=0; i<8; i++)
		strcpy(sub_command[i], "");
	
	
	int c = 0, k = 0, i = 0;
	while(1)
	{
		c = 0;
		for(i; 1; i++){
			if(command[i] == '\0')
			{
				sub_command[k][c] = '\0';
				return ;
			}
			if(command[i] != ' ')
				sub_command[k][c] = command[i];
			else
			{
				sub_command[k][c] = '\0';
				break;
			}
			c++;
		}
		k++;
		i++;

	}
}
	

int main(){
	
	GenLinkedList* servicies = new GenLinkedList;
	LinkedList* agencies = new LinkedList(servicies);
	
	char* command = new char[50];
	char** sub_command = new char*[8];
	for(int i=0; i<8; i++)
		sub_command[i] =  new char[20];
		
	while(1){

		cin.getline(command, 50);
		split_command(command, sub_command);
		
		
		if(!strcmp(sub_command[0], "add")){
			
			if(!strcmp(sub_command[1], "service")){
				
				servicies->add_service(sub_command[2]);
			}
			else if(!strcmp(sub_command[1], "subservice")){
				servicies->add_subservice(sub_command[2], sub_command[4]);
			}
			
			else if(!strcmp(sub_command[1], "offer")){
				agencies->add_offer(sub_command[2], sub_command[4]);
				
			}
			else if(!strcmp(sub_command[1], "agency")){
		
				agencies->add_agency(sub_command[2]);
			}
		}
		else if(!strcmp(sub_command[0], "list")){
			
			if(!strcmp(sub_command[1], "services") && !strcmp(sub_command[2],"from")){
				
				servicies->list_subservices(sub_command[3]);
			}
			else if(!strcmp(sub_command[1], "services")){
				servicies->list_services();
			}
			
			else if(!strcmp(sub_command[1], "agencies")){
		
				agencies->list_agencies();
			}
			else if(!strcmp(sub_command[1], "orders")){
		
				agencies->list_orders(sub_command[2]);
			}
		}
		else if(!strcmp(sub_command[0], "order")){
			agencies->make_order(sub_command[1], sub_command[3], sub_command[5], sub_command[7]);
		}
		else if(!strcmp(sub_command[0], "delete")){
			agencies->delete_service(sub_command[1], sub_command[3]);
		}
		
	
	}
}

