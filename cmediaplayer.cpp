#include "cmediaplayer.h"


//Class Header
/************************************************************************************************/
/* */
/* ClassName : CMEDIAPLAYER*/
/* ParentClass(es) : QObject */
/* Friend of : -*/
/* */
/* Description : Contains all mediaplayer and playlist functions */
/* */
/* Author(s) : Sindhu Ramanath */
/* Date Created : */
/* */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/************************************************************************************************/


CMEDIAPLAYER::CMEDIAPLAYER(QObject *parent) : QObject(parent)
{
    //Creating QMediaplayer and QMediaplaylist objects
    oPlayer = new QMediaPlayer;
    oPlaylist = new QMediaPlaylist;
    oNewPlaylist = new QMediaPlaylist;
    m_opRecentPlaylist = new QMediaPlaylist;


    m_bPlaylistSelectedStatus = false;

    //Setting music directory
    m_oDirectoryPath = QDir::homePath()+"/Music/";

    QDir odirectory(m_oDirectoryPath);

    /* Filtering music files (.mp3) and playlists (.m3u) and storing them in stringlists*/
    m_oTracks = odirectory.entryList(QStringList()<<"*.mp3",QDir::Files);
    m_oListOfPlaylists = odirectory.entryList(QStringList()<<"*.m3u",QDir::Files);

    // Adding music files to alltracks playlist
    foreach(QString sTrack,m_oTracks)
    {
        oPlaylist->addMedia(QUrl::fromLocalFile(m_oDirectoryPath+sTrack));

    }

    //Initializing playlist and player
    oPlaylist->setCurrentIndex(0);
    oPlayer->setPlaylist(oPlaylist);
    oPlayer->setVolume(50);
    oPlaylist->setPlaybackMode(QMediaPlaylist::Loop);

    //connecting QMediaplayer signals - durationChanged and positionChanged
    connect(oPlayer,&QMediaPlayer::durationChanged,this,&CMEDIAPLAYER::durationChanged);
    connect(oPlayer,&QMediaPlayer::positionChanged,this,&CMEDIAPLAYER::positionChanged);

}

/*************************************************************************************************/
/* */
/* Function Name : fnvOnPlayClicked*/
/* */
/* Input(s) : play button checked state*/
/* Output : void */
/* Functionality : Toggles between QMediaplayer play() and pause() functions based on bchecked value */
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

void CMEDIAPLAYER::fnvOnPlayClicked(bool bChecked)
{
    if(bChecked)
    {
        oPlayer->play();
    }
    else
    {
        oPlayer->pause();
    }
}


/*************************************************************************************************/
/* */
/* Function Name : fnvOnNextClicked*/
/* */
/* Input(s) : - */
/* Output : void */
/* Functionality : calls QMediaplaylist function next()- changes current media to next media in the playlist*/
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

void CMEDIAPLAYER::fnvOnNextClicked()
{
    oPlayer->playlist()->next();
}


/*************************************************************************************************/
/* */
/* Function Name : fnvOnPreviousClicked*/
/* */
/* Input(s) : -*/
/* Output : void */
/* Functionality : calls QMediaplaylist function previous()- changes current media to previous media in the playlist */
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

void CMEDIAPLAYER::fnvOnPreviousClicked()
{
    //if current media position is less than 5 seconds, changes to previous track, else restarts current track
    if(oPlayer->position()<5000)
    {
        oPlayer->playlist()->previous();
    }
    else
    {
        oPlayer->setPosition(0);
    }
}


/*************************************************************************************************/
/* */
/* Function Name : fnvOnRepeatClicked*/
/* */
/* Input(s) : checked state of repeat button */
/* Output : void */
/* Functionality : on checked - sets player playback mode to loop, else sets playback mode to sequential */
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

void CMEDIAPLAYER::fnvOnRepeatClicked(bool bChecked)
{
    if(bChecked)
    {
        oPlayer->playlist()->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    }
    else
    {
        oPlayer->playlist()->setPlaybackMode(QMediaPlaylist::Loop);
    }
}

/*************************************************************************************************/
/* */
/* Function Name : fnvOnShuffleClicked*/
/* */
/* Input(s) : checked state of shuffle button */
/* Output : void */
/* Functionality : on checked - sets player playback mode to random, else sets playback mode to sequential */
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

