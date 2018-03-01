#include "Universe.h"
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

void Universe::Left() {
	for (auto a : objects)
		a->x += 1.0;
}

void Universe::Right() {
	for (auto a : objects)
		a->x -= 1.0;
}

void Universe::Up() {
	for (auto a : objects)
		a->y -= 1.0;
}

void Universe::Down() {
	for (auto a : objects)
		a->y += 1.0;
}

void Universe::clear() {
	for (auto a : objects)
		delete a;
}

Universe::~Universe() {
	for (auto a : objects)
		delete a;
}

void Universe::add(Object* newobj) {
	objects.push_back(newobj);
}

double Universe::getDistance(Object* A, Object* B) {
	return sqrt(pow((A->x - B->x), 2) + pow((A->y - B->y), 2));
}

bool Universe::is_collapse(Object* A, Object* B, double r) {
	return  ((A->radius + B->radius) - r >= 0);
}

void Universe::updateObject(Object* A, double ch_ax, double ch_ay) {
	A->changed_ax += ch_ax;
	A->changed_ay += ch_ay;
}

void Universe::setObject(Object* A) {
	A->ax += A->changed_ax;
	A->ay += A->changed_ay;
	A->x += A->ax;
	A->y += A->ay;
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
	auto e = objects.end();

	while (i < e - 1 && objects.size() > 0) {

		auto j = i + 1;
		while (j < e) {

			double r = getDistance(*i, *j);
			if (r - 0.0 < 0.000001) {
				cout << "divinition to zero!" << endl;
				return false;
			}

			if (!is_collapse(*i, *j, r)) {

				//FOR I
				double a1 = (*j)->weight / pow(r, 2);

				double ch_ax1 = a1 * ((*j)->x - (*i)->x) / r;///cos
				double ch_ay1 = a1 * ((*j)->y - (*i)->y) / r;///sin

				updateObject(*i, ch_ax1, ch_ay1);

				//FOR J

				double a2 = (*i)->weight / pow(r, 2);
				double ch_ax2 = a2 * ((*i)->x - (*j)->x) / r;///cos
				double ch_ay2 = a2 * ((*i)->y - (*j)->y) / r;///sin

				updateObject(*j, ch_ax2, ch_ay2);

			}
			else {
				/*if ((*i)->weight * sqrt((*i)->ax * (*i)->ax + (*i)->ay * (*i)->ay)
				        - (*j)->weight * sqrt((*j)->ax * (*j)->ax + (*j)->ay * (*j)->ay) > 0.0001) {
					this->collapse(*j, *i);
					objects.erase(i);
				} else {
					this->collapse(*i, *j);
					objects.erase(j);
				}
				e = objects.end();*/
			}
			++j;
		}
		setObject(*i);
		++i;
	}

	if (i < e - 1 && objects.size() > 0) {
		auto l = objects.end() - 1;/////last object
		setObject(*l);
	}

	for (auto q : objects) {
		q->changed_ax = 0; q->changed_ay = 0;//////deleting makes it too fast
	}

	return true;
}