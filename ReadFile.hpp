#ifndef READFILE_HPP
#define READFILE_HPP

#include <iostream>
#include <fstream>  // File Stream Header
#include <vector>
#include <regex>
using namespace std;


class ReadFile{
public:
    ReadFile(string file_name); // Constructor  -- Opens File, get headers, Closes File
    ~ReadFile();                // Deconstructor
    void print_c_file_includes(void);
    string get_c_file_name(void);
    int ERRNO;
    vector<string> h_file_vector;

protected:
    bool check_if_exists(string file_name); // Not Currently Needed
    bool add_to_vector(string file_name);
    void print_files_that_include_this_h_file(vector<string> vec);
    bool fill_h_file_vector(void);

    /* Include Header Pattern */
    static const regex system_pattern;
    static const regex user_pattern;
    static const regex header_file_name_pattern;

private:
    string extract_file_name_from_include(string header);
    fstream* file;
    string c_file_name;
};

#endif // READFILE_HPP
