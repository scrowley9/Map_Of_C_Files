#include "ReadFile.hpp"

                            /* Public Methods */

/* Constructor */
ReadFile::ReadFile(string file_name){
    this->file_name = file_name;
    this->file = new fstream(file_name);
    if(!this->file){
        cout << "FAILED TO OPEN: " << file_name << endl;
    }

}

/* Deconstructor */
ReadFile::~ReadFile(){
    this->file->close();
    delete this->file;
}

// Fill System/User Include Vectors
bool ReadFile::fill_include_vectors(void){
    /* Error Checking File */
    if (!*(this->file)){
        cerr << "no file\n";
        return false;
    }

    cout << "Reading: " << this->file_name << endl;

    // Matched Strings Go Here
    smatch matches;

    // Match Line By Line
    for (string line; getline(*(this->file),line);) {
        if (regex_search(line, matches, this->system_pattern)) {
            this->system_includes.push_back(matches[0]);    // Complete System Header Match
        } else if(regex_search(line, matches, this->user_pattern)){
            this->user_includes.push_back(matches[0]);      // Complete User Header Match
        }
    }
    return true;
}

// Print Include Vectors
void ReadFile::print_includes(void){
    for(vector<string>::iterator i = this->system_includes.begin(); i != this->system_includes.end(); i++){
        cout << i->data() << endl;
    }
    for(vector<string>::iterator i = this->user_includes.begin(); i != this->user_includes.end(); i++){
        cout << i->data() << endl;
    }
}

// Get Include Vectors
vector<string> ReadFile::get_system_vector(void){
    return this->system_includes;
}
vector<string> ReadFile::get_user_vector(void){
    return this->user_includes;
}
string ReadFile::get_file_name(void){
    return this->file_name;
}


                              /* Protected */
// Regex Include Patterns
const regex ReadFile::system_pattern = regex("(# *include *<{1}[A-Za-z_*]+.?[h]?>{1})");
const regex ReadFile::user_pattern = regex("(# *include *\"{1}[A-Za-z_*]+.?[h]?\"{1})");
