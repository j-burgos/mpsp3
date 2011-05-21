
#include "main_aux.h"

PSP_MODULE_INFO("pspTunes",PSP_MODULE_USER,2,1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER|THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_MAX();

#define printfd pspDebugScreenPrintf

int main(int argc, char** argv) {

    try {

        //Iniciamos los sistemas de audio y video
        initSystems();

        pspDebugScreenInit();

        //Variables del control de la aplicacion
        int level = FILTER_SELECTION;
        bool running = true;
        int skip = 0;

        //Variables para el manejo de eventos
        int event = EVENT_NONE;
        EventListener el;
        OSL_CONTROLLER *control = NULL;

        printfd("\nIniciando pspTunes - MP3Player...\n\n");
        //Carga de recursos
        printfd("Cargando recursos de la aplicacion...\n\n");
        printfd("Cargando fuente %s... ", DEF_FONT.c_str());
        OSL_FONT* font = LoadFontResource(DEF_FONT);
        printfd("OK\n");
        printfd("Cargando imagen %s... ", (BG_PATH).c_str());
        OSL_IMAGE* bg = LoadImageResource(BG_PATH, PNG);
        printfd("OK\n");
        printfd("Cargando imagen %s... ", (MARKER_PATH).c_str());
        OSL_IMAGE* marker = LoadImageResource(MARKER_PATH, PNG);
        printfd("OK\n");
        printfd("Cargando imagen %s... ", (ALBUMART_PATH).c_str());
        OSL_IMAGE* albumart_def = LoadImageResource(ALBUMART_PATH, PNG);
        printfd("OK\n");
        printfd("Cargando imagen %s... ", (STATUS_BAR).c_str());
        OSL_IMAGE* status_bar = LoadImageResource(STATUS_BAR, PNG);
        printfd("OK\n");
        printfd("Cargando imagen %s... ", (STATUS_BAR_NO).c_str());
        OSL_IMAGE* status_bar_no = LoadImageResource(STATUS_BAR_NO, PNG);
        printfd("OK\n");

        printfd("Cargando imagen %s... ", (BAT_100).c_str());
        OSL_IMAGE* bat_full = LoadImageResource(BAT_100, PNG);
        printfd("OK\n");
        printfd("Cargando imagen %s... ", (BAT_66).c_str());
        OSL_IMAGE* bat_med = LoadImageResource(BAT_66, PNG);
        printfd("OK\n");
        printfd("Cargando imagen %s... ", (BAT_33).c_str());
        OSL_IMAGE* bat_low = LoadImageResource(BAT_33, PNG);
        printfd("OK\n");

        printfd("Cargando imagen %s... ", (HELP_CATEGORIES).c_str());
        OSL_IMAGE* help_cat = LoadImageResource(HELP_CATEGORIES, PNG);
        printfd("OK\n");
        printfd("Cargando imagen %s... ", (HELP_SONGS).c_str());
        OSL_IMAGE* help_song = LoadImageResource(HELP_SONGS, PNG);
        printfd("OK\n");
        printfd("Cargando imagen %s... ", (HELP_PLAYER).c_str());
        OSL_IMAGE* help_player = LoadImageResource(HELP_PLAYER, PNG);
        printfd("OK\n");
        printfd("Cargando imagen %s... ", (HELP_USB).c_str());
        OSL_IMAGE* help_usb = LoadImageResource(HELP_USB, PNG);
        printfd("OK\n");

        OSL_IMAGE* album_art = NULL;
        OSL_IMAGE* help = NULL;
        //Variable que guarda el cuadro de dialogo actual
        int dialog = OSL_DIALOG_NONE;

        //Seteamos la fuente a usar para dibujar strings
        oslSetFont(font);

        Menu<Category> categories(-45, 40, 90, 65, 5);
        Menu<string> subcategories(55, 80, 480, 26, 6);
        Menu<Song> songs(130, 105, 330, 22, 6);
        Player p;
        UsbHandler usbh;

        int ant_level = -1;

        printfd("Cargando iconos de categorias...\n");
        loadCategories(categories);
        printfd("OK\n");
        loadSubcategories(subcategories, categories.get(categories.GetSelected()).GetLabel());

        //Loop principal de la aplicacion
        while (running) {
            try {

                //Al comenzar no ha pasado ningun evento
                event = EVENT_NONE;

                /* Leemos los controles y esperamos un microsegundo
                 * debido a que la lectura de los botones bloquea a otros modulos
                 * como el usb y los message dialogs
                 * */
                control = oslReadKeys();
                sceKernelDelayThread(1);

                /* Revisamos que evento ha sucedido y realizamos una accion acorde
                 * Si no hay ninguno leemos si hay uno nuevo
                 */
                if (event == EVENT_NONE) event = el.getEvent(level, control, 0);
                if (event == EVENT_HELP){
                    if(level == FILTER_SELECTION) help = help_cat;
                    if(level == SONG_SELECTION) help = help_song;
                    if(level == PLAYER_MODE) help = help_player;
                    if(level == USB_MODE) help = help_usb;
                    ant_level = level;
                    level = HELP_SCREEN;
                }
                if(event == EVENT_HELP_CANCEL){
                    level = ant_level;
                }
                if (event == EVENT_NEXT_CATEGORY) {
                    categories.NextOption();
                    loadSubcategories(subcategories, categories.get(categories.GetSelected()).GetLabel());
                    subcategories.Reset();
                }
                if (event == EVENT_PREVIOUS_CATEGORY) {
                    categories.PreviousOption();
                    loadSubcategories(subcategories, categories.get(categories.GetSelected()).GetLabel());
                    subcategories.Reset();
                }
                if (event == EVENT_NEXT_SUBCATEGORY) {
                    subcategories.NextOption();
                }
                if (event == EVENT_PREVIOUS_SUBCATEGORY) {
                    subcategories.PreviousOption();
                }
                if (event == EVENT_FILTER_SELECTED) {
                    if (subcategories.size() == 0)
                            oslInitMessageDialog("Aún no ha sincronizado su biblioteca de música\nNo hay elementos para esta categoria.",0);
                    else {
                        loadSongs(songs, p, categories.get(categories.GetSelected()).GetLabel(),
                                subcategories.get(subcategories.GetSelected()));
                        if (songs.size() > 0) {
                            songs.Reset();
                            categories.SetViewableItems(2);
                            categories.SetItemWidth(65);
                            album_art = loadAlbumArt(songs.get(songs.GetSelected()).GetAlbum().GetDir(), 75, 75);
                            level = SONG_SELECTION;
                        } else throw AppException("SelectionNotFoundException", "No existen canciones con ese criterio");
                    }
                }

                if (event == EVENT_CANCEL_SONG_SELECTION) {
                    categories.SetViewableItems(5);
                    categories.SetItemWidth(90);
                    level = FILTER_SELECTION;
                }
                if (event == EVENT_NEXT_SONG) {
                    songs.NextOption();
                    p.setCurrent(songs.GetSelected());
                    if (songs.size() > 0)
                        album_art = loadAlbumArt(songs.get(songs.GetSelected()).GetAlbum().GetDir(), 75, 75);
                }
                if (event == EVENT_PREVIOUS_SONG) {
                    songs.PreviousOption();
                    p.setCurrent(songs.GetSelected());
                    if (songs.size() > 0)
                        album_art = loadAlbumArt(songs.get(songs.GetSelected()).GetAlbum().GetDir(), 75, 75);
                }

                if (event == EVENT_SONG_SELECTED) {
                    if (songs.size() == 0)
                           oslInitMessageDialog("No hay elementos para esta categoria.",0);
                    else {
                        if (songs.size() > 0) {
                            album_art = loadAlbumArt(songs.get(songs.GetSelected()).GetAlbum().GetDir(), 100, 100);
                            loadPlayerSongs(songs, p);
                            if (p.getSongs().size() > 0) {
                                p.setCurrent(songs.GetSelected());
                                p.load();
                                p.togglePlayPause();
                                level = PLAYER_MODE;
                            }
                        }
                    }
                }
                if (event == EVENT_PLAYER_CANCEL) {
                    p.stop();
                    p.unload();
                    p.getSongs().clear();
                    if (songs.size() > 0)
                        album_art = loadAlbumArt(songs.get(songs.GetSelected()).GetAlbum().GetDir(), 75, 75);
                    level = SONG_SELECTION;
                }
                if (event == EVENT_PLAYER_TOGGLE_PLAY) p.togglePlayPause();
                if (event == EVENT_PLAYER_STOP) p.stop();
                if (event == EVENT_PLAYER_PREVIOUS) {
                    if (songs.size() > 0)
                        album_art = loadAlbumArt(songs.get(songs.GetSelected()).GetAlbum().GetDir(), 100, 100);
                    p.previous();
                }
                if (event == EVENT_PLAYER_NEXT) {
                    if (songs.size() > 0)
                        album_art = loadAlbumArt(songs.get(songs.GetSelected()).GetAlbum().GetDir(), 100, 100);
                    p.next();
                }
                if (event == EVENT_PLAYER_REWIND) p.seekTime(-10);
                if (event == EVENT_PLAYER_FORWARD) p.seekTime(2);

                if (event == EVENT_USB_MODE) {
                    if(!usbh.isCableConnected())
                        throw AppException("USBException","Conecte el cable USB");
                    usbh.startUsbStorage();
                    string msg = 
                            string("En modo USB, tendrá acceso a la MemoryStick como una unidad de almacenamiento USB.\n")
                            + "Sincronice su música utilizando jTunes en este momento.\n"
                            + "Cuando el proceso termine, presione el boton de regresar.";
                    oslInitMessageDialog(msg.c_str(),0);
                    level = USB_MODE;
                }
                if (event == EVENT_USB_CANCEL) {
                    usbh.stopUsbStorage();
                    sceKernelDelayThread(1000000*3);
                    songs.clear();
                    p.getSongs().clear();
                    categories.Reset();
                    loadSubcategories(subcategories, categories.get(categories.GetSelected()).GetLabel());
                    subcategories.Reset();
                    level = FILTER_SELECTION;
                }

                if (p.getSongs().size() > 0)
                    if (p.getLengthInt() != 0)
                        if (p.getCurrentTime() == p.getLength()) p.next();

                /* Si la unidad grafica no se ha atrasado para mantener el framerate
                 * entonces procedemos a dibujar*/
                if (!skip) {
                    oslStartDrawing();

                    //Dibujar el fondo
                    drawImage(0,0,bg);
 
                    if (level == FILTER_SELECTION) {
                        drawImage(0, 247, status_bar);
                        drawCategories(categories);
                        drawSubcategories(subcategories);
                        drawImage(30, 115, marker);
                        drawBatteryLifePercent(bat_low, bat_med, bat_full);
                    }
                    if (level == SONG_SELECTION) {
                        drawImage(0,247,status_bar_no);
                        drawCategories(categories);
                        drawImage(90, 55, marker);
                        drawAlbumArt(130, 30, album_art, albumart_def);
                        drawStyledString(
                                "Canciones de\n" + subcategories.get(subcategories.GetSelected()),
                                215, 45, 0.70f, LEFT, false, true, 240);
                        drawImage(105, 135, marker);
                        drawSongs(songs);
                        drawBatteryLifePercent(bat_low, bat_med, bat_full);
                    }
                    if (level == PLAYER_MODE) {
                        drawImage(0,247,status_bar_no);
                        drawAlbumArt(20, 45, album_art, albumart_def);
                        drawCurrentSong(p);
                        drawBatteryLifePercent(bat_low, bat_med, bat_full);
                    }
                    if (level == USB_MODE) {
                        drawImage(0,247,status_bar_no);
                        drawStyledString("Modo USB",240,100,0.75f,CENTER,true,true);
                        drawBatteryLifePercent(bat_low, bat_med, bat_full);
                    }
                    if( level==HELP_SCREEN) drawImage(0,0,help);
                    
                    //Si hubiese algun message dialog iniciado lo dibujamos
                    dialog = oslGetDialogType();
                    if (dialog) {
                        oslDialogDrawAndWait(1);
                        oslEndDialog();
                    }

                    oslEndDrawing();
                }

                /* Terminamos un frame y sincronizamos con la unidad de graficos
                 * para ver si seria necesario saltarnos algun frame (skip)*/
                oslEndFrame();
                skip = oslSyncFrame();

            } catch (const char* e) {
                p.getSongs().clear();
                oslInitMessageDialog(e, 0);
            } catch (AppException& e) {
                p.getSongs().clear();
                oslInitMessageDialog(e.GetMessage().c_str(), 0);
            } catch (...) {
                p.getSongs().clear();
                oslInitMessageDialog("Error desconocido: Instale la aplicacion nuevamete.", 0);
            }
        }

        //Terminamos la aplicacion
        exitApp();
        return 0;
    } catch(AppException& e){
        printfd("\n%s - %s\n",e.GetName().c_str(),e.GetMessage().c_str());
        printfd("Presione el boton HOME y luego elija Si para salir\n\n\n\n");
        sceKernelSleepThread();
        return -1;
    }
    catch (...) {
        printfd("\nERROR: No se pudo iniciar la aplicacion. Instale la aplicacion nuevamente\n");
        printfd("Presione el boton HOME y luego elija Si para salir\n\n\n\n");
        sceKernelSleepThread();
        return -1;
    }
}


