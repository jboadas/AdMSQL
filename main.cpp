#include <qapplication.h>
#include <QtPlugin>
#include <QtGui>

#include "window.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(iconos);

    QApplication app(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("AdMysql"), QObject::tr("No se Detecta System Tray."));
        return 1;
    }
    QApplication::setQuitOnLastWindowClosed(false);

    Window window;
    window.show();
    return app.exec();
}
