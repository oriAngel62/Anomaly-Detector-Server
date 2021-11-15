
#include "SimpleAnomalyDetector.h"
#include <stdlib.h>

SimpleAnomalyDetector::SimpleAnomalyDetector()
{
	// TODO Auto-generated constructor stub
}

SimpleAnomalyDetector::~SimpleAnomalyDetector()
{
	// TODO Auto-generated destructor stub
	// delete cf;
	// ~TimeSeriesAnomalyDetector();
}

void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts)
{
	// TODO Auto-generated destructor stub
	map<string, vector<float>> csv = ts.csv;
	map<string, vector<float>>::iterator mapItrI;
	for (mapItrI = csv.begin(); mapItrI != csv.end(); ++mapItrI)
	{
		// m=coorealtion => suppose to be above 0.9?
		int m = 0.9;
		int c = -1;
		// float p=0;
		map<string, vector<float>>::iterator mapItrJ;

		for (mapItrJ = next(mapItrI, 1); mapItrI != csv.end(); ++mapItrI)
		{
			vector<float> vI = mapItrI->second;
			vector<float> vJ = mapItrJ->second;
			float p = abs(pearson(&vI[0], &vJ[0], vI.size()));
			if (p > m)
			{
				m = p;
				//c is diffrent then -1
				c = 0;
			}
		}
		//there is correlation
		if (c != -1)
		{
			vector<float> vI = mapItrI->second;
			vector<float> vJ = mapItrJ->second;
			Point **points;
			// vector<*point> points;

			vector<float>::iterator vecItrX;
			vector<float>::iterator vecItrY;
			int i = 0;
			for (vecItrX = vI.begin(); vecItrX != vI.end(); ++vecItrX)
			{
				// Point p = Point(*vecItrX, *vecItrY);
				points[i]->x = *vecItrX;
				points[i]->y = *vecItrY;
				// m[i] = p;
				vecItrY++;
				i++;
			}
			//make the struct
			Line line = linear_reg(points, mapItrI->second.size());
			string s1 = mapItrI->first;
			string s2 = mapItrJ->first;
			//threshold
			float maxThreshold = 0;
			for (int i = 0; i < mapItrI->second.size(); i++)
			{
				int num = dev(*points[i], line);
				if (maxThreshold < num)
				{
					maxThreshold = num;
				}
			}
			correlatedFeatures c1;
			c1.feature1 = s1;
			c1.feature2 = s2;
			c1.lin_reg = line;
			c1.threshold = maxThreshold * 1.1;
			// correlatedFeatures c1(s1, s2, m, l, t * 1.1);
			cf.push_back(correlatedFeatures(c1));
		}
	}

	// 	FOR 𝑖 ← 1 TO 𝑁
	// 𝑚 ← 0 , 𝑐 ← (−1)
	// FOR 𝑗 ← 𝑖 + 1 TO 𝑁
	// IF (𝜌 ← |𝑝𝑒𝑎𝑟𝑠𝑜𝑛(𝑓𝑖
	// , 𝑓𝑗)|) > 𝑚 THEN 𝑚 ← 𝜌 , 𝑐 ← 𝑗
	// IF 𝑐 ≠ (−1) THEN associate 𝑓𝑖 and 𝑓𝑗 as correlated features
}

// float findThreshold(Point **points)
// {

// 	float maxThreshold = 0;
// 	for ()
// }

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts)
{
	// TODO Auto-generated destructor stub
}
