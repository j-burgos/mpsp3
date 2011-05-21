
#ifndef __SPK_LIST__

#define __SPK_LIST__

#include <stdlib.h>

using namespace std;

template <class T>
struct Node{
	T item;
	struct Node<T> *next;
	
	Node(T *item, Node<T> *next){
		this->item = *item;
		this->next = next;
	}
};

template <class T>
class List{
private:
	int n;

	Node<T> *start, *end;
	
	void addFirst(T *item);

	void addLast(T *item);
	
	bool remove(T *item);

	void init();
	
public:
	typedef bool (*sortCriteria)(T *item1, T *item2);

	List();

	List(T *arr, int nElem);

	~List();


        void clear();

        T& get(int i);

        bool exists(T* item);


	void addFirst(T item);

	void addLast(T item);
	
	void removeAt(int ind);
	
	bool remove(T item);
	
	bool removeAll(T item);

	T removeFirst();
	
	T removeLast();

	int size();

	T& operator [](int i);

	void operator +=(T item);

	void operator -=(T item);

	friend List<T>& operator +(List<T> &l, T item){
		l.addLast(&item);
		return l;
	}

	friend List<T>& operator +(T item, List<T> &l){
		l.addFirst(&item);
		return l;
	}
	
	friend List<T>& operator -(List<T> &l, T item){
		l.remove(&item);
		return l;
	}

	void sort(sortCriteria);
};

template <class T>
void List<T>::init(){
	this->start = this->end = NULL;
	this->n = 0;
}

template <class T>
void List<T>::operator +=(T item){
	this->addLast(&item);
}
 
template <class T>
void List<T>::operator -=(T item){
	this->remove(&item);
}

template <class T>
void List<T>::addFirst(T *item){
	Node<T> *n = new Node<T>(item, this->start);
	this->start = n;
	if(this->n == 0)
		end = n;
	this->n++;
}

template <class T>
void List<T>::addLast(T *item){
	if(!end){
		addFirst(item);
		return;
	}
	Node<T> *n = new Node<T>(item, NULL);
	this->end->next = n;
	this->end = n;
	this->n++;
}

template <class T>
void List<T>::addFirst(T item){
	addFirst(&item);
}

template <class T>
void List<T>::addLast(T item){
	addLast(&item);
}

template <class T>
bool List<T>::remove(T item){
	return this->remove(&item);
}

template <class T>
bool List<T>::remove(T *item){
	int i = 0;
	for(Node<T> *t = this->start;t;t = t->next, i++){
		if(t->item == *item){
			this->removeAt(i);
			return true;
		}
	}
	return false;
}

template <class T>
bool List<T>::removeAll(T item){
	int i = 0;
	bool removed = false;
	for(Node<T> *t = this->start;t;t = t->next, i++){
		if(t->item == item){
			this->removeAt(i);
			removed = true;
			i--;
		}
	}
	return removed;
}

template <class T>
void List<T>::removeAt(int ind){
	int i = ind;
	if( (i < 0) || (i >= this->n) )throw "Indice fuera de rango RA\n";
	Node<T> **t = &(this->start); 
	Node<T> *nxt, *end;
	while(i--){
		end = *t;
		t = &((*t)->next);
	}
	nxt = (*t)->next;
	delete (*t);
	*t = nxt;
	if(ind == (this->n - 1)){
		this->end = end;
	}
	if(this->n == 1){
		this->end = this->start = NULL;
	}
	this->n--;
}
template <class T>
void List<T>::clear() {
    if(this->size() == 0) return;
    int size =  this->size();
    for(int i = 0;i<size;i++) this->removeLast();
}

template <class T>
T List<T>::removeFirst(void){
	T item;
	if(this->n > 0){
		item = this->start->item;
		this->removeAt(0);
		return item;
	}
}

template <class T>
T List<T>::removeLast(void){
	T item;
	if(this->n > 0){
		item = this->end->item;
		removeAt(this->n - 1);
		return item;
	}
}

template <class T>
T& List<T>::operator [](int ind){
	if( (ind < 0) || (ind >= this->n) )throw "Indice fuera de rango []\n";
	Node<T> *t = this->start;
	for(int i = 0;i < ind;i++)
		t = t->next;
	return t->item;
}



template <class T>
bool List<T>::exists(T* item) {
    for (int i = 0; i < this->n; i++)
        if(get(i)==(*item)) return true;
    return false;
}

template <class T>
T& List<T>::get(int ind){
	if( (ind < 0) || (ind >= this->n) )throw "Indice fuera de rango GET\n";
	Node<T> *t = this->start;
	for(int i = 0;i < ind;i++)
		t = t->next;
	return t->item;
}

template <class T>
List<T>::List(){
	init();
}

template <class T>
List<T>::List(T *arr, int nElem){
	init();
	while(nElem--){
		this->addFirst((arr + nElem));
	}
}

template <class T>
int List<T>::size(){
	return this->n;
}

template <class T>
List<T>::~List(){
	Node<T> *r = start, *t;
	while(r){
		t = r->next;
		delete r;
		r = t;
	}
}

template <class T> 
void List<T>::sort(sortCriteria crt){
	Node<T> *i, *j;
	T tmp;
	for(i=this->start;i->next;i = i->next){
		for(j=this->start;j->next;j = j->next){
			if(!crt(&j->item, &j->next->item)){
				tmp = j->item;
				j->item = j->next->item;
				j->next->item = tmp;
			}
		}
	}
}

#endif


