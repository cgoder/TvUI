#include <stdio.h>
#include "MediaPlayer.h"

CCMediaPlayer* CCMediaPlayer::mMediaPlayer = NULL;
CCMediaPlayer* CCMediaPlayer::getInstance()
{
    if (mMediaPlayer == NULL) {
        mMediaPlayer = new CCMediaPlayer();
    }
    return mMediaPlayer;
}

void CCMediaPlayer::destoryInstance(void)
{
    if (mMediaPlayer != NULL) {
        delete mMediaPlayer;
        mMediaPlayer = NULL;            
    }
}

CCMediaPlayer::CCMediaPlayer()
{  
   
}

CCMediaPlayer::~CCMediaPlayer()
{

}

void CCMediaPlayer::setListener(const ccMediaPlayerCallback& callback) 
{

}

int CCMediaPlayer::setDataSource(string& path, MP_TYPE_e type)
{
    return 0;
}

int CCMediaPlayer::prepareAsync()
{   
    return 0;
}

BOOL CCMediaPlayer::ProcessEvent(void * arg1, void * arg2, void * arg3)
{
	return TRUE;
}

int CCMediaPlayer::start()
{
    return 0;    
}

int CCMediaPlayer::stop()
{
    return 0;
}

int CCMediaPlayer::pause()
{
    return 0;
}

bool CCMediaPlayer::isPlaying()
{
    return false;       
}

int CCMediaPlayer::seekTo(int msec)
{
    return 0;
}

int CCMediaPlayer::getCurrentPosition(int* PositionMs)
{
    return 0;
}

int CCMediaPlayer::getDuration(int * duration)
{

    return 0;
}

int CCMediaPlayer::reset()
{    
    return 0;
}

int CCMediaPlayer::zoom(const MP_ZOOM_SCALE_e eScale)
{
    return 0;
}

//    MP_ZOOM_SCALE_e getZoomScale();
int CCMediaPlayer::rotate(const MP_DEGREE_e eDegree)
{
    return 0;
}

int CCMediaPlayer::move(const MP_MOVE_DIRECTION_e eMove, const unsigned int u32Offset)
{
    return 0;
}

int CCMediaPlayer::getMusicTitle(string& title)
{
    return 0;
}


int CCMediaPlayer::getMusicAlbum(string& album)
{
    return 0;
}

int CCMediaPlayer::getMusicArtist(string& artist)
{
    return 0;
}

int CCMediaPlayer::getMusicPicture(void* &ptr, int& size)
{
    return 0;
}


