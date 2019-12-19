#ifndef CONNECTIONS_HPP
#define CONNECTIONS_HPP

#include <iostream>
#include <vector>
using namespace std;

/*
    NOTE: Index 0 in every vector is the vertex for that vector
        Any other indices connected to the 2nd dimension vector are adjacent vertices
*/

template <class T>
class Connections{
public:
    Connections(T vertex);                  // DONE
    bool add_new_vertex_to_matrix(T v1);    // DONE

    // Note these both search starting at 0 (includes 'first' vertex)
    int find_row_index(T vertex);           // DONE
    int find_col_index(int row, T vertex);  // DONE
    void connect_edge(T v1, T v2);          // DONE
    void print_matrix(void);                // DONE
    bool push_back_iff_vertex_dne_in_vector(vector<T>& vector, T vertex);   // DONE

    // Adjacency Matrix
    vector<vector<T> > matrix;
};

#endif // CONNECTIONS_HPP
