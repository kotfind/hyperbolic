#include "Canvas.h"

#include <QApplication>

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    Canvas win;
    win.show();
    
    return app.exec();
}
