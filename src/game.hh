// game.hh

#ifndef INCLUDED_GAME
# define INCLUDED_GAME

#include "decisiontree.hh"
#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>
//#include <queue>

class Game
{
public: // Helper struct
struct Guess
{
  //std::vector<char> guess;
  std::string guess;
  short ok;
  short misplaced;
  /*
  Guess() { guess = std::vector<char>( 4, ' ' ); ok = 0; misplaced = 0; }
  ~Guess() {}
  */
};

private:
  std::string d_goal;
  std::vector<Guess> d_guesses;
  DecisionTree d_dt;

public:
  // CONSTRUCTORS
  Game( const std::string& goal );
  
  // DESTRUCTOR
  ~Game();

  // ACCESSORS
  const std::string& goal() const;
  std::vector<Game::Guess>& guesses();

  // MEMBER FUNCTIONS
  const std::string guess() const;
  void print() const;
};

#endif
