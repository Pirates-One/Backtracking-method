/*
算法复杂度为n!
测试数据：
test1
4
14 14
14 2
2 4
4 5
最优的计算次数为：572
乘法顺序：((A1A2)(A3A4))

test2
8
9 16
16 4
4 1
1 7
7 2
2 11
11 4
4 16
最优的计算次数为：496
乘法顺序：((A1(A2A3))((((A4A5)A6)A7)A8))
*/

#include<bits/stdc++.h>
using namespace std;

int Min=1e9;
int s[100];
int _min[100];
int n;
vector<vector<int>>matrix(2);


int product(int a,int b,int c) {
	return a*b*c;
}

bool back(int j,int m) {
	for(int i=0; i<m; i++) {
		if(s[i]==j) {
			return false;
		}
	}
	return true;
}


void backtracking(int i,int n) {//回溯
	if(i>n-2) {
		int sum=0;
		vector<vector<int>>_matrix(2);
		_matrix.assign(matrix.begin(),matrix.end());
		for(int k=0; k<n-1; k++) {
			int k1,k2,s1,s2;
			for(k1=k,s1=s[k1]; _matrix[0][s1]==0; s1++);
			for(k2=k,s2=s[k2]; _matrix[0][s2-1]==0; s2--);
			sum=sum+product(_matrix[0][s2-1],_matrix[1][s1],_matrix[0][s1]);
			_matrix[0][s1]=_matrix[0][s2-1];
			_matrix[0][s2-1]=0;
		}
		if(sum<Min) {//更新最优解
			for(int k=0; k<n-1; k++) {
				_min[k]=s[k];
			}
			Min=sum;
		}
		return ;
	}
	for(int j=1; j<n; j++) {
		if(back(j,i)) {
			s[i]=j;
			backtracking(i+1,n);
		}
	}
}

void printf_min() {
	int t[100];
	int p_min[2][100];
	for(int i=0; i<100; i++) {
		t[i]=-1;
		for(int j=0; j<2; j++)
			p_min[j][i]=0;
	}
	for(int i=0; i<n-1; i++) {
		int left=_min[i],right=_min[i]+1;
		if(t[left]==0) {
			for(left--; t[left]==0; left--)if(p_min[1][left]>=p_min[0][_min[i]]) break;
			p_min[1][left]++;
		} else {
			t[left]=0;
			p_min[1][left-1]++;
		}
		if(t[right]==0) {
			for(right++; t[right]==0; right++)if(p_min[0][right-1]>=p_min[1][_min[i]]) break;
			p_min[0][right-1]++;
		} else {
			t[right]=0;
			p_min[0][right]++;
		}
	}
	for(; p_min[1][0]>0; p_min[1][0]--)
		cout<<"(";
	for(int i=1; i<=n; i++) {
		cout<<"A"<<i;
		for(int j=0; p_min[j][i]>0; p_min[j][i]--) {
			cout<<")";
		}
		for(int j=1; p_min[j][i]>0; p_min[j][i]--) {
			cout<<"(";
		}
	}

}

int main() {
	cout<<"请输入矩阵的个数: ";
	cin>>n;
	cout<<"请输入矩阵:"<<endl;
	for(int i=0; i<2; i++)
		matrix[i].resize(n);
	for(int i=0; i<n; i++)
		for(int j=0; j<2; j++) {
			cin>>matrix[j][i];
		}
	backtracking(0,n);
	cout<<endl<<"最优的计算次数为："<<Min<<endl;
	cout<<"乘法顺序："; 
	printf_min();
	return 0;
}
