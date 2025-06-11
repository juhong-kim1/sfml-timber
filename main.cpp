#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Timber!");

    sf::Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");

    sf::Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    sf::Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    sf::Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");

    sf::Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    sf::Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    sf::Sprite spriteCloud;
    spriteCloud.setTexture(textureCloud);
    sf::Sprite spriteCloud2;
    spriteCloud2.setTexture(textureCloud);
    sf::Sprite spriteCloud3;
    spriteCloud3.setTexture(textureCloud);
    sf::Sprite spriteBee;
    spriteBee.setTexture(textureBee);



    spriteTree.setPosition(1920 * 0.5f - textureTree.getSize().x *0.5f, 0);
    spriteCloud2.setPosition(0, 0 + textureCloud.getSize().y);
    spriteCloud3.setPosition(0, 0 + textureCloud.getSize().y * 2);
    spriteBee.setPosition(0, 750);



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();


        window.draw(spriteBackground);
        window.draw(spriteCloud);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);

        window.draw(spriteTree);
        window.draw(spriteBee);
        window.display();
    }

    return 0;
} //æ»≥Á«œººø‰