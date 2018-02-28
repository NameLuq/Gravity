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
	int N = 500;
	for (int rr = 0; rr < N; ++rr) {
		unsigned long int m = (rand() % 4 + 1) * 1000000;
		int r = m / 1000000;

		double x = (double)((2 * ((2 * rand()) / RAND_MAX) - 1) * (rand() % 390));
		double y = (double)((2 * ((2 * rand()) / RAND_MAX) - 1) * (rand() % 290));

		double ax = (double)((2 * ((2 * rand()) / RAND_MAX) - 1) *
		                     (((2 * rand()) / RAND_MAX) - 1) * (rand() % 3999000 + 1000));
		double ay = (double)((2 * ((2 * rand()) / RAND_MAX) - 1) *
		                     (((2 * rand()) / RAND_MAX) - 1) * (rand() % 3999000 + 1000));
		Object* obj = new Object(m, r, x, y, ax, ay);
		uni.add(obj);
	}

	/*Object* sun = new Object(50000, 20, 0.0, 0.0, 0.0, 0.0);

	Object* earth = new Object(1, 5, 0.0, 100.0, -6000.0 , -2000.0);

	Object* nibiru = new Object(1, 3, 0.0, -50.0, 8000.0, 2000.0);

	Object* planet228 = new Object(1, 7, 150.0, 0.0, -2000.0, 4000.0);

	Object* planet1 = new Object(1, 4, 75.0, 0.0, -1500.0, 6000.0);
	uni.add(sun);
	uni.add(earth);
	uni.add(nibiru);
	uni.add(planet228);
	uni.add(planet1);*/

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
			float f = (float)obj->radius;

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
			window.clear();
	}

	cout << "BOOOM";

	return 0;
}
