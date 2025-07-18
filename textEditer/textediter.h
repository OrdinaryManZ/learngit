#ifndef TEXTEDITER_H
#define TEXTEDITER_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QWidget>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QDebug>
#include <QFontDialog>
#include <QColorDialog>
#include <QInputDialog>
#include <QMessageBox>

class TextEditer : public QMainWindow
{
    Q_OBJECT

public:
    TextEditer(QWidget *parent = nullptr);
    ~TextEditer();

    void mySetTitle();
    void fileBaseFun();
    void fileEdit();
    void fileTool();
    void fileCenterSet();
    void fileStatus();

private:
    QAction *file_open, *file_close, *txt_color, *txt_font, *txt_copy, *txt_cat, *txt_paste, *txt_find;
    QMenuBar *mb;
    QTextEdit * te;
    QStatusBar *sb;
    QLabel *lb1, *lb2;
    int r = 1, c = 1;
};
#endif // TEXTEDITER_H
