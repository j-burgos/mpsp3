
#include "Category.h"

Category::Category(){

}

Category::Category(string label, string imgpath) {
    int location = OSL_IN_RAM|OSL_SWIZZLED;
    int pxlfmt = OSL_PF_8888;
    this->label = label;
    this->imgDisabled = oslLoadImageFilePNG((char*)(imgpath+"normal.png").c_str(),location,pxlfmt);
    this->imgEnabled = oslLoadImageFilePNG((char*)(imgpath+"selected.png").c_str(),location,pxlfmt);
}

Category::Category(const Category& orig) {
}

Category::~Category() {
}
void Category::SetLabel(string label) {
    this->label = label;
}
string Category::GetLabel() const {
    return label;
}
void Category::SetImgDisabled(OSL_IMAGE* imgDisabled) {
    this->imgDisabled = imgDisabled;
}
OSL_IMAGE* Category::GetImgDisabled() const {
    return imgDisabled;
}
void Category::SetImgEnabled(OSL_IMAGE* imgEnabled) {
    this->imgEnabled = imgEnabled;
}
OSL_IMAGE* Category::GetImgEnabled() const {
    return imgEnabled;
}

