

#ifndef CLI_H_
#define CLI_H_

// #include <string.h>
// #include <iostream>
#include "commands.h"
#include <memory>
using namespace std;

class CLI
{
	DefaultIO *dio;
	HybridAnomalyDetector *sharedAnomalyDetector;
	//  this->sharedAnomalyDetector(new HybridAnomalyDetector());

	vector<Command *> commands;
	// you can add data members
public:
	CLI(DefaultIO *dio);
	void start();
	virtual ~CLI();
	void printMenu();
	void readCsv();
};

#endif /* CLI_H_ */
