#include <iostream>
#include <fstream>
#include "vec3.h";
#include "color.h";
#include "ray.h";


//Red Sphere
//sphere properties
const point3 sphereObjCenter = point3(0.0, 0.0, -1);
double sphereObjRadius = 0.5;

double hitSphere(const point3& center, double radius, const ray& r)
{
	// a = dot(b, b) , b = 2 * dot(b, A - C), c = dot( (A-C), (A-C) ) - radius*radius
	vec3 oc = r.origin() - center;
	double a = r.direction().lengthSquared();
	double bHalved = dot(r.direction(), oc);		
	double c = oc.lengthSquared() -radius * radius;
	double discriminant = bHalved * bHalved - 4 * a * c;	//from quadratic equation
	if (discriminant < 0)				// true -> the ray hits the ball, false -> does not
	{
		return -1.0;
	}
	else
	{
		return (-bHalved - sqrt(discriminant)) / (a);
	}				
}

color rayColor(const ray& r)
{
	double t = hitSphere(sphereObjCenter, sphereObjRadius, r);
	if (t > 0.0)
	{
		vec3 norm = unitVector(r.at(t) - vec3(0, 0, -1));
		return 0.5 * color(norm.x() + 1.0, norm.y() + 1.0, norm.z() + 1.0);
	}
	vec3 unitDirection = unitVector(r.direction());							//unitVector range [-1.0 ~ 1.0]
	t = 0.5 * (unitDirection.y() + 1.0);								//range [-1.0 ~ 1.0] -> [0.0 ~1.0]
	//return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);		//lerp(a,b,t) = a + (b - a)*t
	return color(1.0, 1.0, 1.0) + (color(0.5, 0.7, 1.0) - color(1.0, 1.0, 1.0)) * t;
}

int main() {
	//image 
	const double AspectRatio = 16.0 / 9.0;
	const int imageWidth = 400;
	const int imageHeight = static_cast<int>(static_cast<double>(imageWidth) / AspectRatio);

	//Camera view set up
	const double viewportHeight = 2.0;
	const double viewportWidth = viewportHeight * AspectRatio;
	const double focalLength = 1.0;

	point3 origin = point3(0.0, 0.0, 0.0);
	vec3 horizontal = vec3(viewportWidth, 0, 0);
	vec3 vertical = vec3(0, viewportHeight, 0);
	vec3 lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focalLength);

	//render
	std::ofstream  MyFile;
	MyFile.open("renderView.ppm");
	if (MyFile.is_open()) {

		MyFile << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

		for (int j = imageHeight - 1; j >= 0; --j) {
			for (int i = 0; i < imageWidth; ++i) {

				double u = double(i) / (static_cast<double>(imageWidth - 1));
				double v = double(j) / (static_cast<double>(imageHeight - 1));
				//^ simply makes pixel from range from 0 ~ 1
			
				ray r(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
				color pixelColor = rayColor(r);

				writeColor(MyFile, pixelColor);
			}
		}
	}

	MyFile.close();
	return 0;
}