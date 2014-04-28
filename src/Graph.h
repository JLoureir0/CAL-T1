/*
 * Graph.h
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <climits>
#include <cmath>
#include <cstdio>
#include <sstream>
#include <stack>

#include "Constants.h"

using namespace std;

template<class T> class Edge;
template<class T> class Graph;

const int NOT_VISITED = 0;
const int BEING_VISITED = 1;
const int DONE_VISITED = 2;
const int INT_INFINITY = INT_MAX;


/*
 * ================================================================================================
 * Class Vertex
 * ================================================================================================
 */
template<class T>
class Vertex {
	T info;
	bool visited;
	bool processing;
	double dist;
	vector<Edge<T> > adj;
	vector<Vertex<T>*> reachableWithinRange;
public:
	Vertex(T in);
	friend class Graph<T> ;
	void addEdge(Vertex<T> *dest, double w);
	void addPrevEdge(Vertex<T> *source, double w);
	bool removeEdgeTo(Vertex<T> *d);
	T getInfo() const;
	void setInfo(T info);
	int getDist() const;
	int getIndegree() const;
	bool operator<(const Vertex<T> vertex);
	Vertex* path;
};

template<class T>
struct vertex_greater_than {
	bool operator()(Vertex<T> * a, Vertex<T> * b) const {
		return a->getDist() > b->getDist();
	}
};

template<class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	typename vector<Edge<T> >::iterator it = adj.begin();
	typename vector<Edge<T> >::iterator ite = adj.end();
	while (it != ite) {
		if (it->dest == d) {
			adj.erase(it);
			return true;
		} else
			it++;
	}
	return false;
}

template<class T>
Vertex<T>::Vertex(T in) :
		info(in), visited(false), processing(false), dist(0) {
	path = NULL;
}

template<class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double w) {
	Edge<T> edgeD(dest, w);
	adj.push_back(edgeD);
}

//--
template<class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template<class T>
int Vertex<T>::getDist() const {
	return this->dist;
}

template<class T>
void Vertex<T>::setInfo(T info) {
	this->info = info;
}

/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */
template<class T>
class Edge {
	Vertex<T> * dest;
	double weight;
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T> ;
	friend class Vertex<T> ;
};

template<class T>
Edge<T>::Edge(Vertex<T> *d, double w) :
		dest(d), weight(w) {
}

/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */
template<class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
	static Vertex<T> * vertexInRange;
public:
	bool addVertex(const T &in);
	bool removeVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeEdge(const T &sourc, const T &dest);
	vector<Vertex<T> *> getVertexSet() const;
	int getNumVertex() const;

	Vertex<T>* getVertex(const T &v) const;

	void bellmanFordShortestPath(const T &s);

	void drawGraph() const;
	vector<Vertex<T>*> getVertexInRange(int range, Vertex<T> * vertex) const;
	void recursivePath(vector<Vertex<T>*> *res, Vertex<T>* v, int range, Vertex<T> * originalVertex) const;
	void attributeHealthUnits();
	vector<Vertex<T>*> sortByReachableLocations(vector<Vertex<T> *> Vertexes);
	void attributeHealthUnitsStage2();
	double calculateMedium(vector<Vertex<T> *> vertexes, int position);
};

template<class T>
bool Graph<T>::addVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	for (; it != ite; it++)
		if ((*it)->info == in)
			return false;
	Vertex<T> *v1 = new Vertex<T>(in);
	vertexSet.push_back(v1);
	return true;
}

template<class T>
bool Graph<T>::removeVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	for (; it != ite; it++) {
		if ((*it)->info == in) {
			Vertex<T> * v = *it;
			vertexSet.erase(it);
			typename vector<Vertex<T>*>::iterator it1 = vertexSet.begin();
			typename vector<Vertex<T>*>::iterator it1e = vertexSet.end();
			for (; it1 != it1e; it1++) {
				(*it1)->removeEdgeTo(v);
			}

			typename vector<Edge<T> >::iterator itAdj = v->adj.begin();
			typename vector<Edge<T> >::iterator itAdje = v->adj.end();
			for (; itAdj != itAdje; itAdj++) {
				itAdj->dest->indegree--;
			}
			delete v;
			return true;
		}
	}
	return false;
}

template<class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	int found = 0;
	Vertex<T> *vS, *vD;
	while (found != 2 && it != ite) {
		if ((*it)->info == sourc) {
			vS = *it;
			found++;
		}
		if ((*it)->info == dest) {
			vD = *it;
			found++;
		}
		it++;
	}
	if (found != 2)
		return false;
	vS->addEdge(vD, w);
	vD->addEdge(vS,w);

	return true;
}

