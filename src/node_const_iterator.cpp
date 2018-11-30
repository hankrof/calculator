#include "node_const_iterator.h"
#include <stack>
#include <queue>
#include <algorithm>

NodeOperandConstIterator::NodeOperandConstIterator(const Node *)
{

}

void NodeOperandConstIterator::begin() const
{

}

void NodeOperandConstIterator::next () const
{

}

const Node* NodeOperandConstIterator::item () const
{
    return nullptr;
}

bool NodeOperandConstIterator::end() const
{
    return true;
}


NodeInfixOperatorConstIterator::NodeInfixOperatorConstIterator(const Node *n)
    : _idx(0), _root(n)
{

}

void NodeInfixOperatorConstIterator::begin() const
{
    _idx = 0;
    initBufferedNodes();
}

void NodeInfixOperatorConstIterator::next() const
{
    _idx++;
}

const Node* NodeInfixOperatorConstIterator::item() const
{
    return _bufferedNodes[_idx];
}

bool NodeInfixOperatorConstIterator::end() const
{
    return static_cast<size_t>(_idx) > _bufferedNodes.size() - 1;
}

void NodeInfixOperatorConstIterator::initBufferedNodes() const
{

}

NodePrefixOperatorConstIterator::NodePrefixOperatorConstIterator(const Node *)
{

}

void NodePrefixOperatorConstIterator::begin() const
{

}

void NodePrefixOperatorConstIterator::next() const
{

}

const Node* NodePrefixOperatorConstIterator::item() const
{
    return nullptr;
}

bool NodePrefixOperatorConstIterator::end() const
{
    return true;
}


NodePostfixOperatorConstIterator::NodePostfixOperatorConstIterator(const Node *n)
    : _idx(0), _root(n)
{

}

void NodePostfixOperatorConstIterator::begin() const
{
    _idx = 0;
    initBufferedNodes();
}

void NodePostfixOperatorConstIterator::next() const
{
    _idx++;
}

const Node* NodePostfixOperatorConstIterator::item() const
{
    return _bufferedNodes[_idx];
}

bool NodePostfixOperatorConstIterator::end() const
{
    return static_cast<size_t>(_idx) > _bufferedNodes.size() - 1;
}

void NodePostfixOperatorConstIterator::initBufferedNodes() const
{
    std::stack<const Node*> _nodesStack;
    _bufferedNodes.clear();

    auto pushNodes = [&_nodesStack](const Node *n) -> bool
    {
        bool result(false);
        if(n->right() &&n->left() )
        {
            _nodesStack.push(n->left());
            _nodesStack.push(n->right());
            result = true;
        }
        return result;
    };
    
    auto popNodes = [&_nodesStack](const Node* &n) -> void
    {
        n = _nodesStack.top();
        _nodesStack.pop();
    };

    pushNodes(_root);
    const Node *n(_root);
    while(!_nodesStack.empty())
    {
        _bufferedNodes.push_back(n);
        popNodes(n);
        pushNodes(n);
    }
    _bufferedNodes.push_back(n);
    std::reverse(_bufferedNodes.begin(), _bufferedNodes.end());
}

