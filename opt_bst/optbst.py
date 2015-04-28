#!/usr/bin/python
import sys


"""
Cij = max_k(Cik-1 + fij + Ck+1j)
"""


def precompute_range_freqs(f):
    """
    precompute range frequences = sum of frequencies of elements from i to j
    f_ij = f_ij-1 + frequencies_j
    """
    fsum = [[0] * len(f) for _ in range(len(f))] 
    for i in range(len(f)):
        fsum[i][i] = f[i] 

    for j in range(1, len(f)):
        for i in range(0, j):
            fsum[i][j] = fsum[i][j - 1] + f[j]   
            
#print i, j, fsum[i][j]

    return fsum


def opt_bst_dynamic(f):
    """
    i <= j
    j     ^
          |         
        <-
    
          i
    """
    fsum = precompute_range_freqs(f)
    cost = [[0] * len(f) for _ in range(len(f))]
    for i in range(len(f)):
        cost[i][i] = f[i]

    for j in range(1, len(f)):
        for i in reversed(range(0, j)):
            cost_right = cost[i + 1][j] if j > i else 0
            cost[i][j] = cost_right + fsum[i][j]
            for root in range(i, j + 1):
                cost_left = cost[i][root - 1] if root > i else 0
                cost_right = cost[root + 1][j] if root < j else 0
                cost[i][j] = min([fsum[i][j] + cost_left + cost_right, cost[i][j]]) 

    return cost


class Node(object):
    def __init__(self, data=None):
        self.data = data
        self.left = None
        self.right = None


def reconstruct_tree(cost, fsum, left, right):

    if left > right:
        return None

    root = left
    opt_cost = fsum[i][j] + cost[i + 1][j] if i < j else fsum[i][j]
    for k in range(left, right + 1):
        left_cost = cost[i][k - 1] if k > i else 0
        right_cost = cost[k + 1][j] if k < j else 0
        if left_cost + right_cost + fsum[i][j] < opt_cost:
            root = k
            opt_cost = left_cost + right_cost + fsum[i][j]

    root = Node(root)
    root.left = reconstruct_tree(cost, fsum, left, k - 1)
    root.left = reconstruct_tree(cost, fsum, k + 1, right)
    return root

if __name__ == '__main__':

    elem = []
    f = []
    for line in open(sys.argv[1]):
        el, freq = line.strip().split()
        f.append(float(freq))
        elem.append(int(el))
    
    mapping, freq = zip(*sorted(zip(elem, f)))
       
    cost = opt_bst_dynamic(freq) 
    opt_cost = cost[0][len(freq) - 1]
    print opt_cost 
     
     