template<class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	int found = 0;
	Vertex<T> *vS, *vD;
	while (found != 2 && it != ite) {
		if ((*it)->info == sourc) {
			vS = *it;
			found++;
		}
		if ((*it)->info == dest) {
			vD = *it;
			found++;
		}
		it++;
	}
	if (found != 2)
		return false;

	vD->indegree--;

	return vS->removeEdgeTo(vD);
}

template<class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

template<class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template<class T>
Vertex<T>* Graph<T>::getVertex(const T &v) const {
	for (unsigned int i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == v)
			return vertexSet[i];
	return NULL;
}

template<class T>
void Graph<T>::bellmanFordShortestPath(const T &s) {

	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
	}

	Vertex<T>* v = getVertex(s);
	v->dist = 0;
	queue< Vertex<T>* > q;
	q.push(v);

	while( !q.empty() ) {
		v = q.front(); q.pop();
		for(unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T>* w = v->adj[i].dest;
			if(v->dist + v->adj[i].weight < w->dist) {
				w->dist = v->dist + v->adj[i].weight;
				w->path = v;
				q.push(w);
			}
		}
	}
}

template<class T>
void Graph<T>::drawGraph() const {
	int vertexID = 0;
	int edgeID = 0;
	vector<int> destinations;
	vector<int> sources;

	GraphViewer *graphviewer = new GraphViewer(WINDOW_WIDTH, WINDOW_HEIGHT, true);
	graphviewer->createWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
	graphviewer->setBackground("background.jpg");
	graphviewer->defineVertexColor("blue");
	graphviewer->defineEdgeColor("black");

	typename vector<Vertex<T> *>::const_iterator it = vertexSet.begin();
	typename vector<Vertex<T> *>::const_iterator ite = vertexSet.end();
	for (; it != ite; it++) {

		if((*it)->info.getHealthUnit())
			graphviewer->setVertexColor(vertexID,"red");
		else
			graphviewer->setVertexColor(vertexID,"blue");

		graphviewer->addNode(vertexID);
		graphviewer->setVertexLabel(vertexID, (*it)->info.getName());
		vertexID++;
	}

	for (int i = 0; i < vertexSet.size(); i++) {
		typename vector<Edge<T> >::const_iterator ited = vertexSet[i]->adj.begin();
		typename vector<Edge<T> >::const_iterator itede = vertexSet[i]->adj.end();
		for (; ited != itede; ited++) {
			for (int j = 0; vertexSet.size(); j++) {
				bool found = false;
				for(unsigned int n = 0; n < destinations.size(); n++) {
					if(i == destinations[n] && j == sources[n]) {
						found = true;
						break;
					}
				}

				if ((*ited).dest->info == vertexSet[j]->info && !found) {
					graphviewer->addEdge(edgeID, i, j, EdgeType::UNDIRECTED);
					destinations.push_back(j);
					sources.push_back(i);
					ostringstream weight;
					weight << ((*ited).weight);
					graphviewer->setEdgeLabel(edgeID, weight.str());
					edgeID++;
					break;
				}
				else if((*ited).dest->info == vertexSet[j]->info && found) {
					break;
				}
			}
		}
	}
	graphviewer->rearrange();
}

template<class T>
vector<Vertex<T>*> Graph<T>::getVertexInRange(int range, Vertex<T> * vertex) const {
	vector<Vertex<T>*> res;

	while(!distances.empty())
		distances.pop();

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->visited = false;
	}

	distances.push(0);
	recursivePath(&res, vertex, range, vertex);

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->visited = false;
	}
	return res;
}

template<class T>
void Graph<T>::recursivePath(vector<Vertex<T>*> * res,  Vertex<T>* vertex, int range, Vertex<T> * originalVertex) const {

	for(unsigned int i = 0; i < vertex->adj.size(); i++) {

		int distance = distances.top() + vertex->adj[i].weight;
		if(distance < range && !vertex->visited) {
			distances.push(distance);
			vertex->visited = true;
			Vertex<T>* nextVertex = vertex->adj[i].dest;

			bool alreadyExists = false;
			for(unsigned int j = 0; j < res->size(); j++) {
				if((*res)[j]->info == nextVertex->info) {
					alreadyExists = true;
				}
			}

			if(!alreadyExists && !(nextVertex->info == originalVertex->info)) {
				res->push_back(nextVertex);
			}
			recursivePath(res, nextVertex, range, originalVertex);
		}
	}

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->visited = false;
	}

	distances.pop();
	return;
}

