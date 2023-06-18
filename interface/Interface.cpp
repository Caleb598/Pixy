#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create the main window
    QWidget mainWindow;
    mainWindow.setWindowTitle("Four Window Interface");
    mainWindow.resize(800, 600);

    // Create the layout for the main window
    QVBoxLayout layout(&mainWindow);

    // Create the top-right window
    QWidget topRightWindow;
    topRightWindow.setStyleSheet("background-color: lightgray;");
    topRightWindow.setWindowTitle("Pixy Scene Collection");

    // Create the bottom window
    QWidget bottomWindow;
    bottomWindow.setStyleSheet("background-color: lightgray;");
    bottomWindow.setWindowTitle("Pixy Animation");

    // Create the right corner window
    QWidget rightCornerWindow;
    rightCornerWindow.setStyleSheet("background-color: lightgray;");
    rightCornerWindow.setWindowTitle("Pixy Settings");

    // Create the remaining window
    QWidget remainingWindow;
    remainingWindow.setStyleSheet("background-color: white;");
    remainingWindow.setWindowTitle("Pixy Viewport");

    // Add the windows to the layout
    layout.addWidget(&topRightWindow);
    layout.addWidget(&remainingWindow);

    // Create a horizontal layout for the bottom window and right corner window
    QHBoxLayout bottomLayout;
    bottomLayout.addWidget(&bottomWindow);
    bottomLayout.addWidget(&rightCornerWindow);
    layout.addLayout(&bottomLayout);

    mainWindow.show();

    return app.exec();
}
