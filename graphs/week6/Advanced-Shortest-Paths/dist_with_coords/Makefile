.PHONY: astar bidirectional_astar

default: astar bidirectional_astar

astar:
	g++ -pipe -O2 -std=c++14 astar.cpp -lm -Wall -pedantic -o astar

bidirectional_astar:
	g++ -pipe -O2 -std=c++14 bidirectional_astar.cpp -lm -Wall -pedantic -o bidirectional_astar

bbidirectional_astar_debug:
	g++ -pipe -std=c++14 -g bidirectional_astar.cpp -lm -Wall -pedantic -o bidirectional_astar

clean:
	rm *~ a.out bidirectional_astar astar
