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

class NodeOperandIterator : public Iterator
{
public:
    NodeOperandIterator(Node *n);
    NodeOperandIterator(const Node *n);
    void  begin();
    void  next ();
    Node* item ();
    bool  end  ();
};


class NodeInfixOperatorIterator : public Iterator
{
public:
    NodeInfixOperatorIterator(Node *n);
    void  begin();
    void  next ();
    Node* item ();
    bool  end  ();
private:
    void initBufferedNodes();
    int _idx;
    Node *_root;
    std::vector<Node*> _bufferedNodes;
};

class NodePrefixOperatorIterator : public Iterator
{
public:
    NodePrefixOperatorIterator(Node *n);
    void  begin();
    void  next ();
    Node* item ();
    bool  end  ();
};

class NodePostfixOperatorIterator : public Iterator
{
public:
    NodePostfixOperatorIterator(Node *n);
    void  begin();
    void  next ();
    Node* item ();
    bool  end  ();
};

#endif
