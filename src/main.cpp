#include <QApplication>
#include <file_browser.h>
#include "search_gui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    auto window = new SearchGUI;


    window->resize(600,600);
    window->show();
    return QApplication::exec();
}
