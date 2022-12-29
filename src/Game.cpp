#pragma once
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Ball.hpp>
#include <Game.hpp>

namespace mt {
	Game::~Game() { //����������
		if (m_window != nullptr)
			delete m_window;
	}

	void Game::SetCaption(const std::string& caption) { //������� ��������
		m_caption = caption;
	}

	void Game::SetResolution(int width, int height) { //������� ������� ������ � ������ ������
		m_width = width;
		m_height = height;
	}

	void Game::Setup() { //������ ����
		m_window = new sf::RenderWindow(sf::VideoMode(m_width, m_height), m_caption);
	}

	void Game::Run() { //���������� ��� �������� � �������� ����
		std::vector<mt::Ball*> balls; //������ ������ �������

		balls.emplace_back(new mt::Ball({ 0,300 }, 30, sf::Color(255, 99, 71))); //��������� ������ �����
		balls.emplace_back(new mt::Ball({ 1000,300 }, 30, sf::Color(139, 0, 0))); //������ �����

		balls[0]->SetVelocity({ 270,200 }); //������� ������ ��������
		balls[1]->SetVelocity({ 300,150 });

		sf::Clock timer; //������

		std::vector<b::Block*> blocks; //������ ������ ������
		blocks.emplace_back(new b::Block({ 0,0 }, 200, 70, sf::Color(255, 140, 0))); //��������� �����
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

		while (m_window->isOpen()) { //������� ����������� ���� ���� ���� �������
			sf::Event event;
			while (m_window->pollEvent(event)) { //���� ���������� ������� �������� ����
				if (event.type == sf::Event::Closed)
					m_window->close(); //��������� ����
			}

			for (int i = 0; i < balls.size(); i++) { //����������� ������������ ������� �� ��������
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

			sf::Time dt = timer.restart(); //��������� �������

			for (int i = 0; i < balls.size(); i++) //����������� ������� ��������� ������
				balls[i]->Move(dt.asSeconds());


			for (int i = 0; i < balls.size(); i++) { //���������� ������������ ������� � �������
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

			for (int i = 0; i < balls.size(); i++) { //����������� ������������ ���� �������
				Vec v = balls[i]->GetVelocity();
				sf::FloatRect boundingBox = (*balls[0]->Get()).getGlobalBounds();
				sf::FloatRect otherBox = (*balls[1]->Get()).getGlobalBounds();
				if (boundingBox.intersects(otherBox)) {
					balls[i]->SetVelocity({ -v.x, -v.y });
				}
			}


			m_window->clear(); //������� ����

			for (int i = 0; i < blocks.size(); i++)
				m_window->draw(*blocks[i]->Get()); //������ ����� ������
			for (int i = 0; i < balls.size(); i++)
				m_window->draw(*balls[i]->Get()); //������ ����� �������
			m_window->display();
		}
		
		for (int i = 0; i < balls.size(); i++)
			delete balls[i]; //�������� ������� �������
		for (int i = 0; i < blocks.size(); i++)
			delete blocks[i]; //�������� ������� ������
	}
}

