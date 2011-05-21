

#include "UsbHandler.h"


UsbHandler::UsbHandler() {
    this->started = false;

}

UsbHandler::UsbHandler(const UsbHandler& orig) {
}

UsbHandler::~UsbHandler() {
}

void UsbHandler::startUsbStorage(){
    if(!started){
        //oslInitUsbStorage();
        int res = oslStartUsbStorage();
        /*if(res!=0){
            oslDeinitUsbStorage();
            throw AppException("USBException","No se pudo iniciar el modo USB");
        }*/
        started = true;
    }
}

void UsbHandler::stopUsbStorage() {
    if(started){
        oslStopUsbStorage();
        //Por los archivos corruptos
        sceIoDevctl("fatms0:", 0x0240D81E, NULL, 0, NULL, 0 );
        //oslDeinitUsbStorage();
        started = false;
    }
}
void UsbHandler::toggleUsbStorage(){
    if(started) stopUsbStorage();
    else startUsbStorage();
}

bool UsbHandler::isCableConnected(){
    return (sceUsbGetState() & PSP_USB_CABLE_CONNECTED);
}

bool UsbHandler::isUsbActive(){
    return (sceUsbGetState() & PSP_USB_ACTIVATED);
}

bool UsbHandler::isConnectionEstablished(){
    return  (sceUsbGetState() & PSP_USB_CONNECTION_ESTABLISHED);
}