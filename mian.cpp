#include <iostream>
#include <fstream>
#include "vec3.h";
#include "color.h";
#include "ray.h";


color rayColor(const ray& r)
{
	vec3 unitDirection = unitVector(r.direction());
	double t = 0.5 * (unitDirection.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {
	//image 
	const double AspectRatio = 16.0 / 9.0;
	const int imageWidth = 400;
	const int imageHeight = static_cast<int>(static_cast<double>(imageWidth) / AspectRatio);

	//Camera view set up
	const double viewportHeight = 2.0;
	const double viewportWidth = 2.0 * AspectRatio;
	const double focalLength = 1.0;

	point3 origin = point3(0.0, 0.0, 0.0);
	vec3 horizontal = vec3(viewportHeight, 0, 0);
	vec3 vertical = vec3(0, viewportWidth, 0);
	vec3 lowerLeftCorver = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focalLength);

	//render
	std::ofstream  MyFile;
	MyFile.open("file.txt");
	if (MyFile.is_open()) {

		MyFile << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

		for (int j = imageWidth - 1; j >= 0; --j) {
			for (int i = 0; i < imageHeight; ++i) {

				double u = double(i) / (static_cast<double>(imageWidth - 1));
				double v = double(j) / (static_cast<double>(imageHeight - 1));
			
				ray r(origin, lowerLeftCorver + u * horizontal + v * vertical - origin);
				color pixelColor = rayColor(r);

				writeColor(MyFile, pixelColor);
			}
		}
	}

	MyFile.close();
	return 0;
}