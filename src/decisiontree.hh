// decisiontree.hh

#ifndef INCLUDED_DECISIONTREE
# define INCLUDED_DECISIONTREE

#include <vector>
#include <string>
#include <iostream>

class Node
{
private:
  std::vector<Node> d_children;
  char d_value;
  bool d_active;
  int d_level;
public:
  Node();
  Node( const std::string& impossible, char value, int level );
  ~Node();
  //std::vector<Node>& children();
  char value() const;
  bool active() const;
  int level() const;
  const Node& child( unsigned int index ) const;
  //void count( unsigned int& acc ) const;
  unsigned int count() const;
  void print() const;
};

class DecisionTree
{
private:
  unsigned int d_nLeft;
  Node d_root;
public:
  // CONSTRUCTORS
  DecisionTree();

  // DESTRUCTOR
  ~DecisionTree();

  // ACCESSORS
  unsigned int nLeft() const;

  // MEMBER FUNCTIONS
  void print() const;
  unsigned int count() const;
};

#endif
