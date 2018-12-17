#include <bits/stdc++.h>

using namespace std;

int main(){

	int k, c;
	cin >> k >> c;

	int V = k * k / 2 + k * k / 2 + (k / 2) * (k / 2);
	int E = 2 * k * (k / 2) * (k / 2);

	cout << V << " " << E << endl;

	for (int p = 0; p < k; p++){
		for (int i = 0; i < k / 2; i++){
			for (int j = 0; j < k / 2; j++){
				cout << p * k / 2 + i << " " << (p + k) * k / 2 + j << " " << c << endl;
			}
		}
	}

	for (int p = 0; p < k; p++){
		for (int j = 0; j < k / 2; j++){
			for (int l = 0; l < k / 2; l++){
				cout << (p + k) * k / 2 + j << " " << k * k + (j * k / 2 + p + l) % (k / 2 * k / 2) << " " << c << endl;
			}
		}
	}

	return 0;
}