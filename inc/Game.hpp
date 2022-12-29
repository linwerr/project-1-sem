#pragma once
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Ball.hpp>
#include <C:\Users\Samsung\source\repos\project\built\Block.hpp>

namespace mt {
	class Game {
	private:
		int m_width, m_height; //ширина и высота экрана
		std::string m_caption; //название
		sf::RenderWindow* m_window = nullptr; //задание пустого окна

	public:
		Game() {

		}
		~Game();

		void SetCaption(const std::string& caption);
		void SetResolution(int width, int height);
		void Setup();
		void Run();
	};
}