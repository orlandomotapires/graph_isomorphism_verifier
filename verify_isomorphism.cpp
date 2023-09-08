#include "isomorphism.h"

int main() {
    FILE *file_a, *file_b;
    Graph *graph_a, *graph_b;

    file_a = fopen("adj_a.txt", "rt");
    file_b = fopen("adj_b.txt", "rt");

    graph_a = initialize_vertex();
    graph_b = initialize_vertex();

    if (file_a == NULL) {
        printf("Problems opening the file\n");
        return 1;
    }

    read_file_create_graph(&graph_a, file_a, 0);
    read_file_create_graph(&graph_b, file_b, 1);

    fclose(file_a);
    fclose(file_b);

    if (check_isomorphism(graph_a, graph_b)) printf("They are isomorphic!\n");
    else printf("They are not isomorphic!\n");

    return 0;
}
