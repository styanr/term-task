#include "customexception.h"

CustomException::CustomException(const char* message) : m_message(message) {}

const char* CustomException::what() { return m_message; }
