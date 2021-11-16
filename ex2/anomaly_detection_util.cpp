/*
 * animaly_detection_util.cpp
 *
 * Author: write your ID and name here
 */

#include <math.h>
#include "anomaly_detection_util.h"

float avg(float *x, int size)
{
	float avg = 0;
	for (int i = 0; i < size; i++)
	{
		avg += x[i];
	}
	return avg / size;
}

// returns the variance of X and Y
float var(float *x, int size)
{
	float summ = 0;
	float avrage = avg(x, size);
	for (int i = 0; i < size; i++)
	{
		summ += x[i] * x[i];
	}
	summ = summ / size;
	return (summ - avrage * avrage);
}

// returns the covariance of X and Y
float cov(float *x, float *y, int size)
{
	float summ = 0;
	float avgX = avg(x, size);
	float avgY = avg(y, size);
	for (int i = 0; i < size; i++)
	{
		summ += (x[i] - avgX) * (y[i] - avgY);
	}
	return summ / size;
}

// returns the Pearson correlation coefficient of X and Y
float pearson(float *x, float *y, int size)
{
	float varX, varY, covOfXY;
	varX = var(x, size);
	varY = var(y, size);
	covOfXY = cov(x, y, size);
	return covOfXY / (sqrt(varX) * sqrt(varY));
}

// performs a linear regression and returns the line equation
Line linear_reg(Point **points, int size)
{

	float a, b, corolation;
	float xArray[size];
	float yArray[size];
	for (int i = 0; i < size; i++)
	{
		xArray[i] = (*points)[i].x;
		yArray[i] = (*points)[i].y;
	}
	corolation = pearson(xArray, yArray, size);
	if (corolation == 0)
	{
		// std::cout << "no corolation!";
		Line l = Line();
		return l;
	}
	a = cov(xArray, yArray, size) / var(xArray, size);
	b = avg(yArray, size) - a * avg(xArray, size);
	return Line(a, b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p, Point **points, int size)
{
	float distance;
	Line line = linear_reg(points, size);
	if (line.f(1) == line.f(-1) && line.f(1) == 0)
	{
		// std::cout << "no corolation!";
		exit(-1);
	}
	distance = p.y - line.f(p.x);
	if (distance < 0)
	{
		distance *= -1;
	}
	return distance;
}

// returns the deviation between point p and the line
float dev(Point p, Line l)
{
	float distance;
	distance = p.y - l.f(p.x);
	if (distance < 0)
	{
		distance *= -1;
	}
	return distance;
}
