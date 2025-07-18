#include "textediter.h"

TextEditer::TextEditer(QWidget *parent)
    : QMainWindow(parent)
{
    mb = menuBar();
    sb = statusBar();
    mySetTitle();
    fileBaseFun();
    fileEdit();
    fileTool();
    fileCenterSet();
    fileStatus();

    connect(txt_color,&QAction::triggered,this,[=](){R
        QColor color = QColorDialog::getColor();
        te->setTextColor(color);
    });

    connect(txt_font,&QAction::triggered,this,[=](){
        bool ok;
        QFont font = QFontDialog::getFont(&ok);
        if(ok)
            te->setFont(font);
    });

    connect(txt_copy,&QAction::triggered,this,[=](){
        te->copy();
    });

    connect(txt_paste,&QAction::triggered,this,[=](){
        te->paste();
    });

    connect(txt_cat,&QAction::triggered,this,[=](){
        te->cut();
    });

    //查找光标要在第一行才能查找到
    connect(txt_find,&QAction::triggered,this,[=](){
        QString text;
        bool ok;
        text = QInputDialog::getText(this,"文件编辑器","查找");

        ok = te->find(text);
        if(ok)
        {
            QMessageBox::information(this,"文本编辑器",text+" is find",QMessageBox::Ok,QMessageBox::Ok);
        }
        else
            QMessageBox::information(this,"文本编辑器",text+" is not find",QMessageBox::Ok,QMessageBox::Ok);
    });

    connect(file_close,&QAction::triggered,this,&TextEditer::close);

}

TextEditer::~TextEditer()
{

}

//设置标题栏
void TextEditer::mySetTitle()
{
    this->setWindowTitle("文本编辑器");
    this->setWindowIcon(QIcon(":/icon/EditDoc.png"));
}


//创建文件这个菜单栏   打开和关闭
void TextEditer::fileBaseFun()
{
    //1 构建action
    file_open = new QAction(QIcon(":/icon/open.jpg"),"打开文件");
    file_close = new QAction(QIcon(":/icon/close.png"),"关闭文件");

    //增加快捷键
    file_open->setShortcut(QKeySequence("ctrl+p"));
    file_close->setShortcut(QKeySequence("Ctrl+q"));

    //2 构建Menu
    QMenu *m = new QMenu("文件(&F)");

    m->addAction(file_open);
    m->addAction(file_close);

    //3 构建MenuBar
    mb->addMenu(m);
}

//创建编辑这个菜单栏  编辑 字体、颜色
void TextEditer::fileEdit()
{
    //1 action
    txt_color = new QAction(QIcon(":/icon/color.png"),"颜色");
    txt_font = new QAction(QIcon(":/icon/font.png"),"字体");

    //快捷键 暂时不设置

    //2 menu
    QMenu *m = new QMenu("编辑(&E)");
    m->addAction(txt_color);
    m->addAction(txt_font);

    //3 menubar

    mb->addMenu(m);

}

//功能区的设计 剪切 复制 粘贴
void TextEditer::fileTool()
{
    //设置action
    txt_cat = new QAction(QIcon(":/icon/cat.png"),"剪切");
    txt_copy = new QAction(QIcon(":/icon/copy.png"),"复制");
    txt_paste = new QAction(QIcon(":/icon/paste.png"),"粘贴");
    txt_find = new QAction(QIcon(":/icon/find.png"),"查找");

    txt_find->setShortcut(QKeySequence("ctrl+f"));
    //加入toolbar

    QToolBar *tb = addToolBar("tool");
    tb->addAction(txt_cat);
    tb->addAction(txt_copy);
    tb->addAction(txt_paste);
    tb->addAction(txt_find);

}

//设置中央区  需要先创建wedgit，再在Widget上布置布局，在添加控件。
//在 Qt 中向QStatusBar添加布局时，必须先添加一个QWidget控件，再将布局设置到这个控件上。这是因为QStatusBar的addWidget()和addPermanentWidget()方法只接受QWidget类型的参数，无法直接添加布局。
//也可以直接添加控件
void TextEditer::fileCenterSet()
{
    QWidget *centralWidget = new QWidget; //创建一个控件
    QHBoxLayout *hbox = new QHBoxLayout(centralWidget);//在控件上布置布局
    te = new QTextEdit;
    hbox->addWidget(te);//将文本编辑器加载到布局上
    this->setCentralWidget(centralWidget);//将最底层的控件布置到中央区
}

//显示文本编辑状态栏  这个上面要添加相应的label显示对应的东西，需要用到布局，在添加控件
//在 Qt 中向QStatusBar添加布局时，必须先添加一个QWidget控件，再将布局设置到这个控件上。这是因为QStatusBar的addWidget()和addPermanentWidget()方法只接受QWidget类型的参数，无法直接添加布局。
void TextEditer::fileStatus()
{
    QWidget *statusbar = new QWidget;

    QHBoxLayout *hbox = new QHBoxLayout;
    QString row = "Row: ";
    QString col = "Col: ";
    row += QString::number(r);
    col += QString::number(c);
    if(r == 1 && c == 1)
    {
        lb1 = new QLabel;
        lb2 = new QLabel;
        // qDebug() << "r = 1, c = 1";
    }
    lb1->setText(row);
    lb2->setText(col);

    hbox->addWidget(lb1);
  //  hbox->addWidget(lb2);

    statusbar->setLayout(hbox);

    sb->addWidget(statusbar);
}
