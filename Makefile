all:
	g++ -o main main.cpp drevo.cpp igralec.cpp ogenj.cpp sdl-window-and-renderer.cpp seznamSovraznikov.cpp seznamStaroselcev.cpp sovraznik.cpp staroselec.cpp verigaOgnjev.cpp zemljevidDreves.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image 