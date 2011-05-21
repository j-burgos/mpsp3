
#ifndef _MENU_H
#define	_MENU_H

#include <string>

#include "List.cpp"

using namespace std;

template <class T>
class Menu: public List<T> {
public:
    Menu();
    Menu(int x, int y, int itemw, int itemh, int viewableItems, int selected=0);
    Menu(const Menu& orig);
    virtual ~Menu();
    void SetItemHeight(int itemHeight);
    int GetItemHeight() const;
    void SetItemWidth(int itemWidth);
    int GetItemWidth() const;
    void SetViewableItems(int viewableItems);
    int GetViewableItems() const;
    void SetSelected(int selected);
    int GetSelected() const;
    void SetY(int y);
    int GetY() const;
    void SetX(int x);
    int GetX() const;

    void NextOption();
    void PreviousOption();
    void Reset();

private:
    int x, y;
    int selected;
    int viewableItems;
    int itemWidth, itemHeight;
};


template <class T>
Menu<T>::Menu() {
}

template <class T>
Menu<T>::Menu(int x, int y, int itemw, int itemh, int viewableItems, int selected)
    :List<T>(){
    this->x = x;
    this->y = y;
    this->itemWidth = itemw;
    this->itemHeight = itemh;
    this->selected = selected;
    this->viewableItems = viewableItems;
}
template <class T>
Menu<T>::Menu(const Menu& orig) {
}

template <class T>
Menu<T>::~Menu() {
}
template <class T>
void Menu<T>::SetItemHeight(int itemHeight) {
    this->itemHeight = itemHeight;
}
template <class T>
int Menu<T>::GetItemHeight() const {
    return itemHeight;
}
template <class T>
void Menu<T>::SetItemWidth(int itemWidth) {
    this->itemWidth = itemWidth;
}
template <class T>
int Menu<T>::GetItemWidth() const {
    return itemWidth;
}
template <class T>
void Menu<T>::SetViewableItems(int viewableItems) {
    this->viewableItems = viewableItems;
}
template <class T>
int Menu<T>::GetViewableItems() const {
    return viewableItems;
}
template <class T>
void Menu<T>::SetSelected(int selected) {
    this->selected = selected;
}
template <class T>
int Menu<T>::GetSelected() const {
    return selected;
}
template <class T>
void Menu<T>::SetY(int y) {
    this->y = y;
}
template <class T>
int Menu<T>::GetY() const {
    return y;
}
template <class T>
void Menu<T>::SetX(int x) {
    this->x = x;
}
template <class T>
int Menu<T>::GetX() const {
    return x;
}

template <class T>
void Menu<T>::PreviousOption(){
    if(this->selected > 0){
        this->selected = this->selected - 1;
    }
}
template <class T>
void Menu<T>::NextOption(){
    if(this->selected < this->size() - 1){
        this->selected = this->selected + 1;
    }
}
template <class T>
void Menu<T>::Reset(){
    this->selected = 0;
}

#endif	/* _MENU_H */