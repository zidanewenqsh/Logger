#include <iostream>
#include "Logger.h"
int main () {
    Logger logger;
    logger.SetLevel(LogLevel::DEBUG);
    LOGDEBUG("This is Debug");
    LOGINFO("This is Info");
    LOGWARNING("This is Warning");
    LOGERROR("This is Error");
    LOGFATAL("This is Fatal");
    return 0;
}