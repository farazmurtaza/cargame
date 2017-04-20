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
int flag=20;

using namespace sf;

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

//
//        if(flag<=20){
//            drawQuad(app, gray, 208, 0, 223, 25);
//            drawQuad(app, gray, 223+108, 0, 223+108+15, 25);
//            drawQuad(app, gray, 223+108+108, 0, 223+108+108+15, 25);
//            drawQuad(app, gray, 208, 0, 223, 25);
//            drawQuad(app, gray, 208, 0, 223, 25);
//            flag--;
//            if(flag==0){
//                flag=30;
//            }
//        }else{
//            flag--;
//        }



        drawQuad(app, gray, 208, in0, 223, in0+50);
        drawQuad(app, gray, 331, in0, 346, in0+50);
        drawQuad(app, gray, 454, in0, 469, in0+50);
        drawQuad(app, gray, 577, in0, 592, in0+50);
        in0 += velocity;
        if (in0>height)
        {
            in0 -=height;
        }

        drawQuad(app, gray, 208, in1, 223, in1+50);
        drawQuad(app, gray, 331, in1, 346, in1+50);
        drawQuad(app, gray, 454, in1, 469, in1+50);
        drawQuad(app, gray, 577, in1, 592, in1+50);
        in1 += velocity;
        if (in1>height)
        {
            in1 -=height;
        }

        drawQuad(app, gray, 208, in2, 223, in2+50);
        drawQuad(app, gray, 331, in2, 346, in2+50);
        drawQuad(app, gray, 454, in2, 469, in2+50);
        drawQuad(app, gray, 577, in2, 592, in2+50);
        in2 += velocity;
        if (in2>height)
        {
            in2 -=height;
        }

        drawQuad(app, gray, 208, in3, 223, in3+50);
        drawQuad(app, gray, 331, in3, 346, in3+50);
        drawQuad(app, gray, 454, in3, 469, in3+50);
        drawQuad(app, gray, 577, in3, 592, in3+50);
        in3 += velocity;
        if (in3>height)
        {
            in3 -=height;
        }

        drawQuad(app, gray, 208, in4, 223, in4+50);
        drawQuad(app, gray, 331, in4, 346, in4+50);
        drawQuad(app, gray, 454, in4, 469, in4+50);
        drawQuad(app, gray, 577, in4, 592, in4+50);
        in4 += velocity;
        if (in4>height)
        {
            in4 -=height;
        }

        drawQuad(app, gray, 208, in5, 223, in5+50);
        drawQuad(app, gray, 331, in5, 346, in5+50);
        drawQuad(app, gray, 454, in5, 469, in5+50);
        drawQuad(app, gray, 577, in5, 592, in5+50);
        in5 += velocity;
        if (in5>height)
        {
            in5 -=height;
        }
        app.display();
    }

    return 0;
}
