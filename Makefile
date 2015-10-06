CXX=g++
CXXFLAGS=-std=c++0x -Wall -Werror
CPPFILES=decisiontree.cpp game.cpp main.cpp
SRCDIR=src/
EXEC=MasterMind

all:
	${CXX} ${CXXFLAGS} ${addprefix ${SRCDIR}, ${CPPFILES}} -o ${EXEC}

clean:
	-@rm -rf ${EXEC}
	-@rm -rf *~ ${SRCDIR}*~
	-@rm -rf ${SRCDIR}\#*
