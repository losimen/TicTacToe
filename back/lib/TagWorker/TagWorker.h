#include <Arduino.h>


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