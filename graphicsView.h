#include <QGraphicsView>

class graphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	enum Grid { On = true, Off = false };
	graphicsView(QWidget* parent) : QGraphicsView(parent) {};
	graphicsView(QGraphicsScene * parent) : QGraphicsView(parent) {};
	void setGrid(graphicsView::Grid);
	void setSnapToGrid(graphicsView::Grid);
	void setGridStep(double x, double y);
	void setGridVerticalStep(double y);
	void setGridHorizontalStep(double x);
	double getGridSize();

signals:
	void viewPosition(QGraphicsSceneMouseEvent* event);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
	void keyPressEvent(QKeyEvent* event);
	void drawBackground(QPainter* painter, const QRectF& rect);
private:
	bool clicked;
	bool gridStatus;
	bool snapToGrid;
	double vGridStep;
	double hGridStep;
	int gridSize;
};