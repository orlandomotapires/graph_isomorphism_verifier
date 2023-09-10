#include "graph.h"
#include "stack.h"

#define num_vertices 4

int adjacency_matrix_a[50][50];
int adjacency_matrix_b[50][50];

/*******************
 * Function Signatures
 *******************/

/* 
   Function: read_file_create_graph
   Description: Reads a file and creates a graph based on its contents.

   Parameters:
   - graph: Pointer to a pointer to a Graph structure.
   - file: Pointer to the file to be read.
   - graph_num: An integer indicating which graph (a or b) is being processed.

   Returns: void
*/

void read_file_create_graph(Graph **graph, FILE *file, int graph_num);

/* 
   Function: graphs_have_equal_number_of_vertices
   Description: Checks if two graphs have the same number of vertices.

   Parameters:
   - graph_a: Pointer to the first graph.
   - graph_b: Pointer to the second graph.

   Returns: bool (true if the graphs have equal sizes, false otherwise)
*/
bool graphs_have_equal_number_of_vertices(Graph *graph_a, Graph *graph_b);

/* 
   Function: vertices_have_equal_degrees
   Description: Checks if the degrees of corresponding vertices in two graphs are equal.

   Parameters:
   - graph_a: Pointer to the first graph.
   - graph_b: Pointer to the second graph.

   Returns: bool (true if the degrees are equal, false otherwise)
*/
bool vertices_have_equal_degrees(Graph *graph_a, Graph *graph_b);

/* 
   Function: print_matrix
   Description: Prints a 2D matrix.

   Parameters:
   - matrix: A 2D matrix to be printed.

   Returns: void
*/
void print_matrix(int matrix[50][50]);

/* 
   Function: main_diagonal_have_the_same_numbers_of_1
   Description: Checks if the main diagonal of two matrices is equal.

   Returns: bool (true if the main diagonals are equal, false otherwise)
*/
bool main_diagonal_have_the_same_numbers_of_1();

/* 
   Function: rows_columns_equal
   Description: Checks if the rows and columns of a given matrix are equal.

   Parameters:
   - current_adjacency_matrix: The matrix to be checked.

   Returns: bool (true if rows and columns are equal, false otherwise)
*/
bool rows_columns_equal(int current_adjacency_matrix[50][50]);

/* 
   Function: both_digraphs_or_both_normal_graphs
   Description: Checks if two graphs are both directed (digraphs) or both undirected (normal graphs).

   Returns: bool (true if both graphs are of the same type, false otherwise)
*/
bool both_digraphs_or_both_normal_graphs();

/* 
   Function: has_cycles
   Description: Checks if a graph has cycles.

   Parameters:
   - graph: Pointer to the graph to be checked.

   Returns: bool (true if the graph has cycles, false otherwise)
*/
bool has_cycles(Graph *graph);

/* 
   Function: is_a_isomorphism
   Description: Checks if two graphs are isomorphic based on various conditions.

   Parameters:
   - graph_a: Pointer to the first graph.
   - graph_b: Pointer to the second graph.

   Returns: int (1 if the graphs are isomorphic, 0 otherwise)
*/
bool is_a_isomorphism(Graph *graph_a, Graph *graph_b);

int get_num_edges(int matrix_adj[50][50]);

bool num_vertices_are_equal();

/*******************
 * Function Implementations
 *******************/

void read_file_create_graph(Graph **graph, FILE *file, int graph_num) {
    int a, i = 0;
    char Line[300];

    Graph *node_to_insert, *base_node;

    node_to_insert = initialize_vertex();
    base_node = initialize_vertex();
    
    if (fgets(Line, 100, file)) {
        for (a = 0; a <= (strlen(Line)); a++) {
            if (Line[a] != ' ') insert_main_list(graph, Line[a]);   
        }
    }

    while (!feof(file)) {
        if (fgets(Line, 100, file)) {
            for (a = 0; a <= (strlen(Line)); a++) {
                if (Line[a] == '1') {
                    node_to_insert = find_vertex(*graph, a + 1);
                    base_node = find_vertex(*graph, (i + 1));
                    insert_at_end_adj_list(&node_to_insert->main_list, &base_node);
                }

                if (Line[a] == '1' || Line[a] == '0') {
                    if (graph_num) {
                        adjacency_matrix_b[i][a] = Line[a];
                    } else {
                        adjacency_matrix_a[i][a] = Line[a];
                    }
                }
            }
        }
        i++;
    }
}

bool graphs_have_equal_number_of_vertices(Graph *graph_a, Graph *graph_b) {
    return main_list_size(graph_a) == main_list_size(graph_b);
}

