all: clean puzz14a puzz14b
	clear
	@printf "$$ "
	./puzz14a < input.txt
	@printf "$$ "
	./puzz14b < input.txt
	@make clean >/dev/null

puzz14a: puzz14a.o
	g++ $(CXXFLAGS) -o puzz14a puzz14a.o

puzz14b: puzz14b.o
	g++ $(CXXFLAGS) -o puzz14b puzz14b.o

puzz14a.o: puzz14a.cpp
	g++ $(CXXFLAGS) -c puzz14a.cpp

puzz14b.o: puzz14b.cpp
	g++ $(CXXFLAGS) -c puzz14b.cpp

clean:
	rm -f puzz14a puzz14b puzz14a.o puzz14b.o
