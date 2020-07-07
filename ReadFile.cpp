#include "ReadFile.hpp"
#include <string>

                            /* Public */

/* Constructor */
ReadFile::ReadFile(string file_name){
    this->ERRNO = 0;
    this->c_file_name = file_name;
    this->file = new fstream(file_name);
    if(!*(this->file)){
        cout << "FAILED TO OPEN: " << file_name << endl;
        this->ERRNO = 1;    // There was an error
    } else{
        this->fill_h_file_vector(); // Read C File headers into the vector
    }
    this->file->close();
}

/* Deconstructor */
ReadFile::~ReadFile(){
}

// Print Include Vectors && C File
void ReadFile::print_c_file_includes(void){
    if(this->h_file_vector.size() < 1){
        cout << "No files in .h file vector " << this->c_file_name << endl;
    }
    for(int i = 0; i < this->h_file_vector.size(); i++){
        cout << this->h_file_vector[i] << endl;
    }
}

/* Get C File Name */
string ReadFile::get_c_file_name(void){
    return this->c_file_name;
}

                              /* Protected */

/**
    @Brief Search through current directory for file by this name
 
    @Param file_name Name of file to search for
    @Return bool: true on success, false otherwise
 */
bool ReadFile::check_if_exists(string file_name){
    fstream file;

    // Otherwise open, check, and close
    file.open(file_name);
    if (file.is_open()) {
        file.close();
        return true;
    }
    return false;
}

/**
    @Brief Checks if file by that name exists and adds it to the instance vector if it does.
 
    @Param file_name Name of file adding to vector
    @Return bool: true on success, false otherwise
 */
bool ReadFile::add_to_vector(string file_name){
    // Check if h file already exists in vector
    for(int i = 0; i < h_file_vector.size(); i++){
        if(!h_file_vector[i].compare(file_name)){
            return false;
        }
    }

    this->h_file_vector.push_back(file_name);
    return true;
}


// Fill vector with include headers
bool ReadFile::fill_h_file_vector(void){
    
    /* Error Checking File */
    if (!*(this->file)){
        cerr << "no file\n";
        return false;
    }

    // Matched Strings Go Here
    smatch matches;

    // Match Line By Line
    for (string line; getline(*(this->file),line);) {

        /* Match System/User Include Header */
        if (regex_search(line, matches, this->system_pattern) || regex_search(line, matches, this->user_pattern)) {
            
            /* Get .h file name */
            string header_file_name = this->extract_file_name_from_include(matches[0]);
            if(header_file_name.empty()){
                cout << this->c_file_name << " - header empty..." << endl;
            } else{
                /* Add .h file to vector */
                this->add_to_vector(header_file_name);
            }
        }
    }
    return true;
}

string ReadFile::extract_file_name_from_include(string header){
    smatch matches;
    if(regex_search(header, matches, this->header_file_name_pattern)){
        return matches[0];
    }
    return string();
}

// Print Individual Vector
void ReadFile::print_files_that_include_this_h_file(vector<string> vec){
    for(int i = 0; i < vec.size(); i++){
        if(i+1 == vec.size()){
            cout << vec[i] << endl;
        }else{
            cout << vec[i] << ", " << endl;
        }
    }
}

// Regex Include Patterns
const regex ReadFile::system_pattern = regex("(# *include *<{1}[0-9A-Za-z_.*/]+.?[h]?>{1})");
const regex ReadFile::user_pattern = regex("(# *include *\"{1}[0-9A-Za-z_.*/]+.?[h]?\"{1})");
const regex ReadFile::header_file_name_pattern = regex("([0-9A-Za-z_*/]+.h)"); // PATTERN MUST HAVE '.h' in it!
