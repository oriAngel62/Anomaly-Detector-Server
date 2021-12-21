

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO
{
public:
	virtual string read() = 0;
	virtual void write(string text) = 0;
	virtual void write(float f) = 0;
	virtual void read(float *f) = 0;
	// virtual void read(int fromLine,int toLine)=0;
	virtual void close() = 0;
	virtual ~DefaultIO() {}

	// you may add additional methods here
};

// you may add here helper classes

// you may edit this class
class Command
{
	DefaultIO *dio;

public:
	Command(DefaultIO *dio) : dio(dio) {}
	virtual void execute() = 0;
	virtual ~Command() {}
};

// implement here your command classes

class upload_command : public Command
{
public:
	DefaultIO *dio;
	upload_command(DefaultIO *dio) : Command(dio)
	{
		this->dio = dio;
	};

	virtual ~upload_command();
	virtual void execute();
};

class get_set_treshold : public Command
{
public:
	DefaultIO *dio;
	get_set_treshold(DefaultIO *dio) : Command(dio)
	{
		this->dio = dio;
	};

	virtual ~upload_command();
	virtual void execute();
};

#endif /* COMMANDS_H_ */
