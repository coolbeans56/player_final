// This is the header file for the class MEDIAPLAYER, which is responsible for all functionalities of the mediaplayer
// Derived from: QObject class


#ifndef CMEDIAPLAYER_H
#define CMEDIAPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDir>
#include <QMediaMetaData>
#include <QQuickView>
#include <QQmlContext>
#include <QFile>
#include <QFileInfo>

class CMEDIAPLAYER : public QObject
{
    //ash
    Q_PROPERTY(QStringList track_list READ fnoGetTrackList)
    Q_PROPERTY(int index READ getIndex)
    Q_PROPERTY(QString track_name READ fnoGetTrackName)

    Q_PROPERTY(bool status READ fnbGetSelectedPlaylistStatus NOTIFY statusChanged)
    Q_PROPERTY(QStringList playlist_tracks READ fnsGetPlaylistTracks NOTIFY playlistTracksChanged)
    Q_PROPERTY(QStringList playlist_list READ fnsGetListOfPlaylists NOTIFY playlistListChanged)
    Q_PROPERTY(QString playlist_duplicate READ fnoGetDuplicatePlaylistError NOTIFY duplicateChanged)
    Q_PROPERTY(int count READ fnnGetMediaCount NOTIFY countChanged)
    Q_PROPERTY(QString song_title READ fnoGetTitle)
    Q_PROPERTY(QString song_artist READ fnoGetAlbumArtist)
    Q_PROPERTY(QString song_album READ fnoGetAlbumTitle)
    Q_PROPERTY(QStringList def_track_list READ fnoGetDefPlaylistTracks)
    Q_PROPERTY(int currentMediaIndex READ fnnGetIndex)
    Q_OBJECT
public:
    explicit CMEDIAPLAYER(QObject *parent = nullptr);
    Q_INVOKABLE QStringList fnoGetSearchList(QString oText);
    Q_INVOKABLE bool fnbDuplicatePlaylistCheck(QString sName);
    Q_INVOKABLE QStringList fnoGetRecentPlaylist();
    Q_INVOKABLE bool fnoGetTrackCheckState();

signals:
    void durationChanged(qint64 duration);
    void positionChanged(qint64 position);
    void countChanged();
    void playlistListChanged();
    void playlistTracksChanged();
    void statusChanged();
    void metadataChanged();
    void duplicateChanged();



public slots:
    void fnvOnPlayClicked(bool bChecked);
    void fnvOnNextClicked();
    void fnvOnPreviousClicked();
    void fnvOnRepeatClicked(bool bChecked);
    void fnvOnShuffleClicked(bool bChecked);
    void fnvOnMuteClicked(bool bChecked);

    void fnvOnSeekbarSliderMoved(qint64 nPosition);
    void fnvOnVolumeSliderMoved(int nValue);
    void fnvOnTrackSelected(int nIndex);

    void fnvOnTrackCheckBoxChecked(int nIndex);
    void fnvRemoveCheckedState(int nIndex);
    void fnvClearTrackCheckBox();

    int fnnGetIndex();
    int fnnGetMediaCount();

    void fnvCreateNewPlaylist(QString sName);
    void fnvAddToExistingPlaylist(int nIndex);
    void fnvDisplayPlaylistTracks(QString sName);
    void fnvLoadPlaylist(int nPlaylistIndex);
    void fnvSetSelectedPlaylist(int nIndex);
    void fnvClearSelectedPlaylist();
    void fnvDeletePlaylist();
    void fnvDeleteTrack();
    void fnvSetToDefPlaylist();

    QList<int> fnoDuplicateTracksCheck(int nIndex);

    QStringList fnoGetDefPlaylistTracks();

    bool fnbGetSelectedPlaylistStatus();


   QString fnoGetTitle();
   QString fnoGetAlbumArtist();
   QString fnoGetAlbumTitle();

   QString fnoGetDuplicatePlaylistError();
   QStringList fnsGetListOfPlaylists();
   QStringList fnsGetPlaylistTracks();


    //ash

    QString fnoSelectSearchedTrack(QString oText, int nIndex);
    QString fnoGetTrackName();
    QStringList fnoAddTrackToRecentPlaylist();
    void fnvOnRecentlyPlayedClicked();

    QString fnoSelectRecentlyPlayedTrack(int nIndex);
    QStringList fnoGetTrackList();
    int getIndex();


private:
    QMediaPlayer *oPlayer;
    QMediaPlaylist *oPlaylist;
    QMediaPlaylist *oNewPlaylist;

    QString m_oDirectoryPath;
    QStringList m_oTracks;
    QStringList m_oListOfPlaylists;

    QList <int> m_oTrackCheckState;

    QStringList m_oPlaylistTracks;
    int m_nPlaylistIndex;
    bool m_bPlaylistSelectedStatus;
    QString m_oMetadataTitle;
    QString m_oMetadataAlbumArtist;
    QString m_oMetadataAlbumTitle;
    QString m_oDuplicatePlaylist;
    QList<int> m_oDuplicateTrack;


    //ash
    QMediaPlaylist *m_opRecentPlaylist;
    QString m_oCurrentTrackName;
    QString m_oCurrentTrackPath;
    QStringList m_oRecentlyPlayedList;



};

#endif // CMEDIAPLAYER_H
