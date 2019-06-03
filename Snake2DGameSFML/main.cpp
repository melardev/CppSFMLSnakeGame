#include "Game.h"

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "opengl32.lib")

// Link statically, do not forget SFML_STATIC preprocessor as well
#if defined(_WIN32) || defined(_WIN64)
#if _DEBUG
#pragma comment(lib, "sfml-graphics-s-d.lib")
#pragma comment(lib, "sfml-window-s-d.lib")
#pragma comment(lib, "sfml-system-s-d.lib")
#pragma comment(lib, "freetyped.lib")
#elif NDEBUG
#pragma comment(lib, "sfml-graphics-s.lib")
#pragma comment(lib, "sfml-window-s.lib")
#pragma comment(lib, "sfml-system-s.lib")
#pragma comment(lib, "freetype.lib")
#endif
#endif

Game* game;

int main(int argc, char* argv[])
{
	game = new Game(argc, argv);
	game->start();
	return 0;
}
