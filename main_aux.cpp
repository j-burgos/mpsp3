#include "main_aux.h"

void initSystems() {
    oslInit(0);
    oslInitGfx(OSL_PF_8888, 1);
    oslIntraFontInit(INTRAFONT_CACHE_ALL|INTRAFONT_STRING_UTF8);
    audioInit(1);
    oslSetKeyAutorepeatInit(40);
    oslSetKeyAutorepeatInterval(10);
    oslInitUsbStorage();
}
void termSystems() {
    oslDeinitUsbStorage();
    audioEnd();
    oslIntraFontShutdown();
    oslEndGfx();
}
void exitApp() {
    termSystems();
    oslQuit();
}

OSL_IMAGE* LoadImageResource(string path, int extension){
    OSL_IMAGE* resource = NULL;
    int location = OSL_IN_RAM|OSL_SWIZZLED;
    int pxlfmt = OSL_PF_8888;
    if(extension==PNG) resource = oslLoadImageFilePNG((char*)path.c_str(),location,pxlfmt);
    if(extension==JPG) resource = oslLoadImageFileJPG((char*)path.c_str(),location,pxlfmt);
    if(!resource)
        throw AppException("ImageResourceException","No se pudo cargar el recurso: " + path);
    return resource;
}
OSL_FONT* LoadFontResource(string path){
    OSL_FONT* font_resource = NULL;
    font_resource = oslLoadFontFile(path.c_str());
    if(!font_resource)
        throw AppException("FontResourceException","No se pudo cargar el recurso: " + path);
    return font_resource;
}
OSL_IMAGE* loadAlbumArt(string path, int nw, int nh){
    int location = OSL_IN_RAM|OSL_SWIZZLED;
    int pxlfmt = OSL_PF_8888;
    OSL_IMAGE* img = oslLoadImageFileJPG((char*)(path+ALBUMART_DEF).c_str(),location,pxlfmt);
    if(!img) return NULL;
    OSL_IMAGE* scaled = oslScaleImageCreate(img,location,nw,nh,pxlfmt);
    if(!scaled){
        oslDeleteImage(img);
        return NULL;
    }
    return scaled;
}

