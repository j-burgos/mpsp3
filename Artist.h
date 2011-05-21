

#ifndef _ARTIST_H
#define	_ARTIST_H

#include <string>

using namespace std;
class Artist {
public:
    Artist();
    Artist(string name);
    Artist(const Artist& orig);
    virtual ~Artist();
    void SetName(string name);
    string GetName() const;
private:
    string name;
};

#endif	/* _ARTIST_H */

