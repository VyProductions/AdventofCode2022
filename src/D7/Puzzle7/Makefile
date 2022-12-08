all: clean puzz7a puzz7b
	clear
	@printf "$$ "
	./puzz7a < input.txt
	@printf "$$ "
	./puzz7b < input.txt
	@make clean >/dev/null

puzz7a: puzz7a.o
	g++ $(CXXFLAGS) -o puzz7a puzz7a.o

puzz7b: puzz7b.o
	g++ $(CXXFLAGS) -o puzz7b puzz7b.o

puzz7a.o: puzz7a.cpp
	g++ $(CXXFLAGS) -c puzz7a.cpp

puzz7b.o: puzz7b.cpp
	g++ $(CXXFLAGS) -c puzz7b.cpp

clean:
	rm -f puzz7a puzz7b puzz7a.o puzz7b.o
