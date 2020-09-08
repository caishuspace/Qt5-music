#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QMediaMetaData>
#include <QMediaplayList>
#include <QMediaplayer>
#include <QMouseEvent>
#include  <QPoint>
#include <QSystemTrayIcon>

#include <QTimer>
#include <QMovie>
#include <QSlider>
#include <QFile>
#include <QFileDialog>
#include <QTreeWidgetItem>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updatePostion(qint64 position);
    void updateDuration(qint64 duration);

private slots:
    void on_about_clicked();

    void on_pushButton_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_verticalSlider_actionTriggered(int action);

    void on_horizontalSlider_actionTriggered(int action);

    void on_toolButton_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_5_clicked();

    void on_pushButton_3_clicked();


    void on_toolButton_6_clicked();

public slots:
    void IniteTree();

   // void setPosition(int position)；
    void itemDoubleClickedSlot(QTreeWidgetItem*,int);//双击播放

private:
    Ui::MainWindow *ui;
public :
    bool flag;
    bool mstate;
    bool myvoice;
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    QPoint last;
    QMediaPlayer *player;
    QMediaPlaylist *myplaylist;//播放列表
    QMovie *movie;
    QSlider *positionSlider;//进度条位置
    QMediaPlayer::State state;//歌曲播放状态
    QString path;
    QTreeWidgetItem* selectItem;//选中区间
    QString paths[50];
    qint64 n,m;
    QStringList neirong;
    int xunhuan;
    QSystemTrayIcon *mSysTrayIcon;

};

#endif // MAINWINDOW_H
