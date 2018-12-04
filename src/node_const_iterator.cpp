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


NodePrefixOperatorConstIterator::NodePrefixOperatorConstIterator(const Node *n)
    : _idx(0), _root(n)
{

}

void NodePrefixOperatorConstIterator::begin() const
{
    _idx = 0;
    initBufferedNodes();
}

void NodePrefixOperatorConstIterator::next() const
{
    _idx++;
}

const Node* NodePrefixOperatorConstIterator::item() const
{
    return _bufferedNodes[_idx];
}

bool NodePrefixOperatorConstIterator::end() const
{
    return static_cast<size_t>(_idx) > _bufferedNodes.size() - 1;
}

void NodePrefixOperatorConstIterator::initBufferedNodes() const
{
    std::stack<const Node*> _nodesStack;
    _bufferedNodes.clear();

    auto pushNodes = [&_nodesStack](const Node *n) -> bool
    {
        bool result(false);
        if(n->right() &&n->left() )
        {
            _nodesStack.push(n->right());
            _nodesStack.push(n->left());
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
    /*         
     *        +
     *       / \
     *      +   -
     *     / \ / \
     *    1  2 3  4
     *   
     * Infix =  1 + 2 + 3 - 4
     *
     * Stk: 
     * Out: 
     *
     *
     *
     *
     *
     * Delete this after implementing the algorithm.
     */
    std::stack<const Node*> _nodesStack;
    _bufferedNodes.clear();
    const Node *n(_root);
    while(!_nodesStack.empty())
    {
        for(const Node* l = n; l->left(); l = l->left())
            _nodesStack.push(l);

        for(const Node* r = n; r->right(); r = r->right())
            _nodesStack.push(r);
    }
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

