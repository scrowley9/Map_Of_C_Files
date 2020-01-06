#include "Connections.hpp"
#include <string>
using namespace std;

Connections::Connections(){
    this->matrix = vector< vector<string> >(); // Init Matrix
}

// Constructor -- DONE
Connections::Connections(string str){
    vector<vector<string> > matrix(1, vector<string>(1)); // Init Matrix
    matrix[0][0] = str;
    this->matrix = matrix;
}

/* Add New Vertex To Graph -- DONE */
bool Connections::add_new_vertex_to_matrix(string vertex){
    for(int i = 0; i < this->matrix.size(); i++){
        if(!this->matrix[i][0].compare(vertex)){
            return false;
        }
    }
    this->matrix.push_back(vector<string>(1));
    this->matrix[this->matrix.size()-1][0] = vertex;
    return true;
}

// Seems alright thus far
void Connections::connect_edge(string v1, string v2){
    if(v1 == v2) return;
    int v1_r = find_row_index(v1);
    int v2_r = find_row_index(v2);
    int v1_c = -1;
    int v2_c = -1;

    if(v1_r == -1){
        if(v2_r == -1){
            //cout << "Neither vertex exists in the graph.\nAdding Both and Connecting." << endl;
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
            //cout << v1 << ": DNE... Adding " << v1 << "\n" << v2 << ": Exists" << endl;
            if(!this->add_new_vertex_to_matrix(v1)){
                cout << "Something really bad happened V1 - connect_edge" << endl;
                return;
            }
            this->push_back_iff_vertex_dne_in_vector(this->matrix[v2_r], v1);                   // Connect v2->v1
            this->push_back_iff_vertex_dne_in_vector(this->matrix[this->matrix.size()-1], v2);  // Connect v1->v2
        }
    } else{
        if(v2_r == -1){
            //cout << v2 << ": DNE... Adding " << v2 << "\n" << v1 << ": Exists" << endl;
            if(!this->add_new_vertex_to_matrix(v2)){
                cout << "Something really bad happened V2 - connect_edge" << endl;
                return;
            }
            this->push_back_iff_vertex_dne_in_vector(this->matrix[v1_r], v2);                   // Connect v1->v2
            this->push_back_iff_vertex_dne_in_vector(this->matrix[this->matrix.size()-1], v1);  // Connect v2->v1

        }else{
            //cout << "Both v1 && v2 exist! Connecting if they aren't already..." << endl;
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

bool Connections::push_back_iff_vertex_dne_in_vector(vector<string>& vector, string vertex){
    for(int i = 0; i < vector.size(); i++){
        if(!vector[i].compare(vertex)){
            return false;
        }
    }
    /* Push Back */
    vector.push_back(vertex);
    return true;
}

/* Print Matrix - DONE */

void Connections::print_matrix(void){
    for(int i = 0; i < this->matrix.size(); i++){
        for(int j = 0; j < this->matrix[i].size(); j++){
            if(j == 0){
                cout << "(" << i << "," << j << ") H File: " << this->matrix[i][j].data();
            }else{
                cout << "(" << i << "," << j << ") C File: " << this->matrix[i][j].data();
            }
            
            if(j+1 < this->matrix[i].size()){
                cout << ", ";
            }
        }
        cout << endl;
    }
}

// DONE

int Connections::find_row_index(string vertex){
    for(int i = 0; i < this->matrix.size(); i++){
        if(vertex == matrix[i][0]){
            return i;
        }
    }
    return -1;
}



int Connections::find_col_index(int row, string vertex){
    if(this->matrix.size() <= row) return -1;
    for(int j = 0; j < this->matrix[row].size(); j++){
        if(vertex == matrix[row][j]){
            return j;
        }
    }
    return -1;
}


string Connections::get_vertex(int row){
    if(this->matrix.size() <= row) return NULL;
    return this->matrix[row][0];
}

/* Returns true if they contain at least 1 similar header file */
bool Connections::compare_header_files(vector<string> v1, vector<string> v2){
    const regex h_file_pattern = regex("([A-Za-z1-9_/]+.h)");

    for(int i = 1; i < v1.size(); i++){
        for(int j = 1; j < v2.size(); j++){
            if(!v1[i].compare(v2[j])){
                return true;
            }
        }
    }
    return false;
}

