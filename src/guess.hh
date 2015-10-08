// guess.hh

#ifndef INCLUDED_GUESS
# define INCLUDED_GUESS

#include <string>

struct Guess
{
  std::string guess;
  short ok;
  short misplaced;
};

#endif
