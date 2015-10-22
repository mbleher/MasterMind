// decisiontree.cpp

#include "decisiontree.hpp"
#include <algorithm>
#include <iostream>

Node::Node()
{
}

Node::Node( const std::string& impossible, char value, int level )
  : d_completevalue( "" ), d_value( value ),
    d_active( true ), d_level( level )
{
  bool possible;

  if( d_level == 4 )
  {
    d_completevalue = impossible;
    return;
  }
  
  for( int i = 0; i < 10; ++i )
  {
    possible = true;
    for( unsigned int j = 0; possible && j < impossible.length(); ++j )
    {
      if( impossible[j] == i + '0' )
      {
	possible = false;
	continue;
      }
    }
    d_children.push_back( Node( impossible + (char) ( i + '0' ),
				  i + '0', d_level + 1 ) );
    if( !possible )
    {
      d_children[i].d_active = false;
    }
  }
}

Node::~Node()
{
}

char Node::value() const
{
  return d_value;
}

bool Node::active() const
{
  return d_active;
}

int Node::level() const
{
  return d_level;
}

const Node& Node::child( unsigned int index ) const
{
  return d_children[index];
}

unsigned int Node::countUpdate( Guess g )
{
  if ( d_level != 4 && !d_active )
  {
    return 0;
  }

  if ( d_level == 4 )
  {
    short ok = 0;
    short misplaced = 0;
    for( unsigned int i = 0; i < 4; ++i )
    {
      for( unsigned int j = 0; j < 4; ++j )
      {
	if( g.guess[i] == d_completevalue[j] )
	{
	  if( i == j )
	  {
	    ++ok;
	  }
	  else
	  {
	    ++misplaced;
	  }
	}
      }
    }
    if( ok != g.ok || misplaced != g.misplaced )
    {
      d_active = false;
      return 0;
    }
    return 1;
  }

  unsigned int acc = 0;
  for( unsigned int i = 0; i < d_children.size(); ++i )
  {
    acc += d_children[i].countUpdate( g );
  }
  checkActiveSons();

  return acc;
}

void Node::getRandomGuess( std::string& res )
{
  if( d_level == 4 )
  {
    d_active = false;
    return;
  }

  int nextIndex = std::rand() % 10;

  while( !d_children[nextIndex].d_active )
  {
    nextIndex = std::rand() % 10;
  }
  res += d_children[nextIndex].d_value;
  d_children[nextIndex].getRandomGuess( res );
  checkActiveSons();
}

void Node::getNextGuess( std::vector<std::vector<score_t> >& scores, std::string& res )
{
  if( d_level == 4 )
  {
    d_active = false;
    return;
  }

  unsigned int best = 0;

  int nextIndex = scores[d_level][best].first;

  while( !d_children[nextIndex].d_active )
  {
    nextIndex = scores[d_level][++best].first;
  }
  res += d_children[nextIndex].d_value;
  d_children[nextIndex].getNextGuess( scores, res );
  checkActiveSons();
}

void Node::checkActiveSons()
{
  bool stillHasActiveChildren = false;

  for( unsigned int i = 0; !stillHasActiveChildren && i < d_children.size(); ++i )
  {
    if( d_children[i].d_active )
    {
      stillHasActiveChildren = true;
    }
  }
  if( !stillHasActiveChildren )
  {
    d_active = false;
  }
}

void Node::deactivateSons( char c, int level )
{
  bool found;

  if( d_level == level )
  {
    found = false;
    for( unsigned int i = 0; !found && i < d_children.size(); ++i )
    {
      if( d_children[i].d_value == c )
      {
	d_children[i].d_active = false;
	found = true;
      }
    }
  }
  else
  {
    for( unsigned int i = 0; i < d_children.size(); ++i )
    {
      d_children[i].deactivateSons( c, level );
    }
  }
  checkActiveSons();
}

void Node::print() const
{
  std::cout << "Val: " << d_value << std::endl;
  std::cout << "Level: " << d_level << std::endl;
  std::cout << "Sons: " << std::endl;
  for( unsigned int i = 0; i < d_children.size(); ++i )
  {
    std::cout << "\t" << d_children[i].d_value << std::endl;
  }
}

std::ostream& operator<<( std::ostream& stream, const Node& node )
{
  if( !node.active() || node.level() == 4 )
  {
    return stream << std::endl;
  }

  for( int i = 0; i < node.level() - 1; ++i )
  {
    stream << "  ";
  }

  stream << node.value();
  for( int i = 0; i < 10 - node.level(); ++i )
  {
    stream << node.child( i );
  }
  return stream << std::endl;
}


