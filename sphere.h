#pragma once

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:

	sphere()
		: center(point3(0.0, 0.0, 0.0)), radius(1.0)
	{
	};

	sphere(point3 cen, double r)
		: center(cen), radius(r)
	{
	};

	virtual bool hit(const ray& r, double t_min, double t_max, hitRecord& rec) const override;

public:
	point3 center;
	double radius;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hitRecord& rec) const
{
	vec3 oc = r.origin() - center;

	double a = r.direction().lengthSquared();
	double bHalved = dot(r.direction(), oc);
	double c = oc.lengthSquared() - radius * radius;

	double discriminant = bHalved * bHalved - a * c;	//from quadratic equation

	if (discriminant < 0) return false;				// true -> the ray hits the ball, false -> does not
	double sqrtd = sqrt(discriminant);

	//first Find the root that is further away -> hence - sqrt(discriminant)
	double root = (-bHalved - sqrt(discriminant)) / (a);

	if (t_min > root || t_max < root)
	{
		// finding closest 
		root = (-bHalved + sqrt(discriminant)) / (a);
		//If outside of the acceptable range -> return false
		if (t_min > root || t_max < root)
			return false;
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	rec.normal = (rec.p - center) / radius;

	return true;
}