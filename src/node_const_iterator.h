#ifndef NODE_CONST_ITERATOR_H
#define NODE_CONST_ITERATOR_H
#include "node_iterator.h"
class ConstIterator
{
public:
    virtual void  begin()       const  = 0;
    virtual void  next ()       const  = 0;
    virtual const Node* item () const  = 0;
    virtual bool  end  ()       const  = 0;
};

class NodeOperandConstIterator : public ConstIterator
{
public:
    NodeOperandConstIterator (const Node *n);
    void  begin() const;
    void  next () const;
    const Node* item () const;
    bool  end() const;
};

class NodePrefixOperatorConstIterator : public ConstIterator
{
public:
    NodePrefixOperatorConstIterator(const Node *n);
    void  begin() const;
    void  next() const;
    const Node* item() const;
    bool  end() const;
private:
    void initBufferedNodes() const;
    mutable int _idx;
    const Node *_root;
    mutable std::vector<const Node*> _bufferedNodes;
};

class NodeInfixOperatorConstIterator : public ConstIterator
{
public:
    NodeInfixOperatorConstIterator(const Node *n);
    void  begin() const;
    void  next () const;
    const Node* item () const;
    bool  end() const;
private:
    void initBufferedNodes() const;
    mutable int _idx;
    const Node *_root;
    mutable std::vector<const Node*> _bufferedNodes;
};

class NodePostfixOperatorConstIterator : public ConstIterator
{
public:
    NodePostfixOperatorConstIterator(const Node *n);
    void  begin() const;
    void  next() const;
    const Node* item() const;
    bool  end() const;
private:
    void initBufferedNodes() const;
    mutable int _idx;
    const Node *_root;
    mutable std::vector<const Node*> _bufferedNodes;
};
#endif
