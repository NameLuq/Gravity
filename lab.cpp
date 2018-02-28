#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Universe.h"
using namespace std;

int main(int argv, char** args) {

	srand(time(NULL));

	Universe uni;
	int N = 100;
	for (int rr = 0; rr < N; ++rr) {
		int m = (rand() % 4 + 1) * 1000000;
		int r = m / 1000000;

		float x = (float)((2 * ((2 * rand()) / RAND_MAX) - 1) * (rand() % 390));
		float y = (float)((2 * ((2 * rand()) / RAND_MAX) - 1) * (rand() % 290));
		//while (!uni.check(x, y)) {
		//	x = (float)((2 * ((2 * rand()) / RAND_MAX) - 1) * (rand() % 390));
		//	y = (float)((2 * ((2 * rand()) / RAND_MAX) - 1) * (rand() % 290));
		//}

		float ax = (float)((2 * ((2 * rand()) / RAND_MAX) - 1) *
		                   (((2 * rand()) / RAND_MAX) - 1) * (rand() % 3999000 + 1000));
		float ay = (float)((2 * ((2 * rand()) / RAND_MAX) - 1) *
		                   (((2 * rand()) / RAND_MAX) - 1) * (rand() % 3999000 + 1000));
		Object* obj = new Object(m, r, x, y, ax, ay);
		uni.add(obj);
	}

	/*Object* obj = new Object(1000000, 10, 0.0, 0.0, 0.0, 0.0);
	uni.add(obj);
	Object* obj2 = new Object(200000, 2, 100.0, 0.0, -100000.0, 0.0);
	uni.add(obj2);
	Object* obj3 = new Object(20000, 3, -100.0, 0.0, 0.0, 100000.0);
	uni.add(obj3);
	Object* obj4 = new Object(2000000, 5, 300.0, -200.0, -15000.0, 5000.0);
	uni.add(obj4);*/

	sf::RenderWindow window(sf::VideoMode(800, 600), "Gravity");
	window.setFramerateLimit(60);

	int gg = 0;
	while (window.isOpen())
	{
		N = uni.getsize();
		gg = 1 + gg % 1000;

		uni.exist();

		sf::CircleShape shape(1, 1);

		for (int i = 0; i < N; ++i) {

			Object* obj = uni.getObject(i);
			float f = obj->radius / 1.0;

			shape.setRadius(f);
			shape.setPointCount(100);

			if (obj->radius == 1)
				shape.setFillColor(sf::Color::Red);
			else if (obj->radius == 2)
				shape.setFillColor(sf::Color::Green);
			else if (obj->radius == 3)
				shape.setFillColor(sf::Color::Blue);
			else
				shape.setFillColor(sf::Color::Cyan);

			shape.setPosition(400 - f + obj->x, 300 - f - obj->y);

			window.draw(shape);
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.display();
		if (gg % 7 == 0)
			window.clear(sf::Color(0, 0, 0, 1));
	}

	cout << "BOOOM";

	return 0;
}
