all: clean puzz5a puzz5b
	clear
	@printf "$$ "
	./puzz5a < input.txt
	@printf "$$ "
	./puzz5b < input.txt
	@make clean >/dev/null

puzz5a: puzz5a.o
	g++ $(CXXFLAGS) -o puzz5a puzz5a.o

puzz5b: puzz5b.o
	g++ $(CXXFLAGS) -o puzz5b puzz5b.o

puzz5a.o: puzz5a.cpp
	g++ $(CXXFLAGS) -c puzz5a.cpp

puzz5b.o: puzz5b.cpp
	g++ $(CXXFLAGS) -c puzz5b.cpp

clean:
	rm -f puzz5a puzz5b puzz5a.o puzz5b.o
