///////////////////////////////////////////////////
//
//		Creator : Sara Baradaran
//		Create Date : Fall 2019
//		Consept : Greedy Algorithms
//
///////////////////////////////////////////////////

#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

class p{
public:	
	int x;
	int y;
} *a;


float** dis;
bool** msp_mat;
int max_dis, point_num , state_num;
float min_way, min_rail; 

bool find(vector<int> &v, int s){
	for(int i=0; i<v.size(); i++)
		if(v[i] == s)
			return 1;
	return 0;
}
/*
void print(vector<int>&v){
	for(int i=0; i<v.size(); i++)
		cout << v[i] << " ";
	cout << endl;	
}
*/
int find_nearest(int x, float &min_dis, vector<int> &v){
	
	min_dis = 9999999999;
	float m;
	int nearest = -1;

	for(int i=0; i< point_num; i++){
		m = dis[i][x];
	//	cout << "dis [ " << i << " ][ " << x << " ] = " << m << endl;
		if(m < min_dis && find(v, i) == 0 && x != i){
			min_dis = m;
			nearest = i;
		}
	}
	return nearest;
		
}

void msp(){
	
	vector<int> v;
	v.push_back(0);
	
	int nearest, m, t;
	float min_dis_x;
	float min_dis = 9999999999;
	
	while(v.size() != point_num){
		min_dis = 9999999999;
		for(int x=0; x< v.size(); x++){
			m =	find_nearest(v[x], min_dis_x, v);
		//	cout << min_dis_x << " _____________ \n";
			if(min_dis_x < min_dis){
				nearest = m;
				min_dis = min_dis_x;
				t = v[x];
			}
		}
	//	cout << "nearest to " << t << " = " << nearest << endl;
		v.push_back(nearest);
		msp_mat[nearest][t] = msp_mat[t][nearest]= 1;
		if(dis[nearest][t] > max_dis){
			min_rail += dis[nearest][t];
			state_num++;
		}
		else{
			min_way += dis[nearest][t];
		}
	}
}
int F(float k){
	int w = k;
	if(k-w >=0.5)
		return w+1;
	else
		return w;	
}
int main(){
	int n, counter = 1;
	cin >> n;
	
	while(counter <= n){
		
		state_num = 1;
		min_way = min_rail = 0;
		
		cin >> point_num >> max_dis;
		
		a = new p[point_num];
		
		for(int i=0; i< point_num; i++)
			cin >> a[i].x >> a[i].y;
			
		dis = new float*[point_num];	
		for(int i=0; i< point_num; i++)
			dis[i] = new float[point_num];
			
		for(int i=0; i< point_num; i++){
			dis[i][i] = 0;
			for(int j=i+1; j< point_num; j++)
				dis[i][j] = dis[j][i] = sqrt(pow((a[i].x - a[j].x), 2) + pow((a[i].y - a[j].y), 2));
		}
		msp_mat = new bool*[point_num];
		for(int i=0; i< point_num; i++)
			msp_mat[i] = new bool[point_num];
		
		for(int i=0; i< point_num; i++)
			for(int j=0; j < point_num; j++)
				msp_mat[i][j] = 0;	
			
		msp();
		
		delete [] a;
		for(int i=0; i< point_num; i++)
			delete [] dis[i];
		delete [] dis;
		for(int i=0; i< point_num; i++)
			delete [] msp_mat[i];
		delete [] msp_mat;
			

		cout << "Case #" << counter << ": " << state_num << " " << F(min_way) << " " << F(min_rail) << endl;
		counter++;
	}	
}

