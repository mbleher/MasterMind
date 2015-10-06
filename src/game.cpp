// game.cpp

#include "game.hh"


// CONSTRUCTORS

Game::Game( const std::string& goal )
{
  bool valid = true;
  std::vector<char> digits;

  if( goal.length() != 4 )
  {
    throw std::invalid_argument("The input number must be 4 digits long.");
  }
  for( unsigned int i = 0; valid && i < 4; ++i )
  {
    for( unsigned int j = 0; j < digits.size(); ++j )
    {
      if( goal[i] == digits[j] )
      {
	valid = false;
      }
    }
    digits.push_back( goal[i] );
  }
  if( !valid )
  {
    throw std::invalid_argument("All the digits must be different.");
  }
  d_goal = goal;
}


// DESTRUCTORS

Game::~Game()
{
}


// ACCESSORS

const std::string& Game::goal() const
{
  return d_goal;
}

std::vector<Game::Guess>& Game::guesses()
{
  return d_guesses;
}


// MEMBER FUNCTIONS

const std::string Game::guess() const
{
  return "";
}

void Game::print() const
{
  //std::cout << d_dt;
  //d_dt.print();
  std::cout << d_dt.count() << std::endl;
}