void loadCategories(Menu<Category>& categories){
    categories.addLast(Category(FILTER_ARTIST,GUI_PATH+"artist/"));
    categories.addLast(Category(FILTER_ALBUM,GUI_PATH+"album/"));
    categories.addLast(Category(FILTER_GENRE,GUI_PATH+"genre/"));
    categories.addLast(Category(FILTER_YEAR,GUI_PATH+"year/"));
    categories.addLast(Category(FILTER_PLAYLIST,GUI_PATH+"playlist/"));
    categories.addLast(Category(FILTER_ALL,GUI_PATH+"all/"));
    categories.addLast(Category(FILTER_FOLDER,GUI_PATH+"folder/"));
}
void loadSubcategories(Menu<string>& subcategories, string filter){
    subcategories.clear();
    try {
        if (filter == FILTER_ARTIST) {
            XmlInterface xmli;
            List<Artist>* list = xmli.getArtists(MUSIC_DB, "artist");
            for (int i = 0; i < list->size(); i++){
                subcategories.addLast(list->get(i).GetName());
            }
            delete list;
        }
        if (filter == FILTER_ALBUM) {
            XmlInterface xmli;
            List<Album>* list = xmli.getAlbumsByAttr(MUSIC_DB, "album", "album");
            for (int i = 0; i < list->size(); i++){
                subcategories.addLast(list->get(i).GetTitle());
            }
            delete list;
        }
        if (filter == FILTER_GENRE) {
            XmlInterface xmli;
            List<Album>* list = xmli.getAlbumsByAttr(MUSIC_DB, "album", "genre");
            for (int i = 0; i < list->size(); i++){
                subcategories.addLast(list->get(i).GetGenre());
            }
            delete list;
        }
        if (filter == FILTER_YEAR) {
            XmlInterface xmli;
            List<Album>* list = xmli.getAlbumsByAttr(MUSIC_DB, "album", "year");
            for (int i = 0; i < list->size(); i++){
                subcategories.addLast(list->get(i).GetYear());
            }
            delete list;
        }
        if (filter == FILTER_PLAYLIST) {
            FileLister fl;
            List<string>* list = fl.getFiles(PLAYLIST_DIR,"xml",false);
            for (int i = 0; i < list->size(); i++){
                subcategories.addLast(list->get(i));
            }
            delete list;
        }
        if(filter == FILTER_FOLDER){
            FileLister fl;
            List<string>* list = fl.getDirectories(MUSIC_DIR,true);
            for (int i = 0; i < list->size(); i++){
                subcategories.addLast(list->get(i));
            }
            delete list;
        }
        if(filter == FILTER_ALL){
            XmlInterface xmli;
            List<Artist>* list = xmli.getArtists(MUSIC_DB, "artist");
            if(list->size() == 0){
                delete list;
                return;
            }
            subcategories.addLast("Toda la biblioteca");
            delete list;
        }
        
    } catch (AppException& e) {
        throw AppException(e.GetName(), e.GetMessage());
    } catch (...) {
        throw AppException("Exception", "No se pudieron cargar las subcategorias");
    }
}
void loadSongs(Menu<Song>& songs, Player& p, string filter, string value) {
    songs.clear();
    XmlInterface xmli;
    FileLister fl;
    List<Song>* list = new List<Song>();
    try {
        if (filter == FILTER_ARTIST)
            list = xmli.getSongsByArtist(MUSIC_DB, "song", "artist", value);
        if (filter == FILTER_ALBUM)
            list = xmli.getSongsByAlbum(MUSIC_DB, "song", "album", value);
        if (filter == FILTER_GENRE)
            list = xmli.getSongsByAlbum(MUSIC_DB,"song","genre",value);
        if (filter == FILTER_YEAR)
            list = xmli.getSongsByAlbum(MUSIC_DB,"song","year",value);
        if (filter == FILTER_PLAYLIST)
            list = xmli.getPlaylistSongs(PLAYLIST_DIR+value+".xml","song");
        if (filter == FILTER_FOLDER){
            List<string>* temp = fl.getFiles(MUSIC_DIR+value,"mp3",true);
            for(int i = 0; i < temp->size(); i++){
                stringstream s;
                s << i+1;
                list->addLast(
                        Song(
                        temp->get(i),
                        temp->get(i),
                        s.str(),
                        "Desconocido",
                        "Desconocido",
                        "",
                        Album(
                        value,
                        "Desconocido",
                        "Desconocido",
                        value,
                        Artist("Desconocido"))));
            }
            delete temp;
        }
        if (filter == FILTER_ALL){
            list = xmli.getSongs(MUSIC_DB,"song");
        }
        for (int i = 0; i < list->size(); i++) {
                songs.addLast(
                        Song(
                        list->get(i).GetTitle(),
                        list->get(i).GetFilename(),
                        list->get(i).GetTrack(),
                        list->get(i).GetKbps(),
                        list->get(i).GetSize(),
                        list->get(i).GetLength(),
                        Album(
                        list->get(i).GetAlbum().GetTitle(),
                        list->get(i).GetAlbum().GetYear(),
                        list->get(i).GetAlbum().GetGenre(),
                        MUSIC_DIR + list->get(i).GetAlbum().GetDir(),
                        Artist(list->get(i).GetAlbum().GetArtist().GetName()))));
            }
            delete list;
            if(songs.size()==0) throw AppException("EmptyException", "No hay elementos para ese criterio");
    } catch (AppException& e) {
        delete list;
        throw AppException(e.GetName(), e.GetMessage());
    } catch (...) {
        delete list;
        throw AppException("Exception", "No se pudieron cargar las subcategorias");
    }
}
void loadPlayerSongs(Menu<Song>& songs, Player& p){
    for (int i = 0; i < songs.size(); i++) {
        p.getSongs().addLast(
                Song(
                songs.get(i).GetTitle(),
                songs.get(i).GetFilename(),
                songs.get(i).GetTrack(),
                songs.get(i).GetKbps(),
                songs.get(i).GetSize(),
                songs.get(i).GetLength(),
                Album(
                songs.get(i).GetAlbum().GetTitle(),
                songs.get(i).GetAlbum().GetYear(),
                songs.get(i).GetAlbum().GetGenre(),
                songs.get(i).GetAlbum().GetDir(),
                Artist(songs.get(i).GetAlbum().GetArtist().GetName()))));
    }
}

