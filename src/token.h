#ifndef HM_RESULT_TOKEN_H
#define HM_RESULT_TOKEN_H
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <unordered_map>
#include <algorithm>
class Token
{
public:
	Token(const std::string &value);
	virtual ~Token() = 0;
	virtual const std::string& value() const final;
	virtual std::string& value() final;
private:
	std::string _value;
};

class TokenUndefined : public Token
{
public:
	TokenUndefined();

};

class TokenWord : public Token
{
public:
	TokenWord(const std::string &value);

};

class TokenNumber : public Token
{
public:
	TokenNumber(const std::string &value);
};

class TokenLeftSquareBracket : public Token
{
public:
	TokenLeftSquareBracket();

};

class TokenRightSquareBracket : public Token
{
public:
	TokenRightSquareBracket();

};

class TokenLeftParenthese : public Token
{
public:
	TokenLeftParenthese();

};

class TokenRightParenthese : public Token
{
public:
	TokenRightParenthese();

};

class TokenColon : public Token
{
public:
	TokenColon();

};

class TokenSemicolon : public Token
{
public:
	TokenSemicolon();

};


class TokenComma : public Token
{
public:
	TokenComma();

};

class TokenDiv : public Token
{
public:
	TokenDiv();

};

class TokenAdd : public Token
{
public:
	TokenAdd();

};

class TokenSub : public Token
{
public:
	TokenSub();

};

class TokenMul : public Token
{
public:
	TokenMul();

};

class TokenAssignment : public Token
{
public:
	TokenAssignment();

};

class TokenDot : public Token
{
public:
	TokenDot();

};

class TokenEOF : public Token
{
public:
	TokenEOF();

};

typedef std::shared_ptr<Token> TokenPtr;
class TokenFactory
{
public:
	TokenFactory();
	TokenPtr createToken(int c, const std::string &value = std::string("")) const;
	TokenPtr createTokenEOF() const;
private:
	void initAsciiTokenTable();
	TokenFactory& operator=(const TokenFactory&);
	mutable std::unordered_map<int, TokenPtr> _availableAsciiTokenTable;
};
#endif
