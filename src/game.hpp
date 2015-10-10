// game.hh

#ifndef INCLUDED_GAME
# define INCLUDED_GAME

#include "decisiontree.hpp"
#include "guess.hpp"
#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <queue>

class Game
{
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
  std::vector<Guess>& guesses();
  unsigned int nLeft() const;

  // MEMBER FUNCTIONS
  const std::string guess();
  Guess evaluateGuess( std::string& guess );
  void print() const;
};

#endif
