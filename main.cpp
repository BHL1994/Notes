#include "Notes.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Notes notes;
    notes.show();
    return app.exec();
}
