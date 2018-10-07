#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <cmediaplayer.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<CMEDIAPLAYER>("mediaplayer",1,0,"Player");


    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
