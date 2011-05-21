

#ifndef _EXCEPTION_H
#define	_EXCEPTION_H

#include <string>

using namespace std;
class AppException {
public:
    AppException();
    AppException(string name, string message);
    AppException(const AppException& orig);
    virtual ~AppException();
    void SetMessage(string message);
    string GetMessage() const;
    void SetName(string name);
    string GetName() const;
private:
    string name;
    string message;
};

#endif	/* _EXCEPTION_H */

