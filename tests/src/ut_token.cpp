#include <gtest/gtest.h>
#include "../../src/token.h"
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Token, CreateWord)
{
    TokenPtr p(new TokenWord("Word"));
    ASSERT_EQ("Word", p->value());
}

TEST(Token, CreateNumber)
{
    TokenPtr p(new TokenNumber("1234"));
    ASSERT_EQ("1234", p->value());
}

TEST(Token, CreateLeftSquareBracket)
{
    TokenPtr p(new TokenLeftSquareBracket());
    ASSERT_EQ("[", p->value());
}

TEST(Token, CreateRightSquareBracket)
{
    TokenPtr p(new TokenRightSquareBracket());
    ASSERT_EQ("]", p->value());
}

TEST(Token, CreateTokenLeftParenthese)
{
    TokenPtr p(new TokenLeftParenthese());
    ASSERT_EQ("(", p->value());
}

TEST(Token, CreateTokenRightParenthese)
{
    TokenPtr p(new TokenRightParenthese());
    ASSERT_EQ(")", p->value());
}

TEST(Token, CreateColon)
{
    TokenPtr p(new TokenColon());
    ASSERT_EQ(":", p->value());
}

TEST(Token, CreateSemicolon)
{
    TokenPtr p(new TokenSemicolon());
    ASSERT_EQ(";", p->value());
}


TEST(Token, CreateTokenComma)
{
    TokenPtr p(new TokenComma());
    ASSERT_EQ(",", p->value());
}

TEST(Token, CreateTokenAdd)
{
    TokenPtr p(new TokenAdd());
    ASSERT_EQ("+", p->value());
}

TEST(Token, CreateTokenSub)
{
    TokenPtr p(new TokenSub());
    ASSERT_EQ("-", p->value());
}

TEST(Token, CreateTokenMul)
{
    TokenPtr p(new TokenMul());
    ASSERT_EQ("*", p->value());
}

TEST(Token, CreateTokenDiv)
{
    TokenPtr p(new TokenDiv());
    ASSERT_EQ("/", p->value());
}

TEST(Token, CreateTokenAssignment)
{
    TokenPtr p(new TokenAssignment());
    ASSERT_EQ("=", p->value());
}

TEST(Token, CreateTokenDot)
{
    TokenPtr p(new TokenDot());
    ASSERT_EQ(".", p->value());
}

//
//typedef std::shared_ptr<Token> TokenPtr;
//class TokenFactory
//{
//public:
//	TokenFactory();
//	TokenPtr createToken(int c, const std::string &value = std::string("")) const;
//	TokenPtr createTokenEOF() const;
//private:
//	void initAsciiTokenTable();
//	TokenFactory& operator=(const TokenFactory&);
//	mutable std::unordered_map<int, TokenPtr> _availableAsciiTokenTable;
//};
//
