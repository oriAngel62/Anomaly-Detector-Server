#ifndef UPLOAD_COMMAND_H_
#define UPLOAD_COMMAND_H_

#include "commands.h"

class upload_command : public Command
{
    DefaultIO *dio;

public:
    upload_command(DefaultIO *dio) : dio(dio) {}
    virtual ~upload_command();
    virtual void execute();
};

#endif /*  UPLOAD_COMMAND_H_ */