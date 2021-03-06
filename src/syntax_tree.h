#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H
#include <string>
#include <memory>
class Iterator;
class ConstIterator;
typedef std::unique_ptr<Iterator> NodeIterator;
typedef std::unique_ptr<ConstIterator> NodeConstIterator;

//We should implement the bignumber class for OperandType.
typedef double OperandType;
class Node
{
public:
    virtual ~Node() = 0;
    virtual OperandType eval() const = 0;
    virtual char op() const = 0;
    virtual std::string symbol() const = 0;
    virtual Node* left() = 0;
    virtual Node* right() = 0;
    virtual const Node* left() const = 0;
    virtual const Node* right() const = 0;
    virtual NodeIterator createPrefixIterator() = 0 ;
    virtual NodeConstIterator createPrefixIterator() const = 0 ;
    virtual NodeIterator createInfixIterator() = 0 ;
    virtual NodeConstIterator createInfixIterator() const = 0 ;
    virtual NodeIterator createPostfixIterator() = 0 ;
    virtual NodeConstIterator createPostfixIterator() const = 0 ;
};

class NodeOperand : public Node
{
public:
    NodeOperand(OperandType&& value);
    OperandType eval() const;
    char op() const;
    std::string symbol() const;
    Node* left() final;
    Node* right() final;
    const Node *left() const;
    const Node *right() const;
    NodeIterator createPrefixIterator();
    NodeConstIterator createPrefixIterator() const;
    NodeIterator createInfixIterator();
    NodeConstIterator createInfixIterator() const;
    NodeIterator createPostfixIterator();
    NodeConstIterator createPostfixIterator() const;
private:
    OperandType _value;
};


class NodeOperator : public Node
{
public:
    NodeOperator(char op, Node *left, Node *right);
    char op() const;
    std::string symbol() const final;
    Node* left() final;
    Node* right() final;
    const Node* left() const final;
    const Node* right() const final;
    NodeIterator createPrefixIterator();
    NodeConstIterator createPrefixIterator() const;
    NodeIterator createInfixIterator();
    NodeConstIterator createInfixIterator() const;
    NodeIterator createPostfixIterator();
    NodeConstIterator createPostfixIterator() const;
private:
    char  _op;
    Node *_left;
    Node *_right;
};


class NodeAddOperator : public NodeOperator
{
public:
    NodeAddOperator(Node *left, Node *right);
    OperandType eval() const;
};


class NodeSubOperator : public NodeOperator
{
public:
    NodeSubOperator(Node *left, Node *right);
    OperandType eval() const;
};


class NodeMulOperator : public NodeOperator
{
public:
    NodeMulOperator(Node *left, Node *right);
    OperandType eval() const;
};


class NodeDivOperator : public NodeOperator
{
public:
    NodeDivOperator(Node *left, Node *right);
    OperandType eval() const;
};

#endif
