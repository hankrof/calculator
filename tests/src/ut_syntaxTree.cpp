#include <gtest/gtest.h>
#include "../../src/syntax_tree.h"
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(NodeOperand, CreateNodeOperand)
{
    Node *num = new NodeOperand(1);
    ASSERT_EQ(1, num->eval());
}

TEST(NodeOperand, NodeSymbol)
{
    Node *num = new NodeOperand(1);
    ASSERT_EQ("1", num->symbol());
}

TEST(NodeOperand, OperatorException)
{
    Node *num = new NodeOperand(1);
    ASSERT_ANY_THROW(num->op());
}

TEST(NodeOperand, OperandIsLeafTesting)
{
    Node *num = new NodeOperand(1);
    ASSERT_EQ(nullptr, num->left());
    ASSERT_EQ(nullptr, num->right());
}

TEST(NodeOperator, CreateAddOperator)
{
    NodeOperator *add = new NodeAddOperator(new NodeOperand(1), new NodeOperand(2));
    ASSERT_EQ('+', add->op());
    ASSERT_EQ("+", add->symbol());
    ASSERT_EQ(1, add->left()->eval());
    ASSERT_EQ(2, add->right()->eval());
}

TEST(NodeOperator, EvaluateAddOperator)
{
    NodeOperator *add = new NodeAddOperator(new NodeOperand(1), new NodeOperand(2));
    ASSERT_EQ(3, add->eval());
}

TEST(NodeOperator, EvaluateTwoAddOperator)
{
    NodeOperator *add1 = new NodeAddOperator(new NodeOperand(1), new NodeOperand(2));
    NodeOperator *add2 = new NodeAddOperator(add1, new NodeOperand(3));
    ASSERT_EQ(6, add2->eval());
}

TEST(NodeOperator, CreateSubOperator)
{
    NodeOperator *sub = new NodeSubOperator(new NodeOperand(1), new NodeOperand(2));
    ASSERT_EQ('-',     sub->op());
    ASSERT_EQ("-",     sub->symbol());
    ASSERT_EQ(1, sub->left()->eval());
    ASSERT_EQ(2, sub->right()->eval());
}

TEST(NodeOperator, EvaluateSubOperator)
{
    NodeOperator *sub = new NodeSubOperator(new NodeOperand(1), new NodeOperand(2));
    ASSERT_EQ(-1, sub->eval());
}

TEST(NodeOperator, EvaluateTwoSubOperator)
{
    NodeOperator *sub1 = new NodeSubOperator(new NodeOperand(1), new NodeOperand(2));
    NodeOperator *sub2 = new NodeSubOperator(sub1, new NodeOperand(3));
    ASSERT_EQ(-4, sub2->eval());
}

TEST(NodeOperator, EvaluateAddAndSubOperator)
{
    //1 + 2 - 3 = 0 
    NodeOperator *add = new NodeAddOperator(new NodeOperand(1), new NodeOperand(2));
    NodeOperator *sub = new NodeSubOperator(add, new NodeOperand(3));
    ASSERT_EQ(0, sub->eval());
}

TEST(NodeOperator, CreateMulOperator)
{
    NodeOperator *mul = new NodeMulOperator(new NodeOperand(2), new NodeOperand(3));
    ASSERT_EQ('*',     mul->op());
    ASSERT_EQ("*",     mul->symbol());
    ASSERT_EQ(2, mul->left()->eval());
    ASSERT_EQ(3, mul->right()->eval());
}

TEST(NodeOperator, EvaluateMulOperator)
{
    NodeOperator *mul = new NodeMulOperator(new NodeOperand(2), new NodeOperand(3));
    ASSERT_EQ(6, mul->eval());
}

TEST(NodeOperator, EvaluateTwoMulOperator)
{
    NodeOperator *mul1 = new NodeMulOperator(new NodeOperand(2), new NodeOperand(3));
    NodeOperator *mul2 = new NodeMulOperator(mul1, new NodeOperand(4));
    ASSERT_EQ(24, mul2->eval());
}

TEST(NodeOperator, CreateDivOperator)
{
    NodeOperator *div = new NodeDivOperator(new NodeOperand(6), new NodeOperand(3));
    ASSERT_EQ('/',     div->op());
    ASSERT_EQ("/",     div->symbol());
    ASSERT_EQ(6, div->left()->eval());
    ASSERT_EQ(3, div->right()->eval());
}

TEST(NodeOperator, EvaluateDivOperator)
{
    NodeOperator *div = new NodeDivOperator(new NodeOperand(6), new NodeOperand(3));
    ASSERT_EQ(2, div->eval());
}

TEST(NodeOperator, EvaluateTwoDivOperator)
{
    NodeOperator *div1 = new NodeDivOperator(new NodeOperand(20), new NodeOperand(2));
    NodeOperator *div2 = new NodeDivOperator(div1, new NodeOperand(5));
    ASSERT_EQ(2, div2->eval());
}



























