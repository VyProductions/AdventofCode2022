all: clean puzz9a puzz9b
	clear
	@printf "$$ "
	./puzz9a < input.txt
	@printf "$$ "
	./puzz9b < input.txt
	@make clean >/dev/null

puzz9a: puzz9a.o
	g++ $(CXXFLAGS) -o puzz9a puzz9a.o

puzz9b: puzz9b.o
	g++ $(CXXFLAGS) -o puzz9b puzz9b.o

puzz9a.o: puzz9a.cpp
	g++ $(CXXFLAGS) -c puzz9a.cpp

puzz9b.o: puzz9b.cpp
	g++ $(CXXFLAGS) -c puzz9b.cpp

clean:
	rm -f puzz9a puzz9b puzz9a.o puzz9b.o
