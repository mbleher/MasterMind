// main.cpp

#include "game.hpp"

int main( int argc, char *argv[] )
{
  if( argc < 2 )
  {
    std::cerr << "usage:\t" << argv[0] << " <number>" << std::endl;
    return 0;
  }
  try
  {
    Game g( argv[1] );
    std::string guess = g.guess();
    Guess gs;
    unsigned int nbGuess = 0;

    
    //std::cout << g.nLeft() << std::endl;
    //std::cout << guess << std::endl;
    //gs = g.evaluateGuess( guess );
    //std::cout << g.nLeft() << std::endl;
    
    while( guess != g.goal() )
    {
      gs = g.evaluateGuess( guess );
      std::cout << "Guess: " << gs.guess << " " << gs.ok << "A" << gs.misplaced << "B" << std::endl;
      std::cout << "Number of possibilities left: " << g.nLeft() << std::endl;
      ++nbGuess;
      guess = g.guess();
    }
    
    std::cout << "Guess: " << guess << std::endl;
    std::cout << "Found goal in " << ++nbGuess << " guesses." << std::endl;
    return nbGuess;
  }
  catch( const std::invalid_argument& ia )
  {
    std::cerr << ia.what() << std::endl;
    return 0;
  }

  return 0;
}
