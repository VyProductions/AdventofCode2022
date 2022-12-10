all: clean puzz6a puzz6b
	clear
	@printf "$$ "
	./puzz6a < input.txt
	@printf "$$ "
	./puzz6b < input.txt
	@make clean >/dev/null

puzz6a: puzz6a.o
	g++ $(CXXFLAGS) -o puzz6a puzz6a.o

puzz6b: puzz6b.o
	g++ $(CXXFLAGS) -o puzz6b puzz6b.o

puzz6a.o: puzz6a.cpp
	g++ $(CXXFLAGS) -c puzz6a.cpp

puzz6b.o: puzz6b.cpp
	g++ $(CXXFLAGS) -c puzz6b.cpp

clean:
	rm -f puzz6a puzz6b puzz6a.o puzz6b.o
