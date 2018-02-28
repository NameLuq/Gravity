#include "Universe.h"
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

Universe::~Universe() {
	for (auto a : objects)
		delete a;
}

/*bool Universe::check(double a, double b) {
	for (auto i : objects)
		if (a - i->x < 0.001 && b - i->y < 0.001)
			return false;
	return true;
}*/

void Universe::add(Object* newobj) {
	objects.push_back(newobj);
}

double Universe::getDistance(Object* A, Object* B) {
	return sqrt(pow((A->x - B->x), 2) + pow((A->y - B->y), 2));
}

bool Universe::is_collapse(Object* A, Object* B, double r) {
	return  ((A->radius + B->radius) * (1 + dt) - r >= 0);
}

void Universe::updateObject(Object* A, double ch_ax, double ch_ay) {

	A->changed_ax += ch_ax;
	A->changed_ay += ch_ay;
}

void Universe::setObject(Object* A) {
	A->ax += A->changed_ax;
	A->ay += A->changed_ay;

	A->x += A->ax * dt * dt * 3 / 2;
	A->y += A->ay * dt * dt * 3 / 2;
}

Object* Universe::getObject(int i) {
	return objects[i];
}

void Universe::collapse(Object* A, Object* B) {
	A->ax = (A->ax * A->weight + B->ax * B->weight) / (A->weight + B->weight);
	A->ay = (A->ay * A->weight + B->ay * B->weight) / (A->weight + B->weight);
}

bool Universe::exist() {

	auto i = objects.begin();

	while (i < objects.end() - 1) {

		auto j = i + 1;
		while (j < objects.end()) {

			double r = getDistance(*i, *j);
			if (r - 0.0 < 0.000001) {
				cout << "divinition to zero!" << endl;
				return false;
			}
			//cout << "distance " << setprecision(6) << r << endl;

			if (!is_collapse(*i, *j, r)) {

				//FOR I
				double a1 = (*j)->weight / pow(r, 2);

				double ch_ax1 = a1 * (abs((*j)->x - (*i)->x)) / r;///cos
				double ch_ay1 = a1 * (abs((*j)->y - (*i)->y)) / r;///sin
				int sing_x = 1;
				int sing_y = 1;
				if ((*i)->x - (*j)->x > 0)
					sing_x = -1;
				if ((*i)->y - (*j)->y > 0)
					sing_y = -1;

				//cout << "acceleration1 " << setprecision (6) << ch_ax1*sing_x << ' ' <<  ch_ay1*sing_y << endl;

				updateObject(*i, ch_ax1 * sing_x, ch_ay1 * sing_y);

				//FOR J
				sing_x *= -1;
				sing_y *= -1;

				double a2 = (*i)->weight / pow(r, 2);
				double ch_ax2 = a2 * (abs((*j)->x - (*i)->x)) / r;///cos
				double ch_ay2 = a2 * (abs((*j)->y - (*i)->y)) / r;///sin

				//cout << "acceleration2 " << setprecision (6) << ch_ax2*sing_x << ' ' <<  ch_ay2*sing_y << endl;

				updateObject(*j, ch_ax2 * sing_x, ch_ay2 * sing_y);

			}
			else {
				if ((*i)->weight * sqrt((*i)->ax * (*i)->ax + (*i)->ay * (*i)->ay)
				        > (*j)->weight * sqrt((*j)->ax * (*j)->ax + (*j)->ay * (*j)->ay)) {
					this->collapse(*j, *i);
					objects.erase(j);
				} else {
					this->collapse(*i, *j);
					objects.erase(i);
				}

			}
			++j;
		}

		setObject(*i);
		++i;
	}

	auto e = objects.end() - 1;/////last object
	setObject(*e);

	for (auto q : objects) {
		/*cout << "coord " << setprecision (6) << ' ' << q->x <<
		' ' << setprecision (6) << q->y << endl;*/
		q->changed_ax = 0; q->changed_ay = 0;//////deleting makes it too fast
	}

	return true;
}