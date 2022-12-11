all: clean puzz11a puzz11b
	clear
	@printf "$$ "
	./puzz11a < input.txt
	@printf "$$ "
	./puzz11b < input.txt
	@make clean >/dev/null

puzz11a: puzz11a.o
	g++ $(CXXFLAGS) -o puzz11a puzz11a.o

puzz11b: puzz11b.o
	g++ $(CXXFLAGS) -o puzz11b puzz11b.o

puzz11a.o: puzz11a.cpp
	g++ $(CXXFLAGS) -c puzz11a.cpp

puzz11b.o: puzz11b.cpp
	g++ $(CXXFLAGS) -c puzz11b.cpp

clean:
	rm -f puzz11a puzz11b puzz11a.o puzz11b.o
