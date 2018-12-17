#include <bits/stdc++.h>

using namespace std;

#define RAND_SEED time(NULL)
#define MIN_BANDWIDTH 100
#define MAX_BANDWIDTH 1000
#define MIN_DEMAND_BANDWIDTH 100
#define MAX_DEMAND_BANDWIDTH 200

int main(){

	int k, c, num_demands;
	cin >> k >> num_demands;

	int V = k * k / 2 + k * k / 2 + (k / 2) * (k / 2);
	int E = 2 * k * (k / 2) * (k / 2);

	cout << V << " " << E << endl;

	srand(RAND_SEED);
	// EDGE to AGGREGATION
	for (int p = 0; p < k; p++){
		for (int i = 0; i < k / 2; i++){
			for (int j = 0; j < k / 2; j++){
				c = rand() % (MAX_BANDWIDTH - MIN_BANDWIDTH) + MIN_BANDWIDTH;
				cout << p * k / 2 + i << " " << (p + k) * k / 2 + j << " " << c << endl;
			}
		}
	}

	// AGGREGATION to CORE
	for (int p = 0; p < k; p++){
		for (int j = 0; j < k / 2; j++){
			for (int l = 0; l < k / 2; l++){
				c = rand() % (MAX_BANDWIDTH - MIN_BANDWIDTH) + MIN_BANDWIDTH;
				cout << (p + k) * k / 2 + j << " " << k * k + (j * k / 2 + p + l) % (k / 2 * k / 2) << " " << c << endl;
			}
		}
	}

	// Demands
	cout << num_demands << endl;
	for (int d = 0; d < num_demands; d++) {
		int source = rand() % (k * k / 2);
		int destin = source;
		while (destin == source)
			destin = rand() % (k * k / 2);
		int demand = rand() % (MAX_DEMAND_BANDWIDTH - MIN_DEMAND_BANDWIDTH) + MIN_DEMAND_BANDWIDTH;
		cout << source << " " << destin << " " << demand << endl;
	}

	return 0;
}


