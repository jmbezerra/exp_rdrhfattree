#include <bits/stdc++.h>

using namespace std;

#define RAND_SEED time(NULL)

vector<vector<float> > p;
int V, d;
int d_;

fstream results;

vector<vector<pair<int, int> > > g;
map<pair<int, int>, int> commodities;

list<int> sortear(int i, int destination){
	if (i == destination){
		list<int> r;
		r.push_back(i);
		return r;
	}
	vector<pair<int, float> > prob;
	for (int j = 0; j < V; j++){
		if (p[i][j] > 0){
			if (prob.empty())
				prob.push_back(make_pair(j, p[i][j]));
			else
				prob.push_back(make_pair(j, prob.back().second + p[i][j]));
		}
	}

	for (int j = 0; j < prob.size(); j++){
		prob[j].second = prob[j].second / prob.back().second;
	}

	float s = ((float)rand()) / RAND_MAX;

	int j = 0;
	while (j < prob.size() - 1 && s > prob[j].second){
		j++;
	}

	list<int> path = sortear(prob[j].first, destination);

	path.push_front(i);

	return path;
}

int main(){
	srand(RAND_SEED);
	results.open("./TCC/Algoritmos/results_.txt");

	list<list<int> > alocation;

	//criando a arvore
	fstream file;
	file.open("./TCC/Algoritmos/in.txt", fstream::in);
	int E;
	file >> V >> E;

	g.resize(V);

	int u, v, w;
	for (int i = 0; i < E; i++){
		file >> u >> v >> w;
		g[u].push_back(make_pair(v, w));
		g[v].push_back(make_pair(u, w));
	}

	int num_commodities;
	file >> num_commodities;
	for (int i = 0; i < E; i++){
		file >> u >> v >> w;
		commodities.insert(make_pair(make_pair(u, v), w));
	}	

	cin >> V >> d;
	p.resize(V);

	double t = 0;

	for (d_ = 0; d_ < d; d_++){
		//zerar matriz de probabilidades
		for (int i = 0; i < V; i++){
			p[i].assign(V, 0);
		}

		int u, v, source, destination, n;
		float p_;
		cin >> source >> destination;
		cin >> n; //quantidade de possiveis sorteios para demanda d_
		for (int i = 0; i < n; i++){
			cin >> u >> v >> p_;
			p[u][v] = p_;
		}

		clock_t begin_time = clock();
		list<int> path = sortear(source, destination);
		clock_t end_time = clock();

		alocation.push_back(path);

		t +=  (double)(end_time-begin_time)/CLOCKS_PER_SEC;
	}

	for (list<list<int> >::iterator it = alocation.begin(); it != alocation.end(); it++){
		int bandwidth = commodities[make_pair(it->front(), it->back())];
		bool flag = false;
		int u, v;
		for (list<int>::iterator itt = it->begin(); itt != it->end(); itt++){
			v = u;
			u = *itt;
			cout << u << " ";
			if (flag){
				for (int i = 0; g[v][i].first != u; i++){
					g[v][i].second -= bandwidth;
				}
				for (int i = 0; g[u][i].first != v; i++){
					g[u][i].second -= bandwidth;
				}
			}
			flag = true;
		}
		cout << endl;
	}

	int maior_sobrecarga = 1<<30;
	for (int i = 0; i < g.size(); i++){
		for (int j = 0; j < g[i].size(); j++){
			maior_sobrecarga = min(maior_sobrecarga, g[i][j].second);
		}
	}

	cout << -maior_sobrecarga << endl;
	cout << t << endl;

	//results << -maior_sobrecarga << endl << t << endl;

	results << alocation.size() << endl;
	for (list<list<int> >::iterator it = alocation.begin(); it != alocation.end(); it++){
		results << it->size() << endl;
		for (list<int>::iterator itt = it->begin(); itt != it->end(); itt++){
			results << *itt << " ";
		}
		results << endl;
	}

	results.close();
	file.close();

	return 0;
}
