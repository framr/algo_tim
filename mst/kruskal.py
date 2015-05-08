#!/usr/bin/python

import sys
from operator import attrgetter


from dsu import DisjointSetUnion


class Edge(object):
    def __init__(self, tail=None, head=None, weight=None):
        self.head = head
        self.tail = tail
        self.weight = weight


class Graph(object):
    def __init__(self):
        self.adj_list = {}
    def add_edge(self, tail, head, weight):
        self.adj_list[tail].append(Edge(tail, head, weight))
        self.adj_list[head].append(Edge(head, tail, weight))
    def vertices(self):
        return self.adj_list.iteritems()
    def edges(self, v):
        return self.adj_list[v]

def kruskal(graph):
    
    edges = sorted([edge for v, edge in graph.vertices()], key=attrgetter('weight'))
    for edge in edges:






if __name__ == '__main__':

    pass
