#include "pqueue.h"

class SimplePriorityQueue {

    map<int, int> _pqueue;
   
public:

    SimplePriorityQueue() : {}

    pair<int, int> min() {
        min_elem = -1;
        min_value = INFTY;
        for (map<int, int>::const_iterator it = _pqueue.begin(); it != _pqueue.end(); ++it) {
            int el = it->first;
            int value = it->second;
            if (min_value > value) {
                min_value = value;
                min_elem = el;
            }
        }
        return make_pair(min_elem, min_value);
    }

    void update(int element, int value) {
        _pqueue[element] = value;
    }
    void insert(int element, int value) {
        _pqueue[element] = value;
    }
    void remove(int elem) {
        _pqueue.erase(elem);
    }

    int pop_min() {
        int elem = this->min();
        this->remove(elem);
        return elem;
    }
    bool empty() const {
        return _pqueue.empty();
    }
};





