#pragma once

#include <iostream>
#include "vec3.h";

void writeColor(std::ostream& out, color pixel_color)
{
	//Translate [0 ~ 1] into [0 ~ 255] rbg color format
	out << static_cast<int>(255.999 * pixel_color[0]) << ' '
		<< static_cast<int>(255.999 * pixel_color[1]) << ' '
		<< static_cast<int>(255.999 * pixel_color[2]) << '\n';

	//Trying to mimic
	//int ir = static_cast<int>(255.999 * r);
	//int ig = static_cast<int>(255.999 * g);
	//int ib = static_cast<int>(255.999 * b);
	//MyFile << ir << ' ' << ig << ' ' << ib << '\n';
}