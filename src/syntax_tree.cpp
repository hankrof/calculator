#include "syntax_tree.h"
#include "node_iterator.h"
#include "node_const_iterator.h"
#include <sstream>
#include <stdexcept>
Node::~Node()
{
    //dummy code, just for linkage.
}


NodeOperand::NodeOperand(OperandType&& value)
    : _value(value)
{

}

OperandType NodeOperand::eval() const
{
    return _value;
}

char NodeOperand::op() const
{
    throw std::logic_error("An operand is not possible to possess an opeartor.");
    return static_cast<char>(-1);
}

std::string NodeOperand::symbol() const
{
    std::stringstream ss;
    ss << _value;
    return ss.str();
}

Node* NodeOperand::left()
{
    return nullptr;
}

Node* NodeOperand::right()
{
    return nullptr;
}

const Node* NodeOperand::left() const
{
    return nullptr;
}

const Node* NodeOperand::right() const
{
    return nullptr;
}

NodeIterator NodeOperand::createPrefixIterator()
{
    return NodeIterator(new NodeOperandIterator(this));
}

NodeConstIterator NodeOperand::createPrefixIterator() const
{
    return NodeConstIterator(new NodeOperandConstIterator(this));
}

NodeIterator NodeOperand::createInfixIterator()
{
    return NodeIterator(new NodeOperandIterator(this));
}

NodeConstIterator NodeOperand::createInfixIterator() const
{
    return NodeConstIterator(new NodeOperandConstIterator(this));
}

NodeIterator NodeOperand::createPostfixIterator()
{
    return NodeIterator(new NodeOperandIterator(this));
}

NodeConstIterator NodeOperand::createPostfixIterator() const
{
    return NodeConstIterator(new NodeOperandConstIterator(this));
}

NodeOperator::NodeOperator(char op, Node *left, Node *right)
    : _op(op), _left(left), _right(right)
{

}

char NodeOperator::op() const
{
    return _op;
}

std::string NodeOperator::symbol() const
{
    return std::string(1, op());
}

Node* NodeOperator::left() 
{
    return _left;
}

Node* NodeOperator::right() 
{
    return _right;
}

const Node* NodeOperator::left() const
{
    return _left;
}

const Node* NodeOperator::right() const
{
    return _right;
}

NodeIterator NodeOperator::createPrefixIterator()
{
    return NodeIterator(new NodePrefixOperatorIterator(this));
}

NodeConstIterator NodeOperator::createPrefixIterator() const
{
    return NodeConstIterator(new NodePrefixOperatorConstIterator(this));
}

NodeIterator NodeOperator::createInfixIterator()
{
    return NodeIterator(new NodeInfixOperatorIterator(this));
}

NodeConstIterator NodeOperator::createInfixIterator() const
{
    return NodeConstIterator(new NodeInfixOperatorConstIterator(this));
}

NodeIterator NodeOperator::createPostfixIterator()
{
    return NodeIterator(new NodePostfixOperatorIterator(this));
}

NodeConstIterator NodeOperator::createPostfixIterator() const
{
    return NodeConstIterator(new NodePostfixOperatorConstIterator(this));
}

NodeAddOperator::NodeAddOperator(Node *left, Node *right)
    : NodeOperator('+', left, right)
{

}

OperandType NodeAddOperator::eval() const
{
    return NodeOperator::left()->eval() + 
        NodeOperator::right()->eval();
}

NodeSubOperator::NodeSubOperator(Node *left, Node *right)
    : NodeOperator('-', left, right)
{

}

OperandType NodeSubOperator::eval() const
{
    return NodeOperator::left()->eval() - 
        NodeOperator::right()->eval();
}


NodeMulOperator::NodeMulOperator(Node *left, Node *right)
        : NodeOperator('*', left, right)
    {

    }

OperandType NodeMulOperator::eval() const
{
    return NodeOperator::left()->eval() * 
        NodeOperator::right()->eval();
}

NodeDivOperator::NodeDivOperator(Node *left, Node *right)
    : NodeOperator('/', left, right)
{

}

OperandType NodeDivOperator::eval() const
{
    return NodeOperator::left()->eval() / 
        NodeOperator::right()->eval();
}
