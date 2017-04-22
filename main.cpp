#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>

using namespace sf;

// Number of objects of obstacle cars to be spawned
#define noOfobs 200

int width = 800;
int height = 600;
sf::Color gray(105, 105, 105);
int in[6] = { 0,100,200,300,400,500 };
int velocity = 3;
int trackW = 90, segW = 12;
int obsP[noOfobs];
sf::Clock c;
bool accelerate = false;

// Initialize all obstacle cars' objects to 0
void init() {
	for (int i = 0; i<noOfobs; i++) {
		obsP[i] = 0;
	}
}

int my_rand()
{
	static std::mt19937 rng(std::time(nullptr));
	static std::uniform_int_distribution<int> distrib(0, 5);
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

class PlayerCar : public Car {
public:
	PlayerCar(int x = 115, int y = height - 100) : Car(x, y) {
		tex.loadFromFile("resources/playercar.png");
		spr.setTexture(tex, true);
		spr.setPosition(x, y);
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
};

class ObstacleCar : public Car {
public:
	ObstacleCar(int x = 115, int y = 0) : Car(x, y) {
		int type = my_rand() + 1;
		std::stringstream ss;
		ss << type;
		tex.loadFromFile("resources/" + ss.str() + ".png");
		spr.setTexture(tex, true);
		x = ((my_rand() + 1) * 110);
		setxy(x, y);
		spr.setPosition(x, y);
	}

	void move() {
		y = y + 1.5*velocity;
		spr.setPosition(x, y);
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

int check = 60;
int temp = 0;
int ptempx, ptempy;
bool collision = false;

int main(void)
{
	init();
	RenderWindow app(VideoMode(width, height), "Car Game");
	app.setFramerateLimit(60);
	app.setKeyRepeatEnabled(false);

	PlayerCar pCar;
	ObstacleCar Enemy1[noOfobs];

	// Score part starts here
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
	text.setPosition(345, 10);
	// Score part ends here

	while (app.isOpen() && !Keyboard::isKeyPressed(Keyboard::Escape))
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
		drawQuad(app, gray, 100, 0, 700, height);

		for (int i = 0; i<5; i++) {
			drawQuad(app, sf::Color::White, 100 + trackW + ((trackW + segW)*i), in[0], 100 + trackW + segW + ((trackW + segW)*i), in[0] + 50);
		}
		moveSeg(in[0]);

		for (int i = 0; i<5; i++) {
			drawQuad(app, sf::Color::White, 100 + trackW + ((trackW + segW)*i), in[1], 100 + trackW + segW + ((trackW + segW)*i), in[1] + 50);
		}
		moveSeg(in[1]);

		for (int i = 0; i<5; i++) {
			drawQuad(app, sf::Color::White, 100 + trackW + ((trackW + segW)*i), in[2], 100 + trackW + segW + ((trackW + segW)*i), in[2] + 50);
		}
		moveSeg(in[2]);

		for (int i = 0; i<5; i++) {
			drawQuad(app, sf::Color::White, 100 + trackW + ((trackW + segW)*i), in[3], 100 + trackW + segW + ((trackW + segW)*i), in[3] + 50);
		}
		moveSeg(in[3]);

		for (int i = 0; i<5; i++) {
			drawQuad(app, sf::Color::White, 100 + trackW + ((trackW + segW)*i), in[4], 100 + trackW + segW + ((trackW + segW)*i), in[4] + 50);
		}
		moveSeg(in[4]);

		for (int i = 0; i<5; i++) {
			drawQuad(app, sf::Color::White, 100 + trackW + ((trackW + segW)*i), in[5], 100 + trackW + segW + ((trackW + segW)*i), in[5] + 50);
		}
		moveSeg(in[5]);

		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			pCar.moveRight();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left)) {
			pCar.moveLeft();
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
		    accelerate = true;
            velocity+=3;
		}

		if (check <= 0) {
			obsP[temp] = 1;
			if (temp < noOfobs) {
				temp++;
			}
			else {
				temp = temp % noOfobs;
				temp++;
			}
			check = 60;
		}
		check--;
		int tempy, tempx;
		for (int aa = 0;aa < noOfobs;aa++) {
			if (obsP[aa] == 1) {
				tempy = Enemy1[aa].getY();
				if (tempy > 600) {
					obsP[aa] = 0;
					tempx = (my_rand() + 1) * 100;
					Enemy1[aa].setxy(tempx, 0);
				}
			}
		}

		//CHECK COLLISION

		for (int aa = 0;aa < noOfobs;aa++) {
			if (obsP[aa] == 1) {
				tempx = Enemy1[aa].getX();
				tempy = Enemy1[aa].getY();
				ptempx = pCar.getX();
				ptempy = pCar.getY();

				if (tempx > ptempx) {
					if ((tempx - ptempx) < 50) {
						if (tempy > ptempy) {
							if ((tempy - ptempy) < 100) {
								collision = true;
							}
						}
						else {
							if ((ptempy - tempy) < 100) {
								collision = true;
							}
						}
					}
				}
				else {
					if ((ptempx - tempx) < 45) {
						if (tempy > ptempy) {
							if ((tempy - ptempy) < 100) {
								collision = true;
							}
						}
						else {
							if ((ptempy - tempy) < 100) {
								collision = true;
							}
						}
					}
				}
			}
		}
		////

		for (int aa = 0;aa < noOfobs;aa++) {
			if (obsP[aa] == 1) {
				Enemy1[aa].move();
			}
		}

		for (int aa = 0;aa < noOfobs;aa++) {
			if (obsP[aa] == 1) {
				app.draw(Enemy1[aa].spr);
			}
		}


		sf::Time t = c.getElapsedTime();
		std::stringstream ss2;
		ss2 << (int)t.asSeconds();
		std::cout << t.asSeconds() << std::endl;

		if (collision) {
			text.setCharacterSize(48);
			text.setPosition(240, 250);
			text.setString("GAME OVER");
		}
		else {
			text.setString("Score: " + ss2.str());
			app.draw(pCar.spr);
		}
		app.draw(text);
		app.display();
		if (accelerate) {
            velocity -= 3;
            accelerate = false;
		}
	}
	return 0;
}
