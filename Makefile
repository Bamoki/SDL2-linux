all:
	g++ -o main src/main.cpp -I"/usr/include/SDL2" -lSDL2 -lSDL2_ttf -lSDL2_image
