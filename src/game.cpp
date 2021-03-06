// game.cpp

#include "game.hpp"


// CONSTRUCTORS

Game::Game()
{
}

Game::Game( const std::string& goal, unsigned int threshold )
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
  d_dt = DecisionTree( threshold );
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

std::vector<Guess>& Game::guesses()
{
  return d_guesses;
}

unsigned int Game::nLeft() const
{
  return d_dt.nLeft();
}

// MEMBER FUNCTIONS

const std::string Game::guess()
{
  if( d_guesses.size() == 0 )
  {
    return d_dt.getRandomGuess();
  }
  return d_dt.getNextGuess();
  //return d_dt.getRandomGuess();
}

Guess Game::evaluateGuess( std::string& guess )
{
  short nbok = 0;
  short nbmisplaced = 0;

  for( unsigned int i = 0; i < 4; ++i )
  {
    for( unsigned int j = 0; j < 4; ++j )
    {
      if( guess[i] == d_goal[j] )
      {
	if ( i == j )
	{
	  ++nbok;
	}
	else
	{
	  ++nbmisplaced;
	}
      }
    }
  }
  Guess g = { guess, nbok, nbmisplaced };
  d_dt.processGuess( g );
  d_guesses.push_back( g );
  return g;
}

void Game::print() const
{
  //std::cout << d_dt;
  //d_dt.print();
  std::cout << d_dt.nLeft() << std::endl;
}
