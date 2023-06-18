#include <QtWidgets>
#include <QtCharts>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create the main window
    QMainWindow mainWindow;
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

    // Create a chart view
    QtCharts::QChartView chartView(&bottomWindow);
    chartView.setRenderHint(QPainter::Antialiasing);

    // Create a chart
    QtCharts::QChart chart;
    chart.setTitle("Chart with 101 Columns and 10 Rows");

    // Create a bar series
    QtCharts::QBarSeries series;

    // Generate random data for the chart
    srand(time(nullptr));

    // Labels for the first row
    QStringList labels = {"Frame", "Move X", "Move Y", "Move Z", "Rotate X", "Rotate Y", "Rotate Z", "Size X", "Size Y", "Size Z"};

    for (int i = 0; i < 10; ++i)
    {
        QtCharts::QBarSet *set = new QtCharts::QBarSet(labels.at(i));

        for (int j = 0; j < 101; ++j)
        {
            set->append(rand() % 100);
        }

        // Set colors for specific cells in the first row
        if (i == 0)
        {
            set->setColor(QColor("yellow"));
        }
        else if (i >= 1 && i <= 3)
        {
            set->setColor(QColor("lightblue"));
            set->setColorAt(j, QColor("lightblue"));
        }
        else if (i >= 4 && i <= 6)
        {
            set->setColor(QColor("purple"));
            set->setColorAt(j, QColor("purple"));
        }
        else if (i >= 7 && i <= 9)
        {
            set->setColor(QColor("green"));
            set->setColorAt(j, QColor("green"));
        }

        series.append(set);
    }

    // Add the series to the chart
    chart.addSeries(&series);

    // Create an axis for the X-axis
    QtCharts::QValueAxis xAxis;
    xAxis.setTickCount(10); // Set the number of ticks on the X-axis
    xAxis.setTitleText("Columns");
    chart.addAxis(&xAxis, Qt::AlignBottom);
    series.attachAxis(&xAxis);

    // Create an axis for the Y-axis
    QtCharts::QValueAxis yAxis;
    yAxis.setTitleText("Values");
    chart.addAxis(&yAxis, Qt::AlignLeft);
    series.attachAxis(&yAxis);

    // Set the chart as the chart view's chart
    chartView.setChart(&chart);

    // Set the chart view as the central widget of the bottom window
    QVBoxLayout bottomWindowLayout(&bottomWindow);
    bottomWindowLayout.addWidget(&chartView);
    bottomWindow.setLayout(&bottomWindowLayout);

    mainWindow.show();

    return app.exec();
}
