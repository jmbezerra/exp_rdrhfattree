#include <bits/stdc++.h>

using namespace std;

string convert(int n){
	switch (n){
		case 0: return "3001";
		case 1: return "3002";
		case 2: return "3003";
		case 3: return "3004";
		case 4: return "3005";
		case 5: return "3006";
		case 6: return "3007";
		case 7: return "3008";
		case 8: return "2001";
		case 9: return "2002";
		case 10: return "2003";
		case 11: return "2004";
		case 12: return "2005";
		case 13: return "2006";
		case 14: return "2007";
		case 15: return "2008";
		case 16: return "1001";
		case 17: return "1002";
		case 18: return "1003";
		case 19: return "1004";
	}
}

int main(){

	int n;

	cin >> n;
	cout << n << endl;

	for (int i = 0; i < n; i++){
		int m;
		cin >> m;
		cout << m << endl;
		for (int j = 0; j < m; j++){
			int index;
			cin >> index;
			cout << convert(index) << " ";
		}
		cout << endl;
	}

	return 0;
}