#include <gtest/gtest.h>
#include "../../src/node_iterator.h"
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(NodeIterator, CreateNullIterator)
{
    Node *num = new NodeOperand(1);
    NodeIterator iter = num->createIterator();
    iter->begin();
    ASSERT_EQ(nullptr, iter->item());
    ASSERT_EQ(true,    iter->end());
}

