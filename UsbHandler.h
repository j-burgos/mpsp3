


#ifndef _USBHANDLER_H
#define	_USBHANDLER_H

#include <oslib/oslib.h>
#include "AppException.h"

class UsbHandler {
public:
    UsbHandler();
    UsbHandler(const UsbHandler& orig);
    virtual ~UsbHandler();

    void toggleUsbStorage();
    void startUsbStorage();
    void stopUsbStorage();
    bool isUsbActive();
    bool isCableConnected();
    bool isConnectionEstablished();

private:
    bool started;
};

#endif	/* _USBHANDLER_H */

