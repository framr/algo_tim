#include<cstdlib>
#include<cstdio>
#include<vector>
#include<unordered_map>
#include<limits.h>

using std::vector;
using std::unordered_map;
using std::make_pair;
using std::pair;

struct Edge {
    int head;
    int tail;
    int weight;
    Edge(int v_tail, int v_head, int w): tail(v_tail), head(v_head), weight(w) {};
};

 
Edge reverse_edge(const Edge& e) {
    return Edge(e.tail, e.head, e.weight); 
};

int INFTY = INT_MAX;


class Graph {

    bool directed;
    unordered_map<int, vector<Edge> > adj_list;

public:
   
    Graph() {directed = false;}
    
    //Graph(int num_vertices) : adj_list(num_vertices) {adj_list.resize(num_vertices); directed = false;};
    
    void insert(int tail, int head, int weight) {
        Edge e = Edge(tail, head, weight);
        adj_list[tail].push_back(e);
        if (!directed) {
            adj_list[head].push_back(reverse_edge(e));
        }
    }
    int size() const {
        return adj_list.size();
    }

    vector<Edge> neighbours(int vertex) {
        return adj_list[vertex];
    }

    typedef vector<Edge>::const_iterator EdgeIterator;
    typedef unordered_map<int, vector<Edge> >::const_iterator VertexIterator;

    EdgeIterator edge_begin(int vertex) const {
        return adj_list.at(vertex).cbegin();
    }
    EdgeIterator edge_end(int vertex) const {
        return adj_list.at(vertex).cend();
    }

    VertexIterator begin() const {
        return adj_list.cbegin();
    }
    VertexIterator end() const {
        return adj_list.cend();
    }

}; 


void read_graph(const char* infile, Graph* g) {

    FILE* fp;
    
    if ((fp = fopen(infile, "r")) == NULL) {
        perror("Error opening file");
    }
    
    int size;
    int num_edges;
    fscanf(fp, "%d %d\n", &size, &num_edges);
    int head, tail, weight;
    for (int i = 0; i < num_edges; ++i) {
        fscanf(fp, "%d %d %d\n", &tail, &head, &weight);
        g->insert(tail, head, weight);
    }

}


int bellman_ford(const Graph& g, int source, unordered_map<int, int>* paths) {

    // cost[v][budget] vector of shortest paths from source to v with fixed edge budget
    vector<vector<int> > cost;
    cost.resize(g.size() + 1, vector<int>(g.size()));
    //paths->resize(g.size());

    for (Graph::VertexIterator it = g.begin(); it != g.end(); ++it) {
        int v = it->first;
        cost[v][0] = INFTY;
    }

    cost[source][0] = 0;


    for (int budget = 1; budget <= g.size(); ++budget) {
        for (Graph::VertexIterator it = g.begin(); it != g.end(); ++it) {  
            int v = it->first;
            int min_cost = cost[v][budget - 1];
            for (Graph::EdgeIterator it = g.edge_begin(v); it != g.edge_end(v); ++it) {
                int cur_cost = it->weight + cost[it->head][budget - 1];
                min_cost = (min_cost < cur_cost) ? min_cost : cur_cost; 
            }
        }
    }


    for (Graph::VertexIterator it = g.begin(); it != g.end(); ++it) {  
        int v = it->first;
        paths->at(v) = cost[v][g.size() - 1];
        if (cost[v][g.size()] != cost[v][g.size() - 1]) {
            return v; //oops, seems like we've got a neg cycle      
        }
    }

    return -1;
}


class PriorityQueue {

    unordered_map<int, int> _pqueue;
   
public:

    PriorityQueue() : {}

    pair<int, int> min() {
        min_elem = -1;
        min_value = INFTY;
        for (unordered_map<int, int>::const_iterator it = _pqueue.begin(); it != pqueue.end(); ++it) {
            int el = it->first;
            int value = it->second;
            if (min_value > value) {
                min_value = value;
                min_elem = el;
            }
        }
        return make_pair(min_elem, min_value);
    }

    void update(int element, int value) {
        _pqueue[element] = value;
    }
    void insert(int element, int value) {
        _pqueue[element] = value;
    }
    void remove(int elem) {
        _pqueue.erase(elem);
    }

    int pop_min() {
        int elem = this->min();
        remove(elem);
        return elem;
    }
    bool empty() {
        return _pqueue.empty();
    }
}

int dijkstra(const Graph& g, int source, const unordered_map<int, int>* paths) {
    
    PriorityQueue pq;
    pq.insert(source, 0);
    
    while (!pq.empty()) {
        
        
    }     

}


void output_result(const unordered_map<int, int>& paths) {
    for (unordered_map<int, int>::const_iterator it = paths.begin(); it != paths.end(); ++it) {
        int v = it->first;
        int w = it->second; 
        printf("%d %d\n", v, w); 
    }

}



int main(int argc, char** argv) {

    unordered_map<int, int> paths;

    Graph g;
    read_graph(argv[1], &g);
    bellman_ford(g, atoi(argv[2]), &paths);
    output_result(paths);


    return 0;
}
