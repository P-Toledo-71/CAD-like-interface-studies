#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QToolBar>
#include <QAction>
#include <QLayout>
#include <QGraphicsGridLayout>
#include <QGraphicsWidget>
#include <QLabel>
#include <QLineEdit>
#include "graphicsView.h"
#include "scene.h"
class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow();
public slots:
	void actionGroupClicked(QAction*);
	void  scenePosition(QGraphicsSceneMouseEvent* event);
private:
	QGraphicsView* view;
	Scene * scene;
	QGridLayout* mainLayout;
	QLineEdit * vCoord;
	QLineEdit * hCoord;
	QLabel* vLabel, * hLabel;


	void createActions();
	void createConnections();
	void createToolBar();
	

	QAction* lineAction;
	QAction* selectAction;
	QActionGroup* actionGroup;
	QToolBar* drawingToolBar, *statusToolBar;

};

#endif // MAINWINDOW_H