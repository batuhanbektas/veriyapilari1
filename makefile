hepsi: derle calistir

derle: 
	g++ -I ./include -o ./bin/Test ./src/main.cpp
	g++ -I ./include -o ./lib/App.o ./include/App.hpp
calistir:
	./bin/Test