# Verify Isomorphism

## Introduction to Graphs

Graphs are fundamental data structures used to represent a wide range of relationships between objects. In a graph, entities (nodes or vertices) are connected by edges, which can be directed or undirected. Graphs find applications in various fields, including computer science, social networks, transportation systems, and more. Understanding and analyzing graphs play a crucial role in solving complex problems.

## Isomorphism in Graphs

Graph Isomorphism is a fundamental problem in graph theory. Two graphs are said to be isomorphic if there exists a one-to-one correspondence between their vertices such that the edge relationships are preserved. In simpler terms, if you can match the vertices of one graph to the vertices of another in a way that preserves connections, the two graphs are isomorphic.

Graph Isomorphism Problem: Given two graphs G₁ and G₂, determine if they are isomorphic.

## The Importance of Checking Isomorphism

Checking the isomorphism of graphs is a critical task in various domains, including:

1. **Chemistry**: Identifying chemical compounds with the same structural formula.
2. **Computer Science**: Optimizing data structures and algorithms by recognizing structurally equivalent graphs.
3. **Cryptography**: Identifying isomorphic graphs is essential for cryptographic protocols.
4. **Pattern Recognition**: Recognizing isomorphisms helps in image and pattern recognition.

## Computational Complexity

The Graph Isomorphism problem is known for its complexity. In computer science, we classify problems based on their difficulty to solve efficiently. Two important complexity classes relevant to this problem are P and NP:

- **P (Polynomial Time)**: [Problems in P](https://en.wikipedia.org/wiki/P_(complexity)) can be solved in polynomial time, where the time required to solve them grows at most as a polynomial of the input size.
- **NP (Nondeterministic Polynomial Time)**: [Problems in NP](https://en.wikipedia.org/wiki/NP_(complexity)) are those for which a proposed solution can be verified in polynomial time.

Graph Isomorphism is an NP problem, which means that while verifying a proposed isomorphism is easy (polynomial time), finding an isomorphism is currently not known to be in P. This leads to the classification of Graph Isomorphism as a challenging problem, and no known polynomial-time algorithms exist for it.

## Limitations

The limitations of current graph isomorphism verification include:

1. **Complexity**: The problem is NP, which means that it is computationally challenging to find an isomorphism, especially for large graphs.
2. **Practical Constraints**: For practical applications, finding an isomorphism may not be feasible in a reasonable time frame for large or complex graphs.
3. **Approximations**: In some cases, heuristic approaches or approximations may be used to identify potential isomorphisms, but these may not guarantee correctness.

## Code Files

### [graph.h](./libraries/graph.h)

- Purpose: Header file defining data structures and functions related to graphs.
- Details: This file defines essential structures and operations for creating and manipulating graphs, such as vertices and edges.

### [isomorphism.h](./libraries/isomorphism.h)

- Purpose: Header file containing declarations for functions related to graph isomorphism.
- Details: This file defines functions and data structures used for checking graph isomorphism, including comparisons and verifications.

### [stack.h](./libraries/stack.h)

- Purpose: Header file defining a stack data structure.
- Details: This file defines a stack data structure and relevant operations, which are utilized in the isomorphism checking process.

### [verify_isomorphism.c](verify_isomorphism.c)

- Purpose: Implementation file containing the main program for verifying graph isomorphism.
- Details: This file contains the main logic for reading adjacency matrices from files ([adj_a.txt](./matrixes/adj_a.txt) and [adj_b.txt](./matrixes/adj_b.txt)), creating graphs, and checking isomorphism between them using various conditions and algorithms.

### [adj_a.txt](./matrixes/adj_a.txt) and [adj_b.txt](./matrixes/adj_b.txt)

- Purpose: Text files containing adjacency matrices for two graphs.
- Details: These files represent the adjacency matrices of the two graphs (graph A and graph B) to be compared for isomorphism. Each element in the matrix represents an edge between vertices.

In summary, the code files collectively provide the tools and logic needed to read adjacency matrices, create graphs, and verify graph isomorphism between the provided graphs.

## Additional References

- [MIT OpenCourseWare: Complexity: P, NP, NP-completeness, Reductions](https://www.youtube.com/watch?v=eHZifpgyH_4&ab_channel=MITOpenCourseWare)
- [Master's Thesis on Graph Isomorphism](https://repositorio.ufsc.br/bitstream/handle/123456789/218147/TCC.pdf?sequence=1&isAllowed=y)
