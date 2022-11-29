#pragma once
#include <math.h>
#include <iostream>
void normalize(float v[])
{
	float d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (d == 0.0)
	{
		std::cout << "zero length vector" << std::endl;
		//exit(1);
	}

	for (int i = 0; i < 3; i++)
		v[i] /= d;
}

void normCrossProduct(float v[], float w[], float vout[])
{
	vout[0] = v[1] * w[2] - w[1] * v[2];
	vout[1] = v[2] * w[0] - w[2] * v[0];
	vout[2] = v[0] * w[1] - w[0] * v[1];

	normalize(vout);
}

void normalVector(float v1[], float v2[], float v3[], float vnormal[])
{
	float va[3], vb[3];
	for (int i = 0; i < 3; i++)
	{
		va[i] = v1[i] - v2[i];
		vb[i] = v2[i] - v3[i];
	}
	normCrossProduct(va, vb, vnormal);
}