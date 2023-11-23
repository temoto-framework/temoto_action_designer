#include <QtWidgets>
#include "temoto_action_engine/umrf_node.h"

int main(int argc, char *argv[])
{
    UmrfNode umrfNode;

    QApplication app(argc, argv);
    QWidget window;
    window.resize(320, 240);
    window.show();
    window.setWindowTitle(
        QApplication::translate("toplevel", "Top-level widget"));
    return app.exec();
}
