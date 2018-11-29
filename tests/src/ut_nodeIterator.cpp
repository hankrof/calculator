#include <gtest/gtest.h>
#include "../../src/node_iterator.h"
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Iterator, CreateInfixIterator)
{
    Node *num1 = new NodeOperand(1);
    Node *num2 = new NodeOperand(2);
    Node *add  = new NodeAddOperator(num1, num2);
    Iterator *infixIterator = new NodeInfixIterator(add);
    
}
