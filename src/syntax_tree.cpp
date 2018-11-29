#include "syntax_tree.h"
#include <sstream>
#include <stdexcept>
#include "node_iterator.h"
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

NodeIterator NodeOperand::createIterator()
{
    return NodeIterator(new NodeNullIterator(this));
}

NodeIterator NodeOperand::createIterator() const
{
    return NodeIterator(new NodeNullIterator(this));
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

//Just for compilation!!!! PLZ change to correct iterator
NodeIterator NodeOperator::createIterator()
{
    return NodeIterator(new NodeNullIterator(this));
}

//Just for compilation!!!! PLZ change to correct iterator
NodeIterator NodeOperator::createIterator() const
{
    return NodeIterator(new NodeNullIterator(this));
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
