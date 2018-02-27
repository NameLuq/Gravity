#ifndef UNIVERSE_H_
#define UNIVERSE_H_

#include "Object.h"
#include <vector>

class Universe
{
private:
	std::vector<Object*> objects;
	const double dt = 0.003;

public:
	Universe() = default;
	~Universe() = default;

	void add(Object*);

	double getDistance(Object*, Object*);
	bool is_collapse(Object*, Object*, double);

	bool exist();

	void updateObject(Object*, double, double);
	void setObject(Object*);
	Object* getObject(int);
};

#endif