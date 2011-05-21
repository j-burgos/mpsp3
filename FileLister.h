
#ifndef _FILELISTER_H
#define	_FILELISTER_H

#include <string>
#include <dirent.h>
#include <algorithm>
#include "List.cpp"
#include "AppException.h"

using namespace std;
class FileLister {
public:
    FileLister();
    FileLister(string dir);
    FileLister(const FileLister& orig);
    virtual ~FileLister();
    
    void SetDirectory(string directory);
    string GetDirectory() const;

    List<string>* getDirectories();
    List<string>* getDirectories(string dir, bool self=true);

    List<string>* getFiles(string extension="",bool withExtension=false);
    List<string>* getFiles(string dir, string extension="", bool withExtension=false);

private:
    string directory;
};

bool sortFileEntrys(string* entry1, string* entry2);

#endif	/* _FILELISTER_H */

