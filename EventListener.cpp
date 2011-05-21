

#include "EventListener.h"

EventListener::EventListener() {
}

EventListener::EventListener(const EventListener& orig) {
}

EventListener::~EventListener() {
}

int EventListener::getEvent(int appLevel, OSL_CONTROLLER* control, int player_ctrl){
    switch(appLevel){
        case FILTER_SELECTION:
            return getEventFilterSelection(control);
            break;
        case SONG_SELECTION:
            return getEventSongSelection(control);
            break;
        case PLAYER_MODE:
            return getEventPlayerMode(control, player_ctrl);
            break;
        case USB_MODE:
            if(control->pressed.circle) return EVENT_USB_CANCEL;
            if(control->pressed.select) return EVENT_HELP;
            break;
        case HELP_SCREEN:
            if(control->pressed.circle) return EVENT_HELP_CANCEL;
            break;
        default:
            return EVENT_NONE;
            break;
    }
}

int EventListener::getEventFilterSelection(OSL_CONTROLLER* control){
    if(control->pressed.right) return EVENT_NEXT_CATEGORY;
    if(control->pressed.left) return EVENT_PREVIOUS_CATEGORY;
    if(control->pressed.up) return EVENT_PREVIOUS_SUBCATEGORY;
    if(control->pressed.down) return EVENT_NEXT_SUBCATEGORY;
    if(control->pressed.cross) return EVENT_FILTER_SELECTED;

    if(control->pressed.R) return EVENT_NEXT_CATEGORY;
    if(control->pressed.triangle) return EVENT_USB_MODE;
    if(control->pressed.L) return EVENT_PREVIOUS_CATEGORY;
    if(control->pressed.select) return EVENT_HELP;
    return EVENT_NONE;
}

int EventListener::getEventSongSelection(OSL_CONTROLLER* control){
    if(control->pressed.up) return EVENT_PREVIOUS_SONG;
    if(control->pressed.down) return EVENT_NEXT_SONG;
    if(control->pressed.cross) return EVENT_SONG_SELECTED;
    if(control->pressed.circle) return EVENT_CANCEL_SONG_SELECTION;

    if(control->pressed.right) return EVENT_SONG_SELECTED;
    if(control->pressed.left) return EVENT_CANCEL_SONG_SELECTION;
    if(control->pressed.select) return EVENT_HELP;
    return EVENT_NONE;
}

int EventListener::getEventPlayerMode(OSL_CONTROLLER* control, int player_ctrl){
    if(control->pressed.circle) return EVENT_PLAYER_CANCEL;
    if(control->pressed.L) return EVENT_PLAYER_PREVIOUS;
    if(control->pressed.R) return EVENT_PLAYER_NEXT;
    if(control->pressed.square) return EVENT_PLAYER_STOP;
    if(control->pressed.start) return EVENT_PLAYER_TOGGLE_PLAY;
    if (control->pressed.cross)  return EVENT_PLAYER_TOGGLE_PLAY;
    if(control->pressed.right) return EVENT_PLAYER_FORWARD;
    if(control->pressed.left) return EVENT_PLAYER_REWIND;
    if(control->pressed.select) return EVENT_HELP;
    
    return EVENT_NONE;
}
