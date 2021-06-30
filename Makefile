# This Makefile
# gives instructions to the command
# make
# about how and whether to build programs

# thingtobuld:  what-it-needs-or-depends-on
#    instructions on how to build it

# make uses the modification dates to determine
# if the programs need to be re-built

all: board
tetris: Tetris_Board.cpp
	g++ -g Piece.cpp Tetris_Board.cpp -o tetris -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
