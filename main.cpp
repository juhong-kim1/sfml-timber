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
    sf::Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");



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

    spriteTree.setPosition(1920 * 0.5f - textureTree.getSize().x * 0.5f, -50);
    spriteBackgroundElements[0].setPosition(960, 0);
    spriteBackgroundElements[1].setPosition(960, 0 + textureCloud.getSize().y);
    spriteBackgroundElements[2].setPosition(960, 0 + textureCloud.getSize().y * 2);


    //UI
    sf::Text textScore;
    textScore.setFont(font);
    textScore.setString("SCORE: 0");
    textScore.setCharacterSize(100);
    textScore.setFillColor(sf::Color::White);
    textScore.setPosition(20,20);






    sf::Text textMessage;
    textMessage.setFont(font);
    textMessage.setString("Press Enter to Start!");
    textMessage.setCharacterSize(50);
    textMessage.setFillColor(sf::Color::Yellow);
    sf::Vector2f messageOrigin;
    messageOrigin.x = textMessage.getLocalBounds().width * 0.5f;
    messageOrigin.y = textMessage.getLocalBounds().height * 0.5f;
    textMessage.setOrigin(messageOrigin);
    textMessage.setPosition(1920 * 0.5f, 1080 * 0.5f);
 





    sf::RectangleShape timeBar;
    float timeBarWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize({ timeBarWidth, timeBarHeight });
    timeBar.setFillColor(sf::Color::Red);
    timeBar.setPosition(1920 * 0.5f - timeBarWidth * 0.5f, 1000.f - 100.f);



    //게임데이터
    int score = 0;
    float timeBarSpeed = timeBarWidth / 5.f;
    float remaingTime = 5.f;
    bool isPlaying = false;



    sf::Clock clock;

    bool isLeft = false;
    bool isRight = false;
    bool isCrash = false;
    bool keyPressed = false;
    bool isPressEnter = false;
    int isStartCount = 0;
    bool isStart = true;

    
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
                        case sf::Keyboard::Return:
                            isPlaying = !isPlaying;
                            if (!isPlaying)
                            {
                                textMessage.setString("Press Enter to Resume");
                                textMessage.setFillColor(sf::Color::Red);
                                sf::Vector2f messageOrigin;
                                messageOrigin.x = textMessage.getLocalBounds().width * 0.5f;
                                messageOrigin.y = textMessage.getLocalBounds().height * 0.5f;
                                textMessage.setOrigin(messageOrigin);

                            }
                            else if (remaingTime == 0.f || sidePlayer == sideBranch[NUM_BRANCHES - 1])
                            {
                                score = 0;
                                textScore.setString("SCORE: 0");
                                remaingTime = 5.f;
                                sideBranch[NUM_BRANCHES - 1] = Side::NONE;

                            }




                        }
               

                        break;

                    }

                }

                if (isPlaying)
                {

                    remaingTime -= deltaTime;
                    if (remaingTime < 0.f)
                    {
                        remaingTime = 0.f;
                        isPlaying = false;
                        textMessage.setString("Press Enter to Restart");
                        textMessage.setFillColor(sf::Color::Blue);
                        sf::Vector2f messageOrigin;
                        messageOrigin.x = textMessage.getLocalBounds().width * 0.5f;
                        messageOrigin.y = textMessage.getLocalBounds().height * 0.5f;
                        textMessage.setOrigin(messageOrigin);

                    }
                    timeBar.setSize({timeBarSpeed * remaingTime, timeBarHeight});



                    sf::Vector2f timeBarSize = timeBar.getSize();
                    timeBarSize.x -= timeBarSpeed * deltaTime;
                    timeBar.setSize(timeBarSize);



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
                        if (sidePlayer == sideBranch[NUM_BRANCHES - 1])
                        {
                            printf("충돌!\n");
                            score = 0;
                            textScore.setString("SCORE: " + std::to_string(score));
                            isPlaying = false;
                            textMessage.setString("Press Enter to Restart");
                            textMessage.setFillColor(sf::Color::Blue);
                            sf::Vector2f messageOrigin;
                            messageOrigin.x = textMessage.getLocalBounds().width * 0.5f;
                            messageOrigin.y = textMessage.getLocalBounds().height * 0.5f;
                            textMessage.setOrigin(messageOrigin);
                        }
                        else
                        {
                            score += 10;
                            textScore.setString("SCORE: " + std::to_string(score));
                        }

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






    


                }


            // 그리기
            window.clear();

            //WORLD
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
          

            if (isLeft || isRight && !isPlaying)
            {
                window.draw(spriteAxe);
            }



            //UI
            window.draw(textScore);
            window.draw(timeBar);

            if (!isPlaying)
            {
                window.draw(textMessage);
            }

            window.display();

                    
    }
        
 }