#ifndef LOREWALKER_SKYPLAYER_H
#define LOREWALKER_SKYPLAYER_H

#include <string>
#include <functional>
#ifndef _WIN32
#include <pthread.h>
#endif

typedef enum {
    MP_TYPE_MUSIC,
    MP_TYPE_PHOTO,
    MP_TYPE_VIDEO,
    MP_TYPE_UNKNOWN,
}MP_TYPE_e;

typedef enum {
    MP_MSG_ERROR,
    MP_MSG_PREPARED,
    MP_MSG_COMPLETED,
    MP_MSG_VIDEO_SIZE_CHANGED,
    MP_MSG_SEEK_COMPLETE,
}MP_MSG_e;

typedef enum 
{
    MP_STATE_IDLE,
    MP_STATE_INITIALIZED,
    MP_STATE_ASYNC_PREPARING,
    MP_STATE_PREPARED,
    MP_STATE_STARTED,
    MP_STATE_PAUSED,
    MP_STATE_STOPPED,
    MP_STATE_ERROR,
}MP_STATE_e;

/// Define media item (photo and movie) view move direction.
typedef enum
{
    /// The zoom factor is one eighth.
    MP_ZOOM_SCALE_1_8,
    /// The zoom factor is one forth.
    MP_ZOOM_SCALE_1_4,
    /// The zoom factor is half.
    MP_ZOOM_SCALE_1_2,
    /// The zoom factor is 1X.
    MP_ZOOM_SCALE_1,
    /// The zoom factor is 2X.
    MP_ZOOM_SCALE_2,
    /// The zoom factor is 4X.
    MP_ZOOM_SCALE_4,
    /// The zoom factor is 8X.
    MP_ZOOM_SCALE_8,
    /// The zoom factor is 10/12X.
    MP_ZOOM_SCALE_10_12,
    /// The zoom factor is 10/16X.
    MP_ZOOM_SCALE_10_16,
    /// The zoom factor is 10/18X.
    MP_ZOOM_SCALE_10_18,
    /// The zoom factor is 1.2X.
    MP_ZOOM_SCALE_12_10,
    /// The zoom factor is 1.6X.
    MP_ZOOM_SCALE_16_10,
    /// The zoom factor is 1.8X.
    MP_ZOOM_SCALE_18_10,
    /// the total counts of this enum
    MP_ZOOM_SCALE_NUM,
}MP_ZOOM_SCALE_e;

/// Define media item (photo and movie) view move direction.
typedef enum
{
    /// 0 degree.
    MP_DEGREE_0,
    /// 90 degrees.
    MP_DEGREE_90,
    /// 180 degrees.
    MP_DEGREE_180,
    /// 270 degrees.
    MP_DEGREE_270,
    /// the total counts of this enum
    MP_DEGREE_NUM,
} MP_DEGREE_e;

/// Define media item (photo and movie) view move direction.
typedef enum
{
    /// The view move direction is up.
    MP_MOVE_DIRECTION_UP,
    /// The view move direction is down.
    MP_MOVE_DIRECTION_DOWN,
    /// The view move direction is left.
    MP_MOVE_DIRECTION_LEFT,
    /// The view move direction is right.
    MP_MOVE_DIRECTION_RIGHT,
    /// the total counts of this enum
    MP_MOVE_DIRECTION_NUM,
} MP_MOVE_DIRECTION_e;


class MSrv_MediaFile;
class MSrv_MM_PlayerInterface;

typedef std::function<void (MP_MSG_e, void* pUserData)> ccMediaPlayerCallback;

#ifdef _WIN32
//#include <WinDef.h>
typedef unsigned long      U32;
typedef int      BOOL;
#else
typedef unsigned long      U32;
typedef unsigned char      BOOL;

#endif

#if !defined(TRUE)
#define TRUE 1
#endif

#if !defined(FALSE)
#define FALSE 0
#endif

using std::string;

class CCMediaPlayer
{	
private:
    static CCMediaPlayer* mMediaPlayer;
    CCMediaPlayer();
    ~CCMediaPlayer();	

public:
    static CCMediaPlayer* getInstance();    
    static void destoryInstance(void);
    
    void setListener(const ccMediaPlayerCallback& callback);    
    void removeListener(void);
    
    int  setDataSource(string& path,MP_TYPE_e type);
    int  prepareAsync() ;
    int  start();
    int  stop();
    int  reset();
    int  pause();
    bool isPlaying() ;
    int  seekTo(int msec);
    int  getCurrentPosition(int *msec);
    int  getDuration(int *msec);

    //only used for photo player.
    int zoom(const MP_ZOOM_SCALE_e eScale);
//    MP_ZOOM_SCALE_e getZoomScale();
    int rotate(const MP_DEGREE_e eDegree);
    int move(const MP_MOVE_DIRECTION_e eDirection, const unsigned int u32Offset);

    //only used for music player ,id3info
    int getMusicTitle(string& title);
    int getMusicAlbum(string& album);
    int getMusicArtist(string& artist); 
    int getMusicPicture(void* &ptr, int& size);
   
private:
    static BOOL ProcessEvent(void * arg1, void * arg2, void * arg3);
    //player status.
    MP_STATE_e mState;
    MP_TYPE_e mType;
    //mstar interface ptr
    MSrv_MM_PlayerInterface *m_pMMInterface;
    MSrv_MediaFile * m_pMediaFile;
    U32 m_u32MediaItem;
    
    //msg notify to player app
    ccMediaPlayerCallback mCallback;   
#ifndef _WIN32
    pthread_mutex_t mMutex;
#endif
    //used for store music picture
    U32 mAlbumSize;    
    U32 mAlbumOffset;
};

#endif//LOREWALKER_SKYPLAYER_H