void CMEDIAPLAYER::fnvOnShuffleClicked(bool bChecked)
{
    if(bChecked)
    {
        oPlayer->playlist()->setPlaybackMode(QMediaPlaylist::Random);
    }
    else
    {
        oPlayer->playlist()->setPlaybackMode(QMediaPlaylist::Loop);
    }
}


/*************************************************************************************************/
/* */
/* Function Name : fnvOnMuteClicked*/
/* */
/* Input(s) : checked state of mute button */
/* Output : void */
/* Functionality : calls QMediaPlayer setMuted function  */
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

void CMEDIAPLAYER::fnvOnMuteClicked(bool bChecked)
{
    oPlayer->setMuted(bChecked);
}


/*************************************************************************************************/
/* */
/* Function Name : fnvOnSeekbarSliderMoved*/
/* */
/* Input(s) : position of seekbar */
/* Output : void */
/* Functionality : calls QMediaPlayer setPosition function- sets current media position to seekbar position */
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

void CMEDIAPLAYER::fnvOnSeekbarSliderMoved(qint64 nPosition)
{
    oPlayer->setPosition(nPosition);
}

/*************************************************************************************************/
/* */
/* Function Name : fnvOnVolumeSliderMoved*/
/* */
/* Input(s) : position(value) of volume slider */
/* Output : void */
/* Functionality : calls QMediaPlayer setVolume function- sets current media volume to volume slider value */
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

void CMEDIAPLAYER::fnvOnVolumeSliderMoved(int nValue)
{
    oPlayer->setVolume(nValue);
}

/*************************************************************************************************/
/* */
/* Function Name : fnvOnTrackSelected*/
/* */
/* Input(s) : song index in listview */
/* Output : void */
/* Functionality : sets the current index of the playlist to the index of selected track */
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

void CMEDIAPLAYER::fnvOnTrackSelected(int nIndex)
{
    oPlayer->playlist()->setCurrentIndex(nIndex);
    //oPlayer->play();
}


/*************************************************************************************************/
/* */
/* Function Name : fnvOnTrackCheckBoxChecked*/
/* */
/* Input(s) : index of selected track (from listview) */
/* Output : void */
/* Functionality : saves checked state of track */
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

void CMEDIAPLAYER::fnvOnTrackCheckBoxChecked(int nIndex)
{
    m_oTrackCheckState.append(nIndex);
    qDebug()<<"Selected tracks:"<<m_oTrackCheckState;
}


/*************************************************************************************************/
/* */
/* Function Name : fnvRemovedCheckedState*/
/* */
/* Input(s) : track index */
/* Output : void */
/* Functionality : Updates the checked (selected) state of each track */
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

void CMEDIAPLAYER::fnvRemoveCheckedState(int nIndex)
{
    m_oTrackCheckState.removeAll(nIndex);
}

/*************************************************************************************************/
/* */
/* Function Name : fnvClearTrackCheckBox*/
/* */
/* Input(s) : - */
/* Output : void */
/* Functionality : clears track check state */
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

void CMEDIAPLAYER::fnvClearTrackCheckBox()
{
    m_oTrackCheckState.clear();
}

/*************************************************************************************************/
/* */
/* Function Name : fnnGetIndex*/
/* */
/* Input(s) : - */
/* Output : playlist current index */
/* Functionality : returns the index of the current media in playlist */
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

int CMEDIAPLAYER::fnnGetIndex()
{
    return oPlayer->playlist()->currentIndex();
}

/*************************************************************************************************/
/* */
/* Function Name : fnnGetMediaCount*/
/* */
/* Input(s) : - */
/* Output : playlist media count */
/* Functionality : returns the total number of tracks in current playlist */
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

int CMEDIAPLAYER::fnnGetMediaCount()
{
    return oPlayer->playlist()->mediaCount();
}


/*************************************************************************************************/
/* */
/* Function Name : fnvCreateNewPlaylist*/
/* */
/* Input(s) : playlist name  */
/* Output : void */
/* Functionality : adds selected media and saves playlist by the given name in m3u format */
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

