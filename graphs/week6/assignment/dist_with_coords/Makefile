.PHONY: astar bidirectional_astar

default: astar bidirectional_astar

astar:
	g++ -pipe -O2 -std=c++14 astar.cpp -lm -Wall -pedantic -o bin/astar

bidirectional_astar: bin
	g++ -pipe -O2 -std=c++14 bidirectional_astar.cpp -lm -Wall -pedantic -o bin/bidirectional_astar

bbidirectional_astar_debug: bin
	g++ -pipe -std=c++14 -g bidirectional_astar.cpp -lm -Wall -pedantic -o bin/bidirectional_astar

clean:
	rm *~ a.out bidirectional_astar astar

test: bidirectional_astar
	time ./bin/bidirectional_astar < tests/03 > bin/ans
bin:
	mkdir $@
