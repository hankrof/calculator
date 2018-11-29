#ifndef ITERATOR_H
#define ITERATOR_H
#include "syntax_tree.h"
#include <vector>
class Iterator
{
public:
    virtual void  begin()  = 0;
    virtual void  next ()  = 0;
    virtual Node* item ()  = 0;
    virtual bool  end  ()  = 0;
};

class NodeNullIterator : public Iterator
{
public:
    NodeNullIterator(const Node *n);
    void  begin();
    void  next ();
    Node* item ();
    bool  end  ();
};

class NodeInfixOperatorIterator : public Iterator
{
public:
    NodeInfixOperatorIterator(const Node *n);
    void  begin();
    void  next ();
    Node* item ();
    bool  end  ();
private:
    std::vector<Node*> _bufferedNodes;
};
#endif