void CMEDIAPLAYER::fnvCreateNewPlaylist(QString sName)
{
    QString sPath = m_oDirectoryPath+sName+".m3u";
    oNewPlaylist->clear();

    for(int i=0; i < m_oTrackCheckState.length(); i++)
    {
        oNewPlaylist->addMedia(QUrl::fromLocalFile(m_oDirectoryPath+m_oTracks[m_oTrackCheckState[i]]));
    }

    qDebug()<<"New playlist saved"<<oNewPlaylist->save(QUrl::fromLocalFile(sPath),"m3u");
    m_oListOfPlaylists.append(sName+".m3u");
    qDebug()<<"Playlist saved:"<<m_oListOfPlaylists;
    emit playlistListChanged();
    fnvClearTrackCheckBox();
    m_oDuplicatePlaylist = "";
}

/*************************************************************************************************/
/* */
/* Function Name : fnvAddToExistingPlaylist*/
/* */
/* Input(s) : playlist index */
/* Output : void */
/* Functionality : adds selected media to selected playlist */
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) Sindhu Ramanath*/
/* Checks for duplicates (fnoDuplicateTracksCheck is called). Prevents addition of duplicates  */
/* */
/*************************************************************************************************/

void CMEDIAPLAYER::fnvAddToExistingPlaylist(int nIndex)
{
    QList<int> nCheck;
    nCheck = fnoDuplicateTracksCheck(nIndex);
    if(!nCheck.isEmpty())
    {
        for(int i = 0; i < nCheck.length(); i++)
        {
            m_oTrackCheckState.removeAll(nCheck[i]);
        }
    }
    else
    {
        QString sPlaylistName = m_oDirectoryPath+m_oListOfPlaylists[nIndex];
        oNewPlaylist->clear();
        oNewPlaylist->load(QUrl::fromLocalFile(sPlaylistName),"m3u");
        if(!m_oTrackCheckState.isEmpty())
        {
            for(int i=0 ;i < m_oTrackCheckState.length(); i++)
            {
                oNewPlaylist->addMedia(QUrl::fromLocalFile(m_oDirectoryPath+m_oTracks[m_oTrackCheckState[i]]));
            }


            qDebug()<<"Added to existing"<<oNewPlaylist->save(QUrl::fromLocalFile(sPlaylistName),"m3u");
            fnvDisplayPlaylistTracks(sPlaylistName);
        }
        else
        {
            return;
        }
    }
    fnvClearTrackCheckBox();
    nCheck.clear();
}

/*************************************************************************************************/
/* */
/* Function Name : fnvDisplayPlaylistTracks*/
/* */
/* Input(s) : playlist name */
/* Output : void */
/* Functionality : Reads the playlist file line by line and extracts track names */
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

void CMEDIAPLAYER::fnvDisplayPlaylistTracks(QString sName)
{
    m_oPlaylistTracks.clear();
    QFile file(sName);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        return;

    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        m_oPlaylistTracks.append(line.mid(27,line.length()));

    }

    file.close();
    emit playlistTracksChanged();
}

/*************************************************************************************************/
/* */
/* Function Name : fnvLoadPlaylist*/
/* */
/* Input(s) : playlist index */
/* Output : void */
/* Functionality : Loads selected playlist tracks */
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

void CMEDIAPLAYER::fnvLoadPlaylist(int nPlaylistIndex)
{
    QString sPlayName = m_oDirectoryPath+m_oListOfPlaylists[nPlaylistIndex];
    qDebug()<<"Current playlist"<<m_oListOfPlaylists[nPlaylistIndex];
    oNewPlaylist->clear();
    oNewPlaylist->load(QUrl::fromLocalFile(sPlayName),"m3u");

    qDebug()<<"entered load" << sPlayName << oNewPlaylist->mediaCount() ;

    fnvDisplayPlaylistTracks(sPlayName);

    oPlayer->setPlaylist(oNewPlaylist);
    oNewPlaylist->setCurrentIndex(0);

    oNewPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
}

/*************************************************************************************************/
/* */
/* Function Name : vSetSelectedPlaylist*/
/* */
/* Input(s) : playlist index */
/* Output : void */
/* Functionality : Sets selected playlist index */
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

void CMEDIAPLAYER::fnvSetSelectedPlaylist(int nIndex)
{
    qDebug()<<"Inside set selected playlist";
    m_nPlaylistIndex = nIndex;
    qDebug()<<"Playlist no:"<<m_nPlaylistIndex;
    m_bPlaylistSelectedStatus = true;
    qDebug()<<"View status"<<m_bPlaylistSelectedStatus;
    emit statusChanged();
}

