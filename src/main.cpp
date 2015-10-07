// main.cpp

#include "game.hh"

int main( int argc, char *argv[] )
{
  if( argc < 2 )
  {
    std::cerr << "usage:\t" << argv[0] << " <number>" << std::endl;
    return 1;
  }
  try
  {
    Game g( argv[1] );
    std::string guess = g.guess();
    unsigned int nbGuess = 0;

    while( guess != g.goal() )
    {
      std::cout << "Guess: " << guess << std::endl;
      ++nbGuess;
      guess = g.guess();
    }
    std::cout << "Guess: " << guess << std::endl;
    ++nbGuess;
    std::cout << "Found goal in " << nbGuess << " guesses." << std::endl;
  }
  catch( const std::invalid_argument& ia )
  {
    std::cerr << ia.what() << std::endl;
    return 2;
  }

  return 0;
}
