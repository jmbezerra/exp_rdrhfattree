#include <bits/stdc++.h>

using namespace std;

string int2string(int n){
	string r = "";
	while (n > 0){
		r += n % 10 + '0';
		n = n / 10;
	}
	reverse(r.begin(), r.end());
	return r;
}

string convert(int n){
	if (n < 32) return int2string(3001 + n);
	if (n < 64) return int2string(2001 + n - 32);
	return int2string(1001 + n - 64);
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