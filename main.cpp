#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "painteditem.h"

#include  "testpainteditem.h"
#include <QtTest/QtTest>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


    QQmlApplicationEngine engine;
    qmlRegisterType<PaintedItem>("PaintedItem", 1, 0, "PaintedItem");
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    QTest::qExec(new TestPaintedItem, argc, argv);

    return app.exec();
}