/*************************************************************************************************/
/* */
/* Function Name : fnvClearSelectedPlaylist*/
/* */
/* Input(s) : - */
/* Output : void */
/* Functionality : clears playlist index */
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

void CMEDIAPLAYER::fnvClearSelectedPlaylist()
{
    m_bPlaylistSelectedStatus = false;
    emit statusChanged();
    qDebug()<<"View status"<<m_bPlaylistSelectedStatus;
}

/*************************************************************************************************/
/* */
/* Function Name : fnvDeletePlaylist*/
/* */
/* Input(s) : - */
/* Output : void */
/* Functionality : Deletes selected playlists */
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

void CMEDIAPLAYER::fnvDeletePlaylist()
{
    for(int i = 0; i < m_oTrackCheckState.length(); i++)
    {
        QString path = m_oDirectoryPath+m_oListOfPlaylists[m_oTrackCheckState[i]];
        QFile file(path);
        file.remove();
        m_oListOfPlaylists.removeAt(m_oTrackCheckState[i]);
        emit playlistListChanged();
    }
    fnvClearTrackCheckBox();
    m_bPlaylistSelectedStatus = false;
}

/*************************************************************************************************/
/* */
/* Function Name : fnvDeleteTrack*/
/* */
/* Input(s) : - */
/* Output : void */
/* Functionality : Deletes selected tracks in playlist */
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

void CMEDIAPLAYER::fnvDeleteTrack()
{
    qDebug()<<"Inside track delete";
    QString playlist_name = m_oDirectoryPath+m_oListOfPlaylists[m_nPlaylistIndex];

    //oNewPlaylist->clear();

    //oNewPlaylist->load(QUrl::fromLocalFile(playlist_name),"m3u");
    for(int i = 0; i < m_oTrackCheckState.length(); i++)
    {
        qDebug()<<"Song removed"<<oNewPlaylist->removeMedia(m_oTrackCheckState[i]);
    }

    qDebug()<<"Save success"<<oNewPlaylist->save(QUrl::fromLocalFile(playlist_name),"m3u");
    fnvDisplayPlaylistTracks(playlist_name);
    fnvClearTrackCheckBox();
    emit countChanged();
}

/*************************************************************************************************/
/* */
/* Function Name : fnvSetToDefPlaylist*/
/* */
/* Input(s) : - */
/* Output : void */
/* Functionality : Sets current playlist to all tracks playlist*/
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

void CMEDIAPLAYER::fnvSetToDefPlaylist()
{
    oPlayer->setPlaylist(oPlaylist);
}

/*************************************************************************************************/
/* */
/* Function Name : fnoDuplicateTracksCheck*/
/* */
/* Input(s) : playlist index */
/* Output : Indexes of duplicate tracks */
/* Functionality : Checks if tracks are already present at the time of adding media. If true, stores the duplicate track indexes*/
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

QList<int> CMEDIAPLAYER::fnoDuplicateTracksCheck(int nIndex)
{
    QString sPath = m_oDirectoryPath+m_oListOfPlaylists[nIndex];
    QStringList oTrack;
    oTrack.clear();
    int bCheck = 0;
    oTrack.clear();

    qDebug()<<"In duplicate track check";
    for (int i = 0; i < m_oTrackCheckState.length(); i++)
    {
        oTrack.append("file://"+m_oDirectoryPath+m_oTracks[m_oTrackCheckState[i]]);
    }

    QFile file(sPath);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream in(&file);

        while(!in.atEnd()){

            QString line = in.readLine();
            for (int i =0; i < m_oTrackCheckState.length(); i++)
            {
                bCheck = QString::compare(line,oTrack[i],Qt::CaseInsensitive);
                if(!bCheck)
                {
                    qDebug()<<"inside comparison";
                    m_oDuplicateTrack.append(m_oTrackCheckState[i]);

                }
            }
        }
    }
    file.close();
    qDebug()<<m_oDuplicateTrack;
    return m_oDuplicateTrack;

}


/*************************************************************************************************/
/* */
/* Function Name : fnoGetDefPlaylistTracks*/
/* */
/* Input(s) : - */
/* Output : All tracks string list */
/* Functionality : returns QStringlist that contains names of all tracks */
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

QStringList CMEDIAPLAYER::fnoGetDefPlaylistTracks()
{
    return m_oTracks;
}


/*************************************************************************************************/
/* */
/* Function Name : fnbGetSelectedPlaylistStatus*/
/* */
/* Input(s) : - */
/* Output : integer */
/* Functionality : returns index of selected playlist */
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

