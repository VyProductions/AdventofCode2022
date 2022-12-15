all: clean puzz15a puzz15b
	clear
	@printf "$$ "
	./puzz15a < input.txt
	@printf "$$ "
	./puzz15b < input.txt
	@make clean >/dev/null

puzz15a: puzz15a.o
	g++ $(CXXFLAGS) -o puzz15a puzz15a.o

puzz15b: puzz15b.o
	g++ $(CXXFLAGS) -o puzz15b puzz15b.o

puzz15a.o: puzz15a.cpp
	g++ $(CXXFLAGS) -c puzz15a.cpp

puzz15b.o: puzz15b.cpp
	g++ $(CXXFLAGS) -c puzz15b.cpp

clean:
	rm -f puzz15a puzz15b puzz15a.o puzz15b.o
