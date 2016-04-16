/*
 * Copyright (C) 2013-2015 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// Uncomment if you need to use QML analyzer
// #define QT_QML_DEBUG
// #include <QtQuick>

#include <QGuiApplication>
#include <QQuickView>
#include <QLibrary>
#include <QtQml>

#include <QDebug>
#include <QElapsedTimer>

#include "config.h"

void loadTestability() {
    QLibrary testLib(QLatin1String("qttestability"));

    if (testLib.load()) {
        typedef void (*TasInitialize)(void);
        TasInitialize initFunction = (TasInitialize)testLib.resolve("qt_testability_init");

        if (initFunction) {
            initFunction();
        } else {
            qCritical("Library qttestability resolve failed!");
        }
    } else {
        qCritical("Library qttestability load failed!");
    }
}

int main(int argc, char *argv[])
{
    QElapsedTimer initTimer;
    initTimer.start();

    QGuiApplication app(argc, argv);
    QQuickView view;

    view.rootContext()->setContextProperty("window", &view);
    QObject::connect(view.engine(), SIGNAL(quit()), &app, SLOT(quit()));

    if (qgetenv("QT_LOAD_TESTABILITY") == "1")
       loadTestability();

    if (!isRunningInstalled())
        view.engine()->addImportPath(QCoreApplication::applicationDirPath() + "/../plugin/");

    view.setSource(QUrl::fromLocalFile(applicationDirectory() + "/qml/main.qml"));
    view.setResizeMode(QQuickView::SizeRootObjectToView);

    // UITK/QML command line arguments are parsed before view's window becomes visible.
    if (view.windowState() == Qt::WindowFullScreen)
        view.showFullScreen();
    else
        view.show();

    qDebug() << "App required" << initTimer.elapsed() << "msec to be initialised.";

    return app.exec();
}
