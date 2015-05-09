#!/usr/bin/python


class MinHeap(object):
    def __init__(self):
        # array of nodes
        self._heap = []
        # mapping key ->index in array
        self._mapping = {}
    
    def insert(self, key, value):
        self._heap.append((key, value))
        self._mapping[key] = len(self._heap) - 1 
        self._siftup(len(self._heap) - 1)

    def min(self):
        return self._heap[0]
    def pop_min(self):
        min_node = self._heap[0]
        self._swap(0, len(self._heap) - 1)
        self._heap.pop()
        return min_node

    def remove(self, key):

        pos = self._mapping[key]
        old_key, old_value = self._heap[pos]
        self._swap(pos, len(self._heap) - 1)
        new_key, new_value = self._heap[pos]
        if new_value > old_value:
            self._siftdown(pos)
        else:
            self._siftup(pos)

    def _siftup(self, pos):
        if pos == 0:
            return

        current_value = self._heap[pos]
        parent_value = self._heap[self._parent(pos)][1] 
        while parent_value > current_value:
            self._swap(pos, self._parent(pos))
            pos = self._parent(pos)
            parent = self._parent(pos)
            if parent <= 0:
                return
            parent_value = self._heap[parent][1]
            current_value = self._heap[pos][1]

    def _siftdown(self, pos):
        
        smallest = self._smallest_child(pos) 
        while smallest is not None and self._heap[pos] > self._heap[smallest]:
            self._swap(pos, smallest)
            pos = smallest
            smallest = self._smallest_child(pos)

    def _smallest_child(self, pos):
        left_child = self._left_child(pos)
        right_child = self._right_child(pos)
        smallest = None
        if left_child is not None:
            smallest = left_child
            left_value = self._heap[left_child]
            if right_child is not None:
                right_value = self._heap[right_child]
                smallest = left_child if left_value < right_value else right_child
        return smallest


    def _parent(self, pos):
        return int((pos - 1) / 2)

    def _left_child(self, pos):
        tmp = 2 * pos + 1
        if tmp >= len(self._heap):
            return None
        else:
            return tmp
    def _right_child(self, pos):
        tmp = 2 * pos + 2
        if tmp >= len(self._heap):
            return None
        else:
            return tmp


    def _swap(self, first, second):
        first_key = self._heap[first][0]
        second_key = self._heap[second][0]
        self._heap[first], self._heap[second] = (self._heap[second], self._heap[first])
        self._mapping[first_key], self._mapping[second_key] = second, first

    


if __name__ == '__main__':

    pass
