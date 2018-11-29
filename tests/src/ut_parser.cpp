#include <gtest/gtest.h>
#include "../../src/parser.h"
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//TEST(Parser, BuildExpression1)
//{
//    Parser parser;
//    NodeOperator<int>* expression = parser.buildExpression("1+2");
//    ASSERT_EQ('+', expression->op());
//    ASSERT_EQ( 1 , expression->left()->eval());
//    ASSERT_EQ( 2 , expression->right()->eval());
//    ASSERT_EQ( 3 , expression->eval());
//}
//
//TEST(Parser, BuildExpression2)
//{
//    Parser parser;
//    Node<int>* expression = parser.buildExpression("(1+2)/3");
//}
//
