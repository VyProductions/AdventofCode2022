all: clean puzz1a puzz1b
	clear
	@printf "$$ "
	./puzz1a < input.txt
	@printf "$$ "
	./puzz1b < input.txt
	@make clean >/dev/null

puzz1a: puzz1a.o
	g++ $(CXXFLAGS) -o puzz1a puzz1a.o

puzz1b: puzz1b.o
	g++ $(CXXFLAGS) -o puzz1b puzz1b.o

puzz1a.o: puzz1a.cpp
	g++ $(CXXFLAGS) -c puzz1a.cpp

puzz1b.o: puzz1b.cpp
	g++ $(CXXFLAGS) -c puzz1b.cpp

clean:
	rm -f puzz1a puzz1b puzz1a.o puzz1b.o
