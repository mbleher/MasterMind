// decisiontree.hh

#ifndef INCLUDED_DECISIONTREE
# define INCLUDED_DECISIONTREE

#include "guess.hh"
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

typedef std::pair<int, int> score_t;

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
  void getNextGuess( std::vector<score_t>& scores, std::string& res );
  void checkActiveSons();
  void deactivateSons( char c, int level );
  void print() const;
};

class DecisionTree
{
private:
  unsigned int d_nLeft;
  Node d_root;
  std::vector<score_t> scores;

  void updateScores( Guess g );
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
  const std::string getNextGuess();
  void processGuess( Guess g );
};

#endif
