all: clean puzz10a puzz10b
	clear
	@printf "$$ "
	./puzz10a < input.txt
	@printf "$$ "
	./puzz10b < input.txt
	@make clean >/dev/null

puzz10a: puzz10a.o
	g++ $(CXXFLAGS) -o puzz10a puzz10a.o

puzz10b: puzz10b.o
	g++ $(CXXFLAGS) -o puzz10b puzz10b.o

puzz10a.o: puzz10a.cpp
	g++ $(CXXFLAGS) -c puzz10a.cpp

puzz10b.o: puzz10b.cpp
	g++ $(CXXFLAGS) -c puzz10b.cpp

clean:
	rm -f puzz10a puzz10b puzz10a.o puzz10b.o