void drawImage(int x, int y, OSL_IMAGE* img){
    if(!img) return;
    else oslDrawImageXY(img,x,y);
}
void drawStyledString(string text, int x, int y, float size, int alignment, bool glowing, bool solid, int width){
    unsigned int fcolor = RGBA(255,255,255,150);
    unsigned int scolor = RGBA(0,0,0,130);
    if(solid){
        fcolor = RGBA(255,255,255,255);
        scolor = RGBA(0,0,0,255);
    }
    if(glowing){
        float t = ((float)(clock() % CLOCKS_PER_SEC)) / ((float)CLOCKS_PER_SEC);
        int val = (t < 0.5f) ? t*511 : (1.0f-t)*511;
        oslIntraFontSetStyle(osl_curFont,size,fcolor,(0xFF<<24)+(val<<16)+(val<<8)+(val),alignment);
        oslDrawStringLimited(x,y,width,text.c_str());
    }else{
        oslIntraFontSetStyle(osl_curFont,size,fcolor,scolor,alignment);
        oslDrawStringLimited(x,y,width,text.c_str());
    }
}
void drawAlbumArt(int x, int y, OSL_IMAGE* album, OSL_IMAGE* default_img){
    if(!album) drawImage(x,y,default_img);
    else drawImage(x,y,album);
}
void drawBatteryLifePercent(OSL_IMAGE* low, OSL_IMAGE* med, OSL_IMAGE* hi) {
    stringstream s;
    int power = scePowerGetBatteryLifePercent();
    s << power << "%";
    drawStyledString(s.str(), 430, 255, 0.70f, RIGHT, false, true);
    if (power >= 66 && power < 101) drawImage(440, 252, hi);
    if (power >= 33 && power < 66) drawImage(440, 252,med);
    if (power > 5 && power < 33) drawImage(440, 252, low);
}

void drawCategories(Menu<Category>& categories){
    int selected = categories.GetSelected();
    int anterior = selected -1;

    int base_x = categories.GetX();
    int base_y = categories.GetY();
    int newx = 0;

    int textx = 0;
    int texty = base_y + categories.GetItemHeight() - osl_curFont->charHeight;

    int size = categories.size();
    int viewables = categories.GetViewableItems();

    int n = 0;
    for (int i = anterior; i < selected + viewables - 1; i++) {
        newx = base_x + n * categories.GetItemWidth() + (categories.GetItemWidth() - CAT_ICON_WIDTH) / 2;
        textx = newx + CAT_ICON_WIDTH / 2;
        if (i < 0 || i >= size) {
            n++;
            continue;
        }
        if (i == selected) {
            drawImage(newx, base_y, categories.get(i).GetImgEnabled());
            drawStyledString(categories.get(i).GetLabel(), textx, texty, 0.70f, CENTER);
        } else drawImage(newx, base_y, categories.get(i).GetImgDisabled());
        n++;
    }

}
void drawSubcategories(Menu<string>& subcategories){

    int selected = subcategories.GetSelected();
    int anterior = selected -1;

    int base_x = subcategories.GetX();
    int base_y = subcategories.GetY();
    int newy = 0;

    int textx = base_x;
    int texty = 0;

    int size = subcategories.size();
    if(size == 0)
        drawStyledString("No hay elementos para esta categoría\n Sincronice su biblioteca de música", textx, base_y+subcategories.GetItemHeight()+ (subcategories.GetItemHeight() - SUBCAT_ICON_HEIGHT) / 2 +5, 0.70f, LEFT, true, true, 400);

    int viewables = subcategories.GetViewableItems();

    int n = 0;
    for (int i = anterior; i < selected + viewables - 1; i++) {
        newy = base_y + n * subcategories.GetItemHeight() + (subcategories.GetItemHeight() - SUBCAT_ICON_HEIGHT) / 2;
        texty = newy + SUBCAT_ICON_HEIGHT / 2;
        if (i < 0 || i >= size) {
            n++;
            continue;
        }
        if( i == anterior) texty = 15;
        if (i == selected)
            drawStyledString(subcategories.get(i), textx, texty, 0.70f, LEFT, true, true, 400);
        else
            drawStyledString(subcategories.get(i), textx, texty, 0.70f, LEFT, false, false, 400);
        n++;
    }

}
void drawSongs(Menu<Song>& songs){
    int selected = songs.GetSelected();
    int anterior = selected -1;

    int base_x = songs.GetX();
    int base_y = songs.GetY();
    int newy = 0;

    int textx = base_x;
    int texty = 0;

    int size = songs.size();
    int viewables = songs.GetViewableItems();

    int n = 0;
    for (int i = anterior; i < selected + viewables - 1; i++) {
        newy = base_y + n * songs.GetItemHeight() + (songs.GetItemHeight() - SONG_ICON_HEIGHT) / 2;
        texty = newy + SONG_ICON_HEIGHT / 2;
        if (i < 0 || i >= size) {
            n++;
            continue;
        }
        if (i == selected){
            drawStyledString(songs.get(i).GetTitle(), textx, texty, 0.60f, LEFT, true,true,280);
            drawStyledString(songs.get(i).GetLength(), songs.GetX()+songs.GetItemWidth(), texty, 0.60f, RIGHT, true,true,40);
        }else{
            drawStyledString(songs.get(i).GetTitle(), textx, texty, 0.60f, LEFT, false, false,280);
            drawStyledString(songs.get(i).GetLength(), songs.GetX()+songs.GetItemWidth(), texty, 0.60f, RIGHT, false,false,40);
        }
        n++;
    }

}

