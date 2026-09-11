#include "../Graph.h"
#include <thread>



template <class T, typename Derived>
int IGraph<T, Derived>::findComponent(int vertex, int* parent) {
    if (parent[vertex] != vertex) {
        parent[vertex] = findComponent(parent[vertex], parent);
    }
    return parent[vertex];
}

template <class T, typename Derived>
void IGraph<T, Derived>::unionComponents(int u, int v, int* parent, int* rank) {
    int rootU = findComponent(u, parent);
    int rootV = findComponent(v, parent);

    if (rootU != rootV) {
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

template <class T, typename Derived>
void IGraph<T, Derived>::BoruvkaMSTStep(int* parent, std::atomic<T>* cheapestWeight, std::atomic<int>* cheapestFrom, std::atomic<int>* cheapestVertex, int start, int end) {
	for (int u = start; u < end; ++u) {
		int uComponent = findComponent(u, parent);
		auto it = neighbors(u);

		while (it.hasNext()) {
			auto [v, weight] = it.next();
			int vComponent = findComponent(v, parent);

			if (uComponent != vComponent) {
				T currentWeight = cheapestWeight[uComponent].load();
				if (weight < currentWeight) {
					cheapestWeight[uComponent].store(weight);
                    cheapestFrom[uComponent].store(u);
					cheapestVertex[uComponent].store(v);
				}
				currentWeight = cheapestWeight[vComponent].load();
				if (weight < currentWeight) {
					cheapestWeight[vComponent].store(weight);
                    cheapestFrom[vComponent].store(v);
					cheapestVertex[vComponent].store(u);
				}
			}
		}
	}
}



template <class T, typename Derived>
IGraph<T, Derived>* IGraph<T, Derived>::BoruvkaMST(int numThreads) {
    int* parent = new int[number_of_vertices];
	int* rank 	= new int[number_of_vertices];
	std::atomic<T>*   cheapestWeight = new std::atomic<T>  [number_of_vertices];
    std::atomic<int>* cheapestFrom = new std::atomic<int>[number_of_vertices];
	std::atomic<int>* cheapestVertex = new std::atomic<int>[number_of_vertices];

	for (int i = 0; i < number_of_vertices; ++i) {
		parent[i] = i;
		rank[i] = 0;
		cheapestWeight[i].store(inf);
		cheapestVertex[i].store(-1);
	}

	int numComponents = number_of_vertices;
	IGraph<T, Derived>* mstGraph = clone();
	mstGraph->clear();
	
	while (numComponents > 1) {
		for (int i = 0; i < number_of_vertices; ++i) {
			cheapestWeight[i].store(inf);
			cheapestFrom[i].store(-1);
        	cheapestVertex[i].store(-1);
		}

		std::vector<std::thread> threads(numThreads);
		int verticesPerThread = (number_of_vertices + numThreads - 1) / numThreads;

		// divide graph's verticies into number of threads and wait till it ends
		for (int threadIndex = 0; threadIndex < numThreads; ++threadIndex) {
			int start = threadIndex * verticesPerThread;
			int end = std::min(start + verticesPerThread, (int)number_of_vertices);

			 threads[threadIndex] = std::thread([=, this]() {
				this->BoruvkaMSTStep(parent, cheapestWeight, cheapestFrom, cheapestVertex, start, end);
			});	
		}

		for (auto &t : threads) {
			t.join();
		}
		
		//connect all mini mst
		bool anyEdgeAdded = false;
		for (int component = 0; component < number_of_vertices; ++component) {
			if (findComponent(component, parent) != component) continue;

            int from = cheapestFrom[component].load();
            int to = cheapestVertex[component].load();
			if (from == -1 || to == -1) continue;

			int fromComponent = findComponent(from, parent);
            int toComponent = findComponent(to, parent);
            if (fromComponent != toComponent) {
                T weight = cheapestWeight[component].load();
                mstGraph->addEdge(from, to, weight);
                unionComponents( fromComponent, toComponent, parent, rank);
                numComponents--;
                anyEdgeAdded = true;
            }
		}

		if (!anyEdgeAdded) {
			break;
		}
	}

	delete[] parent;
	delete[] rank;
	delete[] cheapestWeight;
	delete[] cheapestVertex;

	return mstGraph;
}