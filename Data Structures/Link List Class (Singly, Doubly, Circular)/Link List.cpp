/////////////////////////////////////////////////////////////////////////////
//
//		Creator : Sara Baradaran
//		Create Date : Spring 2018
//		Consept : Data Structures & Advanced Programming (Linked List)
//
////////////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>
#include <windows.h>
#define MAX_CRS 2
#define MAX_STU 10
using namespace std;
void setTextColor(int textColor, int backColor = 0)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int colorAttribute = backColor << 4 | textColor;
	SetConsoleTextAttribute(consoleHandle, colorAttribute);
}

class Student {
private:
	string name;
	int id;
	static int id_gen;
	int max_crs_num;
	int crs_num;
public:
	string* crs;
	Student(string name, int crs_num = 100) :name(name), max_crs_num(crs_num), crs_num(0) {
		id_gen = id_gen + 1;
		id = id_gen;
		crs = new string[max_crs_num];

	}

	~Student() {
		cout << "Student destructor\n";
		delete[] crs;
	}

	void add_crs(string *crs, int num) {
		int max = num + crs_num < max_crs_num ? num + crs_num : max_crs_num;
		for (int i = crs_num; i<max; i++) {
			this->crs[i] = *crs;
			crs++;
		}
		crs_num = max;
	}

	void add_crs(string crs_name) {
		if (crs_num == max_crs_num)
			return;
		crs[crs_num] = crs_name;
		crs_num++;

	}

	void print() {
		cout << id << endl << name << endl;
		for (int i = 0; i<crs_num; i++) {
			cout << crs[i] << ",";
		}
		cout << endl;
	}
};
int Student::id_gen = 0;

class node {
public:
	node(Student* stu, int ptr_num, int nodes_num) :stu_info(stu), node_id(nodes_num) {
		ptr = new node*[ptr_num];
	}
	~node() {
		cout << "node "<<node_id<< " destructor is called \n";
		delete [] ptr;
	}//node destructor

private:
	Student* stu_info;
	node** ptr;
	int node_id;
	friend class Singly_LinkedList;
	friend class Circular_LinkedList;
	friend class Doubly_LinkedList;
};
class Singly_LinkedList {
protected:
	node* first;
	node* last;
	node* created_node;
	node* prev_node = NULL;
	int stu_num;
	int ptr_num;
	int node_id_gen;
	bool stu_found;
public:
	Singly_LinkedList() : first(NULL), last(NULL), stu_num(0), ptr_num(1), node_id_gen(0) {}
	void add_node(Student *stu) {
		node_id_gen++;
		created_node = new node(stu, ptr_num, node_id_gen);

		if (first == NULL) {
			first = created_node;
			last = first;
			last->ptr[0] = NULL;
		}
		else {
			last->ptr[0] = created_node;
			prev_node = last;
			last = created_node;
			last->ptr[0] = NULL;
		}
		stu_num++;

	}//end of add_node
	void remove_node(int no) {
		node* temp = first;
		stu_found = false;
		prev_node = NULL;

		if (temp->node_id == no) {
			first = first->ptr[0];
			stu_found = true;
		}
		else {
			for (int i = 1; i <= stu_num; i++) {
				if (temp->node_id == no) {
					if (temp == last)
						last = prev_node;

					prev_node->ptr[0] = temp->ptr[0];
					stu_found = true;
					break;
				}
				else if (temp->node_id > no || i == stu_num) {
					cout << "Student with this id was not finded\n";
					break;
				}
				prev_node = temp;
				temp = temp->ptr[0];
			}
		}
		if (stu_found) {
			delete temp;
			stu_num--;
		}

	}//end of remove node

	void print_info() {
		node* temp = first;
		if (stu_num == 0)
			cout << "There is not any student's information to print !\n";
		for (int i = 0; i<stu_num; i++) {
			temp->stu_info->print();
			cout << endl;
			temp = temp->ptr[0];
		}
	}//print list
	~Singly_LinkedList() {
		cout << "Singly_LinkedList destructor is called\n";
		node* temp;
		for (int i = 0; i<stu_num; i++) {
			temp = first;
			if (temp->ptr[0] != NULL)
				first = temp->ptr[0];
			delete temp;
		}
	}//Singly_LinkedList destructor
};

class Circular_LinkedList : public Singly_LinkedList {

public:
	Circular_LinkedList() {}
	void add_node(Student* stu) {
		Singly_LinkedList::add_node(stu);
		last->ptr[0] = first;
	}
	~Circular_LinkedList() {
		cout << "Circular_LinkedList destructor is called\n";
	}//Circular_LinkedList destructor

};

class Doubly_LinkedList : public Singly_LinkedList {
public:
	Doubly_LinkedList() {
		ptr_num = 2;
	}
	void add_node(Student *stu) {
		Singly_LinkedList::add_node(stu);
		last->ptr[1] = prev_node;
	}
	void remove_node(int no) {
		Singly_LinkedList::remove_node(no);
		if (stu_found) {
			first->ptr[1] = NULL;
			if (prev_node != NULL && prev_node->ptr[0] != NULL)
				prev_node->ptr[0]->ptr[1] = prev_node;
		}
	}
	~Doubly_LinkedList() {
		cout << "Doubly_LinkedList destructor is called\n";
	}//Doubly_LinkedList destructor
};
int main() {
	Singly_LinkedList l1;
	Circular_LinkedList l2;
	Doubly_LinkedList l3;
	string stu_name;
	string crs_name[MAX_CRS];
	Student* stu[MAX_STU];
	crs_name[0] = "Math";
	crs_name[1] = " Advanced Programming";

	for (int i = 0; i < MAX_STU; i++) {
		cout << "Enter the name of student " << i + 1 << " : ";
		getline(cin, stu_name);
		stu[i] = new Student(stu_name, MAX_CRS);
		for (int j = 0; j < MAX_CRS; j++)
			stu[i]->add_crs(crs_name[j]);
		l1.add_node(stu[i]);
		l2.add_node(stu[i]);
		l3.add_node(stu[i]);
	}

	setTextColor(11, 0);
	cout << "information of Singly_LinkedList:" << endl;
	setTextColor(14, 0);
	l1.print_info();
	setTextColor(11, 0);
	cout << "information of Circular_LinkedList :" << endl;
	setTextColor(14, 0);
	l2.print_info();
	setTextColor(11, 0);
	cout << "information of Doubly_LinkedList:" << endl;
	setTextColor(14, 0);
	l3.print_info();
	setTextColor(7, 0);
	for (int i = 0; i < MAX_STU; i++)
		delete stu[i];
	return 0;
}

