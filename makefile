# === Basit Makefile ===

hepsi: derle calistir

derle:
	g++ -c -I include src/Shape.cpp -o lib/Shape.o
	g++ -c -I include src/ShapeNode.cpp -o lib/ShapeNode.o
	g++ -c -I include src/ShapeList.cpp -o lib/ShapeList.o
	g++ -c -I include src/MainNode.cpp -o lib/MainNode.o
	g++ -c -I include src/MainList.cpp -o lib/MainList.o
	g++ -c -I include src/Rectangle.cpp -o lib/Rectangle.o
	g++ -c -I include src/Triangle.cpp -o lib/Triangle.o
	g++ -c -I include src/Star.cpp -o lib/Star.o
	g++ -c -I include src/Screen.cpp -o lib/Screen.o
	g++ -c -I include src/App.cpp -o lib/App.o
	g++ -c -I include src/Main.cpp -o lib/Main.o
	g++ lib/*.o -o bin/odev1.exe

calistir:
	./bin/odev1.exe

clean:
	del /Q lib\*.o
	del /Q bin\*.exe
