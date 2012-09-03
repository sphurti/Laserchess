Laserchess
==========
Laser Chess is a variant of the regular chess game and has a complete set of different
pieces and moves. The Alpha-Beta tree pruning algorithm is used for performing the
game tree search to find the best move. In this project, a basic version of the Alpha-
Beta serial algorithm is implemented. This algorithm is further parallelized using
OpenMPI. 

In Laser Chess, each player may make two moves per turn. They are:
1. A piece can be moved in any direction.
2. The Laser piece can be fired only once per turn.
3. A piece can be rotated if it is rotatable in either clockwise or anti-clockwise direction.
In this game, it is required to decide the best move among various possible moves
from the current board position. To obtain such best moves, the Game Tree is traversed using
Game Tree Search Algorithms i.e serial Alpha-
Beta Game Tree Search algorithm. Further, to parallelize the Alpha-Beta algorithm the Principal Variation Splitting is used. It has been noticed that the depth of the search
tree affects the evaluation time of the search tree to obtain the best move.

Running the laserchess:
======================
Perform the following to run the laser chess:
1. Download the tar file( laser chess.tar.gz ) that contains various header files and c++
files.
2. Unzip the tar file using the command $ tar -xvf laserchess.tar.gz
3. Once the tar file is unzipped, give the make command
    $ laserchess > make
    $ laserchess /laserchess > make
    $ laserchess /trees > make
3. Run the executable file which has the name ./game in the main directory.
    $ laserchess > ./game

Known Issues:
============
1. The user has to always input a valid command. Ckecking for the validity of input is not taken care of.

2. The validity of each move is checked. But not the validity of
double moves. Corner cases such as hyper cube can teleport
only once, the king can capture once per turn and a block can capture once per turn has to be taken care of.

3. The user cannot give the fire command.

Author:

Sphurti


