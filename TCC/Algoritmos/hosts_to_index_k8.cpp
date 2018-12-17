#include <bits/stdc++.h>

using namespace std;

#define EPS 0.0001

int host_id2switch(string id){
	if (id.size() == 8) return 3000 + (id[3] - '0');
	if (id.size() == 9) return 3000 + 10 * (id[3] - '0') + (id[4] - '0');
	return 3000 + 100 * (id[3] - '0') + 10 * (id[4] - '0') + (id[5] - '0');
}

int switch2index(int entry){
	return entry - 3001;
}

int main(){

	int k = 4, c = 100;

	int V = k * k / 2 + k * k / 2 + (k / 2) * (k / 2);
	int E = 2 * k * (k / 2) * (k / 2);

	cout << V << " " << E << endl;

	// EDGE to AGGREGATION
	for (int p = 0; p < k; p++){
		for (int i = 0; i < k / 2; i++){
			for (int j = 0; j < k / 2; j++){
				cout << p * k / 2 + i << " " << (p + k) * k / 2 + j << " " << c << endl;
			}
		}
	}

	// AGGREGATION to CORE
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 4; j++){
			cout << 8 + 2 * j << " " << 16 + i << " " << c << endl;
		}
	}
	for (int i = 2; i < 4; i++){
		for (int j = 0; j < 4; j++){
			cout << 9 + 2 * j << " " << 16 + i << " " << c << endl;
		}
	}

	int n;
	cin >> n;
	cout << n << endl;
	for (int i = 0; i < n; i++){
		string src, dst;
		cin >> src >> dst;
		float size;
		cin >> size;
		cout << switch2index(host_id2switch(src)) << " " << switch2index(host_id2switch(dst)) << " " << (int)(size * 100 + EPS) << endl;
	}

	return 0;
}
