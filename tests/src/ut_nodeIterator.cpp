#include <gtest/gtest.h>
#include "../../src/node_iterator.h"
#include "../../src/node_const_iterator.h"
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(NodeIterator, CreateInfixOperandConstIterator)
{
    const Node *num = new NodeOperand(1);
    auto iter = num->createInfixIterator();
    iter->begin();
    ASSERT_EQ(nullptr, iter->item());
    ASSERT_EQ(true,    iter->end());
}

TEST(NodeIterator, CreatePrefixOperandConstIterator)
{
    Node *num = new NodeOperand(1);
    auto iter = num->createPrefixIterator();
    iter->begin();
    ASSERT_EQ(nullptr, iter->item());
    ASSERT_EQ(true,    iter->end());
}

TEST(NodeIterator, CreatePostfixOperandConstIterator)
{
    Node *num = new NodeOperand(1);
    auto iter = num->createInfixIterator();
    iter->begin();
    ASSERT_EQ(nullptr, iter->item());
    ASSERT_EQ(true,    iter->end());
}

TEST(NodeIterator, CreateInfixOperandIterator)
{
    Node *num = new NodeOperand(1);
    auto iter = num->createInfixIterator();
    iter->begin();
    ASSERT_EQ(nullptr, iter->item());
    ASSERT_EQ(true,    iter->end());
}

TEST(NodeIterator, CreatePrefixOperandIterator)
{
    Node *num = new NodeOperand(1);
    auto iter = num->createPrefixIterator();
    iter->begin();
    ASSERT_EQ(nullptr, iter->item());
    ASSERT_EQ(true,    iter->end());
}

TEST(NodeIterator, CreatePostfixOperandIterator)
{
    Node *num = new NodeOperand(1);
    auto iter = num->createInfixIterator();
    iter->begin();
    ASSERT_EQ(nullptr, iter->item());
    ASSERT_EQ(true,    iter->end());
}

TEST(NodeOperatorIterator, CreatePrefixOperatorConstIterator)
{
    /*     +   
     *    / \
     *   1   2
     *
     */
    const Node *add = new NodeAddOperator(new NodeOperand(1), new NodeOperand(2));
    auto iter = add->createPrefixIterator();
    iter->begin();
    ASSERT_EQ(false, iter->end());
    ASSERT_EQ("+", iter->item()->symbol());
    iter->next();
    ASSERT_EQ(false, iter->end());
    ASSERT_EQ("1", iter->item()->symbol());
    iter->next();
    ASSERT_EQ(false, iter->end());
    ASSERT_EQ("2",  iter->item()->symbol());
    iter->next();
    ASSERT_EQ(true, iter->end());
}

