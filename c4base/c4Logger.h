#ifndef c4Logger_H
#define c4Logger_H 1

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "FairLogger.h"

// CEJ: removing line number and function brackets
// may change again or completely revert

class c4Logger;

class c4Logger : public FairLogger
{
  public:
#define c4LOG(severity, x)                                                                                             \
    do                                                                                                                 \
    {                                                                                                                  \
        if (true)                                                                                                      \
        {                                                                                                              \
            std::string fileName(__FILE__);                                                                            \
            fileName = fileName.substr(fileName.find_last_of("/") + 1);                                                \
            size_t lastDotPos = fileName.find_last_of(".");                                                            \
            if (lastDotPos != std::string::npos) { fileName = fileName.substr(0, lastDotPos); }                        \
            std::stringstream ss;                                                                                      \
            ss << fileName.substr(fileName.find_last_of("/") + 1) << ":" << __FUNCTION__ << " ";                       \
            LOG(severity) << ss.str() << x;                                                                            \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
        }                                                                                                              \
    }                                                                                                                  \
    while (false)

#define c4LOG_IF(severity, condition, x)                                                                          \
    do                                                                                                            \
    {                                                                                                             \
        if (true)                                                                                                 \
        {                                                                                                         \
            std::string fileNameif(__FILE__);                                                                     \
            fileNameif = fileNameif.substr(fileNameif.find_last_of("/") + 1);                                                \
            size_t lastDotPos = fileNameif.find_last_of(".");                                                            \
            if (lastDotPos != std::string::npos) { fileNameif = fileNameif.substr(0, lastDotPos); }                        \
            std::stringstream ssif;                                                                               \
            ssif << fileNameif.substr(fileNameif.find_last_of("/") + 1) << ":" << __FUNCTION__ << " ";            \
            LOG_IF(severity, condition) << ssif.str() << x;                                                       \
        }                                                                                                         \
        else                                                                                                      \
        {                                                                                                         \
        }                                                                                                         \
    }                                                                                                             \
    while (false)

  private:
    c4Logger();
    ~c4Logger();

  public:
    ClassDefOverride(c4Logger, 0)
};

#endif // c4Logger_H
