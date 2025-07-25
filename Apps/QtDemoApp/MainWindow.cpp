#include "mainwindow.h"
#include "osg/osgWindow.h"
#include <QGridLayout>
#include <QDockWidget>
#include <QTreeWidget>
#include <QListWidget>
#include <QToolBar>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
 
 
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{  
    pOSGWnd = new GraphicsWindowQt(this);

    pOSGWnd->loadModule("axes.osgt",true);

	createToolBar();
    setCentralWidget(pOSGWnd);
}
 
void MainWindow::createToolBar(){

    QToolBar *toolBar = new QToolBar(this);  // 创建工具栏
    addToolBar(Qt::TopToolBarArea,toolBar); // 设置默认停靠范围 [默认停靠左侧]

    toolBar->setAllowedAreas(Qt::TopToolBarArea |Qt::BottomToolBarArea);   // 允许上下拖动
    toolBar->setAllowedAreas(Qt::LeftToolBarArea |Qt::RightToolBarArea);   // 允许左右拖动

    toolBar->setFloatable(false);       // 设置是否浮动
    toolBar->setMovable(false);         // 设置工具栏不允许移动

    //new
    {
        QAction* newAction = new QAction(QIcon(), tr("&New"), this);
        newAction->setPriority(QAction::LowPriority);
        newAction->setShortcut(QKeySequence::New);
        newAction->setStatusTip(tr("Create a new document"));
        newAction->setToolTip(tr("New"));
        connect(newAction, SIGNAL(triggered()), this, SLOT(fileNew()));
        toolBar->addAction(newAction);
    }


   //open
    toolBar->addSeparator();
    {
        QAction* openAction = new QAction(QIcon(), tr("&Open"), this);
        openAction->setPriority(QAction::LowPriority);
        openAction->setShortcut(QKeySequence::Open);
        openAction->setStatusTip(tr("Open a document"));
        openAction->setToolTip(tr("Open"));
        connect(openAction, SIGNAL(triggered()), this, SLOT(fileOpen()));
        toolBar->addAction(openAction);
    }
}

void MainWindow::fileNew()
{ 
}

void MainWindow::fileOpen()
{
	QString fileName = QFileDialog::getOpenFileName();
	std::string stdFile = fileName.toLocal8Bit().constData();
	pOSGWnd->loadModule(stdFile, false);
}

MainWindow::~MainWindow() 
{
}
