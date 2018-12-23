#include <SFML/Graphics.hpp>
#include <iostream>

#include <cstdlib>
#include <ctime>

const int WIDTH = 500;
const int HEIGHT = 500;

const float RADIUS = 20.0f;

const int P_WIDTH = 20;
const int P_HEIGHT = 150;

bool paused = true;

void keepInBounds(sf::Vector2f &pos)
{
    if (pos.y < 0)
        pos.y = 0;

    if (pos.y > HEIGHT - P_HEIGHT)
        pos.y = HEIGHT - P_HEIGHT;
}

int main()
{
    srand(static_cast<unsigned>(time(0)));

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Pong");
    sf::CircleShape ball(RADIUS);
    ball.setFillColor(sf::Color::White);
    sf::Vector2f bPos(WIDTH / 2 - RADIUS, HEIGHT / 2 - RADIUS);
    sf::Vector2f bVel(0.2f, 0.2f);

    sf::RectangleShape rect(sf::Vector2f(P_WIDTH, P_HEIGHT));
    const int SPACING = 20;
    sf::Vector2f p1(SPACING, P_HEIGHT / 2 + P_HEIGHT / 2);
    sf::Vector2f p2(WIDTH - P_WIDTH - SPACING, P_HEIGHT / 2 + P_HEIGHT / 2);

    sf::Clock deltaClock;

    float contact;

    while (window.isOpen())
    {
        sf::Time dt = deltaClock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
            {
                paused = !paused;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            p1.y = p1.y - 1;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            p1.y = p1.y + 1;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            p2.y = p2.y - 1;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            p2.y = p2.y + 1;
        }

        // Keep Player in Bounds
        keepInBounds(p1);
        keepInBounds(p2);

        if (!paused)
        {
            bPos = bPos + (bVel);
            bVel = bVel * (0.9f * dt.asSeconds());
            /*if (bVel.x < .2 && bVel.x > 0)
                bVel.x = .2;
            if (bVel.x > -.2 && bVel.x < 0)
                bVel.x = -.2;

            if (bVel.y < .2 && bVel.y > 0)
                bVel.y = .2;
            if (bVel.y > -.2 && bVel.y < 0)
                bVel.y = -.2;*/

            sf::FloatRect b_ball = ball.getGlobalBounds();
            rect.setPosition(p1);
            sf::FloatRect b_p1 = rect.getGlobalBounds();
            rect.setPosition(p2);
            sf::FloatRect b_p2 = rect.getGlobalBounds();
            if ((b_p1.intersects(b_ball) || b_p2.intersects(b_ball)) && contact < 0)
            {
                const float LO = 10;
                const float HI = 50;
                float r1 = LO + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (HI - LO)));
                float r2 = LO + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (HI - LO)));
                bVel.x = 0 - bVel.x;
                bVel.y = 0 - bVel.y;
                //bVel.x = bVel.x + ((bVel.x < 0) ? (0 - r1) : r1);
                //bVel.y = bVel.y + ((bVel.y < 0) ? (0 - r2) : r2);
                contact = 0.1;
            }
            else
            {
                contact = contact - dt.asSeconds();
            }
        }

        int won = 0;
        if (bPos.x < SPACING - RADIUS)
        {
            paused = true;
            won = 1;
        }

        if (bPos.x > WIDTH - P_WIDTH - SPACING)
        {
            paused = true;
            won = 2;
        }

        if (won > 0)
        {
            std::cout << "Player " << ((won > 1) ? 1 : 2) << " Won the Game!" << std::endl
                      << std::endl;
            window.close();
        }

        window.clear();
        ball.setPosition(bPos);
        window.draw(ball);
        rect.setPosition(p1);
        window.draw(rect);
        rect.setPosition(p2);
        window.draw(rect);
        window.display();
    }

    return 0;
}