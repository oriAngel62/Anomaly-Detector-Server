#ifndef STANDARDIO_H_
#define STANDARDIO_H_
#include <iostream>
#include <string.h>
#include "commands.h"

string read();
void write(string text);
void write(float f);
void read(float *f);

#endif /* STANDARDIO_H_ */