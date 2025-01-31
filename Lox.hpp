#ifndef _LOX_
#define _LOX_
#include <fstream>
#include <vector>
#include <iostream>

class Lox{
    public:
    //running through file
    Lox(int argc,char* argv[]);

    void run_prompt();
    void run_file(std::string source_file);

    private:
};

#endif