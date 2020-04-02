/*

   EGRE 591 Compiler Construction
   Created By: Dan Relser

 */

#include "TCfileData.h"

namespace toyc
{
    TCfile::TCfile() { input = ""; output = ""; lines = 0; }

    TCfile::TCfile(std::string str, std::string str1, int number)
    {
        input = str;
        output = str1;
        lines = number;
    }

    std::string TCfile::getFileInfo()
    {
        return "Input:  " + input +
        "\nOutput: " + output +
        "\n" + std::to_string(lines) + " Lines\n\n[Output]\n";
    }
}
