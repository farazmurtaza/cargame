#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
int width = 800;
int height = 600;
sf::Color gray(105,105,105);
int in0 = 0, in1 = 100, in2 = 200, in3 = 300, in4 = 400, in5 = 500;
int velocity = 5;

class Point {
public:
    int x;
    int y;
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
    void moveRight() {
        if (x < 640) {
            x += 10;
        }
    }
    void moveLeft() {
        if (x >= 110) {
            x -= 10;
        }
    }
};

void moveSeg(int &x) {
    x += velocity;
    if (x>height) {
        x -= height;
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
    RenderWindow app(VideoMode(width, height), "Car Game");
    app.setFramerateLimit(60);
    app.setKeyRepeatEnabled(false);

    sf::Image img;
    if (!img.loadFromFile("resources/playercar.png"))
    {
        return 1;
    }

    sf::Texture texture;
    texture.loadFromImage(img);
    sf::Sprite pCar;
    pCar.setTexture(texture, true);

    Point playerPoint(115, height-100);
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

        for (int i=0; i<4; i++) {
            drawQuad(app, gray, 208+(123*i), in0, 223+(123*i), in0+50);
        }
        moveSeg(in0);

        for (int i=0; i<4; i++) {
            drawQuad(app, gray, 208+(123*i), in1, 223+(123*i), in1+50);
        }
        moveSeg(in1);

        for (int i=0; i<4; i++) {
            drawQuad(app, gray, 208+(123*i), in2, 223+(123*i), in2+50);
        }
        moveSeg(in2);

        for (int i=0; i<4; i++) {
            drawQuad(app, gray, 208+(123*i), in3, 223+(123*i), in3+50);
        }
        moveSeg(in3);

        for (int i=0; i<4; i++) {
            drawQuad(app, gray, 208+(123*i), in4, 223+(123*i), in4+50);
        }
        moveSeg(in4);

        for (int i=0; i<4; i++) {
            drawQuad(app, gray, 208+(123*i), in5, 223+(123*i), in5+50);
        }
        moveSeg(in5);

        if (Keyboard::isKeyPressed(Keyboard::Right)) {
			playerPoint.moveRight();
        } else if (Keyboard::isKeyPressed(Keyboard::Left)) {
            playerPoint.moveLeft();
        }

        pCar.setPosition(Vector2f(playerPoint.x, playerPoint.y));
        app.draw(pCar);

        app.display();
    }
    return 0;
}
