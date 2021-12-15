
/*
 * minCircle.cpp
 *
 * Author: Ori Angel 314617739
 */
#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h> /* srand, rand */
#include <time.h>	/* time */
#include "anomaly_detection_util.h"

using namespace std;

// ------------ DO NOT CHANGE -----------

class Circle
{
public:
	Point center;
	float radius;
	Circle(Point c, float r) : center(c), radius(r) {}
};
// --------------------------------------

Circle findMinCircle(Point **points, size_t size);

// you can add here additional methods

#endif /* MINCIRCLE_H_ */

// Function to return the euclidean distance
// between two points
float distance(const Point &a, const Point &b);

// Function to check whether a point lies inside
// or on the boundaries of the circle
bool is_inside(const Circle &c, const Point &p);

// Helper method to get a circle defined by 3 points
Point get_circle_center(float bx, float by,
						float cx, float cy);

// Function to return a unique circle that intersects
// three points
Circle circle_from(const Point &A, const Point &B,
				   const Point &C);
// Function to return the smallest circle
// that intersects 2 points
Circle circle_from(const Point &A, const Point &B);

// Function to check whether a circle encloses the given points
bool is_valid_circle(const Circle &c, const vector<Point> &P);

// Function to return the minimum enclosing
// circle for N <= 3
Circle min_circle_trivial(vector<Point> &P);

// n represents the number of points in P
// that are not yet processed.
Circle finalCircleHelper(vector<Point> &P,
						 vector<Point> R, int n);

Circle finalCircle(const vector<Point> &P);