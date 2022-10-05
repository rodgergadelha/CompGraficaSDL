all:
	g++ -I src/include -I header_files -L src/lib main.cpp -lmingw32 -lSDL2main -lSDL2 -std=c++20 -o main