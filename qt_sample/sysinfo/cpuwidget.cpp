#include "cpuwidget.h"

#include "sysinfo.h"

using namespace QtCharts;

CpuWidget::CpuWidget(QWidget* parent) :
    SysInfoWidget (parent),
    mSeries(new QPieSeries(this))
{
    mSeries->setHoleSize(0.35);
    mSeries->append(tr("Load"), 30.0);
    mSeries->append(tr("Free"), 70.0);

    QChart *chart = chartView().chart();
    chart->addSeries(mSeries);
    chart->setTitle(tr("CPU Average Load"));
}

void CpuWidget::updateSeries() {
    double cpuLoadAverage = SysInfo::instance().cpuLoadAverage();
    mSeries->clear();
    mSeries->append(tr("Load"), cpuLoadAverage);
    mSeries->append(tr("Free"), 100.0 - cpuLoadAverage);
}
