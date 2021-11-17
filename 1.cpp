#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector<int> v(50);
	int a[20][10];
	for(int i = 0; i < 20; i++) {
		for(int j = 0; j < 10; j++) {
			cin >> a[i][j];
		}
	}
	for(int i = 0; i < 20; i++) {
		for(int j = 0; j < 10; j++) {
			v[a[i][j]]++;
		}
	}
	
	for(int i = 0; i < 50; i++) {
		if(v[i] != 0) cout << i << " " << v[i] << "\n"; 
	}
	
	
	return 0;
}
