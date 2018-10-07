import QtQuick 2.6
import QtQuick.Window 2.0
import QtQuick.Controls 1.5
import QtQuick.Controls 2.0

import QtQuick.Dialogs 1.2
import QtQml.Models 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import mediaplayer 1.0

Window{

    visible: true
    width: 1080
    height:725
    //property alias searchview: searchview
    //  property alias rectangle: rectangle
    title: qsTr("Media Player")
    property int time;
    property int s;
    property int min;
    property int sec;
    property bool view_status;


    Player{
        id:player
        onDurationChanged: {
            //player.fnoAddTrackToRecentPlaylist()
            time = duration;
            s = time/1000;
            min = s/60;
            sec = s%60;
            duration_field.text = min+":"+sec

            //seekbar.maximumValue = duration
            metadata.text = "Title:"+player.song_title+"\n"+"Artist:"+player.song_artist+"\n"+"Album:"+player.song_album
            track_list.currentIndex = player.currentMediaIndex
            view_status = player.status;

            //ash

            player.fnoAddTrackToRecentPlaylist()
            text1.text = player.track_name
            //recently_played_songs_listview.model = player.fnoGetRecentPlaylist()


            if(!view_status)
            {
                track_list.currentIndex = player.currentMediaIndex
                track_count.text = (player.currentMediaIndex+1)+"/"+player.count

            }
            else
            {
                //tabView.getTab(1).item.children[0].currentIndex = player.currentMediaIndex
                track_count.text = (player.currentMediaIndex+1)+"/"+player.count
            }

            tabView.getTab(2).item.children[0].model = player.fnoGetRecentPlaylist()

        }
        onPositionChanged: {
            time = position
            s = time/1000;
            min = s/60;
            sec = s%60;
            position_field.text = min+":"+sec
            seekbar.value = position
        }

    }



    Page{


        id:welcomepage
        x: 0
        y: 0
        width:1080
        height:725
        z:1





        //        Image{
        //            id:image23
        //            x: 0
        //            y: 0
        //            width: 1080
        //            height:50
        //            source: 'qrc:/Icons/M_05_Bosch-Supergraphic-BG.png'


        //        }
        Image {
            id: image22
            x: 65
            y: 75
            anchors.fill: parent
            width: 1080
            height:720
            source: '/home/kenshin/QT/frontend_final/frontend/Icons'
            ScaleAnimator{
                target:image22
                from:0.1
                to:1
                duration:1500
                running: true
            }
            OpacityAnimator{
                target:image22
                from:0.1
                to:1
                duration: 1500
                running:true
            }
        }

        Timer{
            id:timer
            interval: 5000
            running:true
            onTriggered: homepage.open()

        }

        function open(){
            visible = true
            welcomepage.z =  1
            homepage.z=0
        }


    }
    //    Page{


    //            id:rp_page
    //            x: 0
    //            y: 0
    //            width:525
    //            height:300
    //            function open(){
    //                visible = true
    //                rp_page.z =  1
    //                menuwin.z =0
    //                homepage.z=0
    //            }






    //        //Rectangle{

    //            Image {
    //                id: background2
    //                x: -7
    //                y: -39
    //            anchors.fill:parent
    //                source:'qrc:/icons/Icons/hd grey.jpeg'

    //            //anchors.fill: parent
    //            Component{
    //                id:rp_delegate
    //                Item{
    //                    width:parent.width
    //                    height:15
    //                    property int track_list_index: index


    //                    Text{
    //                        text:modelData
    //                    }

    //                    MouseArea{
    //                        anchors.fill:parent
    //                        onClicked: player.fnoSelectRecentlyPlayedTrack(track_list_index)
    //                    }
    //                }

    //            }


    //            ListView {
    //                id: recently_played_songs_listview
    //                x: 128
    //                y: 89
    //                width: 330
    //                height: 312

    //                anchors.bottomMargin: 202
    //                anchors.leftMargin: 475
    //                anchors.rightMargin: 35
    //                anchors.topMargin: 78
    //                focus: true
    //                clip: true

    //                //model:player.recently_played_playlist()
    //                delegate: rp_delegate
    //               // highlightFollowsCurrentItem: true
    //                    /*Component{

    //                        Text {
    //                            text: modelData
    //                        }*/
    //    //            highlight: Rectangle {
    //    //                width: parent.width
    //    //                color: "lightblue"


    //    //            }
    //            }

    //}
    //            Image {
    //                //   property bool checked : false
    //                id: home
    //                x: 0
    //                y: 9
    //                width: 31
    //                height: 30
    //                source: 'qrc:/icons/Icons/home.png'

    //                MouseArea
    //                {
    //                    anchors.rightMargin: -3
    //                    anchors.bottomMargin: -5
    //                    anchors.leftMargin: -3
    //                    anchors.topMargin: -5
    //                    anchors.fill : parent

    //                    onClicked:

    //                        homepage.open()


    //                }
    //            }
    //    }

    //}




    Page{
        id:homepage
        x: 0
        y: 0
        width:525
        height:350




        Image {
            id: background1
            x: 0
            y: 0
            width: 1080
            height: 725
            source:'/home/kenshin/QT/frontend_final/frontend/Icons'



            Image {
                id: image1
                x: 472
                y: 237
                width: 195
                height: 160
                source: 'qrc:/icons/Icons/music.png'
            }

            Slider {
                id: volume_slider
                x: 1023
                y: 142
                width: 23
                height: 377
                //  activeFocusOnPress: true

                value: 0
                orientation: Qt.Vertical
                //maximumValue: 100
                //minimumValue: 0

                onValueChanged:{
                    player.fnvOnVolumeSliderMoved(value)

                }

            }

            Text {
                id: duration_field
                x: 891
                y: 501
                width: 45
                height: 13
                fontSizeMode: Text.Fit

                font.pixelSize: 12

            }

            Text {
                id: text1
                x: 488
                y: 429
                width: 163
                height: 18
                //text: qsTr("name_of _song")
                font.pixelSize: 12
                //text:player.track_name
            }

            Text {
                id: metadata
                x: 158
                y: 283
                width: 262
                height: 102
                text: qsTr("")
                font.pixelSize: 12
                clip:true
            }

            Label {
                id: track_count
                x: 351
                y: 440
                width: 54
                height: 18
                text: qsTr("")
                font.family: "Arial"
                font.pointSize: 9
                lineHeight: 0.5
                fontSizeMode: Text.Fit
            }

            Text {
                id: position_field
                x: 184
                y: 503
                width: 73
                height: 16
                font.pixelSize: 12
            }

            Slider {
                id: seekbar
                x: 170
                y: 525
                width: 766
                height: 22
                spacing: 3
                focusPolicy: Qt.StrongFocus
                orientation: Slider.SnapAlways
                to: 1

                MouseArea{
                    anchors.rightMargin: 0
                    anchors.bottomMargin: 0
                    anchors.leftMargin: 0
                    anchors.topMargin: 0
                    anchors.fill:parent
                    //maximumValue:duration
                    onClicked: player.fnvOnSeekbarSliderMoved((seekbar.maximumValue*mouseX)/seekbar.width)
                }
            }

        }


        Image {
            //   property bool checked : false
            id: home1
            x: 3
            y: 70
            width: 50
            height: 50
            source: 'qrc:/icons/Icons/home.png'

            MouseArea
            {
                anchors.rightMargin: -3
                anchors.bottomMargin: -5
                anchors.leftMargin: -3
                anchors.topMargin: -5
                anchors.fill : parent

                onClicked:

                    homepage.open()


            }
        }



        //        Image {
        //            property bool checked : false
        //            id: rp_image
        //            x: 0
        //            y: 90
        //            width: 31
        //            height: 30
        //            source: 'qrc:/icons/Icons/home.png'

        //            MouseArea
        //            {
        //                anchors.rightMargin: -3
        //                anchors.bottomMargin: -5
        //                anchors.leftMargin: -3
        //                anchors.topMargin: -5
        //                anchors.fill : parent

        //                onClicked:

        //                    rp_page.open()


        //            }
        //        }












        Image {
            //  property bool checked : false
            id: menu
            x: 3
            y: 170
            width: 45
            height: 45
            source: 'qrc:/icons/Icons/menu.png'

            MouseArea
            {
                anchors.rightMargin: -2
                anchors.bottomMargin: -10
                anchors.leftMargin: -4
                anchors.topMargin: 0
                anchors.fill : parent

                onClicked:{


                    menuwin.open()
                    tabView.currentIndex=0
                }

            }

        }

        Image {
            property bool checked : false

            id: shuffle
            x: 825
            y: 550
            width: 69
            height: 51
            source: 'qrc:/icons/Icons/shuffle.png'

            MouseArea
            {
                anchors.rightMargin: 0
                anchors.bottomMargin: -7
                anchors.leftMargin: -7
                anchors.topMargin: 0
                anchors.fill : parent

                onClicked:
                {
                    parent.checked = !parent.checked

                    if(parent.checked)

                    {
                        player.fnvOnShuffleClicked(parent.checked)
                        repeat.enabled = false
                        //  player.shuffle()
                        shuffle.opacity = 0.5
                    }
                    else
                    {
                        player.fnvOnShuffleClicked(parent.checked)
                        repeat.enabled = true

                        //  player.seq()
                        shuffle.opacity = 1
                    }

                }
            }
        }





        Image {
            property bool checked : false

            id: repeat
            x: 201
            y: 550
            width: 68
            height: 51
            source: 'qrc:/icons/Icons/repeat1.png'

            MouseArea
            {
                anchors.rightMargin: -1
                anchors.bottomMargin: -5
                anchors.leftMargin: -5
                anchors.topMargin: 3
                anchors.fill : parent

                onClicked:
                {
                    parent.checked = !parent.checked

                    if(parent.checked)

                    {
                        player.fnvOnRepeatClicked(parent.checked)
                        shuffle.enabled = false
                        //  player.shuffle()
                        repeat.opacity = 0.5
                    }
                    else
                    {
                        player.fnvOnRepeatClicked(parent.checked)
                        shuffle.enabled = false
                        //  player.seq()
                        repeat.opacity = 1
                    }

                }
            }
        }





        Image {
            property bool checked : false
            id: mute
            x: 988
            y: 550
            width: 67
            height: 51

            source: checked ? 'qrc:/icons/Icons/speakerno.png': 'qrc:/icons/Icons/speaker.png'


            MouseArea
            {
                anchors.rightMargin: -3
                anchors.bottomMargin: -8
                anchors.leftMargin: -5
                anchors.topMargin: 2

                anchors.fill : parent

                onClicked:
                {
                    parent.checked = !parent.checked
                    player.fnvOnMuteClicked(parent.checked)

                    if(parent.checked)

                    {
                        //  player.shuffle()
                        //volume.opacity = 0.5
                    }
                    else
                    {
                        //  player.seq()
                        // repeat.opacity = 1
                    }

                }
            }
        }
        Image {
            property bool checked : false
            id: playpause
            x: 524
            y: 550
            width: 66
            height: 56

            source: checked ? 'qrc:/icons/Icons/pause.png': 'qrc:/icons/Icons/play.png'


            MouseArea
            {
                anchors.rightMargin: -4
                anchors.bottomMargin: -6
                anchors.leftMargin: -4
                anchors.topMargin: 0

                anchors.fill : parent

                onClicked:
                {
                    parent.checked = !parent.checked
                    player.fnvOnPlayClicked(parent.checked)

                    if(parent.checked)

                    {
                        playpause1.checked=true



                        //  player.shuffle()
                        //volume.opacity = 0.5
                    }
                    else
                    {
                        playpause1.checked=false
                        //  player.seq()
                        // repeat.opacity = 1
                    }

                }
            }
        }

        Image {

            id: next
            x: 691
            y: 550
            width: 50
            height: 51
            source: 'qrc:/icons/Icons/next.png'


            MouseArea
            {
                anchors.rightMargin: 0
                anchors.bottomMargin: -7
                anchors.leftMargin: -3
                anchors.topMargin: 1

                anchors.fill : parent

                onClicked:
                {

                    player.fnvOnNextClicked()

                    //                    if(parent.checked)

                    //                    {
                    //                        //  player.shuffle()
                    //                        //volume.opacity = 0.5
                    //                    }


                }
            }
        }
        Image {

            id: previous
            x: 383
            y: 550
            width: 57
            height: 51
            source: 'qrc:/icons/Icons/previous.png'


            MouseArea
            {
                anchors.rightMargin: -6
                anchors.bottomMargin: -6
                anchors.leftMargin: -4
                anchors.topMargin: 0

                anchors.fill : parent

                onClicked:
                {
                    //parent.checked = !parent.checked
                    player.fnvOnPreviousClicked()

                    //                    if(parent.checked)

                    //                    {
                    //                        //  player.shuffle()
                    //                        //volume.opacity = 0.5
                    //                    }


                }
            }
        }

        Image {

            id:search
            x: 1000
            y: 70
            width: 70
            height: 51
            source: 'qrc:/icons/Icons/search.png'


            MouseArea
            {
                anchors.rightMargin: -4
                anchors.bottomMargin: -4
                anchors.leftMargin: -4
                anchors.topMargin: -2

                anchors.fill : parent

                onClicked:
                {
                    tabView.currentIndex = 3
                    menuwin.open()
                }
            }
        }

        function open(){
            visible = true
            menuwin.z =  0
            homepage.z=1
        }

    }


    Page{
        id:menuwin
        width: 1080
        height: 725
        x:0
        y:0


        function open(){
            visible = true
            menuwin.z =  1
            homepage.z=0
        }


        Image {
            id: backgroundm
            x: 0
            y: 0
            width: 1080
            height: 725
            source:'/home/kenshin/QT/frontend_final/frontend/Icons'


            Image {
                // property bool checked : false
                id: homem
                x: 0
                y: 70
                width: 50
                height: 50
                source: 'qrc:/icons/Icons/home.png'

                MouseArea
                {
                    anchors.rightMargin: -3
                    anchors.bottomMargin: -5
                    anchors.leftMargin: -3
                    anchors.topMargin: -5
                    anchors.fill : parent

                    onClicked:homepage.open()


                }
            }




            TabView {

                id:tabView

                x: 100
                y: 80
                width:1080
                height: 0

                Image {
                    id: trackimage
                    x: 3
                    y: 475
                    width: 100
                    height: 100
                    source: '/home/kenshin/QT/frontend_final/frontend/Icons'
                }
                Image {

                    id: next1
                    x: 800
                    y: 500
                    width: 60
                    height: 60
                    source: 'qrc:/icons/Icons/next.png'


                    MouseArea
                    {
                        anchors.rightMargin: 0
                        anchors.bottomMargin: -7
                        anchors.leftMargin: -3
                        anchors.topMargin: 1

                        anchors.fill : parent

                        onClicked:
                        {

                            player.fnvOnNextClicked()

                            //                    if(parent.checked)

                            //                    {
                            //                        //  player.shuffle()
                            //                        //volume.opacity = 0.5
                            //                    }


                        }
                    }
                }
                Image {

                    id: previous1
                    x: 300
                    y: 500
                    width: 60
                    height: 60
                    source: 'qrc:/icons/Icons/previous.png'


                    MouseArea
                    {
                        anchors.rightMargin: -6
                        anchors.bottomMargin: -6
                        anchors.leftMargin: -4
                        anchors.topMargin: 0

                        anchors.fill : parent

                        onClicked:
                        {

                            player.fnvOnPreviousClicked()
                        }
                    }
                }


                Image {
                    property bool checked : false
                    id: playpause1
                    x: 550
                    y: 490
                    width: 75
                    height: 75

                    source: checked ? 'qrc:/icons/Icons/pause.png': 'qrc:/icons/Icons/play.png'


                    MouseArea
                    {
                        anchors.rightMargin: -4
                        anchors.bottomMargin: -6
                        anchors.leftMargin: -4
                        anchors.topMargin: 0

                        anchors.fill : parent

                        onClicked:
                        {
                            parent.checked = !parent.checked
                            player.fnvOnPlayClicked(parent.checked)

                            if(parent.checked)

                            {
                                playpause.checked=true



                                //  player.shuffle()
                                //volume.opacity = 0.5
                            }
                            else
                            {
                                //  player.seq()
                                playpause.checked=false
                                // repeat.opacity = 1
                            }

                        }
                    }
                }


                Tab {
                    id:allsongs
                    title: "Allsongs"
                    width: 300
                    height:300
                    onVisibleChanged: player.fnvSetToDefPlaylist()


                    Rectangle{
                        width: 150


                        //all tracks view here

                        ListView {
                            id: track_list
                            width: 300
                            height: 249
                            anchors.bottomMargin: 202
                            anchors.leftMargin: 475
                            anchors.rightMargin: 35
                            anchors.topMargin: 78
                            focus: true
                            clip: true
                            model: player.def_track_list
                            property bool checkState: false

                            spacing: 20
                            delegate:delegateName
                            highlightFollowsCurrentItem: true

                            highlight: Rectangle {
                                width: parent.width
                                color: "lightgreen"

                            }


                        }
                        Component{
                            id:delegateName
                            Item{
                                id:delegateItem
                                property alias checked: song_check_box.checked
                                width:parent.width
                                height:25
                                property int list_index:index

                                Text{
                                    id:song_name
                                    x:50
                                    anchors.verticalCenter: parent.verticalCenter
                                    text:modelData
                                }
                                CheckBox{
                                    id:song_check_box
                                    anchors.verticalCenter: song_name.verticalCenter
                                    //width:5
                                    visible: true
                                    checked: track_list.checkState


                                    onClicked: {

                                        if(checked)
                                        {
                                            player.fnvOnTrackCheckBoxChecked(list_index)
                                        }
                                        else
                                        {
                                            player.fnvRemoveCheckedState(list_index)
                                        }

                                    }
                                }

                                MouseArea{
                                    anchors.fill:song_name

                                    onClicked: {
                                        track_list.currentIndex = list_index
                                        player.fnvOnTrackSelected(list_index)
                                        playpause.checked = true
                                        playpause1.checked = true
                                        player.fnvOnPlayClicked(true)
                                    }
                                }

                            }


                        }
                        //alltracks list view end

                        Image {
                            property bool checked : false

                            id:plus
                            x: 900
                            y:-30
                            width: 52
                            height: 50
                            source: 'qrc:/icons/Icons/plus.png'
                            Menu{
                                //x:-185
                                //y:21

                                id:plalistmenu


                                visible: false
                                MenuItem{
                                    text: "Create New Playlist "
                                    onTriggered: {
                                        create_new_playlist.open()
                                    }


                                }


                                MenuItem{
                                    text:"Add to Existing"

                                    onTriggered:
                                        tabView.currentIndex=1


                                }

                            }
                            Dialog{
                                id:create_new_playlist
                                title: "Create New Playlist"
                                standardButtons: StandardButton.Save | StandardButton.Cancel
                                //property int current_media_index:track_list.currentIndex
                                property bool playlist_check
                                onAccepted: {

                                    playlist_check = player.fnbDuplicatePlaylistCheck(new_playlist_name.text)

                                    if(!playlist_check)
                                    {
                                        console.log("Dup",playlist_check)
                                        player.fnvCreateNewPlaylist(new_playlist_name.text)
                                        tabView.getTab(0).item.children[0].checkState = false
                                        custom_list.append({"Text":new_playlist_name.text})
                                        //custom_list_view.model = player.playlist_list

                                        new_playlist_name.text = ""

                                    }
                                    else
                                    {
                                        duplicatePlaylist.open()
                                        new_playlist_name.text = "Enter name"


                                    }
                                }

                                TextInput{
                                    id:new_playlist_name
                                    text: "Enter name"

                                    cursorVisible: true

                                }

                            }

                            MessageDialog {
                                id: duplicatePlaylist
                                title: "Error"
                                text: player.playlist_duplicate
                                onAccepted: {
                                    create_new_playlist.open()

                                }

                            }




                            MouseArea
                            {
                                anchors.rightMargin: -1
                                anchors.bottomMargin: 0
                                anchors.leftMargin: 8
                                anchors.topMargin: 1
                                anchors.fill : parent

                                onClicked:{
                                    plalistmenu.popup()
                                }
                            }

                        }


                    }

                }




                Tab {

                    title:"Playlist"
                    id:pl

                    Rectangle{
                        width:525
                        height:325
                        /*Custom playlist view*/

                        ListModel{
                            id:custom_list

                            dynamicRoles: true
                        }

                        ListView{
                            id: custom_list_view
                            x:0
                            y:20
                            width: 300
                            height: 200
                            model:player.playlist_list
                            delegate: customDelegate
                            spacing: 20
                            highlightFollowsCurrentItem: true

                            highlight: Rectangle {
                                width: 300
                                color: "lightgreen"

                            }

                        }
                        Component{
                            id:customDelegate
                            Item{
                                width:parent.width
                                height:25
                                property int current_index:index
                                Text{
                                    id:custom_text
                                    x:50
                                    text:modelData
                                    anchors.verticalCenter: parent.verticalCenter
                                }
                                CheckBox{
                                    id:custom_checkbox
                                    anchors.verticalCenter: custom_text.verticalCenter

                                    checked: false
                                    visible: true
                                    onClicked: {
                                        if(checked)
                                        {
                                            player.fnvOnTrackCheckBoxChecked(current_index)
                                        }
                                        else
                                        {
                                            player.fnvRemoveCheckedState(current_index)
                                        }

                                    }


                                }

                                MouseArea{
                                    anchors.fill:custom_text
                                    property bool view_status: player.status
                                    property bool check_status:player.fnoGetTrackCheckState()
                                    onClicked: {
                                        if(!view_status&&check_status)
                                        {
                                            console.log("where",view_status)
                                            custom_list_view.currentIndex = current_index
                                            player.fnvAddToExistingPlaylist(custom_list_view.currentIndex)
                                            //player.fnvLoadPlaylist(custom_list_view.currentIndex)
                                            //player.fnvSetSelectedPlaylist(custom_list_view.currentIndex)
                                            //custom_list_view.model = player.playlist_tracks

                                        }
                                        else if(view_status&&!check_status)
                                        {
                                            custom_list_view.currentIndex = current_index
                                            player.fnvOnTrackSelected(custom_list_view.currentIndex)
                                            player.fnvOnPlayClicked(true)
                                            playpause.checked = true
                                            playpause1.checked = true

                                        }
                                        else if(!view_status&&!check_status)
                                        {
                                            custom_list_view.currentIndex = current_index
                                        }

                                    }
                                    onDoubleClicked: {
                                        if(!view_status)
                                        {
                                            console.log("The view",view_status)
                                            player.fnvSetSelectedPlaylist(custom_list_view.currentIndex)
                                            player.fnvLoadPlaylist(custom_list_view.currentIndex)
                                            custom_text.x = 20
                                            custom_list_view.model = player.playlist_tracks

                                        }

                                    }
                                }
                            }

                        }

                        //                        Image{
                        Button{
                            id:back
                            x:405
                            y:20
                            width: 60
                            text:"Back"

                            //source: 'qrc:/icons/Icons/back.png'
                            //                            MouseArea{
                            //                                anchors.fill : parent
                            onClicked: {
                                custom_list_view.model = player.playlist_list
                                player.fnvClearSelectedPlaylist()

                            }
                            //                            }
                        }

                        //                        }

                        Image {
                            property bool checked : false

                            id:delete1
                            x: 920
                            y: -31
                            width: 40
                            height: 42
                            source: 'qrc:/icons/Icons/delete.png'


                            MouseArea
                            {
                                anchors.rightMargin: -2
                                anchors.bottomMargin: -4
                                anchors.leftMargin: -4
                                anchors.topMargin: 2
                                anchors.fill : parent
                                property bool view_status: player.status
                                onClicked:
                                {
                                    if(view_status == false)
                                    {
                                        console.log("where",view_status)
                                        player.fnvDeletePlaylist()
                                        custom_list_view.model = player.playlist_list
                                        //tabView.currentindex=1
                                    }
                                    else
                                    {

                                        player.fnvDeleteTrack()
                                        custom_list_view.model = player.playlist_tracks
                                    }


                                }
                            }
                        }

                    }
                }

                Tab{
                    id:recentlyPlayed
                    title:"Recently Played"
                    Rectangle{
                        id:rpRect
                        width:200
                        height:200
                        x:0
                        y:20

                        ListView {
                            id: recently_played_songs_listview
                            x: 0
                            y: 20
                            width: 330
                            height: 312

                            anchors.bottomMargin: 202
                            anchors.leftMargin: 475
                            anchors.rightMargin: 35
                            anchors.topMargin: 78
                            focus: true
                            clip: true
                            model:player.fnoGetRecentPlaylist()
                            //model:player.recently_played_playlist()
                            delegate: rp_delegate

                        }

                        Component{
                            id:rp_delegate
                            Item{
                                width:parent.width
                                height:15
                                property int track_list_index: index


                                Text{
                                    text:modelData
                                }

                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: player.fnoSelectRecentlyPlayedTrack(track_list_index)
                                }
                            }

                        }


                    }
                }


                Tab {
                    title:"Search"
                    Rectangle{
                        id: rectangle1
                        width: 200
                        height: 200
                        x:0
                        y:20

                        TextInput {
                            id: searchbar
                            x: 20
                            y: 10
                            width: 245
                            height: 20
                            //displayText: "search"
                            text: qsTr("Search")
                            font.pixelSize: 12
                            //onc
                            onTextChanged: player.fnoGetSearchList(text)

                        }
                        Image {
                            id: searchimage
                            x:0
                            y:10
                            width:20
                            height:20
                            source: "qrc:/icons/Icons/search.png"
                        }


                        ListView {
                            id: searchview
                            x: 50
                            y: 50
                            width: 150
                            height: 148

                            anchors.bottomMargin: 202
                            anchors.leftMargin: 475
                            anchors.rightMargin: 35
                            anchors.topMargin: 78
                            focus: true
                            clip: true
                            spacing: 20
                            model:player.fnoGetSearchList(searchbar.text)
                            delegate: search_delegate

                            //highlightFollowsCurrentItem: true
                            /*Component{

                                   Text {
                                       text: modelData
                                   }*/
                            highlight: Rectangle {
                                width: 300
                                color: "lightgreen"

                            }
                        }


                        Component{
                            id:search_delegate
                            Item{
                                width:parent.width
                                height:15
                                property int track_list_index:index



                                Text{
                                    text:modelData
                                }

                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {player.fnoSelectSearchedTrack(searchbar.text ,track_list_index); searchview.currentIndex = index ;}


                                }
                            }

                        }



                    }

                }

            }
        }


    }
}






















