bool CMEDIAPLAYER::fnbGetSelectedPlaylistStatus()
{
    return m_bPlaylistSelectedStatus;
}



/*************************************************************************************************/
/* */
/* Function Name : fnoGetTitle*/
/* */
/* Input(s) : - */
/* Output : Track title from metadata */
/* Functionality : Checks if title metadata exists. If false shows title as unknown*/
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

QString CMEDIAPLAYER::fnoGetTitle()
{
    if(oPlayer->metaData(QMediaMetaData::Title).isNull())
    {
        m_oMetadataTitle = "Unknown";

    }
    else{
        m_oMetadataTitle = oPlayer->metaData(QMediaMetaData::Title).toString();
    }

    return m_oMetadataTitle;
}



/*************************************************************************************************/
/* */
/* Function Name : fnoGetAlbumArtist*/
/* */
/* Input(s) : - */
/* Output : Track artist from metadata */
/* Functionality : Checks if artist metadata exists and stores artist name. If false shows artist as unknown*/
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

QString CMEDIAPLAYER::fnoGetAlbumArtist()
{
    if(oPlayer->metaData(QMediaMetaData::AlbumArtist).isNull())
    {
        m_oMetadataAlbumArtist = "Unknown";
    }
    else
    {
        m_oMetadataAlbumArtist = oPlayer->metaData(QMediaMetaData::AlbumArtist).toString();
    }

    return m_oMetadataAlbumArtist;
}

/*************************************************************************************************/
/* */
/* Function Name : fnoGetAlbumTitle*/
/* */
/* Input(s) : - */
/* Output : Track album title from metadata */
/* Functionality : Checks if album title metadata exists and stores it. If false shows album title as unknown*/
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

QString CMEDIAPLAYER::fnoGetAlbumTitle()
{
    if(oPlayer->metaData(QMediaMetaData::AlbumTitle).isNull())
    {
        m_oMetadataAlbumTitle = "Unknown";
    }
    else
    {
        m_oMetadataAlbumTitle = oPlayer->metaData(QMediaMetaData::AlbumTitle).toString();
    }

    return m_oMetadataAlbumTitle;
}


/*************************************************************************************************/
/* */
/* Function Name : fnoGetDuplicatePlaylistError*/
/* */
/* Input(s) : - */
/* Output : String containing duplicate playlist name */
/* Functionality : Returns duplicate playlist name*/
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

QString CMEDIAPLAYER::fnoGetDuplicatePlaylistError()
{
    return m_oDuplicatePlaylist;
}


/*************************************************************************************************/
/* */
/* Function Name : sGetListOfPlaylists*/
/* */
/* Input(s) : - */
/* Output : QStringlist */
/* Functionality : returns QStringlist that contains names of all playlists */
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

QStringList CMEDIAPLAYER::fnsGetListOfPlaylists()
{
    return m_oListOfPlaylists;
}


/*************************************************************************************************/
/* */
/* Function Name : fnsGetPlaylistTracks*/
/* */
/* Input(s) : - */
/* Output : QStringlist */
/* Functionality : returns QStringlist that contains all tracks in the playlist */
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

QStringList CMEDIAPLAYER::fnsGetPlaylistTracks()
{
    return m_oPlaylistTracks;
}


/*************************************************************************************************/
/* */
/* Function Name :fnoGetSearchList */
/* */
/* Input(s) : Text (track name to be searched) */
/* Output : list of songs found while searching*/
/* Functionality :It will search the text in the list of All Songs Name */
/* the tracks searched will be appended to the searched list  */
/*if no track is searched it will display "No track found" */
/* Member of :CMediaPlayer */
/* Friend of : */
/* */
/* Author(s) : Asheesh Kumar Singhal*/
/* Date Created : 3/10/18*/
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

QStringList CMEDIAPLAYER::fnoGetSearchList(QString oText)
{
    qDebug()<<"Inside get search list";
    QStringList oSearchedSongList;
    qDebug()<<m_oTracks;
    foreach(QString oTrackName,m_oTracks)
    {

        if(oTrackName.contains(oText,Qt::CaseInsensitive))
        {
            oSearchedSongList.append(oTrackName);
        }
    }

    if(oSearchedSongList.length() ==0){
        oSearchedSongList.append("No track found");
    }

    return oSearchedSongList;
}

