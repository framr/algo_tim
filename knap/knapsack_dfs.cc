#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include<iostream>

/*
capacity number of elements
value weight
*/

using std::vector;
using std::cout;
using std::endl;

void print_vec(const vector<int>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        printf("%d ", vec[i]);
    }
    printf("\n");
}

typedef struct {
    int* weights;
    int* values;
    int size;
    int best_cost;
    int capacity;
} Knapsack;


int vec_sum(int* vec, int size) {
    int res = 0;
    for (int i = 0; i < size; ++i) {
         res += vec[i];
    }
    return res;
}
int dot_prod(int* vec1, int* vec2, int size) {
    int res = 0;
    for (int i = 0; i < size; ++i) {
         res += vec1[i] * vec2[i];
    }
    return res;
}


void read_data(const char* filename, Knapsack* knap) {

    FILE* fp;
    if ((fp = fopen(filename, "r")) == NULL) {
        perror("Error reading input file");
    }
    int num;
    fscanf(fp, "%d %d\n", &knap->capacity, &num);
    knap->size = num;
    knap->values = (int *) malloc(num * sizeof(int));
    knap->weights = (int *) malloc(num * sizeof(int));
    for (int i = 0; i < num; ++i) {
        fscanf(fp, "%d %d\n", &knap->values[i], &knap->weights[i]);
    }
}


int estimate_cost_bound(Knapsack* knap) {
    
    int bound = vec_sum(knap->values, knap->size);
    return bound;
}

int _knapsack_dfs(Knapsack*, int* solution, int first, int capacity_left, int cost_bound);


int knapsack_dfs(Knapsack* knap) {
    int cost_bound = estimate_cost_bound(knap);
    //printf("Initial cost upper bound = %d\n", cost_bound);

    knap->best_cost = 0;

    int solution[knap->size];
    for (int i = 0; i < knap->size; ++i) {
        solution[i] = 0;
    }

    int optimal_cost = _knapsack_dfs(knap, solution, 0, knap->capacity, cost_bound);
    return optimal_cost;

}
int _knapsack_dfs(Knapsack* knap, int* solution, int first, int capacity_left, int cost_bound) {

    if (cost_bound < knap->best_cost) {
        // prune the tree of possibilities
        return 0;
    } else if (first >= knap->size || capacity_left <= 0 || cost_bound <= 0) {
        int result = dot_prod(knap->values, solution, knap->size);
        if (result > knap->best_cost) {
            knap->best_cost = result;
        }

        return 0;
    }

    solution[first] = 0;
    int opt_cost = _knapsack_dfs(knap, solution, first + 1, capacity_left, cost_bound - knap->values[first]);
    
    if (knap->weights[first] <= capacity_left) {
        solution[first] = 1; 
        int cost = (knap->values[first] + 
            _knapsack_dfs(knap, solution, first + 1, capacity_left - knap->weights[first], cost_bound - knap->values[first]));

        opt_cost = (opt_cost > cost) ? opt_cost: cost;
    }

    return opt_cost;
}

int main(char* agrc, char** argv) {


    Knapsack* knap = (Knapsack* ) malloc(sizeof(Knapsack));
    read_data(argv[1], knap);
    int res = knapsack_dfs(knap);

    printf("Optimal dfs cost = %d\n", res);

return 1;
}









