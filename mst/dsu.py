
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
        self.parents[v] = root # path compression
        return root

    def union(self, u, v):
        
        if self.ranks[u] < ranks[v]:


    def rank(self, v):
        return 0
