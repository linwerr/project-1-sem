#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <Game.hpp>

int main() {

	mt::Game game;
	game.SetResolution(1000, 600);
	game.SetCaption("Test game");
	game.Setup();
	game.Run();

	return 0;
}