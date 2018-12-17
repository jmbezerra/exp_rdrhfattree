#include <bits/stdc++.h>
#include <ilcplex/ilocplex.h>

ILOSTLBEGIN

using namespace std;

ofstream results;

vector<list<int> > g;
vector<vector<double> > w;
vector<pair<pair<int, int>, int> > commodities;
vector<vector<vector<IloNumVar> > > f;

double solver(){
	IloEnv env;
	double soluction = 0;
	try {
	
		IloModel model(env);

		IloNumVar y(env, -IloInfinity, IloInfinity, ILOINT, "y");

		IloExpr objective(env);
		objective = y;
		model.add(IloObjective(env, objective, IloObjective::Minimize));
		objective.end();

		char name[20];

		//IloNumVar f[commodities.size()][g.size()][g.size()];
		f.resize(commodities.size());
		for (int i = 0; i < commodities.size(); i++){
			f[i].resize(g.size());
			for (int j = 0; j < g.size(); j++){
				f[i][j].resize(g.size());
			}
		}

		for (int i = 0; i < commodities.size(); i++){
			for (int j = 0; j < g.size(); j++){
				for (list<int>::iterator k = g[j].begin(); k != g[j].end(); k++){
					sprintf(name, "f_%d_%d_%d", i, j, *k);
					IloNumVar v(env, 0, 1, ILOFLOAT, name);
					f[i][j][*k] = v;

					sprintf(name, "f_%d_%d_%d", i, *k, j);
					IloNumVar v_(env, 0, 1, ILOFLOAT, name);
					f[i][*k][j] = v_;
				}
			}
		}

		for (int u = 0; u < g.size(); u++){
			for (list<int>::iterator v = g[u].begin(); v != g[u].end(); v++){
				IloExpr link_capacity(env);
				for (int i = 0; i < commodities.size(); i++){
					link_capacity += f[i][u][*v] * commodities[i].second;
					link_capacity += f[i][*v][u] * commodities[i].second;
				}
				//link_capacity - w <= y
				link_capacity += - y - w[u][*v];
				model.add(IloRange(env, -IloInfinity, link_capacity, 0));
				link_capacity.end();
			}
		}		

		for (int i = 0; i < commodities.size(); i++){
			for (int u = 0; u < g.size(); u++){
				IloExpr flow_conservation(env);
				if (u != commodities[i].first.first && u != commodities[i].first.second){
					for (list<int>::iterator w = g[u].begin(); w != g[u].end(); w++){
						flow_conservation += f[i][*w][u] - f[i][u][*w];
					}
					model.add(IloRange(env, 0, flow_conservation, 0));
				}
				flow_conservation.end();
			}
		}

		for (int i = 0; i < commodities.size(); i++){
			int si = commodities[i].first.first;
			IloExpr flow_conservation_source(env);
			for (list<int>::iterator w = g[si].begin(); w != g[si].end(); w++){
				flow_conservation_source += f[i][si][*w] - f[i][*w][si];
			}
			model.add(IloRange(env, 1, flow_conservation_source, 1));
			flow_conservation_source.end();
		}

		for (int i = 0; i < commodities.size(); i++){
			int fi = commodities[i].first.second;
			IloExpr flow_conservation_destination(env);
			for (list<int>::iterator w = g[fi].begin(); w != g[fi].end(); w++){
				flow_conservation_destination += f[i][*w][fi] - f[i][fi][*w];
			}
			model.add(IloRange(env, 1, flow_conservation_destination, 1));
			flow_conservation_destination.end();
		}


		IloCplex cplex(model);
		cplex.solve();

		if (cplex.getStatus() == IloAlgorithm::Optimal){
			ofstream file("./TCC/Algoritmos/probs.dat");

			file << g.size() << " " << commodities.size() << endl;

//			cout << cplex.getObjValue() << endl;
			results << cplex.getObjValue() << endl;

			for (int i = 0; i < commodities.size(); i++){
				file << commodities[i].first.first << " " << commodities[i].first.second << endl;
				int n = 0; //numero maximo de sorteios por commoditie
				stringstream probs;
				for (int j = 0; j < g.size(); j++){
					for (list<int>::iterator k = g[j].begin(); k != g[j].end(); k++){
						if (cplex.getValue(f[i][j][*k]) != 0){
//							cout << i << ": " << j << "->" << *k << " " << cplex.getValue(f[i][j][*k]) << endl;
							n++;
							probs << j << " " << *k << " " << cplex.getValue(f[i][j][*k]) << endl;
						}
					}
				}
				file << n << endl << probs.str();
			}
			file.close();
		}
    }
    catch(IloException& ex){
        cerr << "Erro no Cplex" << ex << endl;
    }
    catch(std::exception& e){
        cerr << "Erro no Cplex" << e.what() << endl;
    }
    env.end();
    return 0;
}

int main(){
	results.open("./TCC/Algoritmos/results.txt");

	int V, E, k;

	cin >> V >> E;

	k = sqrt(4 * V / 5);

	g.resize(V);
	w.resize(V);
	for (int i = 0; i < V; i++){
		w[i].resize(V);
	}


	int u, v;
	double W;

	for (int i = 0; i < E; i++){
		cin >> u >> v >> W;
		g[u].push_back(v);
		g[v].push_back(u);
		w[u][v] = w[v][u] = W;
	}

	int p;
	cin >> p;
	for (int i = 0; i < p; i++){
		cin >> u >> v >> W;
		commodities.push_back(make_pair(make_pair(u, v), W));
	}

	clock_t begin_time = clock();
	solver();
    clock_t end_time = clock();

    cout << (double)(end_time-begin_time)/CLOCKS_PER_SEC << endl;
    results << (double)(end_time-begin_time)/CLOCKS_PER_SEC << endl;

    results.close();

	return 0;
}

