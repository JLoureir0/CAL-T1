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
	int indegree;
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
	d->indegree--; //adicionado do exercicio 5
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

//atualizado pelo exerc�cio 5
template<class T>
Vertex<T>::Vertex(T in) :
		info(in), visited(false), processing(false), indegree(0), dist(0) {
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

template<class T>
int Vertex<T>::getIndegree() const {
	return this->indegree;
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
	void dfs(Vertex<T> *v, vector<T> &res) const;

	//exercicio 5
	int numCycles;
	void dfsVisit(Vertex<T> *v);
	void dfsVisit();
	void getPathTo(Vertex<T> *origin, list<T> &res);

	//exercicio 6
	int ** W;   //weight
	int ** P;   //path
	static Vertex<T> * vertexInRange;
public:
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeVertex(const T &in);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(Vertex<T> *v) const;
	int maxNewChildren(Vertex<T> *v, T &inf) const;
	vector<Vertex<T> *> getVertexSet() const;
	int getNumVertex() const;

	//exercicio 5
	Vertex<T>* getVertex(const T &v) const;
	void resetIndegrees();
	vector<Vertex<T>*> getSources() const;
	int getNumCycles();
	vector<T> topologicalOrder();
	vector<T> getPath(const T &origin, const T &dest);
	void unweightedShortestPath(const T &v);
	bool isDAG();

	//exercicio 6
	void bellmanFordShortestPath(const T &s);
	void dijkstraShortestPath(const T &s);
	void floydWarshallShortestPath();
	int edgeCost(int vOrigIndex, int vDestIndex);
	vector<T> getfloydWarshallPath(const T &origin, const T &dest);
	void getfloydWarshallPathAux(int index1, int index2, vector<T> & res);

	void drawGraph() const;
	vector<Vertex<T>*> getVertexInRange(int range, Vertex<T> * vertex) const;
	void recursivePath(vector<Vertex<T>*> *res, Vertex<T>* v, int range, Vertex<T> * originalVertex) const;
	void attributeHealthUnits();
	void testRangeFunction();
	vector<Vertex<T>*> sortByReachableLocations(vector<Vertex<T> *> Vertexes);
};

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
			vertexSet[i]->info.setUnidadeSaude(true);
		}
		else {
			vertexes.push_back(vertexSet[i]);
		}
	}

	vertexes = sortByReachableLocations(vertexes); // Ordenar o vector pelo numero de localidades onde cada uma consegue chegar
	cout << endl << " *** Ordered ***" << endl;
	for(unsigned int i = 0; i < vertexes.size(); i++) {
		cout << "Position: " << i << " Localidade: " << vertexes[i]->info.getNome() << " number: " << vertexes[i]->reachableWithinRange.size() << endl;
	}

	for(unsigned int i = 0; i < vertexes.size(); i++) {
		bool canReachHealthUnit = false;
		for(unsigned int j = 0; j < vertexes[i]->reachableWithinRange.size(); j++) {
			if(vertexes[i]->reachableWithinRange[j]->info.getUnidadeSaude()) {
				canReachHealthUnit = true;
			}
		}
		if(!canReachHealthUnit) {
			vertexes[i]->info.setUnidadeSaude(true);
		}
	}

	cout << endl << endl << "*** Unidades de Saude atribuidas ***" << endl;
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		string hasUnidadeSaude;
		if(vertexSet[i]->info.getUnidadeSaude())
			hasUnidadeSaude = "true";
		else
			hasUnidadeSaude = "false";
		cout << "Localidade: " << vertexSet[i]->info.getNome() << " -> Unidade de Saude: " << hasUnidadeSaude << endl;
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
void Graph<T>::testRangeFunction() {

	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		cout << "Vertice: " << vertexSet[i]->info.getNome() << endl;
		Vertex<T> * l = vertexSet[i];
		vector<Vertex<T>*> localidades = getVertexInRange(definedRange,l);
		for(unsigned int i = 0; i < localidades.size(); i++) {
			cout << "   - Localidade: " << localidades[i]->getInfo().getNome() << endl;
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

		if((*it)->info.getUnidadeSaude())
			graphviewer->setVertexColor(vertexID,"red");
		else
			graphviewer->setVertexColor(vertexID,"blue");

		graphviewer->addNode(vertexID);
		graphviewer->setVertexLabel(vertexID, (*it)->info.getNome());
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
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}
template<class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

template<class T>
int Graph<T>::getNumCycles() {
	numCycles = 0;
	dfsVisit();
	return this->numCycles;
}

template<class T>
bool Graph<T>::isDAG() {
	return (getNumCycles() == 0);
}

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
	vD->indegree++;
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
vector<T> Graph<T>::dfs() const {
	typename vector<Vertex<T>*>::const_iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite = vertexSet.end();
	for (; it != ite; it++)
		(*it)->visited = false;
	vector<T> res;
	it = vertexSet.begin();
	for (; it != ite; it++)
		if ((*it)->visited == false)
			dfs(*it, res);
	return res;
}

template<class T>
void Graph<T>::dfs(Vertex<T> *v, vector<T> &res) const {
	v->visited = true;
	res.push_back(v->info);
	typename vector<Edge<T> >::iterator it = (v->adj).begin();
	typename vector<Edge<T> >::iterator ite = (v->adj).end();
	for (; it != ite; it++)
		if (it->dest->visited == false) {
			//cout << "ok ";
			dfs(it->dest, res);
		}
}

template<class T>
vector<T> Graph<T>::bfs(Vertex<T> *v) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	q.push(v);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		typename vector<Edge<T> >::iterator it = v1->adj.begin();
		typename vector<Edge<T> >::iterator ite = v1->adj.end();
		for (; it != ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited == false) {
				d->visited = true;
				q.push(d);
			}
		}
	}
	return res;
}

