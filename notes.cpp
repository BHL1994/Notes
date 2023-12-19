#include "Notes.h"

Notes::Notes(QWidget *parent) : QMainWindow(parent) {
    //Creates a new text editing area as a widget
    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    //Create actions and create menu functions to
    createActions();
    createMenus();

    //Sets up the name of the window
    setWindowTitle("Notes");

    //Sets the size of the window
    resize(800, 600);
}

//This clears the text edit area when a new file is created
void Notes::newFile() {
    textEdit->clear();
}

//Function that opens a saved file
void Notes::openFile() {
    //This opens a dialog box to promp the user to select a file to open.
    //"Open File" is the title of the dialog box and it will only show files with a .txt extension
    //It then stores these values in a fileName variable as a QString object
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt)"));
    //If the fileName variable is empty, meaning no file was selected it will exit the function
    if (fileName.isEmpty()) return;

    //If a file was selected it will create a new QFile object
    //If the file cannot be opened as a text file it will exit the function
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    //QTextStream will parse the text froom the QFile object file and places it in the textEdit widget
    //It will then close the file
    QTextStream in(&file);
    textEdit->setText(in.readAll());
    file.close();
}

//This function saves a file
void Notes::saveFile() {
    //A dialog box opens prompting the user to save a file
    //The text that is entered as the name of the saved file will then be stored in the fileName variable as a QString object
    //If the dialog box was closed and no file name was entered it will exit the function
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt)"));
    if (fileName.isEmpty()) return;

    //Creates a QFile object from the previous fileName object
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    //This will copy the text that is currently in the textEdit window and write it to the file object
    QTextStream out(&file);
    out << textEdit->toPlainText();
    file.close();
}

//Function to quit app
void Notes::exitApp() {
    QApplication::quit();
}

//This will create the actions that a user can perform on the text widget
void Notes::createActions() {

    //Creates objects to create a New file, open a new file, save a file and exit
    //It will then store them in its respective variable ex. newAct, openAct, etc.
    //It then connects them to the respective button in the menu and when the
    //action in the menu is clicked it will trigger its respective function
    //ex. newFile, openFile, saveFile, exitApp
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcut(QKeySequence::New);
    connect(newAct, &QAction::triggered, this, &Notes::newFile);

    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcut(QKeySequence::Open);
    connect(openAct, &QAction::triggered, this, &Notes::openFile);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcut(QKeySequence::Save);
    connect(saveAct, &QAction::triggered, this, &Notes::saveFile);

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, &QAction::triggered, this, &Notes::exitApp);
}

//This will create the menus that can be clicked to save, open and create new file
void Notes::createMenus() {
    //Creates an initial File menu
    fileMenu = menuBar()->addMenu(tr("&File"));
    //In the file menu it adds New, Open, Save and Exit actions
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
}
