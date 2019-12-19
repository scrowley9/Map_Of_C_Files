#include "connections.hpp"
using namespace std;

// /* long int == 8 bytes */
// /* Top 4    == Row index */
// /* Bottom 4 == Col index */
// #define ROW(x) (int)(((x)>>32)&0xFFFFFFFF)
// #define COL(x) (int)((x)&0xFFFFFFFF)

// /* Push together row and column */
// #define R_C_INDEX(r, c) ((long int)(((((long int)r)<<32)&(~(long int)0xFFFFFFFF)) & (long int)((c)&0xFFFFFFFF)))


// Constructor -- DONE
template <class T>
Connections<T>::Connections(T node){
    vector<vector<T> > matrix(1, vector<T>(1)); // Init Matrix
    matrix[0][0] = node;
    this->matrix = matrix;
}

/* Add New Vertex To Graph -- DONE */
template <class T>
bool Connections<T>::add_new_vertex_to_matrix(T vertex){
    for(int i = 0; i < this->matrix.size(); i++){
        if(this->matrix[i][0] == vertex){
            return false;
        }
    }
    this->matrix.push_back(vector<T>(1));
    this->matrix[this->matrix.size()-1][0] = vertex;
    return true;
}

// Seems alright thus far
template <class T>
void Connections<T>::connect_edge(T v1, T v2){
    if(v1 == v2) return;
    int v1_r = find_row_index(v1);
    int v2_r = find_row_index(v2);
    int v1_c = -1;
    int v2_c = -1;

    if(v1_r == -1){
        if(v2_r == -1){
            cout << "Neither vertex exists in the graph.\nAdding Both and Connecting." << endl;
            if(!this->add_new_vertex_to_matrix(v1)){
                cout << "Something really bad happened V1 and V2 - V1 - connect_edge" << endl;
                return;
            }
            if(!this->add_new_vertex_to_matrix(v2)){
                cout << "Something really bad happened V1 and V2 - V2 - connect_edge" << endl;
                this->matrix.pop_back(); // Delete v1 which was just added
                return;
            }
            this->push_back_iff_vertex_dne_in_vector(this->matrix[this->matrix.size()-2], v2);  // Connect v1->v2
            this->push_back_iff_vertex_dne_in_vector(this->matrix[this->matrix.size()-1], v1);  // Connect v2->v1
        }else{
            cout << v1 << ": DNE... Adding " << v1 << "\n" << v2 << ": Exists" << endl;
            if(!this->add_new_vertex_to_matrix(v1)){
                cout << "Something really bad happened V1 - connect_edge" << endl;
                return;
            }
            this->push_back_iff_vertex_dne_in_vector(this->matrix[v2_r], v1);                   // Connect v2->v1
            this->push_back_iff_vertex_dne_in_vector(this->matrix[this->matrix.size()-1], v2);  // Connect v1->v2
        }
    } else{
        if(v2_r == -1){
            cout << v2 << ": DNE... Adding " << v2 << "\n" << v1 << ": Exists" << endl;
            if(!this->add_new_vertex_to_matrix(v2)){
                cout << "Something really bad happened V2 - connect_edge" << endl;
                return;
            }
            this->push_back_iff_vertex_dne_in_vector(this->matrix[v1_r], v2);                   // Connect v1->v2
            this->push_back_iff_vertex_dne_in_vector(this->matrix[this->matrix.size()-1], v1);  // Connect v2->v1

        }else{
            cout << "Both v1 && v2 exist! Connecting if they aren't already..." << endl;
            this->push_back_iff_vertex_dne_in_vector(this->matrix[v1_r], v2);
            this->push_back_iff_vertex_dne_in_vector(this->matrix[v2_r], v1);
        }
    }
}

/** DONE
 * @brief function that pushes to back iff the vertex doesn't already exist in vector!
 * 
 * @return bool - True successfully pushed to back of vector, False if vertex is already in vector
 */
template <class T>
bool Connections<T>::push_back_iff_vertex_dne_in_vector(vector<T>& vector, T vertex){
    for(int i = 0; i < vector.size(); i++){
        if(vector[i] == vertex){
            return false;
        }
    }
    /* Push Back */
    vector.push_back(vertex);
    return true;
}

/* Print Matrix - DONE */
template <class T>
void Connections<T>::print_matrix(void){
    for(int i = 0; i < this->matrix.size(); i++){
        for(int j = 0; j < this->matrix[i].size(); j++){
            cout << "Row(" << i << ")-Column(" << j << ") Data: " << this->matrix[i][j].data() << ", ";
        }
        cout << endl;
    }
}

// DONE
template <class T>
int Connections<T>::find_row_index(T vertex){
    for(int i = 0; i < this->matrix.size(); i++){
        if(vertex == matrix[i][0]){
            return i;
        }
    }
    return -1;
}


template <class T>
int Connections<T>::find_col_index(int row, T vertex){
    if(this->matrix.size() <= row) return -1;
    for(int j = 0; j < this->matrix[row].size(); j++){
        if(vertex == matrix[row][j]){
            return j;
        }
    }
    return -1;
}



void duplicate_vertex_test(void);
void adding_duplicate_edges_test(void);
void test_find_row_index(void);
void test_find_col_index(void);
void test_connect_edge_both_vertices_in_matrix(void);
void test_connect_edge_v1_in_matrix_v2_not(void);
void test_connect_edge_v2_in_matrix_v1_not(void);
void test_multiconnections(void);
void test_connect_edge_v1_v2_dne(void);

