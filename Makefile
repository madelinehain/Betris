# This Makefile
# gives instructions to the command
# make
# about how and whether to build programs
#
# The syntax is

# thingtobuld:  what-it-needs-or-depends-on
#    instructions on how to build it
#

# make uses the modification dates to determine
# is the programs need to be re-built

all: Tetris

<<<<<<< HEAD
Tetris: Tetris_Board.cpp
	g++ Tetris_Board.cpp -o Tetris -lsfml-graphics -lsfml-window -lsfml-system
=======
board: board.cpp
	g++ Tetris_Board.cpp -o tetris -lsfml-graphics -lsfml-window -lsfml-system
>>>>>>> 8f9906801d5a324506c267e1417754259dcf5297