template<class T>
void Graph<T>::attributeHealthUnits() {

	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vector<Vertex<T>*> localidades = getVertexInRange(definedRange,vertexSet[i]);
		vertexSet[i]->reachableWithinRange = localidades;
	}

	vector<Vertex<T> *> vertexes;
	vertexes.clear();
	for(unsigned int i = 0; i < vertexSet.size(); i++) { //Quando nao poder ir para nenhum localidade sendo a distance menor que range colocar unidade de saude
		if(vertexSet[i]->reachableWithinRange.empty()) {
			vertexSet[i]->info.setHealthUnit(true);
		}
		else {
			vertexes.push_back(vertexSet[i]);
		}
	}

	vertexes = sortByReachableLocations(vertexes); // Ordenar o vector pelo numero de localidades onde cada uma consegue chegar
	cout << endl << " *** Ordered ***" << endl;
	for(unsigned int i = 0; i < vertexes.size(); i++) {
		cout << "Position: " << i << " Localidade: " << vertexes[i]->info.getName() << " number: " << vertexes[i]->reachableWithinRange.size() << endl;
	}

	for(unsigned int i = 0; i < vertexes.size(); i++) {
		bool canReachHealthUnit = false;
		for(unsigned int j = 0; j < vertexes[i]->reachableWithinRange.size(); j++) {
			if(vertexes[i]->reachableWithinRange[j]->info.getHealthUnit()) {
				canReachHealthUnit = true;
			}
		}
		if(!canReachHealthUnit) {
			vertexes[i]->info.setHealthUnit(true);
		}
	}

	cout << endl << endl << "*** Unidades de Saude atribuidas ***" << endl;
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		string hasHealthUnit;
		if(vertexSet[i]->info.getHealthUnit())
			hasHealthUnit = "true";
		else
			hasHealthUnit = "false";
		cout << "Localidade: " << vertexSet[i]->info.getName() << " -> Unidade de Saude: " << hasHealthUnit << endl;
	}

	drawGraph();
}

template<class T>
vector<Vertex<T>*> Graph<T>::sortByReachableLocations(vector<Vertex<T> *> vertexes) {

	vector<Vertex<T> *> result;
	int fullSize = vertexes.size();
	vector<int> positions;
	positions.clear();

	while(result.size() != fullSize) {
		unsigned int max_temp = 0;
		int max_position = -1;
		for(unsigned int i = 0; i < vertexes.size(); i++) {
			if(vertexes[i]->reachableWithinRange.size() > max_temp) {
				bool found = false;
				for(unsigned int j = 0; j < positions.size(); j++) {
					if(positions[j] == i) {
						found = true;
					}
				}

				if(!found) {
					max_temp = vertexes[i]->reachableWithinRange.size();
					max_position = i;
				}
			}
		}
		result.push_back(vertexes[max_position]);
		positions.push_back(max_position);
	}

	return result;
}

template<class T>
void Graph<T>::attributeHealthUnitsStage2() {

	vector <int> unidadesSaude;
	unidadesSaude.clear();

	for(int i = 0; i < numMaxUnidadesSaude; i++) {

		double leastValue = 0;
		int vertexPosition = -1;

		for(unsigned int j = 0; j < vertexSet.size(); j++) {

			if(!vertexSet[j]->info.getHealthUnit()) {
				double actualValue = calculateMedium(vertexSet, j);
				if(actualValue < leastValue || leastValue == 0) {
					leastValue = actualValue;
					vertexPosition = j;
				}
			}
		}
		vertexSet[vertexPosition]->info.setHealthUnit(true);
	}

	cout << endl << endl << "*** Unidades de Saude atribuidas ***" << endl;
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		string hasHealthUnit;
		if(vertexSet[i]->info.getHealthUnit())
			hasHealthUnit = "true";
		else
			hasHealthUnit = "false";
		cout << "Localidade: " << vertexSet[i]->info.getName() << " -> Unidade de Saude: " << hasHealthUnit << endl;
	}

	drawGraph();
}

template<class T>
double Graph<T>::calculateMedium(vector<Vertex<T> *> vertexes, int position) {

	vertexes[position]->info.setHealthUnit(true);
	double medium = 0.0;

	for(unsigned int i = 0; i < vertexes.size(); i++) {

		if(!vertexes[i]->info.getHealthUnit()) {
			bellmanFordShortestPath(vertexes[i]->info);
			int least_distance = INT_MAX;
			unsigned long population = 0;
			for(unsigned int j = 0; j < vertexes.size(); j++) {
				if(vertexes[j]->info.getHealthUnit()) {
					if(vertexes[j]->dist < least_distance) {
						least_distance = vertexes[j]->dist;
						population = vertexes[i]->info.getPopulation();
					}
				}
			}

			medium = medium + (least_distance*population);
		}
	}
	vertexes[position]->info.setHealthUnit(false);

	return medium;
}

#endif /* GRAPH_H_ */
