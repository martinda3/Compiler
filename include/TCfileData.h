//
// Created by bart on 4/2/20.
//
#include <iostream>
#include <string>
#ifndef TCFILEDATA_H
#define TCFILEDATA_H

namespace toyc {

    class TCfile {
    public:
        TCfile();
        TCfile(std::string str, std::string str1, int number);
        std::string getFileInfo();

    private:
        std::string input;
        std::string output;
        int lines;

    };

}

#endif //TCFILEDATA_H
