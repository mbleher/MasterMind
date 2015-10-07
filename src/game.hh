// game.hh

#ifndef INCLUDED_GAME
# define INCLUDED_GAME

#include "decisiontree.hh"
#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <queue>

class Game
{
public: // Helper struct
struct Guess
{
  std::string guess;
  short ok;
  short misplaced;
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
  const std::string guess();
  Guess evaluateGuess( std::string& guess );
  void print() const;
};

#endif
