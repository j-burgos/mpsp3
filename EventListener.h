
#ifndef _EVENTLISTENER_H
#define	_EVENTLISTENER_H

#include <oslib/oslib.h>

enum AppLevels{
    FILTER_SELECTION,
    SONG_SELECTION,
    PLAYER_MODE,
    USB_MODE,
    HELP_SCREEN
};

#define EVENT_NONE -100

#define EVENT_EXIT_APP -200

#define EVENT_HELP 10
#define EVENT_HELP_CANCEL 20

#define EVENT_NEXT_CATEGORY 100
#define EVENT_PREVIOUS_CATEGORY 200
#define EVENT_NEXT_SUBCATEGORY 300
#define EVENT_PREVIOUS_SUBCATEGORY 400
#define EVENT_FILTER_SELECTED 500

#define EVENT_NEXT_SONG 600
#define EVENT_PREVIOUS_SONG 700
#define EVENT_SONG_SELECTED 800
#define EVENT_CANCEL_SONG_SELECTION 900

#define EVENT_PLAYER_TOGGLE_PLAY 1000
#define EVENT_PLAYER_NEXT 1100
#define EVENT_PLAYER_PREVIOUS 1200
#define EVENT_PLAYER_STOP 1300
#define EVENT_PLAYER_CANCEL 1400
#define EVENT_PLAYER_FORWARD 1610
#define EVENT_PLAYER_REWIND 1620

#define EVENT_USB_MODE 1700
#define EVENT_USB_CANCEL 1800

class EventListener {
public:
    EventListener();
    EventListener(const EventListener& orig);
    virtual ~EventListener();

    int getEvent(int appLevel, OSL_CONTROLLER* control, int player_ctrl=0);
    
private:
    int getEventFilterSelection(OSL_CONTROLLER* control);
    int getEventSongSelection(OSL_CONTROLLER* control);
    int getEventPlayerMode(OSL_CONTROLLER* control, int player_ctrl);
    int getEventHelp(OSL_CONTROLLER* control);
};

#endif	/* _EVENTLISTENER_H */