bool vertices_have_equal_degrees(Graph *graph_a, Graph *graph_b) {
    int *degrees_a, *degrees_b;

    int size = main_list_size(graph_a);

    degrees_a = get_all_degrees(graph_a);
    degrees_b = get_all_degrees(graph_b);

    int posicional_degrees_a[size], posicional_degrees_b[size]; 

    memset(posicional_degrees_a, 0, size * sizeof(int));
    memset(posicional_degrees_b, 0, size * sizeof(int));

    for(int i = 0; i < size; i++){
        posicional_degrees_a[degrees_a[i]]++; // Insert the degrees on the position and sum 1 for each vertex with that degree
        posicional_degrees_b[degrees_b[i]]++;
    }

    for (int i = 0; i < size; i++) {
        if (posicional_degrees_a[i] != posicional_degrees_b[i]) return false;
    }

    return true;
}

void print_matrix(int matrix[50][50]) {
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

bool main_diagonal_have_the_same_numbers_of_1() {
    int num_1_a = 0, num_1_b = 0;

    for (int i = 0; i < num_vertices; i++) {
        if (adjacency_matrix_a[i][i] == '1') num_1_a++;
        if (adjacency_matrix_b[i][i] == '1') num_1_b++;
    }

    if (num_1_a != num_1_b) return 0;
    
    return 1;
}

bool rows_columns_equal(int current_adjacency_matrix[50][50]) {
    for (int i = 0; i < num_vertices; i++) {
        for (int row = i; row < num_vertices; row++) {
            for (int col = i; col < num_vertices; col++) {
                if (current_adjacency_matrix[row][col] != current_adjacency_matrix[col][row]) return 0;
            }
        }
    }
    return 1;
}

bool both_digraphs_or_both_normal_graphs() {
    if (rows_columns_equal(adjacency_matrix_a) == rows_columns_equal(adjacency_matrix_b)) return 1;
    return 0;
}

bool has_cycles(Graph *graph) {
    struct Stack remaining_nodes;
    int visited_nodes[500], capacity = 50;

    memset(visited_nodes, -1, sizeof(int));

    create_stack(&remaining_nodes, capacity);
    push(&remaining_nodes, 'A');

    while (!is_empty(&remaining_nodes)) {
        int current_node = pop(&remaining_nodes);
        visited_nodes[current_node] = 1;

        Graph *aux;
        aux = initialize_vertex();
        aux = find_vertex(graph, current_node - 64);

        Node *neighbors = aux->main_list;
        neighbors = neighbors->adjacency_list;

        while (neighbors->adjacency_list != NULL) {
            neighbors = neighbors->adjacency_list;

            char current_letter = neighbors->pointed_letter->letter;

            if (visited_nodes[current_letter] == 1) {
                //printf("Found a cycle on the node %c\n", current_letter);
                return true;
            }
            push(&remaining_nodes, current_letter);
        }
    }

    //printf("No cycle found!\n");
    return false;
}

int get_num_edges(int matrix_adj[50][50]){
   int num_ones = 0; 
    
    for(int i = 0; i < 4; i++){
        for(int j = i+1; j < 4; j++)
            if(matrix_adj[i][j] == '1') num_ones++;
    }

    return num_ones;
}

bool num_vertices_are_equal(){
    return get_num_edges(adjacency_matrix_a) == get_num_edges(adjacency_matrix_b);
}

bool is_a_isomorphism(Graph *graph_a, Graph *graph_b){
    if (!main_diagonal_have_the_same_numbers_of_1()) {
        printf("Fell into: main_diagonal_have_the_same_numbers_of_1() \n");
        return false;
    } else if (!num_vertices_are_equal()) {
        printf("Fell into: num_vertices_are_equal() \n");
        return false;
    }else if (!graphs_have_equal_number_of_vertices(graph_a, graph_b)) {
        printf("Fell into: graphs_have_equal_number_of_vertices() \n");
        return false;
    } else if (!vertices_have_equal_degrees(graph_a, graph_b)) {
        printf("Fell into: vertices_have_equal_degrees() \n");
        return false;
    } else if (has_cycles(graph_a) != has_cycles(graph_b)) {
        printf("Fell into: has_cycles() \n");
        return false;
    } else if (!both_digraphs_or_both_normal_graphs()) {
        printf("Fell into: both_digraphs_or_both_normal_graphs() \n");
        return false;
    } else return true;
}

/*
bool relates_vertexA_vertexB(int i, int j){

}
bool brute_force(Graph *graph_a, Graph *graph_b){
    int *degrees_a, *degrees_b;

    degrees_a = get_all_degrees(graph_a);
    degrees_b = get_all_degrees(graph_b);

    for(int i = 0; i < main_list_size(graph_a); i++){
        for(int j = i; j < main_list_size(graph_a); j++){
            if(relates_vertexA_vertexB(i, j)){
                break;
            }
        }
        
    }
}
*/
