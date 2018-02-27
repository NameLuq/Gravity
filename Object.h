#ifndef OBJECT_H_
#define OBJECT_H_

class Object
{
public:
	Object(unsigned long int weight, unsigned long int radius, double x, double y,
	       double ax, double ay) :
		weight(weight), radius(radius), x(x), y(y), ax(ax), ay(ay),
		changed_ax(0), changed_ay(0) {};
	~Object() = default;

	unsigned long int weight;
	unsigned long int radius;
	double x, y, ax, ay, changed_ax, changed_ay;
};
#endif