#include <bits/stdc++.h>

using namespace std;

#define EPS 0.0001

map<int, int> convert;
bool criado = false;

int host_id2switch(string id){
	int aux = ((id[3] - '0' - 1) * 2) + (id[7] - '0');
	return 3000 + (aux + 1) / 2;
}

int switch2index(int entry){
	if (!criado){
		criado = true;
		convert[1001] = 16;
		convert[1002] = 17;
		convert[1003] = 18;
		convert[1004] = 19;
		convert[2001] = 8;
		convert[2002] = 9;
		convert[2003] = 10;
		convert[2004] = 11;
		convert[2005] = 12;
		convert[2006] = 13;
		convert[2007] = 14;
		convert[2008] = 15;
		convert[3001] = 0;
		convert[3002] = 1;
		convert[3003] = 2;
		convert[3004] = 3;
		convert[3005] = 4;
		convert[3006] = 5;
		convert[3007] = 6;
		convert[3008] = 7;
	}
	return convert[entry];
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
			cout << 8 + (2 * j) << " " << 16 + i << " " << c << endl;
		}
	}
	for (int i = 2; i < 4; i++){
		for (int j = 0; j < 4; j++){
			cout << 9 + (2 * j) << " " << 16 + i << " " << c << endl;
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

