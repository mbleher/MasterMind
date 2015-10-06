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
    std::cout << g.goal() << std::endl;
    g.print();
  }
  catch( const std::invalid_argument& ia )
  {
    std::cerr << ia.what() << std::endl;
    return 2;
  }

  return 0;
}
