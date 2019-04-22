all:	main SharedPtr_test

main:	main.o	SharedPtr.hpp
	g++ -Wall -Wextra -pedantic -ggdb3 main.o -o main

SharedPtr_test: SharedPtr_test.o SharedPtr.hpp
	g++ -Wall -Wextra -pedantic -ggdb3 -pthread SharedPtr.o -o SharedPtr_test

main.o:	main.cpp SharedPtr.hpp
	g++ -Wall -Wextra -pedantic -ggdb3 -c main.cpp

SharedPtr_test.o: SharedPtr_test.cpp SharedPtr.hpp
	g++ -Wall -Wextra -pedantic -ggdb3 -pthread -c SharedPtr_test.cpp

clean:
	rm -f main *.o
