all: clean puzz4a puzz4b
	clear
	@printf "$$ "
	./puzz4a < input.txt
	@printf "$$ "
	./puzz4b < input.txt
	@make clean >/dev/null

puzz4a: puzz4a.o
	g++ $(CXXFLAGS) -o puzz4a puzz4a.o

puzz4b: puzz4b.o
	g++ $(CXXFLAGS) -o puzz4b puzz4b.o

puzz4a.o: puzz4a.cpp
	g++ $(CXXFLAGS) -c puzz4a.cpp

puzz4b.o: puzz4b.cpp
	g++ $(CXXFLAGS) -c puzz4b.cpp

clean:
	rm -f puzz4a puzz4b puzz4a.o puzz4b.o