/*************************************************************************************************/
/* */
/* Function Name : fnbDuplicatePlaylistCheck*/
/* */
/* Input(s) : playlist name */
/* Output : boolean value */
/* Functionality : Returns true if playlist already exists, else false*/
/* */
/* Member of :CMEDIAPLAYER */
/* Friend of : - */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

bool CMEDIAPLAYER::fnbDuplicatePlaylistCheck(QString sName)
{
    qDebug()<<"In duplicate playlist check";
    QString sPath = m_oDirectoryPath+sName+".m3u";
    QFileInfo oCheckFile(sPath);
    bool bCheck = oCheckFile.exists()&&oCheckFile.isFile();
    if(bCheck)
    {
        m_oDuplicatePlaylist = sName+" already exists";
        qDebug()<<"Dup name"<<m_oDuplicatePlaylist;
        emit duplicateChanged();
        return bCheck;
    }
    else
    {
        m_oDuplicatePlaylist = "";
        return bCheck;
    }
}

/*************************************************************************************************/
/* */
/* Function Name :fnoSelectSearchedTrack */
/* */
/* Input(s) : searched text and index of song selected*/
/* Output :  name of the song selected for search list view*/
/* Functionality :  gets the song name from searched ListView. Set the selected song as cuurent media and starts playing the song*/
/* */
/* Member of : CMediaPlayer*/
/* Friend of : */
/* */
/* Author(s) : */
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

QString CMEDIAPLAYER::fnoSelectSearchedTrack(QString oText, int nIndex)
{
    qDebug()<<"Inside select searched track";
    QStringList m_oSearchedTracks = fnoGetSearchList(oText);
    QString o_SongName = m_oSearchedTracks.at(nIndex);
    int song_index = m_oTracks.indexOf(o_SongName);
    oPlayer->setPlaylist(oPlaylist);
    oPlayer->playlist()->setCurrentIndex(song_index);
    // qDebug() << o_SongName;
    oPlayer->play();
    return o_SongName;
}




/*************************************************************************************************/
/* */
/* Function Name : fnoGetTrackName*/
/* */
/* Input(s) : */
/* Output : Current Track Name*/
/* Functionality :returns name of track currently being played */
/* */
/* Member of : CMediaPlayer*/
/* Friend of : */
/* */
/* Author(s) : Asheesh Kumar Singhal*/
/* Date Created : 3/10/18*/
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

QString CMEDIAPLAYER::fnoGetTrackName()
{
    qDebug()<<"Inside get track name";
    m_oCurrentTrackPath = oPlayer->currentMedia().canonicalUrl().toString();
    m_oCurrentTrackName = m_oCurrentTrackPath.mid(27, m_oCurrentTrackPath.length());
    QString  o_DisplayName = m_oCurrentTrackName;
    if(m_oCurrentTrackName.length()>20)
    {
        o_DisplayName =  m_oCurrentTrackName.remove(20, m_oCurrentTrackName.length());
        o_DisplayName.append("...");
        //qDebug()<<o_DisplayName;
    }

    return o_DisplayName;
}

/*************************************************************************************************/
/* */
/* Function Name :fnoAddTrackToRecentPlaylist */
/* */
/* Input(s) : */
/* Output : Recently Played Playlist having paths */
/* Functionality :If the currently track being played is present in list, it gets removed.   then, this function adds recently played track to  */
/* the m_oRecentlyPlayedList*/
/* Member of : */
/* Friend of : */
/* */
/* Author(s) : */
/* Date Created : */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

QStringList CMEDIAPLAYER::fnoAddTrackToRecentPlaylist()
{
    if(m_oRecentlyPlayedList.contains(m_oCurrentTrackPath.mid(7, m_oCurrentTrackPath.length())))
    {
        int i=m_oRecentlyPlayedList.indexOf(m_oCurrentTrackPath.mid(7, m_oCurrentTrackPath.length()));
        m_oRecentlyPlayedList.removeAt(i);
    }
    m_oRecentlyPlayedList.prepend(m_oCurrentTrackPath.mid(7, m_oCurrentTrackPath.length()));
    m_oRecentlyPlayedList.removeDuplicates();
    m_oRecentlyPlayedList.removeAll(QString(""));
    //qDebug()<<m_oRecentlyPlayedList;
    return m_oRecentlyPlayedList;
}



