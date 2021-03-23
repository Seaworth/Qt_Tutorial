#include "mainwindow.h"

#include <QApplication>
// The main window to which you add toolbars,
// menubars, widgets and status bar
#include <QtWidgets/QMainWindow>

// Widget used to display charts
#include <QtCharts/QChartView>

// Used to draw bars representing data provided
// grouped into categories
#include <QtCharts/QBarSeries>

// Represents 1 set of bars in a bar chart
#include <QtCharts/QBarSet>

// Displays the color used to represent each
// QBarSet
#include <QtCharts/QLegend>

// Adds categories to the charts axes
#include <QtCharts/QBarCategoryAxis>

// Used to create stacked bar charts
#include <QtCharts/QHorizontalStackedBarSeries>

// Used to create a line chart
#include <QtCharts/QLineSeries>

// Used to change names on axis
#include <QtCharts/QCategoryAxis>

// Used to make Pie Charts
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 1. Bar chart
    // 2. stacked bar chart
#if 0
    // Assign names to the set of bars used
    QBarSet *set0 = new QBarSet("Altuve");
    QBarSet *set1 = new QBarSet("Martinez");
    QBarSet *set2 = new QBarSet("Segura");
    QBarSet *set3 = new QBarSet("Simmons");
    QBarSet *set4 = new QBarSet("Trout");

    // Assign values for each bar
    *set0 << 283 << 341 << 313 << 338 << 346 << 335;
    *set1 << 250 << 315 << 282 << 307 << 303 << 330;
    *set2 << 294 << 246 << 257 << 319 << 300 << 325;
    *set3 << 248 << 244 << 265 << 281 << 278 << 313;
    *set4 << 323 << 287 << 299 << 315 << 306 << 313;

    // Add all sets of data to the chart as a whole
    // 1. Bar Chart
    QBarSeries *series = new QBarSeries();

    // 2. Stacked bar chart
//     QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);

    // Used to define the bar chart to display, title
    // legend,
    QChart *chart = new QChart();

    // Add the chart
    chart->addSeries(series);

    // Set title
    chart->setTitle("Batting Avg by Year");
    // Define starting animation
    // NoAnimation, GridAxisAnimations, SeriesAnimations
    chart->setAnimationOptions(QChart::AllAnimations);

    // Holds the category titles
    QStringList categories;
    categories << "2013" << "2014" << "2015" << "2016" << "2017" << "2018";

    // Adds categories to the axes
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();

    // 1. Bar chart
   chart->setAxisX(axis, series);

    // 2. Stacked Bar chart
//    chart->setAxisY(axis, series);

    // Define where the legend is displayed
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Used to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Used to change the palette
    QPalette pal = qApp->palette();

    // Change the color around the chart widget and text
    pal.setColor(QPalette::Window, QRgb(0xffffff));
    pal.setColor(QPalette::WindowText, QRgb(0x404044));

    // Apply palette changes to the application
    qApp->setPalette(pal);

#endif

    // 3. Line chart
#if 0

    QLineSeries *series = new QLineSeries();
    series->append(0, 16);
    series->append(1, 25);
    series->append(2, 24);
    series->append(3, 19);
    series->append(4, 33);
    series->append(5, 25);
    series->append(6, 34);

    // Create chart, add data, hide legend, and add axis
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();

    // Customize the title font
    QFont font;
    font.setPixelSize(18);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::black));
    chart->setTitle("Barry Bonds HRs as Pirate");

    // Change the line color and weight
    QPen pen(QRgb(0x000000));
    pen.setWidth(5);
    series->setPen(pen);

    chart->setAnimationOptions(QChart::AllAnimations);

    // Change the x axis categories
    QCategoryAxis *axisX = new QCategoryAxis();
    axisX->append("1986",0);
    axisX->append("1987",1);
    axisX->append("1988",2);
    axisX->append("1989",3);
    axisX->append("1990",4);
    axisX->append("1991",5);
    axisX->append("1992",6);
    chart->setAxisX(axisX, series);

    // Used to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


#endif

    // 4. Pie chart
#if 1
    // Define slices and percentage of whole they take up
    QPieSeries *series = new QPieSeries();
    series->append("Vegetables",.40);
    series->append("Beans",.20);
    series->append("Fruits",.15);
    series->append("Seeds/Nuts",.10);
    series->append("Whole Grains",.15);

    // Add label to 1st slice
    QPieSlice *slice0 = series->slices().at(0);
    slice0->setLabelVisible();

    // Add label, explode and define brush for 2nd slice
    QPieSlice *slice1 = series->slices().at(1);
    slice1->setExploded();
    slice1->setLabelVisible();
    slice1->setPen(QPen(Qt::darkGreen, 2));
    slice1->setBrush(Qt::green);

    // Add labels to rest of slices
    QPieSlice *slice2 = series->slices().at(2);
    slice2->setLabelVisible();
    QPieSlice *slice3 = series->slices().at(3);
    slice3->setLabelVisible();
    QPieSlice *slice4 = series->slices().at(4);
    slice4->setLabelVisible();

    // Create the chart widget
    QChart *chart = new QChart();

    // Add data to chart with title and hide legend
    chart->addSeries(series);
    chart->setTitle("What Derek Ate this Week");
    chart->legend()->hide();

    // Used to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

#endif
    MainWindow w;

    // Set the main window widget
    w.setCentralWidget(chartView);
    w.resize(420, 300);

    w.show();
    return a.exec();
}
