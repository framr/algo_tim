#!/usr/bin/python

from copy import copy
from collections import defaultdict


INFTY = 2e+50


class Edge(object):
    def __init__(self, tail=None, head=None, weight=None):
        self.head = head
        self.tail = tail
        self.weight = weight
    def __str__(self):
        return "%s - %s  w = %s" % (self.tail, self.head, self.weight)

class Graph(object):
    def __init__(self):
        self.adj_list = defaultdict(set)
    def add_edge(self, tail, head, weight):
        self.adj_list[tail].add(Edge(tail, head, weight))
        self.adj_list[head].add(Edge(head, tail, weight))
    def edges(self):
        return self.adj_list.iteritems()
    def __iter__(self):
        return self.adj_list.__iter__()
    def vertex_edges(self, v):
        return self.adj_list[v]
    def vertices(self):
        return self.adj_list.keys()


class CostsContainer(self):
    def __init__(self):
        self._container = defaultdict(dict)
    def get(self, v_set, dst):
        if not isinstance(v_set, frozenset):
            v_set = frozenset(v_set)
        return self._container[v_set][dst]
    def set(self, v_set, dst, value):
        if not isinstance(v_set, frozenset):
            v_set = frozenset(v_set)
        self._container[v_set][dst] = value
        

def generate_vertices_set(g, cardinality):
    """
    generate all sets of vertices with given cardinality
    """

    solution = [-1] * len(cardinality)
    def _recursive_set_gen(vertices, start, cur_cardinality, cardinality, solution):
        if cur_cardinality == cardinality:
            # we are done
            yield solution[:kmax]
        
        residual_cardinality = cardinality - cur_cardinality # current cardinality
        if residual_cardinality > vertices.size() - start or start >= vertices.size():
            # oops not enough elements, normally we should not be here
            yield None

        
        # let's first try to take current vertex
        solution[cur_cardinality] = vertices[start] 
        yield _recursive_set_gen(vertices, start + 1, cur_cardinality + 1, cardinality, solution)

        # try to ignore current vertex
        if residual_cardinality < vertices.size() - start:
            yield _recursive_set_gen(vertices, start + 1, cur_cardinality, cardinality, solution)
        
    yield _recursive_set_gen(g.vertices(), 0, 0, cardinality, solution):

def tsp(g, inf=INFTY):
    """
    DP Algorithm:
    Subproblem is a path from 1 to j passing via some set of vertices S, |S| = s, 
    where each vertex is met exactly once. The cost of such a path is C(S, j)
    Then the best path from 1 to j passing through s vertices is min over all paths from 
    1 to adjacent to j vertices i passing via S - j vertices.

    The final answer is min over paths from 1 to vertices adjacent to 1 with S = V, 
    min_{i->1}C(S, i)
    """
 
    costs = CostsContainer()
    costs.set([1], 1) = 0

    for cardinality in xrange(2, g.size() + 1):
        # loop over all paths through vertices set with given cardinality
        for vertices_set in generate_vertices_set(graph, cardinality):
 
            # take a destination vertex in chosen set
            for dst in vertices_set:
                if dst == 1:
                    # can't be one, this is where we've started from
                    continue
                subproblem_vertices_set = copy(vertices_set)
                subproblem_vertices_set.remove() 
            
                # loop over vertices adjacent to dst and lying inside the vertices_set
                for edge in g.edges(dst):
                   if edge.head in vertices_set:
                        costs.set(vertices_set, dst, 
                            min(
                            [
                            costs.get(vertices_set, dst),
                            costs.get(generate_vertices_set, edge.head) + edge.weight
                            ]
                            )
                        )
    best_cost = inf
    full_vertices_set = generate_vertices_set(graph, graph.size())
    for edge in graph.edges(1):
        best_cost = min([best_cost, costs.get(full_vertices_set, edge.tail) + edge.weight])

    return best_cost


if __name__ == '__main__':
    pass
