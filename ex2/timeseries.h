

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

using namespace std;
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <iterator>
#include "anomaly_detection_util.h"

class TimeSeries
{

public:
	map<string, vector<float>> csv;
	vector<string> columnNames;
	// int numOfColumn = 1;

	vector<string> split(string line, string delimiter)
	{
		vector<string> list;
		size_t pos = 0;
		string token;
		while ((pos = line.find(delimiter)) != string::npos)
		{
			token = line.substr(0, pos);
			list.push_back(token);
			line.erase(0, pos + delimiter.length());
		}
		list.push_back(line);
		return list;
	}

	TimeSeries(const char *CSVfileName)
	{
		// File pointer
		fstream f;
		// Open an existing file
		f.open(CSVfileName, ios::in);

		//first line
		string line;
		getline(f, line);
		columnNames = split(line, ",");				 //first line insert feature
		for (int i = 0; i < columnNames.size(); i++) //initialized map
		{
			vector<float> fetureVector;
			csv.insert({columnNames[i], fetureVector});
		}
		//rest of the file
		map<string, vector<float>>::iterator it = csv.begin();
		while (getline(f, line))
		{
			// getline(f, line);
			vector<string> listOfLine;
			listOfLine = split(line, ",");
			for (int i = 1; i <= columnNames.size(); i++)
			{
				it->second.push_back(std::stof(listOfLine[i - 1]));
				if (i == columnNames.size())
					it = csv.begin();
				else
					it++;
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
					findJ++;
				}
			}
			findI++;
		}
		//didnt find place in map
		return 999;
	}
	// map<string, vector<float>> getMap()
	// {
	// 	return csv;
	// }
	// vector<string> getCloumnsNames()
	// {
	// 	return columnNames;
	// }
	// const int getNumOfCloumns()
	// {
	// 	return columnNames.size();
	// }
};

#endif /* TIMESERIES_H_ */
