#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>




int main()
{
    srand((int)time(0));

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
    sf::Sprite spriteBee;
    spriteBee.setTexture(textureBee);


    sf::Sprite spriteCloud[3];

    for (int i = 0;i < 3; i++)
    {
        spriteCloud[i].setTexture(textureCloud);
    }

    float cloudY[3];

    cloudY[0] = 0;
    cloudY[1] = textureCloud.getSize().y;
    cloudY[2] = textureCloud.getSize().y * 2;


    spriteTree.setPosition(1920 * 0.5f - textureTree.getSize().x * 0.5f, 0);
    spriteCloud[0].setPosition(960, 0);
    spriteCloud[1].setPosition(960, 0 + textureCloud.getSize().y);
    spriteCloud[2].setPosition(960, 0 + textureCloud.getSize().y * 2);
    spriteBee.setPosition(960, 750);



    sf::Vector2f beeDirection = { 1.f, 0.f };
    float beeSpeed = 200.f;
    float beerandom = (float)rand() / RAND_MAX;
    if (beerandom > 0.5)
    {
        beeDirection.x = 1.f;
        spriteBee.setScale(-1.f, 1.f);
    }
    else
    {
        beeDirection.x = -1.f;
        spriteBee.setScale(1.f, 1.f);
    }
    beeSpeed = rand() % 200 + 100;

    sf::Vector2f cloudDirection[3];
    for (int i = 0; i < 3; i++)
    {
        cloudDirection[i] = { 1.f, 0.f };
    }

    float cloudspeed[3];
    for (int i = 0; i < 3; i++)
    {
        cloudspeed[i] = 200.f;
    }


    for (int i = 0; i < 3; i++)
    {
  
        float cloud1random = (float)rand() / RAND_MAX;
        if (cloud1random > 0.5)
        {
            cloudDirection[i].x = 1.f;
            spriteCloud[i].setScale(-1.f, 1.f);
        }
        else
        {
            cloudDirection[i].x = -1.f;
            spriteCloud[i].setScale(1.f, 1.f);
        }
        cloudspeed[i] = rand() % 200 + 100;
    }



    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time time = clock.restart();
        float deltaTime = time.asSeconds();

        printf("%f\n", deltaTime);


        // 이벤트 루프
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // 업데이트
        sf::Vector2f pos = spriteBee.getPosition();
        pos += beeDirection * beeSpeed * deltaTime;
        spriteBee.setPosition(pos);

        for (int i = 0; i < 3; i++)
        {
            sf::Vector2f pos_C1 = spriteCloud[i].getPosition();
            pos_C1 += cloudDirection[i] * cloudspeed[i] * deltaTime;
            spriteCloud[i].setPosition(pos_C1);

            if (pos_C1.x < -800 || pos_C1.x > 1920 + 800)
            {
                float cloud1random = (float)rand() / RAND_MAX;
                if (cloud1random < 0.5f)
                {
                    cloudDirection[i].x = 1.f;
                    spriteCloud[i].setScale(-1.f, 1.f);
                    spriteCloud[i].setPosition(0 - 100, 0 + cloudY[i]);
                   
                }
                else
                {
                    cloudDirection[i].x = -1.f;
                    spriteCloud[i].setScale(1.f, 1.f);
                    spriteCloud[i].setPosition(1920 + 100, 0 + cloudY[i]);
                }
                cloudspeed[i] = rand() % 200 + 100;

            }
        }

            if (pos.x < -200 || pos.x > 1920 + 200)
            {
                float beerandom = (float)rand() / RAND_MAX;
                if (beerandom < 0.5f)
                {
                    beeDirection.x = 1.f;
                    spriteBee.setScale(-1.f, 1.f);
                    spriteBee.setPosition(0 - 150, 750);
                }
                else
                {
                    beeDirection.x = -1.f;
                    spriteBee.setScale(1.f, 1.f);
                    spriteBee.setPosition(1920 + 150, 750);
                }
                beeSpeed = rand() % 200 + 100;
            }




            // 그리기
            window.clear();
            window.draw(spriteBackground);
            for (int i = 0; i < 3; i++)
            {
                window.draw(spriteCloud[i]);
            }

            window.draw(spriteTree);
            window.draw(spriteBee);
            window.display();
        
    }
        
 }