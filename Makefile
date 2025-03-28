cpplox: main.o Lox.o Token.o Scanner.o
	g++ -std=c++20 main.o Lox.o Token.o Scanner.o -o cpplox

main.o: main.cpp
	g++ -c -std=c++20 main.cpp

Lox.o: Lox.cpp
	g++ -c -std=c++20 Lox.cpp

Token.o: Token.cpp
	g++ -c -std=c++20 Token.cpp

Scanner.o: Scanner.cpp
	g++ -c -std=c++20 Scanner.cpp

clean:
	del *.o