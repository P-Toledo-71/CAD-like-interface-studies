#pragma once

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QAction>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QLabel>

class Scene : public QGraphicsScene
{
	Q_OBJECT
public:
	enum Mode { NoMode, SelectObject, DrawLine };
	enum Grid {On=true,Off=false};
	Scene(QObject* parent = 0);
	void setMode(Mode mode);
	void setGrid(Scene::Grid);
	void setSnapToGrid(Scene::Grid);
	void setGridStep(double x, double y);
	void setGridVerticalStep(double y);
	void setGridHorizontalStep(double x);
	double getGridSize();
	void scene2Word(QPointF const& sceneCoord, QPointF& wordCoord);
	void word2scene(QPointF const& wordCoord, QPointF& sceneCoord);
	void setOrignPoint(QPointF const& orign);
	void getOriggnPoint(QPointF& orign);

signals:
	void scenePosition(QGraphicsSceneMouseEvent* event);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
	void keyPressEvent(QKeyEvent* event);
	void drawBackground(QPainter* painter, const QRectF& rect);
private:
	Mode sceneMode;
	QPointF origPoint, coordenateOrig;
	QGraphicsLineItem* itemToDraw;
	bool clicked;
	bool gridStatus;
	bool snapToGrid;
	double vGridStep;
	double hGridStep;
	int gridSize;
	void makeItemsControllable(bool areControllable);
};
