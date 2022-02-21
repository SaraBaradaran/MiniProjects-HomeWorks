
#include <iostream>
#include <queue>
#include <stack>
#include <stdlib.h>
#include <string.h>
using namespace std;
int ** network;
int * is_exist;

void showq(queue<int> g)
{
	stack<int> p;
	stack<int> p2;
	
    while (!g.empty()) {
        p.push(g.front());
        g.pop();
    }
    int end, x;
    end = p.top();
    p.pop();
    p2.push(end);
    while(p.top() != -1){
    	p.pop();
	}
	p.pop();
    int min;
    
    while(!p.empty()){
    	x = p.top();
    	p.pop();
    	if (x != -1){	
    		if(network[x][end]){
    			min = x;
			}
		}
		else{
			p2.push(min);
			end = min;
		}
	}
	p2.push(min);
	while (!p2.empty()) {
        cout << p2.top() << " ";
        p2.pop();
    }
    cout << "\n";
}

void BFS(int start, int end, int n){
	
	int next, x;
	bool goal = 0;
	queue<int> explored;
	queue<int> frontier;
	frontier.push(start);
	frontier.push(-1);
	while(!frontier.empty()){
		next = frontier.front();
		frontier.pop();
		if(next == -1){
			if(frontier.back() != -1)
				frontier.push(-1);
			explored.push(-1);
			continue;
		}
		if (next == end){
			explored.push(next);
			goal = 1;
			break;
		}
		is_exist[next] = 1;
		for(int i=1; i<=n; i++){
			x = network[next][i];
			if(x == 1){
				if(!is_exist[i]){
					frontier.push(i);
					is_exist[i] = 1;
				}
			}
		}
		explored.push(next);
	}
	if (!goal){
		cout << "connection impossible\n";
	}
	else
		showq(explored);
}

void split(char* str){
	
    char *tok;
    char *ptr = str;
	bool first = 1;
	int start;
    while ((tok = strtok(ptr, ",-")) != NULL)
    {
    	if(first){
    		start = atoi(tok);	
    		first = 0;
		}
    	else{
        	network[start][atoi(tok)] = 1;
    	}
        ptr = NULL;
    }
}

int main(){
	
	int n;
	char str[110];
	while(1){
		
		cin >> n;
		network = new int* [n+1];
		for(int i=0; i<=n; i++)
			network[i] = new int[n+1];
		
		for(int i=1; i<=n; i++){
			memset (network[i],0,(n+1)*4);
		}

		is_exist = new int [n+1];
		memset (is_exist,0,(n+1)*4);
		
		for(int i=0; i<n; i++){
			cin >> str;
			split(str);
		}
		
		int m, start, end;
		cin >> m;
		for(int i=0; i<m; i++){
			cin >> start >> end;
			BFS(start, end, n);
		}
		
		delete [] is_exist;
		for(int i=0; i<=n; i++)
			delete [] network[i];
				
	}
}
