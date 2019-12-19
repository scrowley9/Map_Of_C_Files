#ifndef READFILE_HPP
#define READFILE_HPP

#include <iostream>
#include <fstream>  // File Stream Header
#include <vector>
#include <regex>
using namespace std;


class ReadFile{
public:
    ReadFile(string file_name); // Constructor
    ~ReadFile();                // Deconstructor
    bool fill_include_vectors(void);
    void print_includes(void);
    vector<string> get_system_vector(void);
    vector<string> get_user_vector(void);
    string get_file_name(void);

protected:
    /* Include Header Pattern */
    static const regex system_pattern;
    static const regex user_pattern;

private:
    vector<string> system_includes;
    vector<string> user_includes;
    fstream* file;
    string file_name;
};

#endif // READFILE_HPP
