#include "Resources.h"

#include <SFML/Graphics.hpp>

namespace Resources
{    
    constexpr char SFMLLogo[] = "1200px-SFML2.png";
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "SFML Template Project");
    sf::Sprite logo(GetTexture(Resources::SFMLLogo));
    logo.scale({ 0.5f, 0.5f });

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(logo);
        window.display();
    }

    return 0;
}