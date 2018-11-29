#include "token.h"
Token::Token(const std::string &value)
    :  _value(value)
{

}

Token::~Token()
{

}

const std::string& Token::value() const
{
    return _value;
}

std::string& Token::value()
{
    return _value;
}

TokenUndefined::TokenUndefined()
    : Token("")
{

}

TokenWord::TokenWord(const std::string &value)
    : Token(value)
{

}

TokenNumber::TokenNumber(const std::string &value)
    : Token(value)
{

}

TokenLeftSquareBracket::TokenLeftSquareBracket()
    : Token("[")
{

}

TokenRightSquareBracket::TokenRightSquareBracket()
    : Token("]")
{

}

TokenLeftParenthese::TokenLeftParenthese()
    : Token("(")
{

}

TokenRightParenthese::TokenRightParenthese()
    : Token(")")
{

}

TokenColon::TokenColon()
    : Token(":")
{

}

TokenSemicolon::TokenSemicolon()
    : Token(";")
{

}

TokenComma::TokenComma()
    : Token(",")
{

}


TokenAdd::TokenAdd()
    : Token("+")
{

}

TokenSub::TokenSub()
    : Token("-")
{

}

TokenMul::TokenMul()
    : Token("*")
{

}

TokenDiv::TokenDiv()
    : Token("/")
{

}


TokenAssignment::TokenAssignment()
    : Token("=")
{

}

TokenDot::TokenDot()
    : Token(".")
{

}

TokenEOF::TokenEOF()
    : Token("")
{

}

TokenFactory::TokenFactory()
{
    initAsciiTokenTable();
}

TokenPtr TokenFactory::createToken(int c, const std::string &value) const
{
    if (_availableAsciiTokenTable[c])
        return _availableAsciiTokenTable[c];
    else if (!value.empty())
    {
        if(std::find_if(value.begin(), value.end(), 
            [](const char &c) { return isalnum(c) == 0; }
          ) ==  value.end())
        {
            return TokenPtr(new TokenNumber(value));
        }
        return TokenPtr(new TokenWord(value));
    }
    else if(value.empty())
    {
        return TokenPtr(new TokenEOF());
    }
    else
        return _availableAsciiTokenTable[256];
}

TokenPtr TokenFactory::createTokenEOF() const
{
    return TokenPtr(new TokenEOF());
}

void TokenFactory::initAsciiTokenTable()
{
    _availableAsciiTokenTable['[']  = std::shared_ptr<Token>(new TokenLeftSquareBracket());
    _availableAsciiTokenTable[']']  = std::shared_ptr<Token>(new TokenRightSquareBracket());
    _availableAsciiTokenTable['(']  = std::shared_ptr<Token>(new TokenLeftParenthese());
    _availableAsciiTokenTable[')']  = std::shared_ptr<Token>(new TokenRightParenthese());
    _availableAsciiTokenTable[':']  = std::shared_ptr<Token>(new TokenColon());
    _availableAsciiTokenTable[',']  = std::shared_ptr<Token>(new TokenComma());
    _availableAsciiTokenTable['/']  = std::shared_ptr<Token>(new TokenDiv());
    _availableAsciiTokenTable['+']  = std::shared_ptr<Token>(new TokenAdd());
    _availableAsciiTokenTable['*']  = std::shared_ptr<Token>(new TokenMul());
    _availableAsciiTokenTable['=']  = std::shared_ptr<Token>(new TokenAssignment());
    _availableAsciiTokenTable['.']  = std::shared_ptr<Token>(new TokenDot());
    _availableAsciiTokenTable[256]  = std::shared_ptr<Token>(new TokenUndefined());
}
