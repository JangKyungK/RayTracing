#include <iostream>
#include <fstream>
#include "vec3.h";
#include "color.h";
#include "ray.h";

int main() {
	//image 

	const int imageWidth = 256;
	const int imageHeight = 256;

	//render

	std::ofstream  MyFile;
	MyFile.open("file.txt");
	if (MyFile.is_open()) {

		MyFile << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

		for (int j = imageWidth - 1; j >= 0; --j) {
			for (int i = 0; i < imageHeight; ++i) {

				//double r = double(i) / (static_cast<double>(imageWidth - 1));
				//double g = double(j) / (static_cast<double>(imageHeight - 1));
				//double b = 0.25;
				// Repaced by the below constructor
				color pixel_color((double(i) / (static_cast<double>(imageWidth - 1))), (double(j) / (static_cast<double>(imageHeight - 1))), 0.25);
				
				/*int ir = static_cast<int>(255.999 * r);
				int ig = static_cast<int>(255.999 * g);
				int ib = static_cast<int>(255.999 * b);*/
				//MyFile << ir << ' ' << ig << ' ' << ib << '\n';
				// Repaced by the below function

				write_color(MyFile, pixel_color);
			}
		}
	}

	MyFile.close();

	return 0;
}