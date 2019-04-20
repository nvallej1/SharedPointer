all:	main

main:	main.o	SharedPtr.hpp
	g++ -Wall -Wextra -pedantic -ggdb3 main.o -o main

main.o:	main.cpp SharedPtr.hpp
	g++ -Wall -Wextra -pedantic -ggdb3 -c main.cpp
