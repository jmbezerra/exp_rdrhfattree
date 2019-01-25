#g++ k_to_fat_tree_random.cpp -o make_fat_tree
# para setar o valor de k alterar os arquivos hosts_to_index_k8.cpp e index_to_switchs_k8.cpp
g++ ./TCC/Algoritmos/hosts_to_index_k4.cpp -o ./TCC/Algoritmos/make_fat_tree
g++ -L. -L/opt/ibm/ILOG/CPLEX_Studio1261/cplex/lib/x86-64_linux/static_pic -L/opt/ibm/ILOG/CPLEX_Studio1261/concert/lib/x86-64_linux/static_pic -I. -I/opt/ibm/ILOG/CPLEX_Studio1261/cplex/include/ -I/opt/ibm/ILOG/CPLEX_Studio1261/concert/include ./TCC/Algoritmos/multi_commodity.cpp -o ./TCC/Algoritmos/multi_commodity -DIL_STD -lilocplex -lcplex -lconcert -m64 -lm -pthread -O3 -DLONG_MAX
g++ ./TCC/Algoritmos/sorteio.cpp -o ./TCC/Algoritmos/sorteio
g++ ./TCC/Algoritmos/index_to_switchs_k4.cpp -o ./TCC/Algoritmos/index_to_switchs
