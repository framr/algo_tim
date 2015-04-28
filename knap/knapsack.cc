#include<stdlib.h>
#include<stdio.h>
#include<vector>


/*
capacity number of elements
value weight
*/

using std::vector;

void read_data(const char* filename, vector<int>* values, vector<int>* weights, int& capacity) {

    FILE* fp;
    if ((fp = fopen(filename, "r")) == NULL) {
        perror("Error reading input file");
    }
    int num;
    fscanf(fp, "%d %d\n", &capacity, &num);
    values->resize(num);
    weights->resize(num);
    for (int i = 0; i < num; ++i) {
        fscanf(fp, "%d %d\n", &values->at(i), &weights->at(i));
    }
}


void print_vec(const vector<int>& vec) {

    for (int i = 0; i < vec.size(); ++i) {
        printf("%d ", vec[i]);
    }
    printf("\n");
}

int dynamic_knapsack(const vector<int>& values, const vector<int>& weights, int capacity) {

   vector<int> cost_prev(capacity + 1);
   vector<int> cost_cur(capacity + 1);

    for (int i = 0; i <= capacity; ++i) { 
        cost_prev[i] = 0;
    }

    for (int max_elem = 1; max_elem <= values.size(); ++max_elem) {

        if (max_elem % 100 == 0) {
            printf("%d\n", max_elem);
        }
        for (int max_weight = 1; max_weight <= capacity; ++max_weight) { 

            int opt_cost = cost_prev[max_weight];
            if (max_weight - weights[max_elem - 1] >= 0) {
                int wi = max_weight - weights[max_elem - 1];
                opt_cost = (cost_prev[wi] + values[max_elem - 1] > opt_cost) ? (cost_prev[wi] + values[max_elem - 1]) : opt_cost;
            }
            cost_cur[max_weight] = opt_cost;
        }

        //print_vec(cost_cur);
        for (int max_weight = 0; max_weight <= capacity; ++max_weight) {
            cost_prev[max_weight] = cost_cur[max_weight];
        }
    }

    return cost_cur[capacity];
}

int main(int argc, char**argv) {

    vector<int> values;
    vector<int> weights;
    int capacity;

    read_data(argv[1], &values, &weights, capacity);
    int result = dynamic_knapsack(values, weights, capacity);
    printf("Optimal cost = %d\n", result);

    return 0;
}
