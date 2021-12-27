

/*
 * CLI.h
 *
 * Author: Ori Angel 314617739
 */
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
	vector<Command *> commands;

public:
	CLI(DefaultIO *dio);
	void start();
	virtual ~CLI();
	void printMenu();
	void readCsv();
};

#endif /* CLI_H_ */
