//
//  FilesToParse.cpp
//  Mapping_Files
//
//  Created by Sean Crowley on 12/18/19.
//  Copyright © 2019 Sean Crowley. All rights reserved.
//

#include "FilesToParse.hpp"
#include <fstream>
#include <string>

using namespace std;

template class std::basic_string<char>;

                                    /* Public */

FilesToParse::FilesToParse(){
    this->file_vector.erase(this->file_vector.begin(), this->file_vector.end());
}

/**
    @brief Checks if file by that name exists and adds it to the instance vector if it does.
 
    @param file_name Name of file adding to vector
    @return bool: true on success, false otherwise
 */
bool FilesToParse::add_to_vector(string file_name){
    if(check_if_exists(file_name)){
        this->file_vector.push_back(file_name);
        //cout << "Adding to FileToParse Vector: " << file_name << endl;
        return true;
    }
    return false;
}

void FilesToParse::print_file_name_vector(void){
    for(vector<string>::iterator i = this->file_vector.begin(); i != this->file_vector.end(); i++){
        //cout << *i << endl;
    }
}

vector<string> FilesToParse::get_vector(void){
    return this->file_vector;
}


                                    /* Private */
/**
    @brief Check if file by this name exists
 
    @param file_name Name of file to search for
    @return bool: true on success, false otherwise
 */
bool FilesToParse::check_if_exists(string file_name){
    fstream file;
    file.open(file_name);
    if (file.is_open()) {
        file.close();
        return true;
    }
    return false;
}
