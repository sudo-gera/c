#include <iostream>

using namespace std;

int main(){
	int n;
	cin>>n;
	int matrix[100][100];
	for (int i=0;i<n;i++){
		for (int j=0;j<n;j++){
			cin>>matrix[i][j];
		}
	}
	int min=9999;
	int min_i,min_j,min_k;
	for (int i=0;i<n;i++){
		for (int j=0;j<n;j++){
			for (int k=0;k<n;k++){
				if (i!=j and j!=k and k!=i){
					if (matrix[i][j]+matrix[j][k]+matrix[k][i]<min){
						min=matrix[i][j]+matrix[j][k]+matrix[k][i];
						min_i=i+1;
						min_j=j+1;
						min_k=k+1;
					}
				}
			}
		}
	}
	cout<<min_i<<' '<<min_j<<' '<<min_k<<endl;
}
