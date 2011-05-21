
#include "AppException.h"

AppException::AppException() {
}
AppException::AppException(string name, string message){
    this->name = name;
    this->message = message;
}
AppException::AppException(const AppException& orig) {
}

AppException::~AppException() {
}
void AppException::SetMessage(string message) {
    this->message = message;
}
string AppException::GetMessage() const {
    return message;
}
void AppException::SetName(string name) {
    this->name = name;
}
string AppException::GetName() const {
    return name;
}

