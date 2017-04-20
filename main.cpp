#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>

using namespace sf;
int width = 800;
int height = 600;
sf::Color gray(105,105,105);
int in[6] = {0,100,200,300,400,500};
int velocity = 5;
int trackW = 90, segW = 12;
int obsP[6] = {0,0,0,0,0,0};
sf::Clock c;

class Car {
    private:
        int x;
        int y;
    public:
        sf::Texture tex;
        sf::Sprite spr;
        Car(int x, int y) {
            this->x = x;
            this->y = y;
        }
        void moveRight() {
            if (x < 640) {
                x += 10;
                spr.setPosition(x, y);
            }
        }
        void moveLeft() {
            if (x >= 110) {
                x -= 10;
                spr.setPosition(x, y);
            }
        }
        void setX(int x) {
            this->x = x;
        }
        void setY(int y) {
            this->y = y;
        }
        void setxy(int x, int y) {
            setX(x);
            setY(y);
        }
        int getX() {
            return x;
        }
        int getY() {
            return y;
        }
};

class PlayerCar: public Car {
    public:
        PlayerCar(int x=115, int y=height-100): Car(x, y) {
            tex.loadFromFile("resources/playercar.png");
            spr.setTexture(tex, true);
            spr.setPosition(x, y);
        }
};

class ObstacleCar: public Car {
    public:
        ObstacleCar(int x=115, int y=100, int t=0): Car(x,y) {
            std::stringstream ss;
            ss << t;
            tex.loadFromFile("resources/"+ss.str()+".png");
            spr.setTexture(tex, true);
            setxy(x, y);
            spr.setPosition(x, y);
        }
        void move() {
            setY(getY() + velocity);
        }
};

void moveSeg(int &y) {
    y += velocity;
    if (y>height) {
        y -= height;
    }
}

void drawQuad(RenderWindow &w, Color c, int x1, int y1, int x2, int y2)
{
    ConvexShape shape(4);
    shape.setFillColor(c);
    shape.setPoint(0, Vector2f(x1, y1));
    shape.setPoint(1, Vector2f(x1, y2));
    shape.setPoint(2, Vector2f(x2, y2));
    shape.setPoint(3, Vector2f(x2, y1));
    w.draw(shape);
}

int main(void)
{
    srand (time(NULL));
    RenderWindow app(VideoMode(width, height), "Car Game");
    app.setFramerateLimit(60);
    app.setKeyRepeatEnabled(false);

    // Instantiate player's car
    PlayerCar pCar;

    // Instantiate pointer for obstacle car

    // Score show Start
    sf::Font font;
    if (!font.loadFromFile("resources/arial.ttf"))
    {
        return 1;
    }
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setFillColor(sf::Color::White);
    text.setPosition(345,10);

    // Score show End

    while(app.isOpen() && !Keyboard::isKeyPressed(Keyboard::Escape))
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                app.close();
            }
        }
        app.clear();
        drawQuad(app, Color::Green, 100, 0, 700, height);

        for (int i=0; i<5; i++) {
            drawQuad(app, gray, 100+trackW+((trackW+segW)*i), in[0], 100+trackW+segW+((trackW+segW)*i), in[0]+50);
        }
        moveSeg(in[0]);

        for (int i=0; i<5; i++) {
            drawQuad(app, gray, 100+trackW+((trackW+segW)*i), in[1], 100+trackW+segW+((trackW+segW)*i), in[1]+50);
        }
        moveSeg(in[1]);

        for (int i=0; i<5; i++) {
            drawQuad(app, gray, 100+trackW+((trackW+segW)*i), in[2], 100+trackW+segW+((trackW+segW)*i), in[2]+50);
        }
        moveSeg(in[2]);

        for (int i=0; i<5; i++) {
            drawQuad(app, gray, 100+trackW+((trackW+segW)*i), in[3], 100+trackW+segW+((trackW+segW)*i), in[3]+50);
        }
        moveSeg(in[3]);

        for (int i=0; i<5; i++) {
            drawQuad(app, gray, 100+trackW+((trackW+segW)*i), in[4], 100+trackW+segW+((trackW+segW)*i), in[4]+50);
        }
        moveSeg(in[4]);

        for (int i=0; i<5; i++) {
            drawQuad(app, gray, 100+trackW+((trackW+segW)*i), in[5], 100+trackW+segW+((trackW+segW)*i), in[5]+50);
        }
        moveSeg(in[5]);

        if (Keyboard::isKeyPressed(Keyboard::Right)) {
			pCar.moveRight();
        } else if (Keyboard::isKeyPressed(Keyboard::Left)) {
            pCar.moveLeft();
        }
        app.draw(pCar.spr);
        sf::Time t = c.getElapsedTime();
        std::stringstream ss;
        ss << (int)t.asSeconds();
        text.setString("Score: "+ss.str());
        app.draw(text);
        app.display();
    }
    return 0;
}
