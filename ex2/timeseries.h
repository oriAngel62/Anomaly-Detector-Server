

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

using namespace std;
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <iterator>

class TimeSeries
{

public:
	map<string, vector<float>> csv;
	vector<string> columnNames;
	int numOfColumn = 1;

	TimeSeries(const char *CSVfileName)
	{
		// File pointer
		fstream f;
		// Open an existing file
		f.open(CSVfileName, ios::in);

		string line;
		//first line insert feature
		while (getline(f, line), ',')
		{
			vector<float> fetureVector;
			csv.insert({line, fetureVector});
			columnNames.push_back(line);
		}

		while (!f.eof())
		{
			map<string, vector<float>>::iterator it = csv.begin();
			while (getline(f, line), ',')
			{
				it->second.push_back(std::stof(line));
				if (numOfColumn == csv.size())
				{
					numOfColumn = 1;
					it = csv.begin();
				}
				else
				{
					numOfColumn++;
					it++;
				}
			}
		}
	}

	float getValFromCSV(int i, int j)
	{
		int findI = 0;
		int findJ = 0;
		map<string, vector<float>>::iterator mapItr;
		for (mapItr = csv.begin(); mapItr != csv.end(); ++mapItr)
		{
			if (findI == i)
			{
				vector<float> v = mapItr->second;
				vector<float>::iterator vecItr;
				for (vecItr = v.begin(); vecItr != v.end(); ++vecItr)
				{
					if (findJ == j)
					{
						return *vecItr;
					}
					findJ;
				}
			}
			findI++;
		}
	}
};

#endif /* TIMESERIES_H_ */
