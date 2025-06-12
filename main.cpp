#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>

enum class Side { LEFT, RIGHT, NONE };
int enterCount = 0;

void updateBranches(Side* branches, int size)
{
    for (int i = size - 1; i >= 1; i--)
    {
        branches[i] = branches[i - 1];
    }
    int r = rand() % 3;
    switch (r)
    {
    case 0:
        branches[0] = Side::LEFT;
        break;
    case 1:
        branches[0] = Side::RIGHT;
        break;
    case 2:
        branches[0] = Side::NONE;
        break;
    }
}




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
    sf::Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    sf::Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");
    sf::Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");


    sf::Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    sf::Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    sf::Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);


    
    int cloudCount = 3;
    const int NUM_BACKGOROUND= 4;
    sf::Sprite spriteBackgroundElements[NUM_BACKGOROUND];
    sf::Vector2f directionElements[NUM_BACKGOROUND];
    float speedElements[NUM_BACKGOROUND];




    for (int i = 0 ; i < NUM_BACKGOROUND; i++)
    {
        if (i < cloudCount)
        {
            spriteBackgroundElements[i].setTexture(textureCloud);
            directionElements[i] = { 1.f, 0.f };
            speedElements[i] = rand() % 200 + 100;
            float cloud1random = (float)rand() / RAND_MAX;
            if (cloud1random > 0.5)
            {
                directionElements[i].x = 1.f;
                spriteBackgroundElements[i].setScale(-1.f, 1.f);
                spriteBackgroundElements[i].setPosition(-150, rand() % 300 + 100);
            }
            else
            {
                directionElements[i].x = -1.f;
                spriteBackgroundElements[i].setScale(1.f, 1.f);
                spriteBackgroundElements[i].setPosition(1920 + 150, rand() % 300 + 10);
            }
           
        }
        else
        {
            spriteBackgroundElements[i].setTexture(textureBee);
            directionElements[i] = { 1.f, 0.f };
            speedElements[i] = rand() % 200 + 100;
            float beerandom = (float)rand() / RAND_MAX;

            if (beerandom > 0.5)
            {
                directionElements[i].x = 1.f;
                spriteBackgroundElements[i].setScale(-1.f, 1.f);
                spriteBackgroundElements[i].setPosition(-150, 750);
            }
            else
            {
                directionElements[i].x = -1.f;
                spriteBackgroundElements[i].setScale(-1.f, 1.f);
                spriteBackgroundElements[i].setPosition(-150, 750);
            }
        }

    }
    sf::Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setOrigin(texturePlayer.getSize().x * -2.f, texturePlayer.getSize().y );
    spritePlayer.setPosition(1920 * 0.5f, 950.f);

    spriteAxe.setOrigin(texturePlayer.getSize().x * -1.1f, texturePlayer.getSize().y);
    spriteAxe.setPosition(1920 * 0.5f, 1060);

   



    const int NUM_BRANCHES = 6;
    sf::Sprite spriteBranch[NUM_BRANCHES];
    Side sideBranch[NUM_BRANCHES];
    Side sidePlayer = Side::RIGHT;
    Side sideAxe=Side::RIGHT;

    switch (sidePlayer)
    {
    case Side::LEFT:
        spritePlayer.setScale(-1.f, 1.f);
        spriteAxe.setScale(-1.f, 1.f);
        break;
    case Side::RIGHT:
        spritePlayer.setScale(1.f, 1.f);
        spriteAxe.setScale(1.f, 1.f);
        break;
    }



    for (int i = 0; i < NUM_BRANCHES; ++i)
    {
        spriteBranch[i].setTexture(textureBranch);
        spriteBranch[i].setOrigin(textureTree.getSize().x * -0.5f, 0.f);
        spriteBranch[i].setPosition(1920.f * 0.5f, i * 150.f);

        int r = rand() % 3;
        switch (r)
        {
        case 0:
            sideBranch[i] = Side::LEFT;
            break;
        case 1:
            sideBranch[i] = Side::RIGHT;
            break;
        case 2:
            sideBranch[i] = Side::NONE;
            break;
        }
    

    }
    sideBranch[NUM_BRANCHES - 1] = Side::NONE;

    spriteTree.setPosition(1920 * 0.5f - textureTree.getSize().x * 0.5f, 0);
    spriteBackgroundElements[0].setPosition(960, 0);
    spriteBackgroundElements[1].setPosition(960, 0 + textureCloud.getSize().y);
    spriteBackgroundElements[2].setPosition(960, 0 + textureCloud.getSize().y * 2);



    sf::Clock clock;

    bool isLeft = false;
    bool isRight = false;
    bool iscrash = false;
    bool keyPressed = false;
    bool isPlaying = true;
    bool isPressEnter = false;

    
    while (window.isOpen())
    {

        
            sf::Time time = clock.restart();
            float deltaTime = time.asSeconds();
            sf::Keyboard::Enter;
          
            
                // printf("%f\n", deltaTime);
                bool isLeftUp = false;
                bool isRightUp = false;
                bool isLeftDown = false;
                bool isRightDown = false;

                // 이벤트 루프
                sf::Event event;
                while (window.pollEvent(event))
                {

                    switch (event.type)
                    {
                    case sf::Event::Closed:
                        window.close();
                        break;
                    case sf::Event::KeyPressed:
                        switch (event.key.code)
                        {
                        case sf::Keyboard::Left:


                            if (!isLeft)
                            {
                                isLeftDown = true;

                            }
                            isLeft = true;
                            keyPressed = true;

                            break;
                        case sf::Keyboard::Right:

                            if (!isRight)
                            {
                                isRightDown = true;
                            }
                            isRight = true;
                            keyPressed = true;


                            break;
                        }
                        break;
                    case sf::Event::KeyReleased:
                        switch (event.key.code)
                        {
                        case sf::Keyboard::Left:
                            isLeft = false;
                            isLeftUp = true;
                            keyPressed = false;

                            break;
                        case sf::Keyboard::Right:
                            isRight = false;
                            isRightUp = true;
                            keyPressed = false;
                            break;
                        }
                        break;

                    }

                }

                if (isPlaying == true)
                {

                    // 업데이트
                    if (isRightDown || isLeftDown)
                    {
                        if (isLeftDown)
                        {
                            sidePlayer = Side::LEFT;
                        }
                        if (isRightDown)
                        {
                            sidePlayer = Side::RIGHT;
                        }
                        updateBranches(sideBranch, NUM_BRANCHES);

                    }





                    for (int i = 0; i < NUM_BACKGOROUND; ++i)
                    {
                        if (cloudCount < 3)
                        {
                            sf::Vector2f position = spriteBackgroundElements[i].getPosition();
                            position += directionElements[i] * speedElements[i] * deltaTime;
                            spriteBackgroundElements[i].setPosition(position);
                            if (position.x < -200 || position.x > 1920 + 200)
                            {
                                float random = (float)rand() / RAND_MAX;
                                if (random < 0.5f)
                                {
                                    directionElements[i].x = 1.f;
                                    spriteBackgroundElements[i].setScale(-1.f, 1.f);
                                    spriteBackgroundElements[i].setPosition(0 - 150, rand() % 300 + 100);
                                }
                                else
                                {
                                    directionElements[i].x = -1.f;
                                    spriteBackgroundElements[i].setScale(1.f, 1.f);
                                    spriteBackgroundElements[i].setPosition(1920 + 150, rand() % 300 + 100);
                                }
                                speedElements[i] = rand() % 200 + 100;

                            }

                        }
                        else
                        {
                            sf::Vector2f position = spriteBackgroundElements[i].getPosition();
                            position += directionElements[i] * speedElements[i] * deltaTime;
                            spriteBackgroundElements[i].setPosition(position);
                            if (position.x < -200 || position.x > 1920 + 200)
                            {
                                float random = (float)rand() / RAND_MAX;
                                if (random < 0.5f)
                                {
                                    directionElements[i].x = 1.f;
                                    spriteBackgroundElements[i].setScale(-1.f, 1.f);
                                    spriteBackgroundElements[i].setPosition(0 - 150, 750);
                                }
                                else
                                {
                                    directionElements[i].x = -1.f;
                                    spriteBackgroundElements[i].setScale(1.f, 1.f);
                                    spriteBackgroundElements[i].setPosition(1920 + 150, 750);
                                }
                                speedElements[i] = rand() % 200 + 100;

                            }
                        }



                    }

                    for (int i = 0; i < NUM_BRANCHES; i++)
                    {
                        switch (sideBranch[i])
                        {
                        case Side::LEFT:
                            spriteBranch[i].setScale(-1.f, 1.f);
                            break;
                        case Side::RIGHT:
                            spriteBranch[i].setScale(1.f, 1.f);
                            break;
                        }


                    }

                    switch (sidePlayer)
                    {
                    case Side::LEFT:
                        spritePlayer.setScale(-1.f, 1.f);
                        spriteAxe.setScale(-1.f, 1.f);
                        break;
                    case Side::RIGHT:
                        spritePlayer.setScale(1.f, 1.f);
                        spriteAxe.setScale(1.f, 1.f);
                        break;
                    }


                    if (sideBranch[NUM_BRANCHES-1] == sidePlayer)
                    {
                        if (!iscrash)
                        {
                            printf("Ouch!");
                            isPlaying = false;
                            iscrash = true;

                        }
                   
                    }

                }
         
                if (event.key.code == sf::Keyboard::Enter)
                {
                    enterCount++;

                   if (event.key.code == sf::Keyboard::Enter && !isPlaying)
                    {
                       enterCount++;
                       if (enterCount >= 2)
                       {
                           isPlaying = true;
                           iscrash = false;
                           enterCount = 0;
                       }
                    }
                }
              




            // 그리기
            window.clear();
            window.draw(spriteBackground);
            for (int i = 0; i < NUM_BACKGOROUND; i++)
            {
                window.draw(spriteBackgroundElements[i]);
            }

            window.draw(spriteTree);
            for (int i = 0; i < NUM_BRANCHES; ++i)
            {
                if (sideBranch[i] != Side::NONE)
                {
                    window.draw(spriteBranch[i]);
                }


            }
            window.draw(spriteBackgroundElements[3]);
            window.draw(spritePlayer);
          

            if (keyPressed == true)
            {
                window.draw(spriteAxe);
            }




            window.display();

                    
    }
        
 }