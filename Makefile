cpplox: main.o Lox.o Token.o Scanner.o Parser.o Expression.o Interpreter.o Statement.o
	g++ -std=c++20 main.o Lox.o Token.o Scanner.o Parser.o Expression.o Interpreter.o Statement.o -o cpplox

main.o: main.cpp
	g++ -c -std=c++20 main.cpp

Lox.o: Lox.cpp
	g++ -c -std=c++20 Lox.cpp

Token.o: Token.cpp
	g++ -c -std=c++20 Token.cpp

Scanner.o: Scanner.cpp
	g++ -c -std=c++20 Scanner.cpp

Expression.o: Expression.cpp
	g++ -c -std=c++20 Expression.cpp

Parser.o: Parser.cpp
	g++ -c -std=c++20 Parser.cpp

Interpreter.o: Interpreter.cpp
	g++ -c -std=c++20 Interpreter.cpp

Statement.o: Statement.cpp
	g++ -c -std=c++20 Statement.cpp

clean:
	rm *.o cpplox

rebuild: clean cpplox
	