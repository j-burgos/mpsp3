
#ifndef _CATEGORY_H
#define	_CATEGORY_H

#include <string>
#include <oslib/oslib.h>

using namespace std;
class Category {
public:
    Category();
    Category(string label, string imgpath);
    Category(const Category& orig);
    virtual ~Category();
    
    void SetLabel(string label);
    string GetLabel() const;
    void SetImgDisabled(OSL_IMAGE* imgDisabled);
    OSL_IMAGE* GetImgDisabled() const;
    void SetImgEnabled(OSL_IMAGE* imgEnabled);
    OSL_IMAGE* GetImgEnabled() const;
private:
    OSL_IMAGE* imgEnabled;
    OSL_IMAGE* imgDisabled;
    string label;
};

#endif	/* _CATEGORY_H */

