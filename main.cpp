#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

int width = 800;
int height = 600;
sf::Color gray(105,105,105);
int in0 = 0, in1 = 100, in2 = 200, in3 = 300, in4 = 400, in5 = 500;
int velocity = 5;

using namespace sf;

void moveSeg(int &x) {
    x += velocity;
    if (x>height) {
        x -= height;
    }
}

struct Line
{
    float x,y,z; //3d center of line
    float X,Y,W; //screen coord
    float curve,spriteX,clip,scale;
    Sprite sprite;

    Line()
    {
        spriteX=curve=x=y=z=0;
    }

//  void project(int camX,int camY,int camZ)
//  {
//    scale = camD/(z-camZ);
//    X = (1 + scale*(x - camX)) * width/2;
//    Y = (1 - scale*(y - camY)) * height/2;
//    W = scale * roadW  * width/2;
//  }

    void drawSprite(RenderWindow &app)
    {
        Sprite s = sprite;
        int w = s.getTextureRect().width;
        int h = s.getTextureRect().height;

        float destX = X + scale * spriteX * width/2;
        float destY = Y + 4;
        float destW  = w * W / 266;
        float destH  = h * W / 266;

        destX += destW * spriteX; //offsetX
        destY += destH * (-1);    //offsetY

        float clipH = destY+destH-clip;
        if (clipH<0) clipH=0;

        if (clipH>=destH) return;
        s.setTextureRect(IntRect(0,0,w,h-h*clipH/destH));
        s.setScale(destW/w,destH/h);
        s.setPosition(destX, destY);
        app.draw(s);
    }
};


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

    std::vector<Line> lines;

    while(app.isOpen())
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

        sf::Image img;
        if (!img.loadFromFile("resources/playercar.png"))
        {
            return 1;
        }


        sf::Texture texture;
        texture.loadFromImage(img);
        sf::Sprite pCar;
        pCar.setPosition(Vector2f(115, height-150));
        pCar.setTexture(texture, true);

        app.draw(pCar);

//        sf::Sprite pCar;
//        pCar.

        app.display();
    }
    return 0;
}
