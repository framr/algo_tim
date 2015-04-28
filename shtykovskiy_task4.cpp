#include<iostream>
#include<vector>
#include<algorithm>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::min;

const int kMaxPossibleCost = 1000000000;
const int kImpossiblyHighCost = kMaxPossibleCost + 1;

typedef enum {WHITE, GREY, BLACK} Color;

struct Edge {
    int tail;
    int head;
    int weight;
    int id;

    Edge(int tail_value, int head_value, int weight_value, int id_value) :
        tail(tail_value), head(head_value), weight(weight_value), id(id_value) {}
};

Edge ReverseEdge(const Edge& old_edge) {
    return Edge(old_edge.head, old_edge.tail, old_edge.weight, old_edge.id);
}


class UndirectedGraph {

    vector<vector<Edge> > adjacency_lists_;

    public:

    typedef vector<Edge>::const_iterator EdgeIterator;

    UndirectedGraph() {}

    explicit UndirectedGraph(int num_of_vertices) {
        adjacency_lists_.resize(num_of_vertices);
    }

    void InsertEdge(const Edge& new_edge) {
        adjacency_lists_[new_edge.tail].push_back(new_edge);
        adjacency_lists_[new_edge.head].push_back(ReverseEdge(new_edge));
    }

    void Resize (int num_of_vertices) {
        adjacency_lists_.resize(num_of_vertices);
    }

    int Order() const {
        return adjacency_lists_.size();
    }

    EdgeIterator EdgesBegin(int vertex) const {
        return adjacency_lists_[vertex].begin();
    }

    EdgeIterator EdgesEnd(int vertex) const {
         return adjacency_lists_[vertex].end();
    }
};

class DFSVisitor {

    int time_;
    vector<int> enter_time_;
    vector<int> reenter_time_;
    int min_weight_;

    public:

    explicit DFSVisitor(int graph_order) : time_(0), enter_time_(graph_order, 0),
    reenter_time_(graph_order, 0), min_weight_(kImpossiblyHighCost) {}

    void EnterVertex(int vertex) {
        enter_time_[vertex] = time_++;
        reenter_time_[vertex] = enter_time_[vertex];
    }

    void BackEdge(const Edge& processed_edge) {
            reenter_time_[processed_edge.tail] = min(reenter_time_[processed_edge.tail],
                    enter_time_[processed_edge.head]);
    }

    void TreeEdge(const Edge& processed_edge) {
            reenter_time_[processed_edge.tail] = min(reenter_time_[processed_edge.tail],
                    reenter_time_[processed_edge.head]);
            if (reenter_time_[processed_edge.head] > enter_time_[processed_edge.tail]) {
                min_weight_ = min(min_weight_, processed_edge.weight);
            }
    }

    int MinWeight() const {
        if (min_weight_ < kImpossiblyHighCost) {
            return min_weight_;
        } else {
            return -1;
        }
    }
};

void Input(UndirectedGraph* pandeya);
int FindMinWeightBridge(const UndirectedGraph& graph);
void DepthFirstSearch(const UndirectedGraph& graph, int vertex, const Edge& incoming_edge,
        vector<Color>* colors, DFSVisitor* visitor);
void Output(int min_cost);


int main() {

    UndirectedGraph pandeya;
    Input(&pandeya);

    int min_cost = FindMinWeightBridge(pandeya);
    Output(min_cost);

    return 0;
}

//==========================================================================

void Input(UndirectedGraph* pandeya) {

    int num_of_cities, num_of_roads;
    cin >> num_of_cities >> num_of_roads;

    pandeya->Resize(num_of_cities);
    int edge_id = 0;
    for (int i = 0; i < num_of_roads; ++i, ++edge_id) {
        int source, destination, cost;
        cin >> source >> destination >> cost;
        pandeya->InsertEdge(Edge(source - 1, destination - 1, cost, edge_id));
    }
}

//==========================================================================

void Output(int min_cost) {

    cout << min_cost << endl;
}

//==========================================================================

int FindMinWeightBridge(const UndirectedGraph& graph) {

    vector<Color> colors(graph.Order(), WHITE);
    DFSVisitor visitor(graph.Order());
    Edge impossible_edge(0, 0, 0, -1);

    DepthFirstSearch(graph, 0, impossible_edge, &colors, &visitor);

    return visitor.MinWeight();
}

//==========================================================================

void DepthFirstSearch(const UndirectedGraph& graph, int vertex, const Edge& incoming_edge,
        vector<Color>* colors, DFSVisitor* visitor) {

    colors->at(vertex) = GREY;
    visitor->EnterVertex(vertex);

    UndirectedGraph::EdgeIterator edge;
    for (edge = graph.EdgesBegin(vertex); edge != graph.EdgesEnd(vertex); ++edge) {
        if (edge->id == incoming_edge.id) {
            continue;
        }

        if (colors->at(edge->head) == GREY) {
            visitor->BackEdge(*edge);
        }

        if (colors->at(edge->head) == WHITE) {
            DepthFirstSearch(graph, edge->head, *edge, colors, visitor);
            visitor->TreeEdge(*edge);
        }
    }
    colors->at(vertex) = BLACK;
}

















