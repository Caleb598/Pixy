#include <QApplication>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QFrame>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create the main window
    QMainWindow window;

    // Create the central widget
    QWidget *centralWidget = new QWidget(&window);
    window.setCentralWidget(centralWidget);

    // Create a horizontal layout for the central widget
    QHBoxLayout *centralLayout = new QHBoxLayout(centralWidget);

    // Create a splitter widget to divide the central widget into two parts
    QSplitter *splitter1 = new QSplitter(Qt::Vertical, centralWidget);
    centralLayout->addWidget(splitter1);

    // Create the top-right window
    QWidget *topRightWindow = new QFrame(splitter1);
    topRightWindow->setStyleSheet("background-color: lightgray;");
    topRightWindow->setMinimumSize(200, 200);
    topRightWindow->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    topRightWindow->setWindowTitle("Rendero Scene Collection");

    // Create a splitter widget to divide the bottom part of the central widget
    QSplitter *splitter2 = new QSplitter(Qt::Horizontal, splitter1);
    splitter1->addWidget(splitter2);

    // Create the remaining window
    QWidget *remainingWindow = new QFrame(splitter1);
    remainingWindow->setStyleSheet("background-color: white;");
    remainingWindow->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    remainingWindow->setWindowTitle("Rendero Viewport");

    // Create the bottom window
    QWidget *bottomWindow = new QFrame(&window);
    bottomWindow->setStyleSheet("background-color: lightgray;");
    bottomWindow->setMinimumHeight(100);
    bottomWindow->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    bottomWindow->setWindowTitle("Rendero Animation");

    // Add the bottom window to the main window
    window.setCentralWidget(centralWidget);
    window.setUnifiedTitleAndToolBarOnMac(true);
    window.addToolBar(Qt::TopToolBarArea, new QToolBar(&window));
    window.setStatusBar(new QStatusBar(&window));
    window.setCentralWidget(centralWidget);
    window.setDockNestingEnabled(true);
    window.setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    window.setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);

    // Set the layout for the central widget
    centralWidget->setLayout(centralLayout);

    // Add the bottom window to the layout
    centralLayout->addWidget(bottomWindow);

    window.show();

    return app.exec();
}
