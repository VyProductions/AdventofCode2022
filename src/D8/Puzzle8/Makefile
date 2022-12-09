all: clean puzz8a puzz8b
	clear
	@printf "$$ "
	./puzz8a < input.txt
	@printf "$$ "
	./puzz8b < input.txt
	@make clean >/dev/null

puzz8a: puzz8a.o
	g++ $(CXXFLAGS) -o puzz8a puzz8a.o

puzz8b: puzz8b.o
	g++ $(CXXFLAGS) -o puzz8b puzz8b.o

puzz8a.o: puzz8a.cpp
	g++ $(CXXFLAGS) -c puzz8a.cpp

puzz8b.o: puzz8b.cpp
	g++ $(CXXFLAGS) -c puzz8b.cpp

clean:
	rm -f puzz8a puzz8b puzz8a.o puzz8b.o
