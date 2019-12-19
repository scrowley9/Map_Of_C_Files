#include "ReadFile.hpp"
#include "FilesToParse.hpp"

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
    cout << endl;
    
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
            read->print_includes();                     // Print includes for fun!
        } else{
            read->~ReadFile();                          // No File - Deconstruct Read
        }
        cout << endl;
    }
    cout << "Done!" << endl;
    return ret_vector;
}

int main(int argc, const char * argv[]){
    FilesToParse file_check_vector = create_vector_of_strings(argc-1, argv+1);
    vector<ReadFile*> read_file_vector = read_files(file_check_vector);
}
