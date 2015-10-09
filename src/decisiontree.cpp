// decisiontree.cpp

#include "decisiontree.hh"

Node::Node()
{
}

Node::Node( const std::string& impossible, char value, int level )
  : d_value( value ), d_active( true ), d_level( level )
{
  bool possible;

  if( d_level == 4 )
  {
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
    if( possible )
    {
      d_children.push_back( Node( impossible + (char) ( i + '0' ),
				  i + '0', d_level + 1 ) );
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

unsigned int Node::count() const
{
  if ( !d_active )
  {
    return 0;
  }

  if ( d_level == 4 )
  {
    return 1;
  }

  unsigned int acc = 0;
  for( unsigned int i = 0; i < d_children.size(); ++i )
  {
    acc += d_children[i].count();
  }
  
  return acc;
}

void Node::getRandomGuess( std::string& res )
{
  if( d_level == 4 )
  {
    d_active = false;
    return;
  }
  int nextIndex = std::rand() % ( 10 - d_level );

  while( !d_children[nextIndex].d_active )
  {
    nextIndex = std::rand() % ( 10 - d_level );
  }
  res += d_children[nextIndex].d_value;
  d_children[nextIndex].getRandomGuess( res );
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

void DecisionTree::updateScores( char c, int toAdd )
{
  
}

// CONSTRUCTORS

DecisionTree::DecisionTree()
  : d_nLeft( 10 * 9 * 8 * 7 )
{
  d_root = Node( "", ' ', 0 );
  std::srand( std::time( 0 ) );

  for( unsigned int i = 0; i < 10; ++i )
  {
    scores.push_back( std::make_pair( i, 0 ) );
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

void DecisionTree::print() const
{
  d_root.print();
  for( unsigned int i = 0; i < 1; ++i )
  {
    d_root.child( i ).print();
    for( unsigned int j = 0; j < 9; ++j )
    {
      d_root.child( i ).child( j ).print();
      for( unsigned int k = 0; k < 8; ++k )
      {
	d_root.child( i ).child( j ).child( k ).print();
	for( unsigned int l = 0; l < 7; ++l )
	{
	  d_root.child( i ).child( j ).child( k ).child( l ).print();
	}
      }
    }
  }
}

unsigned int DecisionTree::count() const
{
  return d_root.count();
}


const std::string DecisionTree::getRandomGuess()
{
  std::string res;

  d_root.getRandomGuess( res );
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
  //updateScores( g );

  d_nLeft = d_root.count();
}

// FREE OPERATORS

std::ostream& operator<<( std::ostream& stream, const DecisionTree& dt )
{
  stream << "Decision Tree" << std::endl;
  stream << "Number of possible guesses left: " << dt.nLeft() << std::endl;

  return stream;
}
