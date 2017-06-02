all: testPart1 testPart2

testPart1: RNA.o Nussinov.cpp
	g++ RNA.o Nussinov.cpp -o testPart1

testPart2: ShortestPath.cpp
	g++ ShortestPath.cpp -o testPart2

RNA.o: RNA.h RNA.cpp
	g++ -c RNA.cpp -o RNA.o

clean:
	rm -f RNA.o testPart1 testPart2
