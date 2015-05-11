#!/usr/bin/python
from copy import copy

def merge(a, first, second, mid):
    tmp = copy(a)
    first_ptr = first
    second_ptr = mid + 1
    for i in range(first, second + 1):
        if first_ptr > mid:
            a[i] = tmp[second_ptr]
            second_ptr += 1
            continue
        elif second_ptr > second:
            a[i] = tmp[first_ptr]
            first_ptr += 1
            continue

        if tmp[first_ptr] < tmp[second_ptr]:
            a[i] = tmp[first_ptr]
            first_ptr += 1
        else:
            a[i] = tmp[second_ptr]
            second_ptr += 1

def _count_inversions(a, first, second):
    if first >= second:
        return 0

    mid = (first + second) / 2;
    c1 = _count_inversions(a, first, mid)
    c2 = _count_inversions(a, mid + 1, second)
    c3 = merge(a, first, mid, second) 
    return c1 + c2 + c3  

def count_inversions(a):
    res = _count_inversions(a, 0, a.size() - 1)
    return res


if __name__ == '__main__':
    pass
