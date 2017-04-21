#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <random>
#include <ctime>
#include <cstdlib>

using namespace sf;
int width = 800;
int height = 600;
sf::Color gray(105,105,105);
int in0 = 0, in1 = 100, in2 = 200, in3 = 300, in4 = 400, in5 = 500;
int velocity = 5;
int trackW = 90, segW = 12;
int obsP[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
sf::Clock c;

int my_rand()
{
	static std::mt19937 rng(std::time(nullptr));
	static std::uniform_int_distribution<int> distrib(0, 4);
	return distrib(rng);
}

class Car {
    private:
        
    public:
		int x;
		int y;
        sf::Texture tex;
        sf::Sprite spr;
        Car(int x, int y) {
            this->x = x;
            this->y = y;
        }
        void moveRight() {
            if (x < 640) {
                x += 6;
                spr.setPosition(x, y);
            }
        }
        void moveLeft() {
            if (x >= 110) {
                x -= 6;
                spr.setPosition(x, y);
            }
        }
        void setxy(int x, int y) {
            this->x=x;
            this->y=y;
        }
        int getX() {
            return x;
        }
        int getY() {
            return y;
        }
		void randomp(int s) {
			x = x + (s * 100);
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
        ObstacleCar(int x=115, int y=0): Car(x, y) {
            srand (time(0));
            int type = my_rand()+1;
			randomp(type);
            std::stringstream ss;
            ss << type;
            tex.loadFromFile("resources/"+ss.str()+".png");
            spr.setTexture(tex, true);
            spr.setPosition(x, y);
        }

		void move() {
			y = y + 3;
			spr.setPosition(x, y);
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

int check = 50;
int temp=0;

int main(void)
{

    RenderWindow app(VideoMode(width, height), "Car Game");
    app.setFramerateLimit(60);
    app.setKeyRepeatEnabled(false);

	sf::Texture TexEnemy;
	if (!TexEnemy.loadFromFile("resources/1.png")) {
		return 1;
	}
	sf::Sprite senemy(TexEnemy);


    PlayerCar pCar;
	ObstacleCar Enemy1[12];

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
            drawQuad(app, gray, 100+trackW+((trackW+segW)*i), in0, 100+trackW+segW+((trackW+segW)*i), in0+50);
        }
        moveSeg(in0);

        for (int i=0; i<5; i++) {
            drawQuad(app, gray, 100+trackW+((trackW+segW)*i), in1, 100+trackW+segW+((trackW+segW)*i), in1+50);
        }
        moveSeg(in1);

        for (int i=0; i<5; i++) {
            drawQuad(app, gray, 100+trackW+((trackW+segW)*i), in2, 100+trackW+segW+((trackW+segW)*i), in2+50);
        }
        moveSeg(in2);

        for (int i=0; i<5; i++) {
            drawQuad(app, gray, 100+trackW+((trackW+segW)*i), in3, 100+trackW+segW+((trackW+segW)*i), in3+50);
        }
        moveSeg(in3);

        for (int i=0; i<5; i++) {
            drawQuad(app, gray, 100+trackW+((trackW+segW)*i), in4, 100+trackW+segW+((trackW+segW)*i), in4+50);
        }
        moveSeg(in4);

        for (int i=0; i<5; i++) {
            drawQuad(app, gray, 100+trackW+((trackW+segW)*i), in5, 100+trackW+segW+((trackW+segW)*i), in5+50);
        }
        moveSeg(in5);

        if (Keyboard::isKeyPressed(Keyboard::Right)) {
			pCar.moveRight();
        } else if (Keyboard::isKeyPressed(Keyboard::Left)) {
            pCar.moveLeft();
        }

		
		if (check <= 0) {
			obsP[temp] = 1;
			if (temp < 12) {
				temp++;
			}
			else {
				temp = temp % 12;
				temp++;
			}
			check=50;
		}
		check--;
		int tempy,tempx;
		for (int aa = 0;aa < 12;aa++) {
			if (obsP[aa] == 1) {
				tempy=Enemy1[aa].getY();
				if (tempy > 600) {
					obsP[aa] = 0;
					tempx = (my_rand()+1) * 100;
					Enemy1[aa].setxy(tempx, 0);
				}
			}
		}

		for (int aa = 0;aa < 12;aa++) {
			if (obsP[aa] == 1) {
				Enemy1[aa].move();
			}
		}

		for (int aa = 0;aa < 12;aa++) {
			if (obsP[aa] == 1) {
				app.draw(Enemy1[aa].spr);
			}
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
