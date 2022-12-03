all: clean puzz3a puzz3b
	clear
	@printf "$$ "
	./puzz3a < input.txt
	@printf "$$ "
	./puzz3b < input.txt
	@make clean >/dev/null

puzz3a: puzz3a.o
	g++ $(CXXFLAGS) -o puzz3a puzz3a.o

puzz3b: puzz3b.o
	g++ $(CXXFLAGS) -o puzz3b puzz3b.o

puzz3a.o: puzz3a.cpp
	g++ $(CXXFLAGS) -c puzz3a.cpp

puzz3b.o: puzz3b.cpp
	g++ $(CXXFLAGS) -c puzz3b.cpp

clean:
	rm -f puzz3a puzz3b puzz3a.o puzz3b.o
