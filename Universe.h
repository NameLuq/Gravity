#ifndef UNIVERSE_H_
#define UNIVERSE_H_

#include "Object.h"
#include <vector>

class Universe
{
private:
	std::vector<Object*> objects;

public:
	Universe() = default;
	~Universe();

	void add(Object*);

	int getsize() {return objects.size();};

	double getDistance(Object*, Object*);
	bool is_collapse(Object*, Object*, double);

	bool exist();

	void collapse(Object*, Object*);

	void updateObject(Object*, double, double);
	void setObject(Object*);
	Object* getObject(int);

	void Left();
	void Right();
	void Up();
	void Down();

	void clear();
};

#endif