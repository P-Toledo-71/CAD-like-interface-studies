#include "mainwindow.h"

MainWindow::MainWindow()
{
	scene = new Scene(this);
	scene->setSceneRect(0, 0, 200, 200);
	view = new QGraphicsView(scene);
	
	view->setRenderHints(QPainter::Antialiasing);
	//QMatrix T(1.0,-.0,-1.0,-1.0,1.0,1.0);
	//view->setTransform(QTransform(a11,a12,a13,a21,a22,a23,a31,a32,a33));
	vCoord = new QLineEdit;
	hCoord = new QLineEdit;
	vLabel = new QLabel;
	hLabel = new QLabel;
	vCoord->setEnabled(false);
	hCoord->setEnabled(false);
	vLabel->setText("&Vertical: ");
	hLabel->setText("&Horizontal");
	vLabel->setBuddy(vCoord);
	hLabel->setBuddy(hCoord);

	setCentralWidget(view);
	createActions();
	createConnections();
	createToolBar();
}

void MainWindow::scenePosition(QGraphicsSceneMouseEvent* event)
{
	QPointF pos = view->mapFromScene(event->scenePos());
	hCoord->setText(QString(QString::number(pos.x())));
	vCoord->setText(QString(QString::number(pos.y())));
	
}

void MainWindow::createActions() {
	lineAction = new QAction("Draw line", this);
	lineAction->setData(int(Scene::DrawLine));
	lineAction->setIcon(QIcon("line.png"));
	lineAction->setCheckable(true);

	selectAction = new QAction("Select object", this);
	selectAction->setData(int(Scene::SelectObject));
	selectAction->setIcon(QIcon("select.png"));
	selectAction->setCheckable(true);

	actionGroup = new QActionGroup(this);
	actionGroup->setExclusive(true);
	actionGroup->addAction(lineAction);
	actionGroup->addAction(selectAction);
}

void MainWindow::createConnections() {

	connect(actionGroup, SIGNAL(triggered(QAction*)),
		this, SLOT(actionGroupClicked(QAction*)));


	connect(scene, SIGNAL( scenePosition(QGraphicsSceneMouseEvent *)),
		this, SLOT(scenePosition(QGraphicsSceneMouseEvent *)));

}

void MainWindow::actionGroupClicked(QAction* action) {
	    scene->setMode(Scene::Mode(action->data().toInt()));
}

void MainWindow::createToolBar() {
	drawingToolBar = new QToolBar;
	addToolBar(Qt::TopToolBarArea, drawingToolBar);
	drawingToolBar->addAction(selectAction);
	drawingToolBar->addAction(lineAction);

	statusToolBar = new QToolBar;
	addToolBar(Qt::BottomToolBarArea, statusToolBar);
	statusToolBar->addWidget(hLabel);
	statusToolBar->addWidget(hCoord);
	statusToolBar->addWidget(vLabel);
	statusToolBar->addWidget(vCoord);



}


