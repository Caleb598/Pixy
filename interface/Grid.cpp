#include <QtWidgets>

class InfiniteGrid : public QGraphicsScene
{
public:
    InfiniteGrid(QObject* parent = nullptr) : QGraphicsScene(parent)
    {
        setSceneRect(-1000, -1000, 2000, 2000);
    }

    void drawBackground(QPainter* painter, const QRectF& rect) override
    {
        Q_UNUSED(rect);

        // Set the background color
        painter->fillRect(sceneRect(), Qt::white);

        // Set the grid properties
        QPen pen(Qt::lightGray);
        pen.setWidth(1);

        const int gridSize = 20; // Size of each grid square

        // Draw vertical lines
        for (qreal x = sceneRect().left(); x < sceneRect().right(); x += gridSize)
        {
            painter->setPen(pen);
            painter->drawLine(QPointF(x, sceneRect().top()), QPointF(x, sceneRect().bottom()));
        }

        // Draw horizontal lines
        for (qreal y = sceneRect().top(); y < sceneRect().bottom(); y += gridSize)
        {
            painter->setPen(pen);
            painter->drawLine(QPointF(sceneRect().left(), y), QPointF(sceneRect().right(), y));
        }
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create the main window
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Pixy Viewport");
    mainWindow.resize(800, 600);

    // Create the graphics view
    QGraphicsView graphicsView(&mainWindow);

    // Create the infinite grid scene
    InfiniteGrid infiniteGrid;
    graphicsView.setScene(&infiniteGrid);

    // Set the graphics view as the central widget
    mainWindow.setCentralWidget(&graphicsView);
    mainWindow.show();

    return app.exec();
}
