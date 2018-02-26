#include <octoon/editor/mainwindow.h>

MainWindow::MainWindow(QWidget *parent) :
    OMainWindow(parent)
{
	this->setWindowTitle("Octoon Studio");
	// menu
	menuBar = new QMenuBar(this);
	QMenu *fileMenu = new QMenu(tr("File"), this);
	QMenu *editMenu = new QMenu(tr("Edit"), this);
	QMenu *viewMenu = new QMenu(tr("View"), this);
	QMenu *helpMenu = new QMenu(tr("Help"), this);

	menuBar->addMenu(fileMenu);
	menuBar->addMenu(editMenu);
	menuBar->addMenu(viewMenu);
	menuBar->addMenu(helpMenu);

	fileMenu->addAction(tr("New"));
	fileMenu->addAction(tr("Open"));

	this->setMenuBar(menuBar);

    // dock
    viewDock = new ODockWidget(this);
    commandDock = new ODockWidget(this);
    hierarchyDock = new ODockWidget(this);
	materialDock = new ODockWidget(this);
	projectDock = new ODockWidget(this);
	consoleDock = new ODockWidget(this);

    // panel
    commandPanel = new QQuickWidget;
    commandPanel->setSource(QUrl::fromLocalFile(QApplication::applicationDirPath() + "/qml/controls/OButton.qml"));
	commandPanel->setResizeMode(QQuickWidget::SizeRootObjectToView);
	
    hierarchyPanel = new QQuickWidget;
    hierarchyPanel->setSource(QUrl::fromLocalFile(QApplication::applicationDirPath() + "/qml/hierarchy_panel.qml"));
	hierarchyPanel->setResizeMode(QQuickWidget::SizeRootObjectToView);
	
	materialPanel = new QQuickWidget;
	materialPanel->setSource(QUrl::fromLocalFile(QApplication::applicationDirPath() + "/qml/material_panel.qml"));
	materialPanel->setResizeMode(QQuickWidget::SizeRootObjectToView);
	
    viewPanel = new OViewWidget(viewDock);

	projectPanel = new QQuickWidget;
	projectPanel->setSource(QUrl::fromLocalFile(QApplication::applicationDirPath() + "/qml/project_panel.qml"));
	projectPanel->setResizeMode(QQuickWidget::SizeRootObjectToView);

	consolePanel = new QQuickWidget;
	consolePanel->setSource(QUrl::fromLocalFile(QApplication::applicationDirPath() + "/qml/console_panel.qml"));
	consolePanel->setResizeMode(QQuickWidget::SizeRootObjectToView);

    viewDock->setWidget(viewPanel);
    viewDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    viewDock->setWindowTitle("View Panel");

    //commandDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    commandDock->setWidget(commandPanel);
    commandDock->setWindowTitle("Command Panel");

	//hierarchyDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	hierarchyDock->setWidget(hierarchyPanel);
	hierarchyDock->setWindowTitle("Hierarchy Panel");

	//materialDock->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);
	materialDock->setWidget(materialPanel);
	materialDock->setWindowTitle("Material Panel");
	materialDock->setMinimumHeight(100);

	projectDock->setWidget(projectPanel);
	projectDock->setWindowTitle("Project Panel");

	consoleDock->setWidget(consolePanel);
	consoleDock->setWindowTitle("Console Panel");

    this->setCentralWidget(viewDock);
    this->addDockWidget(Qt::RightDockWidgetArea,commandDock);
    this->addDockWidget(Qt::LeftDockWidgetArea,hierarchyDock);
	this->addDockWidget(Qt::BottomDockWidgetArea, materialDock);
	this->addDockWidget(Qt::BottomDockWidgetArea, projectDock);
	this->addDockWidget(Qt::BottomDockWidgetArea, consoleDock);
}

MainWindow::~MainWindow()
{
}
