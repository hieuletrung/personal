#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject* target = qobject_cast<QObject*>(ui->quickWidget->rootObject());
    const char* functionName = "addMarker";
    QMetaObject::invokeMethod(target, functionName, Qt::AutoConnection,
                              Q_ARG(QVariant, "Testing"),
                              Q_ARG(QVariant, 40.7274175),
                              Q_ARG(QVariant, -73.99835));

    // Position
    QGeoPositionInfoSource *source = QGeoPositionInfoSource::createDefaultSource(this);
    if (source) {
        connect(source, &QGeoPositionInfoSource::positionUpdated, this, &MainWindow::positionUpdated);
        source->startUpdates();
    }

    // Routing
    QGeoServiceProvider* serviceProvider = new QGeoServiceProvider("osm");
    QGeoRoutingManager* routingManager = serviceProvider->routingManager();
    connect(routingManager, &QGeoRoutingManager::finished, this, &MainWindow::routeCalculated);
    connect(routingManager, &QGeoRoutingManager::error, this, &MainWindow::routeError);

    QGeoRouteRequest request(QGeoCoordinate(40.675895,-73.9562151), QGeoCoordinate(40.6833154,-73.987715));
    routingManager->calculateRoute(request);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::positionUpdated(const QGeoPositionInfo &info)
{
    qDebug() << "Position updated:" << info;
}

void MainWindow::routeCalculated(QGeoRouteReply *reply)
{
    qDebug() << "Route Calculated";
    if (reply->routes().size() != 0) {
        // There could be more than 1 path
        // But we only get the first route
        QGeoRoute route = reply->routes().at(0);
        qDebug() << route.path();
    }
    reply->deleteLater();
}

void MainWindow::routeError(QGeoRouteReply *reply, QGeoRouteReply::Error error, const QString &errorString)
{
    qDebug() << "Route Error" << errorString;
    reply->deleteLater();
}