// PRIVATE MEMBER FUNCTIONS

bool cmpGt( score_t a, score_t b )
{
  return a.second > b.second;
}

bool cmpLt( score_t a, score_t b )
{
  return a.second < b.second;
}

void DecisionTree::updateScores( Guess g )
{
  int coefOk = ( g.ok != 0 ) ? 9 : 0;
  int coefMisplaced = ( g.misplaced != 0 ) ? 1 : 0;

  for( unsigned int i = 0; i < 10; ++i )
  {
    for( unsigned int j = 0; j < 4; ++j ) // Current letter
    {
      if( ( g.guess[j] - '0' ) == scores[j][i].first )
      {
	if( g.ok != 0 )
	{
	  scores[j][i].second += coefOk;
	}
	else
	{
	  scores[j][i].second = -100;
	}
      }
      else
      {
	for( unsigned int k = 0; k < 4; ++k ) // Other letters
	{
	  for( unsigned int l = 0; l < 4; ++l ) // Other levels
	  {
	    if( l != j && ( ( g.guess[k] - '0' ) == scores[k][i].first ) )
	    {
	      scores[l][i].second += coefMisplaced;
	    }
	  }
	}
      }

    }
  }
  // Reorder

  for( unsigned int i = 0; i < 4; ++i )
  {
    if( d_nLeft > d_threshold )
    {
      std::sort( scores[i].begin(), scores[i].end(), cmpLt );
    }
    else
    {
      std::sort( scores[i].begin(), scores[i].end(), cmpGt );
    }
  }
  /*
  for( unsigned int j = 0; j < 4; ++j )
  {
    for( unsigned int i = 0; i < 10; ++i )
    {
      std::cout << "(" << scores[j][i].first << ", "
		<< scores[j][i].second << ") ";
    }
    std::cout << std::endl;
  }
  */
}


// CONSTRUCTORS

DecisionTree::DecisionTree()
  : d_nLeft( 10 * 9 * 8 * 7 )
{
  d_root = Node( "", ' ', 0 );
  std::srand( std::time( 0 ) );

  for( unsigned int i = 0; i < 4; ++i )
  {
    scores.push_back( std::vector<score_t>() );
    for( unsigned int j = 0; j < 10; ++j )
    {
      scores[i].push_back( std::make_pair( j, 0 ) );
    }
  }
}

DecisionTree::DecisionTree( unsigned int threshold )
  : d_nLeft( 10 * 9 * 8 * 7 ), d_threshold( threshold )
{
  d_root = Node( "", ' ', 0 );
  std::srand( std::time( 0 ) );

  for( unsigned int i = 0; i < 4; ++i )
  {
    scores.push_back( std::vector<score_t>() );
    for( unsigned int j = 0; j < 10; ++j )
    {
      scores[i].push_back( std::make_pair( j, 0 ) );
    }
  }
}

// DESTRUCTOR

DecisionTree::~DecisionTree()
{
}


// ACCESSORS

unsigned int DecisionTree::nLeft() const
{
  return d_nLeft;
}


// MEMBER FUNCTIONS

/*
unsigned int DecisionTree::count() const
{
  return d_root.count();
}
*/

const std::string DecisionTree::getRandomGuess()
{
  std::string res;

  d_root.getRandomGuess( res );
  return res;
}

const std::string DecisionTree::getNextGuess()
{
  std::string res;

  d_root.getNextGuess( scores, res );
  return res;
}

void DecisionTree::processGuess( Guess g )
{
  if( g.ok == 0 )
  {
    if( g.misplaced != 0 )
    {
      for( int i = 0; i < 4; ++i )
      {
	d_root.deactivateSons( g.guess[i], i );
      }
    }
    else
    {
      for( int i = 0; i < 4; ++i )
      {
	for( int j = 0; j < 4; ++j )
	{
	  d_root.deactivateSons( g.guess[i], j );
	}
      }
    }
  }
  // Update the score array
  updateScores( g );

  d_nLeft = d_root.countUpdate( g );
}


// FREE OPERATORS

std::ostream& operator<<( std::ostream& stream, const DecisionTree& dt )
{
  stream << "Decision Tree" << std::endl;
  stream << "Number of possible guesses left: " << dt.nLeft() << std::endl;

  return stream;
}