/*************************************************************************************************/
/* */
/* Function Name :fnvOnRecentlyPlayedClicked */
/* */
/* Input(s) : */
/* Output : sets the current playlist to  */
/* Functionality :on clicking on recently played button, it adds the tracks to recently played playlist m_opRecentPlaylist  */
/*                sets m_oRecentPlaylist as current playlist and starts playing the most recent track*/
/* Member of : CMediaPlayer*/
/* Friend of : */
/* */
/* Author(s) : Asheesh Kumar Singhal*/
/* Date Created : 3/10/18 */
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

void CMEDIAPLAYER::fnvOnRecentlyPlayedClicked()
{
    m_opRecentPlaylist->clear();
    foreach(QString song_path, m_oRecentlyPlayedList)
    {
        m_opRecentPlaylist->addMedia(QUrl::fromLocalFile(song_path));
    }


    oPlayer->setPlaylist(m_opRecentPlaylist);
    //oPlayer->playlist()->setCurrentIndex(song_index);
    oPlayer->play();
}


/*************************************************************************************************/
/* */
/* Function Name : fnoGetRecentPlaylist*/
/* */
/* Input(s) : */
/* Output : Name of songs which are recently played*/
/* Functionality :extracts name of songs from their respective paths in m_oRecentlyPlayedList */
/* */
/* Member of :CMediaPlayer */
/* Friend of : */
/* */
/* Author(s) : Asheesh Kumar Singhal*/
/* Date Created : 3/10/18*/
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

QStringList CMEDIAPLAYER::fnoGetRecentPlaylist()
{
    QStringList oRecentlyPlayedSongNames;

    foreach(QString oTrackPath,m_oRecentlyPlayedList )
    {
        oRecentlyPlayedSongNames.append(oTrackPath.mid(20, m_oCurrentTrackPath.length()));
    }
    return oRecentlyPlayedSongNames;
}


/*************************************************************************************************/
/* */
/* Function Name :fnoGetTrackCheckState */
/* */
/* Input(s) : -*/
/* Output : Check state of track */
/* Functionality :returns true if track check boxes have been checked*/
/* */
/* Member of :CMediaPlayer */
/* Friend of : */
/* */
/* Author(s) : Sindhu Ramanath*/
/* Date Created :  3/10/18*/
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/
bool CMEDIAPLAYER::fnoGetTrackCheckState()
{
    if(m_oTrackCheckState.isEmpty())
        return false;
    else
        return true;
}


/*************************************************************************************************/
/* */
/* Function Name :fnoSelectRecentlyPlayedTrack */
/* */
/* Input(s) : Index of selected track*/
/* Output : Song Name selected */
/* Functionality :plays the selected song from recently played playlist*/
/* */
/* Member of :CMediaPlayer */
/* Friend of : */
/* */
/* Author(s) : Asheesh Kumar Singhal*/
/* Date Created :  3/10/18*/
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

QString CMEDIAPLAYER::fnoSelectRecentlyPlayedTrack(int nIndex)
{
    fnvOnRecentlyPlayedClicked();
    fnoGetRecentPlaylist();
    oPlayer->setPlaylist(m_opRecentPlaylist);
    QString oSong_Name = m_oRecentlyPlayedList.at(nIndex);
    qDebug()<<("In Recently Played SElected");
    //qDebug()<<(oSong_Name);
    //oPlayer->setMedia(QUrl::fromLocalFile(oSong_Name));
    qDebug()<<nIndex;

    //int song_index = m_oRecentlyPlayedList.indexOf(oSong_Name);

    oPlayer->playlist()->setCurrentIndex(nIndex);

    oPlayer->play();
    return oSong_Name;
}

/*************************************************************************************************/
/* */
/* Function Name : oGetTrackList*/
/* */
/* Input(s) : */
/* Output : list of songs in all songs*/
/* Functionality : */
/* */
/* Member of :CMediaPlayer */
/* Friend of : */
/* */
/* Author(s) : Asheesh Kumar Singhal*/
/* Date Created : 3/10/18*/
/* Modifications : - Date Author(s) */
/* - Modification Details */
/* */
/*************************************************************************************************/

QStringList CMEDIAPLAYER::fnoGetTrackList()
{
    return m_oTracks;
}

int CMEDIAPLAYER::getIndex()
{

    return oPlaylist->currentIndex();
}






