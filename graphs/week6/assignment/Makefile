all: default test

.PHONY: bidijkstra dijkstra test

default: bidijkstra

bidijkstra:
	g++ -pipe -O2 -std=c++14 bidijkstra.cpp -lm -o bidijkstra

bidijkstra-debug:
	g++ -pipe -std=c++14 bidijkstra.cpp -lm -o bidijkstra -g

dijkstra:
	clang++ -pipe -O2 -std=c++14 dijkstra.cpp -lm -o dijkstra

clean:
	rm -fr bidijkstra dijkstra *.dSYM
test:
	./dijkstra < input_large.txt
	./bidijkstra < input_large.txt
