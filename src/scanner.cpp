#include "scanner.h"
Scanner::Scanner(std::istream& input_stream)
    : _istream(input_stream)
{

}

Scanner::Scanner(std::string filename)
    : _istream(_file)
{
    open(filename);
}

Scanner::~Scanner()
{
    _file.close();
}

bool Scanner::open(std::string filename)
{
    bool result(true);
    try
    {
        if (_file.is_open())
            throw std::logic_error("Scanner is already opened to be associated with a file");
        _file.open(filename);
        if (!_file.is_open())
            throw std::logic_error("Could not open file!");
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        result = false;
    }
    return result;
}

bool Scanner::is_open() const
{
    return _file.is_open();
}

bool Scanner::eof() const
{
    return _bufferedOutput.empty() && _istream.eof();
}

void Scanner::close()
{
    _file.close();
}

TokenPtr Scanner::nextToken()
{
    if (!_bufferedOutput.empty())
        return nextTokenFromBufferedOutput();
    while (!_istream.eof() && _bufferedOutput.empty())
    {
        std::string s = nextStringByDelimeter();
        _bufferedOutput.resize(s.size());
        std::copy(s.begin(), s.end(), _bufferedOutput.begin());
    }
    return nextTokenFromBufferedOutput();
}

TokenPtr Scanner::nextTokenFromBufferedOutput()
{
    std::string output;
    TokenPtr p;
    if (!_bufferedOutput.empty())
    {
        char &c = _bufferedOutput[0];
        if(isalpha(c))
            output = extractWord();
        else if(isalnum(c))
            output = extractNumber();
        else
            output = extractToken();
    }
    p = _tokenFactory.createToken(output[0], output);
    return p;
}

std::string Scanner::nextStringByDelimeter(char delimeter)
{
    int c;
    std::string s;
    for (c = _istream.get(); c != delimeter && !_istream.eof(); c = _istream.get())
        if (c != '\n')
            s += c;
    while (!_istream.eof() && c == delimeter)
        c = _istream.get();
    if (!_istream.eof())
        _istream.unget();
    return s;
}

std::string Scanner::extractChars(std::function<bool(char)> uniFunc)
{
    std::deque<char> &s = _bufferedOutput;
    auto iter = std::find_if(s.begin(), s.end(), uniFunc);
    int  n(iter - s.begin());
    std::string chars;
    chars.reserve(n);
    for(int i = 0; i < n; i++)
    {
        chars.push_back(s.front());
        s.pop_front();
    }
    return chars;

}

std::string Scanner::extractNumber()
{
    return extractChars(
            [](const char &c)
            {
                return isalnum(c) == 0;    
            });
}

std::string Scanner::extractWord()
{
    return extractChars(
            [](const char &c)
            {
                return isalpha(c) == 0;    
            });
}

std::string Scanner::extractToken()
{
    const char c = _bufferedOutput.front();
    _bufferedOutput.pop_front();
    return std::string(1, c);
}

