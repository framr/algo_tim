#!/usr/bin/python

def swap(a, first, second):
    a[second], a[first] = (a[first], a[second])

def partition(a, begin, end, pivot):

    swap(a, begin, pivot)
    first = begin
    
    for second in xrange(begin + 1, end + 1):
        if a[second] < a[begin]:
            swap(a, first + 1, second)
            first += 1

    swap(a, begin, first)
    return first

def choose_pivot(a, begin, end):
    return (begin + end) / 2

def quicksort(a, begin, end):

    if (begin >= end):
        return

    pivot = choose_pivot(a, begin, end)
    pivot_index = partition(a, begin, end, pivot)
    quicksort(a, begin, pivot_index)
    quicksort(a, pivot_index + 1, end)


if __name__ == '__main__':

    tests = [
        [1, 2, 3, 4, 5],
        [5, 4, 3, 2, 1],
        [5, 5, 5, 1, 1, 1],
        [1, 1, 1, 5, 5, 5, 3, 3, 3],
        [10, 1, 9, 2, 8, 3, 7, 4, 6, 5]
    ]

    for test in tests:
        print "%s ->" % test
        quicksort(test, 0, len(test) - 1)
        print "%s" % test
        print "==================================="
