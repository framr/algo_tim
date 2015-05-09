#!/usr/bin/python

import sys
from operator import attrgetter
from itertools import chain


from dsu import DisjointSetUnion
from graph import Graph


def kruskal(graph):
    
    spanning_tree = Graph()
    dsu = DisjointSetUnion(graph) 
    edges = sorted(chain.from_iterable([edge for v, edge in graph.edges()]), key=attrgetter('weight'))
    for edge in edges:
        head_parent = dsu.find(edge.head)
        tail_parent = dsu.find(edge.tail)
        if head_parent != tail_parent:
            dsu.union(head_parent, tail_parent)
            spanning_tree.add_edge(edge.tail, edge.head, edge.weight) 

    return spanning_tree



def read_input(infile):
    
    graph = Graph()
    with open(infile) as tmp:
        header = tmp.readline().strip().split()
        v, e = (int(header[0]), int(header[1]))
        for line in tmp:
            splitted = line.strip().split()
            tail = int(splitted[0])
            head = int(splitted[1])
            weight = float(splitted[2])
            graph.add_edge(tail, head, weight)

    return graph


def dfs(graph, v):
    
    visited = {}
    _dfs(graph, v, visited)

def _dfs(graph, v, visited):

    visited[v] = True
    for edge in graph.vertex_edges(v):
        if edge.head not in visited:
            print edge
            _dfs(graph, edge.head, visited)




if __name__ == '__main__':

    
    graph = read_input(sys.argv[1])
    tree = kruskal(graph)
    dfs(tree, next(tree.__iter__()))