int main(void){
    // duplicate_vertex_test();
    // adding_duplicate_edges_test();
    // test_find_row_index();
    // test_connect_edge_both_vertices_in_matrix();
    // test_connect_edge_v1_in_matrix_v2_not();
    // test_connect_edge_v2_in_matrix_v1_not();
    // test_connect_edge_v1_v2_dne();
    // test_multiconnections();
    test_find_col_index();
}

/**
    void print_matrix(void);
    bool push_back_iff_vertex_dne_in_vector(vector<T> vector, T vertex);
*/

// TESTING:
// Constructor
// add_new_vertex_to_graph(T v1);
void duplicate_test(void){
    Connections<string> s("Barry");
    s.add_new_vertex_to_matrix("Tim");
    s.add_new_vertex_to_matrix("Sean");
    s.add_new_vertex_to_matrix("Sam");
    s.add_new_vertex_to_matrix("Sam");      // Duplicate
    s.add_new_vertex_to_matrix("Sam");      // Duplicate
    s.add_new_vertex_to_matrix("Sarah");
    s.add_new_vertex_to_matrix("Tim");      // Duplicate
    s.add_new_vertex_to_matrix("Sarah");    // Duplicate
    s.add_new_vertex_to_matrix("Tim");      // Duplicate
    s.add_new_vertex_to_matrix("Tim");      // Duplicate
    s.add_new_vertex_to_matrix("Barry");    // Duplicate
    s.add_new_vertex_to_matrix("Sarah");    // Duplicate
    s.print_matrix();
}

// TESTING:
// find_row_index(T vertex);
void test_find_row_index(void){
    Connections<string> s("Barry");
    s.add_new_vertex_to_matrix("Tim");
    s.add_new_vertex_to_matrix("Sean");
    s.add_new_vertex_to_matrix("Sam");
    s.add_new_vertex_to_matrix("Sarah");

    cout << s.find_row_index("Barry") << endl;
    cout << s.find_row_index("Tim") << endl;
    cout << s.find_row_index("Sean") << endl;
    cout << s.find_row_index("Sam") << endl;
    cout << s.find_row_index("Sarah") << endl;
}

// TESTING:
// connect_edge(T v1, T v2);
void test_connect_edge_both_vertices_in_matrix(void){
    Connections<string> s("Barry");
    s.add_new_vertex_to_matrix("Tim");
    s.add_new_vertex_to_matrix("Sean");
    s.add_new_vertex_to_matrix("Sam");
    s.add_new_vertex_to_matrix("Sarah");

    s.connect_edge("Barry", "Tim");
    s.connect_edge("Sean", "Sarah");
    s.print_matrix();
}

// TESTING:
// connect_edge(T v1, T v2);
void test_connect_edge_v1_in_matrix_v2_not(void){
    Connections<string> s("Barry");
    s.connect_edge("Barry", "Tim");
    s.print_matrix();
}

// TESTING:
// connect_edge(T v1, T v2);
void test_connect_edge_v2_in_matrix_v1_not(void){
    Connections<string> s("Barry");
    s.add_new_vertex_to_matrix("Sean");
    s.add_new_vertex_to_matrix("Sarah");
    s.add_new_vertex_to_matrix("Quinn");
    s.connect_edge("Barry", "Tim");
    s.print_matrix();
}

// TESTING:
// connect_edge(T v1, T v2);
void test_connect_edge_v1_v2_dne(void){
    Connections<string> s("Sean");
    s.connect_edge("Barry", "Tim");
    s.print_matrix();
}

void adding_duplicate_edges_test(void){
    Connections<string> s("Barry");
    s.add_new_vertex_to_matrix("Tim");

    // Duplicates
    s.connect_edge("Barry", "Tim");
    s.print_matrix();
}

void test_multiconnections(void){
    Connections<string> s("Barry");
    s.add_new_vertex_to_matrix("Sean");
    s.add_new_vertex_to_matrix("Sarah");
    s.add_new_vertex_to_matrix("Quinn");
    s.connect_edge("Barry", "Sean");
    s.connect_edge("Barry", "Quinn");
    s.connect_edge("Barry", "Sarah");
    s.print_matrix();
}

void test_find_col_index(void){
    Connections<string> s("Barry");
    s.add_new_vertex_to_matrix("Sean");
    s.add_new_vertex_to_matrix("Sarah");
    s.add_new_vertex_to_matrix("Quinn");
    s.connect_edge("Barry", "Sean");
    s.connect_edge("Barry", "Sarah");
    s.connect_edge("Barry", "Quinn");
    s.print_matrix();

    cout << s.find_col_index(0,"Sean") << endl;
    cout << s.find_col_index(0,"Quinn") << endl;
    cout << s.find_col_index(0,"Sarah") << endl;
    cout << s.find_col_index(1,"Barry") << endl;
    cout << s.find_col_index(2,"Barry") << endl;
    cout << s.find_col_index(3,"Barry") << endl;
    cout << s.find_col_index(3,"Sean") << endl;
    cout << s.find_col_index(3,"Quinn") << endl;
    cout << s.find_col_index(4,"Quinn") << endl;
}
