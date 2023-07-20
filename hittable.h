#pragma once

#include "ray.h"

struct hitRecord {
	point3 p;
	vec3 normal;
	double t;
};

class hittable {
public:
	virtual bool hit(const ray& r, double t_min, double t_max, hitRecord& rec) const = 0;
};