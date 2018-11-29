#include "node_iterator.h"

NodeNullIterator::NodeNullIterator(const Node*)
{

}

void NodeNullIterator::begin()
{

}

void NodeNullIterator::next()
{

}

Node* NodeNullIterator::item()
{
    return nullptr;
}

bool NodeNullIterator::end()
{
    return true;
}