void drawCurrentSong(Player& p){

    oslDrawFillRect(0,0, 480, 25, RGBA(0, 0, 0, 255));
    //Estado de la reproduccion
    drawStyledString(p.getSongStatus()+"...",10,8,0.70f,LEFT,false,true);
    //Cual es de cuantas
    stringstream s;
    s << "(" << setfill('0') << setw(2) << p.getCurrent() + 1 << "/";
    s << setw(2) << p.getSongs().size() << ")";
    drawStyledString(s.str(),470,8,0.70f,RIGHT,false,true,450);

    int base_x = 135;
    int base_y = 45;
    int bar_size = 460 - base_x;
    //Track + nombre de la cancion
    string fulltrack = p.getSongs().get(p.getCurrent()).GetTrack()+". "+p.getSongs().get(p.getCurrent()).GetTitle();
    drawStyledString(fulltrack,base_x,base_y,0.70f,LEFT,false,true,bar_size);
    //Informacion de album
    drawStyledString(p.getSongs().get(p.getCurrent()).GetAlbum().GetArtist().GetName(),base_x,base_y+20,0.70f,LEFT,false,true,bar_size);
    drawStyledString(p.getSongs().get(p.getCurrent()).GetAlbum().GetTitle(),base_x,base_y+40,0.70f,LEFT,false,true,bar_size);
    drawStyledString(p.getSongs().get(p.getCurrent()).GetAlbum().GetYear(),base_x,base_y+60,0.70f,LEFT,false,true,bar_size);

    //base_x = 100;
    base_y = 115;
    //Progress bar xD
    //bar_size = 380 - base_x;
    if(p.getLengthInt() > 0){
        float pct = ((float) p.getCurrentTimeInt() / (float) p.getLengthInt());
        int offset = pct * bar_size;
        oslDrawFillRect(base_x, base_y+20, base_x + bar_size, base_y+22, RGBA(0, 0, 0, 255));
        oslDrawFillRect(base_x, base_y+20, base_x + offset, base_y+22, RGBA(255, 255, 255, 255));
    }
    //Tiempos
    string current = p.getCurrentTime();
    string total = p.getLength();
    drawStyledString(current,base_x,base_y+30,0.70f,LEFT,false,true,bar_size);
    drawStyledString(total,base_x + bar_size,base_y+30,0.70f,RIGHT,false,true,bar_size);

    drawStyledString("Nombre de archivo:",30,170,0.65f,LEFT,false,true,460);
    drawStyledString("Tasa de bits:",30,190,0.65f,LEFT,false,true,460);
    drawStyledString("Tamaño:",30,210,0.65f,LEFT,false,true,460);

    drawStyledString(p.getSongs().get(p.getCurrent()).GetFilename(),170,170,0.65f,LEFT,false,true,380);
    drawStyledString(p.getKbps(),170,190,0.65f,LEFT,false,true,380);
    drawStyledString(p.getSongs().get(p.getCurrent()).GetSize(),170,210,0.65f,LEFT,false,true,380);
    
}