#include<cstdio>
#include<cstdlib>
#include<vector>
#include<map>
#include<unordered_map>
#include<limits.h>
#include<utility>

using std::map;
using std::vector;
using std::pair;
using std::make_pair;
using std::unordered_map;

int QUEUE_INFTY = INT_MAX;


class SimplePriorityQueue {
    map<int, int> _pqueue;  
public:
    SimplePriorityQueue();
    pair<int, int> min();
    void update(int element, int value);
    void insert(int element, int value);
    void remove(int elem);
    pair<int, int> pop_min();
    bool empty() const;
};


/* SimplePriorityQueue Implementation*/
pair<int, int> SimplePriorityQueue::min() {
    int min_elem = -1;
    int min_value = QUEUE_INFTY;
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

void SimplePriorityQueue::update(int element, int value) {
    _pqueue[element] = value;
}

void SimplePriorityQueue::insert(int element, int value) {
    _pqueue[element] = value;
}
void SimplePriorityQueue::remove(int elem) {
    _pqueue.erase(elem);
}

pair<int, int> SimplePriorityQueue::pop_min() {
    pair<int, int> elem = this->min();
    this->remove(elem.first);
    return elem;
}
bool SimplePriorityQueue::empty() const {
    return _pqueue.empty();
}



template<class TObject, class TValue>
class MinHeap {

    typedef pair<TObject, TValue> HeapNode;
    // internal heap array
    vector<HeapNode> _heap;
    //mapping object -> location in internal heap array
    unordered_map<TObject, int> _objects_location;

    void _update_in_position(int position, TValue value) {
        HeapNode node = _heap[position];
        _heap[position].second = value;  
        if (value > node.second) {
            this->_sift_down(position);
        } else if (value < node.second) {
            this->_sift_up(position);
        }
    }

    void _sift_up(int position) {
        int parent = _parent(position);
        TValue value = _heap[position].second;

        if (parent < 0) {
            return;
        }
        TValue parent_value = _heap[parent].second;

        while (parent >= 0 and parent_value > value) {
            _swap(position, parent);
            position = parent;
            parent = _parent(position);
            if (parent < 0) {
                break;
            }
            parent_value = _heap[parent].second;
        }
    }

    void _sift_down(int position) {
       
        int left = _left_child(position);
        int right = _right_child(position);


        while (left < this->size() || right < this->size()) {

            int new_position = -1;
            if (left < this->size()) {
                new_position = left;
                if (right < this->size() && _heap[right].second < _heap[left].second) {
                    new_position = right;
                }
            }

            if (new_position < 0 || _heap[new_position].second > _heap[position].second) {
                break;
            }
            _swap(position, new_position);
            position = new_position;

            left = _left_child(position);
            right = _right_child(position);
        }
        
    }

    void _swap(int first, int second) {
        HeapNode first_node = _heap[first];
        HeapNode second_node = _heap[second];

        _heap[first] = second_node;
        _heap[second] = first_node;
        _objects_location[first_node.first] = second;
        _objects_location[second_node.first] = first;
    }

    int _parent(int position) {
        if (position == 0) {
            return -1;
        }

        return (position - 1) / 2;
    }
    int _left_child(int position) {
        return 2 * position + 1;
    }
    int _right_child(int position) {
        return 2 * position + 2;
    }

    void _remove_from_position(int position) {
        //not implemented
    }

    void _remove_min() {
        _swap(0, this->size() - 1);
       _heap.resize(this->size() - 1); 
    }


public:

    MinHeap() {}

    HeapNode get_node(const TObject& key) {
        return _heap[_objects_location[key]];
    }

    HeapNode min() {
        return _heap[0];
    }

    HeapNode pop_min() {

        HeapNode min_element = this->min();
        this->_remove_min();
        return min_element;
    }

    void remove(const TObject& key) {
        //not implemented
    }

    void update(const TObject& element, const TValue& value) {
        int position = _objects_location[element];
        this->_update_in_position(position, value);
    }

    void insert(int element, int value) {
        _heap.push_back(make_pair(element, value));
        _objects_location[element] = this->size() - 1;         
    }
    bool empty() const {
        return _heap.empty();
    }

    bool contains(const TObject& key) {
        return _objects_location.count(key) > 0;
    }

    size_t size() {
        return _heap.size();
    }
};
