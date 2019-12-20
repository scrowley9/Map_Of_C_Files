#include "ReadFile.hpp"
#include "FilesToParse.hpp"
#include "Connections.hpp"
#include <string>
#include <iosfwd>

/**
 * @brief Create FilesToParse object and fill vector with files being compiled together.
 *        File Names passed on execution!
 * 
 * @return FilesToParse object containing any appropriate files
 */
FilesToParse create_vector_of_strings(int argc, const char * argv[]){
    FilesToParse obj;
    for(int i = 0; i < argc; i++){
        if(obj.add_to_vector(string(argv[i])) == false){
            cout << "File: " << argv[i] << " does not exist." << endl;
        }
    }
    return obj;
}


/**
 * @brief Does the string exist in the vector?
 * 
 */
bool exists(vector<string> vector, string str, int index){
    for(int i = 0; i < vector.size(); i++){
        if(i >= index){
            return false;   // DNE
        }
        if(!(str.compare(vector[i]))){
            return true;    // Exists Already
        }
    }
    return false;
}

/**
 * @brief Read each file and determine the necessary includes
 * 
 * @param FilesToParse Vector
 * @return vector<ReadFile>
 */
vector<ReadFile*> read_files(FilesToParse vec){
    //cout << endl;
    
    // Local
    vector<string> local_vector = vec.get_vector();
    vector<ReadFile*> ret_vector;

    for(int i = 0; i < local_vector.size(); i++){
        if(exists(local_vector, local_vector[i], i)){   // Check if file has already been read
            continue;
        }
        ReadFile* read = new ReadFile(local_vector[i]); // Create ReadFile Object
        if(read->fill_include_vectors()){               // Read the files and populate the include vectors
            ret_vector.push_back(read);                 // Add ReadFile Object to the return vector
            //read->print_includes();                     // Print includes for fun!
        } else{
            read->~ReadFile();                          // No File - Deconstruct Read
        }
        //cout << endl;
    }
    //cout << "Done!" << endl;
    return ret_vector;
}

string extract_file_name_from_include(string header){

    const regex system_pattern = regex("(<{1}[A-Za-z_*/]+.?[h]?>{1})");
    const regex user_pattern = regex("(\"{1}[A-Za-z_*/]+.?[h]?\"{1})");

    const regex file_name = regex("([A-Za-z_*/]+.?[h]?)");
    
    // Matched Strings Go Here
    smatch matches;
    smatch matches_round2;

    // Match Line By Line
    if (regex_search(header, matches, system_pattern)) {
        string str = matches[0];
        if(regex_search(str, matches_round2, file_name)){
            return matches_round2[0];
        }
    } else if(regex_search(header, matches, user_pattern)){
        string str = matches[0];
        if(regex_search(str, matches_round2, file_name)){
            return matches_round2[0];
        }
    }
    return NULL;
}

Connections fill_adjacency_matrix(vector<ReadFile*> read_file_vector){
    Connections s = Connections();

    for(int i = 0; i < read_file_vector.size(); i++){
        s.add_new_vertex_to_matrix(read_file_vector[i]->get_file_name()); // Add file_name At Index 0

        // Connecting System Headers To 
        for(int j = 0; j < read_file_vector[i]->get_system_vector().size(); j++){
            string file_name = extract_file_name_from_include(read_file_vector[i]->get_system_vector()[j]);
            s.connect_edge(file_name, read_file_vector[i]->get_file_name());
        }
        for(int j = 0; j < read_file_vector[i]->get_user_vector().size(); j++){
            string file_name = extract_file_name_from_include(read_file_vector[i]->get_user_vector()[j]);
            s.connect_edge(file_name, read_file_vector[i]->get_file_name());
        }
    }
    return s;
}

Connections show_c_file_links(Connections s){

    const regex c_file_pattern = regex("([A-Za-z1-9_/]+.c)");
    
    // Matched Strings Go Here
    smatch matches;
    vector<string> v;
    Connections next;
    int k = 0;

    for(int i = 0; i < s.matrix.size(); i++){
        // Match Line By Line
        if (regex_search(s.matrix[i][0], matches, c_file_pattern)) {
            string str = matches[0];
            v.push_back(str);
            next.add_new_vertex_to_matrix(str);
            k+=1;
        }
    }
    for(int i = 0; i < v.size(); i++){
        int first_vertex = s.find_row_index(v[i]);
        for(int j = i+1; j < v.size(); j++){
            int second_vertex = s.find_row_index(v[j]);
            if(s.compare_header_files(s.matrix[first_vertex], s.matrix[second_vertex])){
                next.connect_edge(v[i], v[j]);  // Link C_files
            }
        }
    }
    return next;
}

int main(int argc, const char * argv[]){
    if(argc < 2) return 0;
    FilesToParse file_check_vector = create_vector_of_strings(argc-1, argv+1);
    vector<ReadFile*> read_file_vector = read_files(file_check_vector);
    Connections s = fill_adjacency_matrix(read_file_vector);
    //s.print_matrix();
    Connections n = show_c_file_links(s);
    n.print_matrix();
}
