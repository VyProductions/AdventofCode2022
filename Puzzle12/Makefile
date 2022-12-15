all: clean puzz12a puzz12b
	clear
	@printf "$$ "
	./puzz12a < input.txt
	@printf "$$ "
	./puzz12b < input.txt
	@make clean >/dev/null

puzz12a: puzz12a.o
	g++ $(CXXFLAGS) -o puzz12a puzz12a.o

puzz12b: puzz12b.o
	g++ $(CXXFLAGS) -o puzz12b puzz12b.o

puzz12a.o: puzz12a.cpp
	g++ $(CXXFLAGS) -c puzz12a.cpp

puzz12b.o: puzz12b.cpp
	g++ $(CXXFLAGS) -c puzz12b.cpp

clean:
	rm -f puzz12a puzz12b puzz12a.o puzz12b.o
