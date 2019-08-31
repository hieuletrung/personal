#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "SoundEffectWidget.h"
#include "PlaybackWorker.h"
#include "Track.h"
#include "Serializer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool eventFilter(QObject* watched, QEvent* event) override;

private slots:
    void playSoundEffect(int soundId);
    void clearPlayback();
    void stopPlayback();

    void saveProject();
    void loadProject();

private:
    void initSoundEffectWidgets();
    void updateState(const Track::State& state);
    void startDisplayTimer();
    void updateDisplayTime();
    void stopDisplayTimer();
    void startPlayback();

    QString formatTime(long ms);

private:
    Ui::MainWindow *ui;
    QVector<SoundEffectWidget*> mSoundEffectWidgets;
    PlaybackWorker* mPlaybackWorker;
    QThread* mPlaybackThread;
    QTimer mDisplayTimer;
    Track mTrack;
    std::unique_ptr<Serializer> mSerializer;
};

#endif // MAINWINDOW_H
