from collections import defaultdict


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


