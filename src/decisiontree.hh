// decisiontree.hh

#ifndef INCLUDED_DECISIONTREE
# define INCLUDED_DECISIONTREE

#include "guess.hh"
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

class Node
{
private:
  std::vector<Node> d_children;
  char d_value;
  bool d_active;
  int d_level;
public:
  // CONSTRUCTORS
  Node();
  Node( const std::string& impossible, char value, int level );

  // DESTRUCTORS
  ~Node();

  // ACCESSORS
  char value() const;
  bool active() const;
  int level() const;
  const Node& child( unsigned int index ) const;

  // MEMBER FUNCTIONS
  unsigned int count() const;
  void getRandomGuess( std::string& res );
  void checkActiveSons();
  void deactivateSons( char c, int level );
  void print() const;
};

class DecisionTree
{
private:
  unsigned int d_nLeft;
  Node d_root;
  std::vector<std::pair<int, int> > scores;

  void updateScores( char c, int toAdd );
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
  const std::string getRandomGuess();
  void processGuess( Guess g );
};

#endif
