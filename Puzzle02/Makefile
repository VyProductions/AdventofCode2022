all: clean puzz2a puzz2b
	clear
	@printf "$$ "
	./puzz2a < input.txt
	@printf "$$ "
	./puzz2b < input.txt
	@make clean >/dev/null

puzz2a: puzz2a.o
	g++ $(CXXFLAGS) -o puzz2a puzz2a.o

puzz2b: puzz2b.o
	g++ $(CXXFLAGS) -o puzz2b puzz2b.o

puzz2a.o: puzz2a.cpp
	g++ $(CXXFLAGS) -c puzz2a.cpp

puzz2b.o: puzz2b.cpp
	g++ $(CXXFLAGS) -c puzz2b.cpp

clean:
	rm -f puzz2a puzz2b puzz2a.o puzz2b.o
