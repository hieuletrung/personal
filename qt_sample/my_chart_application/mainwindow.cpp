#include "mainwindow.h"
#include "ui_mainwindow.h"

QChart *createBarChart() {
    QPieSeries *series = new QPieSeries();
    series->append("Jane", 10);
    series->append("Joe", 20);
    series->append("Andy", 30);
    series->append("Barbara", 40);
    series->append("Jason", 50);
    QPieSlice *slice = series->slices().at(1);
    slice->setExploded(); // Explode this chart
    slice->setLabelVisible(); // Make label visible
    slice->setPen(QPen(Qt::darkGreen, 2)); // Set line color
    slice->setBrush(Qt::green); // Set slice color
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Students Performance");

    return chart;
}

QChart *createLineChart() {
    QBarSet *set0 = new QBarSet("Jane");
    QBarSet *set1 = new QBarSet("John");
    QBarSet *set2 = new QBarSet("Axel");
    QBarSet *set3 = new QBarSet("Mary");
    QBarSet *set4 = new QBarSet("Samantha");
    *set0 << 10 << 20 << 30 << 40 << 50 << 60;
    *set1 << 50 << 70 << 40 << 45 << 80 << 70;
    *set2 << 30 << 50 << 80 << 13 << 80 << 50;
    *set3 << 50 << 60 << 70 << 30 << 40 << 25;
    *set4 << 90 << 70 << 50 << 30 << 16 << 42;
    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Student Performance");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->addAxis(axis, Qt::AlignBottom);

    return chart;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QChart *chart = createLineChart();
//    QChart *chart = createBarChart();

    QChartView *chartView = new QChartView(chart);
    chartView->setParent(ui->verticalFrame);
}

MainWindow::~MainWindow()
{
    delete ui;
}
