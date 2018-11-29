#ifndef HM_RESULT_SCANNER_H
#define HM_RESULT_SCANNER_H
#include "token.h"
#include <iostream>
#include <fstream>
#include <deque>
#include <exception>
#include <algorithm>
#include <functional>
class Scanner
{
public:
    Scanner(std::istream& input_stream);
    Scanner(std::string filename);
    Scanner(const Scanner &scn) = delete;
    Scanner& operator=(const Scanner &scn) = delete;
    ~Scanner();
    bool open(std::string filename);
    bool is_open() const;
    bool eof() const;
    void close();
    TokenPtr nextToken();
    std::string nextStringByDelimeter(char delimeter = ' ');
private:
    std::string extractChars(std::function<bool(char)> uniFunc);
    std::string extractNumber();
    std::string extractWord();
    std::string extractToken();
    TokenPtr nextTokenFromBufferedOutput();
    std::istream& _istream;
    std::ifstream _file;
    TokenFactory _tokenFactory;
    std::deque<char> _bufferedOutput;
};
#endif
