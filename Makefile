#Path donde esta la SDK del PSP para los includes y el linkeo de librerias
PSPSDK = $(shell psp-config --pspsdk-path)

#Nombre del modulo a crear
TARGET = pspTunes

#Objetos que deben ser compilados para el modulo
UTILS = AppException.o
MODEL = FileLister.o XmlInterface.o Artist.o Album.o Song.o 
CONTROL = Player.o AudioMPEG.o Audio.o UsbHandler.o EventListener.o
VIEW = Category.o
MAIN = main.o main_aux.o

OBJS = $(MAIN) $(UTILS) $(MODEL) $(CONTROL) $(VIEW)

#-----LIBRERIAS-----#
#Estandares para la mayoria de librerias y las del usb
STDLIBS = -lpsppower -lstdc++ -lz -lm -lpspusb -lpspusbstor
#Necesarias para manejar la pantalla y manejo del procesador de video
VIDEOLIBS = -lpng -ljpeg -lpspgu -lpspgum
#Librerias para el sistema de audio
AUDIOLIBS = -lpspaudiolib -lpspaudio -lpspaudiocodec
#No son necesarias aparentemente, a menos que se usen las funciones de redes en OSLibMOD
#NETLIBS = -lpsphttp -lpspssl -lpspwlan -lpspnet_adhocmatching -lpspnet_adhoc -lpspnet_adhocctl
#Librerias usadas por la OSLibMOD
OSLIBS = -losl -lpsphprm -lpspumd -lpsprtc
#Libreria para el manejo de XML
TICPPLIBS = -lticppd
         
LIBS = $(TICPPLIBS) $(OSLIBS) $(AUDIOLIBS) $(VIDEOLIBS) $(STDLIBS)

#Crear modulo prx, necesario para firmwares 3.XX
BUILD_PRX = 1
#Darle al modulo la capacidad de usar la memoria extra (+32Mb) de los modelos nuevos
PSP_LARGE_MEMORY = 1
#Minimo firmware necesario para usar la aplicacion
PSP_FW_VERSION = 371

#Flags de compilacion
CFLAGS = -O2 -g -G0 -Wall -DSANE
CXXFLAGS = $(CFLAGS) -fexceptions -frtti
ASFLAGS = $(CFLAGS)

#Ejecutable final, solamente un contenedor del modulo principal
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = pspTunes - MP3Player
PSP_EBOOT_ICON= "icon0.png"

#Se inculye el makefile base de la SDK
include $(PSPSDK)/lib/build.mak