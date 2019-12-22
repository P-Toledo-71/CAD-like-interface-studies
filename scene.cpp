#include "scene.h"

Scene::Scene(QObject* parent) :
QGraphicsScene(parent), gridSize(20),vGridStep(20), hGridStep(20),
clicked(false),itemToDraw(0), sceneMode(NoMode),
gridStatus(true), snapToGrid(true)
{

}

void Scene::setMode(Mode mode) {
	sceneMode = mode;
	QGraphicsView::DragMode vMode =
		QGraphicsView::NoDrag;
	if (mode == DrawLine) {
		makeItemsControllable(false);
		vMode = QGraphicsView::NoDrag;
	}
	else if (mode == SelectObject) {
		makeItemsControllable(true);
		vMode = QGraphicsView::RubberBandDrag;
	}
	QGraphicsView* mView = views().at(0);
	if (mView)
		mView->setDragMode(vMode);
}

void Scene::setGrid(Scene::Grid mode)
{
	gridStatus = mode;
}

void Scene::setSnapToGrid(Scene::Grid mode)
{
	snapToGrid = mode;
}

void Scene::setGridStep(double x, double y)
{
	hGridStep = x;
	vGridStep = y;
}

double Scene::getGridSize()
{
	return gridSize;
}

void Scene::makeItemsControllable(bool areControllable) {
	foreach(QGraphicsItem * item, items()) {
		item->setFlag(QGraphicsItem::ItemIsSelectable,
			areControllable);
		item->setFlag(QGraphicsItem::ItemIsMovable,
			areControllable);
	}
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent* event) {

	emit scenePosition(event);
	if (sceneMode == DrawLine)
	{
		
		clicked = true;
		if (snapToGrid)
		{
			origPoint.rx() = round(event->scenePos().x() / gridSize) * gridSize;
			origPoint.ry() = round(event->scenePos().y() / gridSize) * gridSize;

		} 
		else 
		 origPoint = event ->scenePos();
	}
	QGraphicsScene::mousePressEvent(event);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
	
	emit scenePosition(event);
	
	if (sceneMode == DrawLine && clicked) {
		
		if (!itemToDraw) {
			itemToDraw = new QGraphicsLineItem;
			this->addItem(itemToDraw);
			itemToDraw->setPen(QPen(Qt::black, 3, Qt::SolidLine));
			itemToDraw->setPos(origPoint);
		}
		QPointF destPoint;
		if (snapToGrid)
		{
			
			destPoint.rx() = round(event->scenePos().x() / gridSize) * gridSize;
			destPoint.ry() = round(event->scenePos().y() / gridSize) * gridSize;

		}
		else
			destPoint = event->scenePos();
		itemToDraw->setLine(0, 0,
			destPoint.x() - origPoint.x(),
			destPoint.y() - origPoint.y());
	}
	else
		QGraphicsScene::mouseMoveEvent(event);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
	emit scenePosition(event);
	
	itemToDraw = 0;
	clicked = false;
	QGraphicsScene::mouseReleaseEvent(event);
}

void Scene::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key_Delete)
		foreach(QGraphicsItem * item, selectedItems()) {
		removeItem(item);
		delete item;
	}
	else
		QGraphicsScene::keyPressEvent(event);
}

void Scene::drawBackground(QPainter* painter, const QRectF& rect)
{
	if (gridStatus)
	{
		QPen pen;
		painter->setPen(pen);

		qreal vSize = rect.height();
		qreal hSize = rect.width();
		qreal left = int(rect.left()) - (int(rect.left()) % gridSize);
		qreal top = int(rect.top()) - (int(rect.top()) % gridSize);
		QVector<QPointF> points;
		for (qreal x = left; x < rect.right(); x += hGridStep) {
			for (qreal y = top; y < rect.bottom(); y += vGridStep) {
				points.append(QPointF(x, y));
			}
		}
		painter->drawPoints(points.data(), points.size());
	}
}