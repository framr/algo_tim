#!/usr/bin/python

import sys
import os
form itertools import izip

from math import log
from random import randint, choice

class Constraint(object):
    def __init__(self, elements):

        self.negate = [False, False]
        self.elements = [-1, -1]
        for i, el in enumerate(elements):
            if el.startswith('-'):
                self.negate[i] = True
                self.elements[i] = int(el[1:])
            else:
                self.elements[i] = int(el)
    def sat(self, solution):
        res = False
        for el, neg in izip(self.elements, self.negate):
            if not neg:
                res = res or el
            else:
                res = res or (not el)
        return res


def select_unsat_constraints(constraints, solution):
    unsat = [c for c in constraints if not c.sat(solution)]
    return unsat


def papadimitriou_2sat(constraints, size):
    """
    randomized algorithm based on local search
    """

    if constraints.size() == 0:
        return True

    num_outer_iter = log(constraints.size())     
    for _ in xrange(num_outer_iter):
  
        num_iter = constraints.size() * constraints.size()
        solution = [randint(0, 1) for _ in xrange(size)]                                                                        
        for i in xrange(num_iter):
            unsat = select_unsat_constraints(constraints, solution)
            print "iter %d: %d constraints unsat" % (i, len(unsat))
            if not unsat:
                return True
        
            # fix random unsat constraint
            random_unsat = choice(unsat)
            random_element = random.unsat.elements[randint(0, 1)]
            solution[random_element] = not solution[random_element]  
    return False


def read_input(filename):
   
    constraints = []
    with open(filename) as infile:
        header = infile.readline()
        for line in infile:
            constraints.append(Constraint(line.strip().split()))

    return constraints

if __name__ == '__main__':

    constraints = read_input(sys.argv[1])
    res = papadimitriou_2sat(constraints, constraints.size())
    print res