template<class T>
int Graph<T>::maxNewChildren(Vertex<T> *v, T &inf) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	queue<int> level;
	int maxChildren = 0;
	inf = v->info;
	q.push(v);
	level.push(0);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		int l = level.front();
		level.pop();
		l++;
		int nChildren = 0;
		typename vector<Edge<T> >::iterator it = v1->adj.begin();
		typename vector<Edge<T> >::iterator ite = v1->adj.end();
		for (; it != ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited == false) {
				d->visited = true;
				q.push(d);
				level.push(l);
				nChildren++;
			}
		}
		if (nChildren > maxChildren) {
			maxChildren = nChildren;
			inf = v1->info;
		}
	}
	return maxChildren;
}

template<class T>
Vertex<T>* Graph<T>::getVertex(const T &v) const {
	for (unsigned int i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == v)
			return vertexSet[i];
	return NULL;
}

template<class T>
void Graph<T>::resetIndegrees() {
	//colocar todos os indegree em 0;
	for(unsigned int i = 0; i < vertexSet.size(); i++) vertexSet[i]->indegree = 0;

	//actualizar os indegree
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		//percorrer o vector de Edges, e actualizar indegree
		for(unsigned int j = 0; j < vertexSet[i]->adj.size(); j++) {
			vertexSet[i]->adj[j].dest->indegree++;
		}
	}
}


template<class T>
vector<Vertex<T>*> Graph<T>::getSources() const {
	vector< Vertex<T>* > buffer;
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		if( vertexSet[i]->indegree == 0 ) buffer.push_back( vertexSet[i] );
	}
	return buffer;
}


template <class T>
void Graph<T>::dfsVisit() {
	typename vector<Vertex<T>*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	it=vertexSet.begin();
	for (; it !=ite; it++)
		if ( (*it)->visited==false )
			dfsVisit(*it);
}

template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v) {
	v->processing = true;
	v->visited = true;
	typename vector<Edge<T> >::iterator it= (v->adj).begin();
	typename vector<Edge<T> >::iterator ite= (v->adj).end();
	for (; it !=ite; it++) {
		if ( it->dest->processing == true) numCycles++;
		if ( it->dest->visited == false ){
			dfsVisit(it->dest);
		}
	}
	v->processing = false;
}

template<class T>
vector<T> Graph<T>::topologicalOrder() {
	//vetor com o resultado da ordenacao
	vector<T> res;

	//verificar se é um DAG
	if( getNumCycles() > 0 ) {
		cout << "Ordenacao Impossivel!" << endl;
		return res;
	}

	//garantir que os "indegree" estao inicializados corretamente
	this->resetIndegrees();

	queue<Vertex<T>*> q;

	vector<Vertex<T>*> sources = getSources();
	while( !sources.empty() ) {
		q.push( sources.back() );
		sources.pop_back();
	}


	//processar fontes
	while( !q.empty() ) {
		Vertex<T>* v = q.front();
		q.pop();

		res.push_back(v->info);

		for(unsigned int i = 0; i < v->adj.size(); i++) {
			v->adj[i].dest->indegree--;
			if( v->adj[i].dest->indegree == 0) q.push( v->adj[i].dest );
		}
	}

	//testar se o procedimento foi bem sucedido
	if ( res.size() != vertexSet.size() ) {
		while( !res.empty() ) res.pop_back();
	}

	//garantir que os "indegree" ficam atualizados ao final
	this->resetIndegrees();

	return res;
}



