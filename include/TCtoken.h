#ifndef TCTOKEN_H
#define TCTOKEN_H

namespace toyc {
    class TCtoken {
    public:
        TCtoken();

        TCtoken(int);

        TCtoken(int, std::string);

        int getTokenType();

        std::string getLexeme();

        std::string toString();

    private:
        int tokenType;
        std::string lexeme;
    };

}
#endif
