#ifndef CUSTOMEXCEPTION_H
#define CUSTOMEXCEPTION_H
#include <exception>

class CustomException : std::exception
{
public:
    CustomException(const char* message);
    const char * what();
private:
    const char* m_message;
};

#endif // CUSTOMEXCEPTION_H