template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest){

	list<T> buffer;
	Vertex<T>* v = getVertex(dest);

	buffer.push_front(v->info);
	while ( v->path != NULL &&  v->path->info != origin) {
		v = v->path;
		buffer.push_front(v->info);
	}
	if( v->path != NULL )
		buffer.push_front(v->path->info);


	vector<T> res;
	while( !buffer.empty() ) {
		res.push_back( buffer.front() );
		buffer.pop_front();
	}
	return res;
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &origin, const T &dest){

	int originIndex = -1, destinationIndex = -1;

	for(unsigned int i = 0; i < vertexSet.size(); i++)
	{
		if(vertexSet[i]->info == origin)
			originIndex = i;
		if(vertexSet[i]->info == dest)
			destinationIndex = i;

		if(originIndex != -1 && destinationIndex != -1)
			break;
	}


	vector<T> res;

	//se nao foi encontrada solucao possivel, retorna lista vazia
	if(W[originIndex][destinationIndex] == INT_INFINITY)
		return res;

	res.push_back(vertexSet[originIndex]->info);

	//se houver pontos intermedios...
	if(P[originIndex][destinationIndex] != -1)
	{
		int intermedIndex = P[originIndex][destinationIndex];

		getfloydWarshallPathAux(originIndex, intermedIndex, res);

		res.push_back(vertexSet[intermedIndex]->info);

		getfloydWarshallPathAux(intermedIndex,destinationIndex, res);
	}

	res.push_back(vertexSet[destinationIndex]->info);


	return res;
}



template<class T>
void Graph<T>::getfloydWarshallPathAux(int index1, int index2, vector<T> & res)
{
	if(P[index1][index2] != -1)
	{
		getfloydWarshallPathAux(index1, P[index1][index2], res);

		res.push_back(vertexSet[P[index1][index2]]->info);

		getfloydWarshallPathAux(P[index1][index2],index2, res);
	}
}


template<class T>
void Graph<T>::unweightedShortestPath(const T &s) {

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
			if( w->dist == INT_INFINITY ) {
				w->dist = v->dist + 1;
				w->path = v;
				q.push(w);
			}
		}
	}
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
void Graph<T>::dijkstraShortestPath(const T &s) {

	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
		vertexSet[i]->processing = false;
	}

	Vertex<T>* v = getVertex(s);
	v->dist = 0;

	vector< Vertex<T>* > pq;
	pq.push_back(v);

	make_heap(pq.begin(), pq.end());


	while( !pq.empty() ) {

		v = pq.front();
		pop_heap(pq.begin(), pq.end());
		pq.pop_back();

		for(unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T>* w = v->adj[i].dest;

			if(v->dist + v->adj[i].weight < w->dist ) {

				w->dist = v->dist + v->adj[i].weight;
				w->path = v;

				//se já estiver na lista, apenas a actualiza
				if(!w->processing)
				{
					w->processing = true;
					pq.push_back(w);
				}

				make_heap (pq.begin(),pq.end(),vertex_greater_than<T>());
			}
		}
	}
}

template<class T>
int Graph<T>::edgeCost(int vOrigIndex, int vDestIndex)
{
	if(vertexSet[vOrigIndex] == vertexSet[vDestIndex])
		return 0;

	for(unsigned int i = 0; i < vertexSet[vOrigIndex]->adj.size(); i++)
	{
		if(vertexSet[vOrigIndex]->adj[i].dest == vertexSet[vDestIndex])
			return vertexSet[vOrigIndex]->adj[i].weight;
	}

	return INT_INFINITY;
}

template<class T>
void Graph<T>::floydWarshallShortestPath() {

	W = new int * [vertexSet.size()];
	P = new int * [vertexSet.size()];
	for(unsigned int i = 0; i < vertexSet.size(); i++)
	{
		W[i] = new int[vertexSet.size()];
		P[i] = new int[vertexSet.size()];
		for(unsigned int j = 0; j < vertexSet.size(); j++)
		{
			W[i][j] = edgeCost(i,j);
			P[i][j] = -1;
		}
	}


	for(unsigned int k = 0; k < vertexSet.size(); k++)
		for(unsigned int i = 0; i < vertexSet.size(); i++)
			for(unsigned int j = 0; j < vertexSet.size(); j++)
			{
				//se somarmos qualquer coisa ao valor INT_INFINITY, ocorre overflow, o que resulta num valor negativo, logo nem convém considerar essa soma
				if(W[i][k] == INT_INFINITY || W[k][j] == INT_INFINITY)
					continue;

				int val = min ( W[i][j], W[i][k]+W[k][j] );
				if(val != W[i][j])
				{
					W[i][j] = val;
					P[i][j] = k;
				}
			}

}

#endif /* GRAPH_H_ */
