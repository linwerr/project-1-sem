#pragma once
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Ball.hpp>
#include <Game.hpp>

namespace mt {
	Game::~Game() { //деструктор
		if (m_window != nullptr)
			delete m_window;
	}

	void Game::SetCaption(const std::string& caption) { //функция названия
		m_caption = caption;
	}

	void Game::SetResolution(int width, int height) { //функция задания ширины и высоты экрана
		m_width = width;
		m_height = height;
	}

	void Game::Setup() { //задает окно
		m_window = new sf::RenderWindow(sf::VideoMode(m_width, m_height), m_caption);
	}

	void Game::Run() { //происходят все действия в открытом окне
		std::vector<mt::Ball*> balls; //задаем вектор шариков

		balls.emplace_back(new mt::Ball({ 0,300 }, 30, sf::Color(255, 99, 71))); //добавляем первый шарик
		balls.emplace_back(new mt::Ball({ 1000,300 }, 30, sf::Color(139, 0, 0))); //второй шарик

		balls[0]->SetVelocity({ 270,200 }); //придаем шарику скорость
		balls[1]->SetVelocity({ 300,150 });

		sf::Clock timer; //таймер

		std::vector<b::Block*> blocks; //задаем вектор блоков
		blocks.emplace_back(new b::Block({ 0,0 }, 200, 70, sf::Color(255, 140, 0))); //добавляем блоки
		blocks.emplace_back(new b::Block({ 200,0 }, 200, 70, sf::Color::Yellow));
		blocks.emplace_back(new b::Block({ 400,0 }, 200, 70, sf::Color(255, 140, 0)));
		blocks.emplace_back(new b::Block({ 600,0 }, 200, 70, sf::Color::Yellow));
		blocks.emplace_back(new b::Block({ 800,0 }, 200, 70, sf::Color(255, 140, 0)));

		blocks.emplace_back(new b::Block({ 0,70 }, 200, 70, sf::Color::Yellow));
		blocks.emplace_back(new b::Block({ 200,70 }, 200, 70, sf::Color(255, 140, 0)));
		blocks.emplace_back(new b::Block({ 400,70 }, 200, 70, sf::Color::Yellow));
		blocks.emplace_back(new b::Block({ 600,70 }, 200, 70, sf::Color(255, 140, 0)));
		blocks.emplace_back(new b::Block({ 800,70 }, 200, 70, sf::Color::Yellow));

		blocks.emplace_back(new b::Block({ 0,140 }, 200, 70, sf::Color(255, 140, 0)));
		blocks.emplace_back(new b::Block({ 200,140 }, 200, 70, sf::Color::Yellow));
		blocks.emplace_back(new b::Block({ 400,140 }, 200, 70, sf::Color(255, 140, 0)));
		blocks.emplace_back(new b::Block({ 600,140 }, 200, 70, sf::Color::Yellow));
		blocks.emplace_back(new b::Block({ 800,140 }, 200, 70, sf::Color(255, 140, 0)));

		while (m_window->isOpen()) { //создаем бесконечный цикл пока окно открыто
			sf::Event event;
			while (m_window->pollEvent(event)) { //пока происходит событие закрытия окна
				if (event.type == sf::Event::Closed)
					m_window->close(); //закрываем окно
			}

			for (int i = 0; i < balls.size(); i++) { //прописываем столкновение шариков со стенками
				Point p = balls[i]->GetPosition();
				float r = balls[i]->Radius();
				Vec v = balls[i]->GetVelocity();

				if (p.y + r > m_height && v.y > 0)
					balls[i]->SetVelocity({ v.x, -v.y });

				if (p.y - r < 0 && v.y < 0)
					balls[i]->SetVelocity({ v.x, -v.y });

				if (p.x + r >= m_width && v.x > 0)
					balls[i]->SetVelocity({ -v.x, v.y });

				if (p.x - r <= 0 && v.x < 0)
					balls[i]->SetVelocity({ -v.x, v.y });
			}

			sf::Time dt = timer.restart(); //изменение времени

			for (int i = 0; i < balls.size(); i++) //посекундное задание координат шарика
				balls[i]->Move(dt.asSeconds());


			for (int i = 0; i < balls.size(); i++) { //прописывем столкновение шариков с блоками
				for (int j = 0; j < blocks.size(); j++) {
					Vec v = balls[i]->GetVelocity();
					sf::FloatRect boundingBox = (*balls[i]->Get()).getGlobalBounds();
					sf::FloatRect otherBox = (*blocks[j]->Get()).getGlobalBounds();
					if (boundingBox.intersects(otherBox))
					{
						blocks.erase(blocks.begin() + j);
						balls[i]->SetVelocity({ v.x, -v.y });
					}
				}
			}

			for (int i = 0; i < balls.size(); i++) { //прописываем столкновение двух шариков
				Vec v = balls[i]->GetVelocity();
				sf::FloatRect boundingBox = (*balls[0]->Get()).getGlobalBounds();
				sf::FloatRect otherBox = (*balls[1]->Get()).getGlobalBounds();
				if (boundingBox.intersects(otherBox)) {
					balls[i]->SetVelocity({ -v.x, -v.y });
				}
			}


			m_window->clear(); //очистка окна

			for (int i = 0; i < blocks.size(); i++)
				m_window->draw(*blocks[i]->Get()); //рисуем вывод блоков
			for (int i = 0; i < balls.size(); i++)
				m_window->draw(*balls[i]->Get()); //рисуем вывод шариков
			m_window->display();
		}
		
		for (int i = 0; i < balls.size(); i++)
			delete balls[i]; //удаление вектора шариков
		for (int i = 0; i < blocks.size(); i++)
			delete blocks[i]; //удаление вектора блоков
	}
}