TEST(NodeOperatorIterator, CreatePrefixOperatorConstIterator2)
{
    /*         
     *        +
     *       / \
     *      +   -
     *     / \ / \
     *    1  2 3  4
     *
     * 1 + 2 + 3 - 4 = 2
     *
     * */
    Node *addLeaf = new NodeAddOperator(new NodeOperand(1), new NodeOperand(2));
    Node *subLeaf = new NodeSubOperator(new NodeOperand(3), new NodeOperand(4));
    const Node *addRoot = new NodeAddOperator(addLeaf, subLeaf);
    auto iter = addRoot->createPrefixIterator();
    iter->begin();
    ASSERT_EQ("+", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("+", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("1", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("2", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("-", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("3", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("4", iter->item()->symbol());
    iter->next();
    ASSERT_EQ(true, iter->end());
}

TEST(NodeOperatorIterator, CreatePrefixOperatorConstIterator3)
{
    /*         
     *        +
     *       / \
     *      1   *
     *         / \
     *         3  4
     *
     * 1 + 3 * 4 = 13
     *
     * */
    Node *mul = new NodeMulOperator(new NodeOperand(3), new NodeOperand(4));
    const Node *addRoot = new NodeAddOperator(new NodeOperand(1), mul);
    auto iter = addRoot->createPrefixIterator();
    iter->begin();
    ASSERT_EQ("+", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("1", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("*", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("3", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("4", iter->item()->symbol());
    iter->next();
    ASSERT_EQ(true, iter->end());
    ASSERT_EQ(13, addRoot->eval());
}

TEST(NodeOperatorIterator, CreatePrefixOperatorConstIterator4)
{
    /*         
     *        *
     *       / \
     *      +  10 
     *     /  \
     *    *   /     
     *   / \ / \
     *  1  3 5 6
     *
     * (1 * 3 + 5 / 6) * 10 = (3 + 0.83333) * 10 = 38.3333
     *
     * */
    Node *mulLeaf = new NodeMulOperator(new NodeOperand(1), new NodeOperand(3));
    Node *divLeaf = new NodeDivOperator(new NodeOperand(5), new NodeOperand(6));
    Node *add2nd  = new NodeAddOperator(mulLeaf, divLeaf);
    const Node *mulRoot = new NodeMulOperator(add2nd, new NodeOperand(10));
    auto iter = mulRoot->createPrefixIterator();
    iter->begin();
    ASSERT_EQ("*", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("+", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("*", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("1", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("3", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("/", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("5", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("6", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("10", iter->item()->symbol());
    iter->next();
    ASSERT_EQ(true, iter->end());
    ASSERT_NEAR(38.3333, mulRoot->eval(), 0.0001);
}


TEST(NodeOperatorIterator, CreatePrefixOperatorConstIterator5)
{
    /*         
     *          +
     *         / \
     *        /   \
     *       *     *
     *      / \   / \
     *     5  6  7   *
     *              / \
     *             9   *
     *                / \
     *               10 11
     *
     * */

     Node *fiveSixMul     = new NodeMulOperator(new NodeOperand(5),  new NodeOperand(6));
     Node *tenElevenMul   = new NodeMulOperator(new NodeOperand(10), new NodeOperand(11));
     Node *nineMul        = new NodeMulOperator(new NodeOperand(9),  tenElevenMul);
     Node *sevenMul       = new NodeMulOperator(new NodeOperand(7), nineMul);
     const Node *addRoot  = new NodeAddOperator(fiveSixMul, sevenMul);
     auto iter = addRoot->createPrefixIterator();
     iter->begin();
     ASSERT_EQ("+", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("*", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("5", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("6", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("*", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("7", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("*", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("9", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("*", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("10", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("11", iter->item()->symbol());
     iter->next();
     ASSERT_EQ(true, iter->end());
}

TEST(NodeOperatorIterator, CreateInfixOperatorConstIterator)
{
    /*     +   
     *    / \
     *   1   2
     *
     */
    const Node *add = new NodeAddOperator(new NodeOperand(1), new NodeOperand(2));
    auto iter = add->createInfixIterator();
    iter->begin();
    ASSERT_EQ(false, iter->end());
    ASSERT_EQ("1", iter->item()->symbol());
    iter->next();
    ASSERT_EQ(false, iter->end());
    ASSERT_EQ("+", iter->item()->symbol());
    iter->next();
    ASSERT_EQ(false, iter->end());
    ASSERT_EQ("2",  iter->item()->symbol());
    iter->next();
    ASSERT_EQ(true, iter->end());
}

TEST(NodeOperatorIterator, CreateInfixOperatorConstIterator2)
{
    /*         
     *        +
     *       / \
     *      +   -
     *     / \ / \
     *    1  2 3  4
     *
     * 1 + 2 + 3 - 4 = 2
     *
     * */
    Node *addLeaf = new NodeAddOperator(new NodeOperand(1), new NodeOperand(2));
    Node *subLeaf = new NodeSubOperator(new NodeOperand(3), new NodeOperand(4));
    const Node *addRoot = new NodeAddOperator(addLeaf, subLeaf);
    auto iter = addRoot->createInfixIterator();
    iter->begin();
    ASSERT_EQ("1", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("+", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("2", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("+", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("3", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("-", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("4", iter->item()->symbol());
    iter->next();
    ASSERT_EQ(true, iter->end());
}

TEST(NodeOperatorIterator, CreateInfixOperatorConstIterator3)
{
    /*         
     *        +
     *       / \
     *      1   *
     *         / \
     *         3  4
     *
     * 1 + 3 * 4 = 13
     *
     * */
    Node *mul = new NodeMulOperator(new NodeOperand(3), new NodeOperand(4));
    const Node *addRoot = new NodeAddOperator(new NodeOperand(1), mul);
    auto iter = addRoot->createInfixIterator();
    iter->begin();
    ASSERT_EQ("1", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("+", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("3", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("*", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("4", iter->item()->symbol());
    iter->next();
    ASSERT_EQ(true, iter->end());
    ASSERT_EQ(13, addRoot->eval());
}

TEST(NodeOperatorIterator, CreateInfixOperatorConstIterator4)
{
    /*         
     *        *
     *       / \
     *      +  10 
     *     /  \
     *    *   /     
     *   / \ / \
     *  1  3 5 6
     *
     * (1 * 3 + 5 / 6) * 10 = (3 + 0.83333) * 10 = 38.3333
     *
     * */
    Node *mulLeaf = new NodeMulOperator(new NodeOperand(1), new NodeOperand(3));
    Node *divLeaf = new NodeDivOperator(new NodeOperand(5), new NodeOperand(6));
    Node *add2nd  = new NodeAddOperator(mulLeaf, divLeaf);
    const Node *mulRoot = new NodeMulOperator(add2nd, new NodeOperand(10));
    auto iter = mulRoot->createInfixIterator();
    iter->begin();
    ASSERT_EQ("1", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("*", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("3", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("+", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("5", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("/", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("6", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("*", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("10", iter->item()->symbol());
    iter->next();
    ASSERT_EQ(true, iter->end());
    ASSERT_NEAR(38.3333, mulRoot->eval(), 0.0001);
}


TEST(NodeOperatorIterator, CreateInfixOperatorConstIterator5)
{
    /*         
     *          +
     *         / \
     *        /   \
     *       *     *
     *      / \   / \
     *     5  6  7   *
     *              / \
     *             9   *
     *                / \
     *               10 11
     *
     * */

     Node *fiveSixMul     = new NodeMulOperator(new NodeOperand(5),  new NodeOperand(6));
     Node *tenElevenMul   = new NodeMulOperator(new NodeOperand(10), new NodeOperand(11));
     Node *nineMul        = new NodeMulOperator(new NodeOperand(9),  tenElevenMul);
     Node *sevenMul       = new NodeMulOperator(new NodeOperand(7), nineMul);
     const Node *addRoot  = new NodeAddOperator(fiveSixMul, sevenMul);
     auto iter = addRoot->createInfixIterator();
     iter->begin();
     ASSERT_EQ("5", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("*", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("6", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("+", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("7", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("*", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("9", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("*", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("10", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("*", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("11", iter->item()->symbol());
     iter->next();
     ASSERT_EQ(true, iter->end());
}

TEST(NodeOperatorIterator, CreatePostfixOperatorConstIterator)
{
    /*     +   
     *    / \
     *   1   2
     *
     */
    const Node *add = new NodeAddOperator(new NodeOperand(1), new NodeOperand(2));
    auto iter = add->createPostfixIterator();
    iter->begin();
    ASSERT_EQ(false, iter->end());
    ASSERT_EQ("1", iter->item()->symbol());
    iter->next();
    ASSERT_EQ(false, iter->end());
    ASSERT_EQ("2", iter->item()->symbol());
    iter->next();
    ASSERT_EQ(false, iter->end());
    ASSERT_EQ("+",  iter->item()->symbol());
    iter->next();
    ASSERT_EQ(true, iter->end());
}

TEST(NodeOperatorIterator, CreatePostfixOperatorConstIterator2)
{
    /*         
     *        +
     *       / \
     *      +   -
     *     / \ / \
     *    1  2 3  4
     *
     * 1 + 2 + 3 - 4 = 2
     *
     * */
    Node *addLeaf = new NodeAddOperator(new NodeOperand(1), new NodeOperand(2));
    Node *subLeaf = new NodeSubOperator(new NodeOperand(3), new NodeOperand(4));
    const Node *addRoot = new NodeAddOperator(addLeaf, subLeaf);
    auto iter = addRoot->createPostfixIterator();
    iter->begin();
    ASSERT_EQ("1", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("2", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("+", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("3", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("4", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("-", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("+", iter->item()->symbol());
    iter->next();
    ASSERT_EQ(true, iter->end());
}

TEST(NodeOperatorIterator, CreatePostfixOperatorConstIterator3)
{
    /*         
     *        +
     *       / \
     *      1   *
     *         / \
     *         3  4
     *
     * 1 + 3 * 4 = 38.333333
     *
     * */
    Node *mul = new NodeMulOperator(new NodeOperand(3), new NodeOperand(4));
    const Node *addRoot = new NodeAddOperator(new NodeOperand(1), mul);
    auto iter = addRoot->createPostfixIterator();
    iter->begin();
    ASSERT_EQ("1", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("3", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("4", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("*", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("+", iter->item()->symbol());
    iter->next();
    ASSERT_EQ(true, iter->end());
}

TEST(NodeOperatorIterator, CreatePostfixOperatorConstIterator4)
{
    /*         
     *        *
     *       / \
     *      +  10 
     *     /  \
     *    *   /     
     *   / \ / \
     *  1  3 5 6
     *
     * (1 * 3 + 5 / 6) * 10 = (3 + 0.83333) * 10 = 38.3333
     *
     * */
    Node *mulLeaf = new NodeMulOperator(new NodeOperand(1), new NodeOperand(3));
    Node *divLeaf = new NodeDivOperator(new NodeOperand(5), new NodeOperand(6));
    Node *add2nd  = new NodeAddOperator(mulLeaf, divLeaf);
    const Node *mulRoot = new NodeMulOperator(add2nd, new NodeOperand(10));
    auto iter = mulRoot->createPostfixIterator();
    iter->begin();
    ASSERT_EQ("1", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("3", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("*", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("5", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("6", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("/", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("+", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("10", iter->item()->symbol());
    iter->next();
    ASSERT_EQ("*", iter->item()->symbol());
    iter->next();
    ASSERT_EQ(true, iter->end());
    ASSERT_NEAR(38.3333, mulRoot->eval(), 0.0001);
}


TEST(NodeOperatorIterator, CreatePostfixOperatorConstIterator5)
{
    /*         
     *          +
     *         / \
     *        /   \
     *       *     *
     *      / \   / \
     *     5  6  7   *
     *              / \
     *             9   *
     *                / \
     *               10 11
     *
     * */

     Node *fiveSixMul     = new NodeMulOperator(new NodeOperand(5),  new NodeOperand(6));
     Node *tenElevenMul   = new NodeMulOperator(new NodeOperand(10), new NodeOperand(11));
     Node *nineMul        = new NodeMulOperator(new NodeOperand(9),  tenElevenMul);
     Node *sevenMul       = new NodeMulOperator(new NodeOperand(7), nineMul);
     const Node *addRoot  = new NodeAddOperator(fiveSixMul, sevenMul);
     auto iter = addRoot->createPostfixIterator();
     iter->begin();
     ASSERT_EQ("5", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("6", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("*", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("7", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("9", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("10", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("11", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("*", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("*", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("*", iter->item()->symbol());
     iter->next();
     ASSERT_EQ("+", iter->item()->symbol());
     iter->next();
     ASSERT_EQ(true, iter->end());
}


//TEST(NodeOperatorIterator, CreateInfixOperatorIterator)
//{
//    Node *add = new NodeAddOperator(new NodeOperand(1), new NodeOperand(2));
//    NodeIterator iter = add->createInfixIterator();
//    iter->begin();
//    ASSERT_EQ(false, iter->end());
//    ASSERT_EQ("1", iter->item()->symbol());
//    iter->next();
//    ASSERT_EQ(false, iter->end());
//    ASSERT_EQ("+", iter->item()->symbol());
//    iter->next();
//    ASSERT_EQ(false, iter->end());
//    ASSERT_EQ("2",  iter->item()->symbol());
//    iter->next();
//    ASSERT_EQ(true, iter->end());
//}
//
//TEST(NodeOperatorIterator, CreatePostfixOperatorIterator)
//{
//    Node *add = new NodeAddOperator(new NodeOperand(1), new NodeOperand(2));
//    NodeIterator iter = add->createPostfixIterator();
//    iter->begin();
//    ASSERT_EQ(false, iter->end());
//    ASSERT_EQ("1", iter->item()->symbol());
//    iter->next();
//    ASSERT_EQ(false, iter->end());
//    ASSERT_EQ("2", iter->item()->symbol());
//    iter->next();
//    ASSERT_EQ(false, iter->end());
//    ASSERT_EQ("+",  iter->item()->symbol());
//    iter->next();
//    ASSERT_EQ(true, iter->end());
//}
//
//TEST(NodeOperatorIterator, CreatePrefixOperatorIterator)
//{
//    Node *add = new NodeAddOperator(new NodeOperand(1), new NodeOperand(2));
//    NodeIterator iter = add->createPrefixIterator();
//    iter->begin();
//    ASSERT_EQ(false, iter->end());
//    ASSERT_EQ("+", iter->item()->symbol());
//    iter->next();
//    ASSERT_EQ(false, iter->end());
//    ASSERT_EQ("1", iter->item()->symbol());
//    iter->next();
//    ASSERT_EQ(false, iter->end());
//    ASSERT_EQ("2",  iter->item()->symbol());
//    iter->next();
//    ASSERT_EQ(true, iter->end());
//}

