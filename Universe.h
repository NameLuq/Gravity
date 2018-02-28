#ifndef UNIVERSE_H_
#define UNIVERSE_H_

#include "Object.h"
#include <vector>

class Universe
{
private:
	std::vector<Object*> objects;
	const double dt = 0.001;

public:
	Universe() = default;
	~Universe();

	void add(Object*);

	int getsize() {return objects.size();};
	//bool check(double, double);

	double getDistance(Object*, Object*);
	bool is_collapse(Object*, Object*, double);

	bool exist();

	void collapse(Object*, Object*);

	void updateObject(Object*, double, double);
	void setObject(Object*);
	Object* getObject(int);
};

#endif