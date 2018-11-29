#include <gtest/gtest.h>
#include "../../src/scanner.h"
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Scanner, CreateScannerFromString)
{
    std::stringstream ss("1234");
    Scanner scn(ss);
    ASSERT_EQ("1234", scn.nextStringByDelimeter());
}

TEST(Scanner, GetNumberToken)
{
    std::stringstream ss("1234");
    Scanner scn(ss);
    ASSERT_EQ("1234", scn.nextToken()->value());
}

TEST(Scanner, GetNumberToken2)
{
    std::stringstream ss("1234 4567");
    Scanner scn(ss);
    ASSERT_EQ("1234", scn.nextToken()->value());
    ASSERT_EQ("4567", scn.nextToken()->value());
}

TEST(Scanner, GetNumberAndSemicolonToken)
{
    std::stringstream ss("1234;4567");
    Scanner scn(ss);
    ASSERT_EQ("1234", scn.nextToken()->value());
    ASSERT_EQ(";"   , scn.nextToken()->value());
    ASSERT_EQ("4567", scn.nextToken()->value());
}

TEST(Scanner, GetNumberAndOperatorFromSentence)
{
    std::stringstream ss("1234 + 4567 - 9999");
    Scanner scn(ss);
    ASSERT_EQ("1234", scn.nextToken()->value());
    ASSERT_EQ("+"   , scn.nextToken()->value());
    ASSERT_EQ("4567", scn.nextToken()->value());
    ASSERT_EQ("-", scn.nextToken()->value());
    ASSERT_EQ("9999", scn.nextToken()->value());
}

TEST(Scanner, GetNumberAndOperatorFromSentence2)
{
    std::stringstream ss("(1234 + 4567 - 9999)");
    Scanner scn(ss);
    ASSERT_EQ("(", scn.nextToken()->value());
    ASSERT_EQ("1234", scn.nextToken()->value());
    ASSERT_EQ("+"   , scn.nextToken()->value());
    ASSERT_EQ("4567", scn.nextToken()->value());
    ASSERT_EQ("-", scn.nextToken()->value());
    ASSERT_EQ("9999", scn.nextToken()->value());
    ASSERT_EQ(")", scn.nextToken()->value());
}

TEST(Scanner, GetNumberAndOperatorFromSentence3)
{
    std::stringstream ss("(1+2)/5-10");
    Scanner scn(ss);
    ASSERT_EQ("(", scn.nextToken()->value());
    ASSERT_EQ("1", scn.nextToken()->value());
    ASSERT_EQ("+"   , scn.nextToken()->value());
    ASSERT_EQ("2", scn.nextToken()->value());
    ASSERT_EQ(")", scn.nextToken()->value());
    ASSERT_EQ("/", scn.nextToken()->value());
    ASSERT_EQ("5", scn.nextToken()->value());
    ASSERT_EQ("-", scn.nextToken()->value());
    ASSERT_EQ("10", scn.nextToken()->value());
}

