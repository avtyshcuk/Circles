#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "circlemodel.h"
#include "circlemanager.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    CircleModel model;
    CircleManager manager;
    model.setManager(&manager);

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("circleManager", &manager);
    context->setContextProperty("circleModel", &model);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
