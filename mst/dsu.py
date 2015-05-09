class DisjointSetUnion(object):

    def __init__(self, vertices):
        self.parents = {}
        self.ranks = {}
        for v in vertices:
            self.parents[v] = v
            self.ranks[v] = 0

    def find(self, v):
        if v == self.parents[v]:
            return v
        root = self.find(self.parents[v])
        self.parents[v] = root # paths compression
        return root

    def union(self, u, v):
        
        if self.ranks[u] < self.ranks[v]:
            self.parents[u] = v
        else:
            self.parents[v] = u
            if self.ranks[u] == self.ranks[v]:
                # merging trees of the same height is the only case rank goes up 
                self.ranks[u] += 1

    def parent(self, v):
        return self.parents[v]

    def vertices(self):
        return self.parents.__iter__()

               
    
