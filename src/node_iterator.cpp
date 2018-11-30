#include "node_iterator.h"
#include <stack>
#include <queue>

NodeOperandIterator::NodeOperandIterator(Node*)
{

}

NodeOperandIterator::NodeOperandIterator(const Node*)
{

}

void NodeOperandIterator::begin()
{

}

void NodeOperandIterator::next()
{

}

Node* NodeOperandIterator::item()
{
    return nullptr;
}

bool NodeOperandIterator::end()
{
    return true;
}

NodeInfixOperatorIterator::NodeInfixOperatorIterator(Node *n)
    : _idx(0), _root(n)
{

}

void NodeInfixOperatorIterator::begin()
{
    _idx = 0;
    initBufferedNodes();
}

void NodeInfixOperatorIterator::next()
{
    _idx++;
}

Node* NodeInfixOperatorIterator::item()
{
    return _bufferedNodes[_idx];
}

bool NodeInfixOperatorIterator::end()
{
   return static_cast<size_t>(_idx) == _bufferedNodes.size() - 1;
}

void NodeInfixOperatorIterator::initBufferedNodes()
{
    
}

NodePrefixOperatorIterator::NodePrefixOperatorIterator(Node *)
{

}

void NodePrefixOperatorIterator::begin()
{

}

void NodePrefixOperatorIterator::next()
{

}

Node* NodePrefixOperatorIterator::item()
{
    return nullptr;
}

bool NodePrefixOperatorIterator::end()
{
    return true;
}

NodePostfixOperatorIterator::NodePostfixOperatorIterator(Node *)
{

}

void NodePostfixOperatorIterator::begin()
{

}

void NodePostfixOperatorIterator::next()
{

}

Node* NodePostfixOperatorIterator::item()
{
    return nullptr;
}

bool NodePostfixOperatorIterator::end()
{
    return true;
}

