#include<cstdlib>
#include<cstdio>
#include<vector>
#include<unordered_map>
#include<limits.h>

using std::vector;
using std::unordered_map;

struct Edge {
    int head;
    int tail;
    int weight;
    Edge(int v_tail, int v_head, double w): tail(v_tail), head(v_head), weight(w) {};
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
    
    void insert(int tail, int head, double weight) {
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


int bellman_ford(const Graph& g, int source, vector<int>* paths) {

    // cost[v][budget] vector of shortest paths from source to v with fixed edge budget
    vector<vector<int> > cost;
    cost.resize(g.size() + 1, vector<int>(g.size()));
    paths->resize(g.size());

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


 

int main(int argc, char** argv) {


    return 1;
}
