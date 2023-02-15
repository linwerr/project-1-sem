#include <SFML/Graphics.hpp>
#include <iostream>

class AnimatedText {

private:
     sf::Text text;
     sf::Font font;
     sf::Time duration;
     std::string string;
 
public:
    AnimatedText(sf::Time k)
    {
        duration = k;
        string = "Hello, world!";
    }

    int GetString() { return (string.length()); }

    void drawtext() {
        if (!font.loadFromFile("C:/Users/Samsung/Downloads/sfml_sample-main/sfml_sample-main/d9464-arkhip_font.ttf")) {
            std::cout << "error";
        }
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Yellow);

        sf::Time time = sf::seconds(duration.asSeconds() / GetString());

        char mas[14];
        for (int i = 0; i < 14; i++) {
            mas[i] = string[i];
        }

        string = " ";
        text.setString(" ");
        int k = 0;
        
        sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

        sf::Clock clock;

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

           sf::Time elapsed = clock.getElapsedTime();

            if (elapsed.asSeconds() > time.asSeconds() && string.length() != 14) {
                string += mas[k];
                clock.restart();
                k++;
            }
           
            text.setString(string);

            window.clear();
            window.draw(text);
            window.display();
        }
        
    }

};

int main()
{
    AnimatedText antext (sf::seconds(13));
    antext.drawtext();
}