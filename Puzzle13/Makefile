all: clean puzz13a puzz13b
	clear
	@printf "$$ "
	./puzz13a < input.txt
	@printf "$$ "
	./puzz13b < input.txt
	@make clean >/dev/null

puzz13a: puzz13a.o
	g++ $(CXXFLAGS) -o puzz13a puzz13a.o

puzz13b: puzz13b.o
	g++ $(CXXFLAGS) -o puzz13b puzz13b.o

puzz13a.o: puzz13a.cpp
	g++ $(CXXFLAGS) -c puzz13a.cpp

puzz13b.o: puzz13b.cpp
	g++ $(CXXFLAGS) -c puzz13b.cpp

clean:
	rm -f puzz13a puzz13b puzz13a.o puzz13b.o
