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
   Function: get_num_edges
   Description: Counts the number of '1's in the upper triangular part of a matrix.

   Parameters:
   - matrix_adj: The adjacency matrix to be counted.

   Returns: int (the number of '1's)
*/
int get_num_edges(int matrix_adj[50][50]);

/* 
   Function: num_edges_are_equal
   Description: Checks if the number of edges in both graphs is equal.

   Returns: bool (true if the number of edges is equal, false otherwise)
*/
bool num_edges_are_equal();

/* 
   Function: is_a_isomorphism
   Description: Checks if two graphs are isomorphic based on various conditions.

   Parameters:
   - graph_a: Pointer to the first graph.
   - graph_b: Pointer to the second graph.

   Returns: bool (true if the graphs are isomorphic, false otherwise)
*/
bool is_a_isomorphism(Graph *graph_a, Graph *graph_b);

/* 
   Function: brute_force
   Description: Performs a brute-force isomorphism check.

   Parameters:
   - graph_a: Pointer to the first graph.

   Returns: bool (true if the graphs are isomorphic, false otherwise)
*/
bool brute_force(Graph *graph_a);

/*******************
 * Function Implementations
*******************/

void read_file_create_graph(Graph **graph, FILE *file, int graph_num) {
    int a, i = 0;
    char Line[300];

    Graph *node_to_insert, *base_node;

    node_to_insert = initialize_graph();
    base_node = initialize_graph();
    
    if (fgets(Line, 100, file)) {
        for (a = 0; a < (strlen(Line)); a++) {
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

    int positional_degrees_a[size], positional_degrees_b[size]; 

    memset(positional_degrees_a, 0, size * sizeof(int));
    memset(positional_degrees_b, 0, size * sizeof(int));

    for(int i = 0; i < size; i++){
        positional_degrees_a[degrees_a[i]]++; // Insert the degrees on the position and sum 1 for each vertex with that degree
        positional_degrees_b[degrees_b[i]]++;
    }

    for (int i = 0; i < size; i++) {
        if (positional_degrees_a[i] != positional_degrees_b[i]) return false;
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
        aux = initialize_graph();
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

bool num_edges_are_equal(){
    return get_num_edges(adjacency_matrix_a) == get_num_edges(adjacency_matrix_b);
}

bool is_a_isomorphism(Graph *graph_a, Graph *graph_b){
    if (!main_diagonal_have_the_same_numbers_of_1()) {
        //printf("Fell into: main_diagonal_have_the_same_numbers_of_1() \n");
        return false;
    } else if (!num_edges_are_equal()) {
        //printf("Fell into: num_edges_are_equal() \n");
        return false;
    }else if (!graphs_have_equal_number_of_vertices(graph_a, graph_b)) {
        //printf("Fell into: graphs_have_equal_number_of_vertices() \n");
        return false;
    } else if (!vertices_have_equal_degrees(graph_a, graph_b)) {
        //printf("Fell into: vertices_have_equal_degrees() \n");
        return false;
    } else if (has_cycles(graph_a) != has_cycles(graph_b)) {
        //printf("Fell into: has_cycles() \n");
        return false;
    } else if (!both_digraphs_or_both_normal_graphs()) {
        //printf("Fell into: both_digraphs_or_both_normal_graphs() \n");
        return false;
    } else return true;
}

/*******************
 * Isomorphism Function
*******************/

void swap_char(char* a, char* b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

// Function to generate all the possible permutations of the initial letters
void generate_permutations_char(char permutation[4], int start, int end, char permutations[24][4]) {
    static int count = 0; // Contador para armazenar as permutações

    if (start == end) {
        // Uma permutação completa foi gerada, armazene-a no vetor de permutações
        for (int i = 0; i < 4; i++) {
            permutations[count][i] = permutation[i];
        }
        count++;
    } else {
        for (int i = start; i <= end; i++) {
            swap_char(&permutation[start], &permutation[i]);
            generate_permutations_char(permutation, start + 1, end, permutations);
            swap_char(&permutation[start], &permutation[i]); // Desfaz a troca para a próxima iteração
        }
    }
}

char permutations_char[24][4];

/*******************
 * BRUTE FORCE PART
*******************/

int visited[4] = {0};  // Initially, all columns are unvisited
int permutations[24][4][4];  // Matrix to store permutations

void swap(int col1, int col2) {
    for (int row = 0; row < 4; row++) {
        int temp = adjacency_matrix_b[row][col1];
        adjacency_matrix_b[row][col1] = adjacency_matrix_b[row][col2];
        adjacency_matrix_b[row][col2] = temp;
    }
}

void generate_permutations(int col) {
    if (col == 4) {
        static int count = 0;
        // Store the current matrix as a valid permutation
        for (int row = 0; row < 4; row++) {
            for (int c = 0; c < 4; c++) {
                permutations[count][row][c] = adjacency_matrix_b[row][c];
            }
        }
        count++;
    } else {
        for (int i = 0; i < 4; i++) {
            if (!visited[i]) {
                visited[i] = 1;
                swap(col, i);
                generate_permutations(col + 1);
                swap(col, i);  // Undo the swap for the next iteration
                visited[i] = 0;
            }
        }
    }
}

void read_matrix_create_graph(Graph **graph, int matrix_actu[50][4]) {
    Graph *node_to_insert, *base_node;

    node_to_insert = initialize_graph();
    base_node = initialize_graph();
   
    for (int a = 0; a <= 4; a++) insert_main_list(graph, 'A' + a);  

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if (matrix_actu[i][j] == '1') {
                node_to_insert = find_vertex(*graph, j+1);
                base_node = find_vertex(*graph, (i + 1));
                insert_at_end_adj_list(&node_to_insert->main_list, &base_node);
            }
        } 
    }
}

bool brute_force(Graph *graph){
    Graph *graph_actu;

    int num_permutations = 24;
    generate_permutations(0);

    char elements[4] = {'A', 'B', 'C', 'D'};
    generate_permutations_char(elements, 0, 3, permutations_char);

    for(int i = 0; i < num_permutations; i++){
        graph_actu = initialize_graph();
        read_matrix_create_graph(&graph_actu, permutations[i]);

        if(is_a_isomorphism(graph, graph_actu)){

            printf("They are isomorphic!\n");

            printf("Isomorphism function: \n");
            for(int k = 0; k < 4; k++)
                printf("%c -> %c\n", elements[k], permutations_char[i][k]);
            
            return true;
        }
    }

    return false;
}
