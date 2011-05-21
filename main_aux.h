/* 
 * File:   main_aux.h
 * Author: Jorge
 *
 * Created on 14 de junio de 2010, 02:42 PM
 */

#ifndef _MAIN_AUX_H
#define	_MAIN_AUX_H

#include <pspkernel.h>
#include <sstream>
#include <iomanip>
#include <oslib/oslib.h>

#include "AppException.h"
#include "List.cpp"

#include "FileLister.h"
#include "XmlInterface.h"

#include "Player.h"
#include "UsbHandler.h"
#include "EventListener.h"

#include "Menu.cpp"
#include "Category.h"

#define PNG 10
#define JPG 20

#define DEF_FONT        string("flash0:/font/ltn0.pgf")
#define GUI_PATH        string("gui/")
#define BG_PATH         GUI_PATH+"bg.png"
#define MARKER_PATH     GUI_PATH+"marker.png"
#define ALBUMART_PATH   GUI_PATH+"albumart.png"
#define STATUS_BAR      GUI_PATH+"statusbar.png"
#define STATUS_BAR_NO      GUI_PATH+"statusbar_no.png"
#define ALBUMART_DEF    "Folder.jpg"

#define BAT_PATH        GUI_PATH+"battery/"
#define BAT_100         BAT_PATH+"100.png"
#define BAT_66          BAT_PATH+"66.png"
#define BAT_33          BAT_PATH+"33.png"

#define HELP_PATH           GUI_PATH+"help/"
#define HELP_CATEGORIES     HELP_PATH+"help1.png"
#define HELP_SONGS          HELP_PATH+"help2.png"
#define HELP_PLAYER         HELP_PATH+"help3.png"
#define HELP_USB            HELP_PATH+"help4.png"

#define CENTER          INTRAFONT_ALIGN_CENTER
#define LEFT            INTRAFONT_ALIGN_LEFT
#define RIGHT           INTRAFONT_ALIGN_RIGHT

#define CAT_ICON_WIDTH  45
#define CAT_ICON_HEIGHT 45
#define SUBCAT_ICON_WIDTH  480
#define SUBCAT_ICON_HEIGHT 15
#define SONG_ICON_WIDTH  240
#define SONG_ICON_HEIGHT 15

#define FILTER_ARTIST       "Artista"
#define FILTER_ALBUM        "Álbum"
#define FILTER_GENRE        "Género"
#define FILTER_YEAR         "Año"
#define FILTER_PLAYLIST     "Playlist"
#define FILTER_FOLDER       "Carpeta"
#define FILTER_ALL          "Toda la música"

#define MUSIC_DB            string("music_db.xml")
#define PLAYLIST_DIR        string("playlists/")
#define MUSIC_DIR           string("ms0:/MUSIC/")

void initSystems();
void termSystems();
void exitApp();

OSL_IMAGE* LoadImageResource(string path, int extension);
OSL_FONT* LoadFontResource(string path);
OSL_IMAGE* loadAlbumArt(string path, int nw,int nh);

void loadCategories(Menu<Category>& categories);
void loadSubcategories(Menu<string>& subcategories, string filter);
void loadSongs(Menu<Song>& songs,Player& p, string filter, string value);
void loadPlayerSongs(Menu<Song>& songs, Player& p);

void drawImage(int x, int y, OSL_IMAGE* img);
void drawStyledString(string text, int x, int y, float size, int alignment, bool glowing=false, bool solid=true, int width=480);
void drawAlbumArt(int x, int y, OSL_IMAGE* album, OSL_IMAGE* default_img);
void drawBatteryLifePercent(OSL_IMAGE* low, OSL_IMAGE* med, OSL_IMAGE* hi);

void drawCategories(Menu<Category>& categories);
void drawSubcategories(Menu<string>& subcategories);
void drawSongs(Menu<Song>& songs);
void drawCurrentSong(Player& p);

#endif	/* _MAIN_AUX_H */

