#include <Arduino.h>

#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>

class TagWorker 
{
private:
    String content;

public:
    TagWorker(const String &content)
    {
        this->content = content;
    }

    String getKeyValue(String key)
    {
        return key + " | " + content;
    }
};