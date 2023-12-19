#ifndef NOTES_H
#define NOTES_H

#include <QtWidgets>

class Notes : public QMainWindow {
    Q_OBJECT

public:
    Notes(QWidget *parent = nullptr);

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void exitApp();

private:
    void createActions();
    void createMenus();

    QTextEdit *textEdit;
    QMenu *fileMenu;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
};

#endif
