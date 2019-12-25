#ifndef CONNECTIONS_HPP
#define CONNECTIONS_HPP

#include <iostream>
#include <vector>
#include <regex>
using namespace std;

/*
    NOTE: Index 0 in every vector is the vertex for that vector
        Any other indices connected to the 2nd dimension vector are adjacent vertices
*/

class Connections{
public:
    Connections();
    Connections(string vertex);                  // DONE
    bool add_new_vertex_to_matrix(string v1);    // DONE

    // Note these both search starting at 0 (includes 'first' vertex)
    int find_row_index(string vertex);           // DONE
    int find_col_index(int row, string vertex);  // DONE
    void connect_edge(string v1, string v2);     // DONE
    void print_matrix(void);                // DONE
    bool push_back_iff_vertex_dne_in_vector(vector<string>& vector, string vertex);   // DONE
    string get_vertex(int row);
    bool compare_header_files(vector<string> v1, vector<string> v2);

    // Adjacency Matrix
    vector<vector<string> > matrix;
};

#endif // CONNECTIONS_HPP
