//
//  FilesToParse.cpp
//  Mapping_Files
//
//  Created by Sean Crowley on 12/18/19.
//  Copyright © 2019 Sean Crowley. All rights reserved.
//

#ifndef FilesToParse_hpp
#define FilesToParse_hpp

#include <iostream>
#include <vector>

using namespace std;

class FilesToParse{
public:
    FilesToParse();
    bool add_to_vector(string file_name);       // Checks file existence then adds it to vector
    void print_file_name_vector(void);
    vector<string> get_vector(void);

private:
    bool check_if_exists(string file_name);
    vector<string> file_vector;
};

#endif /* FilesToParse_hpp */
