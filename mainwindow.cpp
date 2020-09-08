#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QMovie>
#include <QFileInfo>
#include <QTime>
#include <QMediaplayer>
 #include<QTextCodec>
#include <QSystemTrayIcon>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    n=0;
    m=0;
    xunhuan=0;
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题头
    flag=true;myvoice=true;
    mstate=false;
    player=new QMediaPlayer;
    myplaylist= new QMediaPlaylist();
    myplaylist->setCurrentIndex(0);
    ui->verticalSlider->setValue(30);//设置音量条的初始音量
    myplaylist->setPlaybackMode(QMediaPlaylist::Loop);
    connect(player,&QMediaPlayer::positionChanged,this,&MainWindow::updatePostion);//连接进度条
    connect(player,&QMediaPlayer::durationChanged,this,&MainWindow::updateDuration);
    connect(ui->treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(itemDoubleClickedSlot(QTreeWidgetItem*,int)));//连接双击槽

   IniteTree();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_about_clicked()
{
       QMessageBox::about(this,"团队",tr("制作：税敏 刘富康 陈志纲 安朝夕"));
}

void MainWindow::on_pushButton_clicked()
{
    this->close();
}

void MainWindow::on_toolButton_2_clicked()  //设置播放循环图标变换，gif动态图
{
     ui->label_4->setText(paths[m]);
     qDebug()<<m<<"----"<<paths[m];
    if(!flag)//播放音乐
    {
           qDebug()<<"暂停";
           ui->toolButton_2->setStyleSheet("background-image: url(:/resource/61V58PICDXw.jpg); border-image: url(:/resource/按键1副本.png); border:2px groove gray;border-radius:10px;padding:2px 4px;");
           player->pause();//停止播放
           movie->stop();
           qDebug()<<player;
    }
    else
    {
        ui->toolButton_2->setStyleSheet("background-image: url(:/resource/61V58PICDXw.jpg);border-image: url(:/resource/按键2.png);border:2px groove gray;border-radius:10px;padding:2px 4px;");

        movie = new QMovie("C:/Users/ZD/Desktop/homework/MyMusic/resource/a.gif");//播放动画gif
        ui->label_2->setMovie(movie);
        movie->start();
        player->play();
    }
    flag=(!flag);

}

void MainWindow::mousePressEvent(QMouseEvent *e)  //重新定义鼠标动作，实现无标题栏的界面拖动
{
    last = e->globalPos();
}
void MainWindow::mouseMoveEvent(QMouseEvent *e) //重新定义鼠标动作，实现无标题栏的界面拖动
{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    last = e->globalPos();
    move(x()+dx, y()+dy);
}
void MainWindow::mouseReleaseEvent(QMouseEvent *e) //重新定义鼠标动作，实现无标题栏的界面拖动
{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    move(x()+dx, y()+dy);
}

void MainWindow::on_toolButton_4_clicked()//最小化到托盘
{
     //隐藏程序主窗口
     this->hide();

     //新建QSystemTrayIcon对象
     mSysTrayIcon = new QSystemTrayIcon(this);
     //新建托盘要显示的icon
     QIcon icon = QIcon(":/resource/th.jpg");
     //将icon设到QSystemTrayIcon对象中
     mSysTrayIcon->setIcon(icon);
     //当鼠标移动到托盘上的图标时，会显示此处设置的内容
     mSysTrayIcon->setToolTip(QObject::trUtf8("MyMusic"));
     //在系统托盘显示此对象
     mSysTrayIcon->show();
}

void MainWindow::on_pushButton_2_clicked()//最小化窗口
{
    setWindowState(Qt::WindowMinimized);
}

void MainWindow::on_verticalSlider_actionTriggered(int action)//声音控件调整音量,直接转到槽
{
     player->setVolume(ui->verticalSlider->value());
}

void MainWindow::on_horizontalSlider_actionTriggered(int action)
{
    ui->horizontalSlider->setValue(player->duration());
}

void MainWindow::on_toolButton_clicked() //上一首
{
    if(myplaylist->currentIndex()==NULL)
    {
       qDebug()<<"wrong";
       myplaylist->setCurrentIndex(0);
       player->play();
    }
    else
    {
    myplaylist->setCurrentIndex(myplaylist->previousIndex());
    player->play();
    m--;
    m=m%(n);
    }
    ui->toolButton_2->setStyleSheet("background-image: url(:/resource/61V58PICDXw.jpg);border-image: url(:/resource/按键2.png);border:2px groove gray;border-radius:10px;padding:2px 4px;");
    movie = new QMovie("C:/Users/ZD/Desktop/homework/MyMusic/resource/a.gif");//播放动画gif
    ui->label_2->setMovie(movie);
    movie->start();

    ui->label_4->setText(paths[m]);
    qDebug()<<m<<"m----"<<paths[m];
}

void MainWindow::on_toolButton_3_clicked()//下一首
{
    if(myplaylist->nextIndex()==NULL)
    {
      // myplaylist->setCurrentIndex(0);
    }
    else
    {
        myplaylist->setCurrentIndex(myplaylist->nextIndex());
        player->play();
        m++;
        m=m%(n);
        ui->label_4->setText(paths[m]);
       qDebug()<<m<<"m----"<<paths[m];
    }
    ui->toolButton_2->setStyleSheet("background-image: url(:/resource/61V58PICDXw.jpg);border-image: url(:/resource/按键2.png);border:2px groove gray;border-radius:10px;padding:2px 4px;");
    movie = new QMovie("C:/Users/ZD/Desktop/homework/MyMusic/resource/a.gif");//播放动画gif
    ui->label_2->setMovie(movie);
    movie->start();


}

void MainWindow::on_toolButton_5_clicked()//切换静音图标
{
    if(myvoice)
    {
        ui->verticalSlider->setValue(0);
        player->setVolume(0);
        ui->toolButton_5->setStyleSheet("border-image: url(:/resource/静音图标.png);background-image: url(:/resource/QQ图片20180719093059.jpg);border:2px groove gray;border-radius:10px;padding:2px 4px");
    }
    else
    {
        ui->verticalSlider->setValue(30);
        player->setVolume(30);
        ui->toolButton_5->setStyleSheet("border-image: url(:/resource/图标音量.jpg);background-image: url(:/resource/QQ图片20180719093059.jpg);border:2px groove gray;border-radius:10px;padding:2px 4px");
    }
   myvoice=(!myvoice);

}


void MainWindow::on_pushButton_3_clicked()  //添加歌曲
{
    QTreeWidget *tree=ui->treeWidget;
    tree->setColumnCount(1);
    path=QFileDialog::getOpenFileName(this,"open","./","*.mp3");
    QFileInfo fileInfo;
    fileInfo=QFileInfo(path);
    QString fileName=fileInfo.baseName();//获取歌名
    QTreeWidgetItem  *node=new QTreeWidgetItem(tree);
    node->setText(0,fileName);
    myplaylist->addMedia(QUrl::fromLocalFile(path));
    paths[n]=fileName;
    qDebug()<<n<<"n----"<<paths[n];
    n++;

    //写入文件
     QFile file("path.txt");
     if(file.open(QIODevice::Append))
    {
     QTextStream out(&file);
     out<<path<<"\r\n"<<endl;
      out<<fileName<<"\r\n"<<endl;
    }
    else
     qDebug()<<file.errorString();
    file.close();
}

void MainWindow::IniteTree() //初始化树
{
    QTextCodec *codec = QTextCodec::codecForName("GBK");
      qDebug()<<" 1";
       QTreeWidget *tree=ui->treeWidget;
       ui->treeWidget->setHeaderHidden("");//隐藏首行
       tree->clear();
       tree->setColumnCount(1);

       QFile file("path.txt");
       if(!file.open(QIODevice::ReadOnly))
            {
            qDebug()<<"open error";
                return;
       }
        bool flag=true;
         while(!file.atEnd())
         {

         QByteArray str = file.readLine();//编码格式
         QString ba=codec->toUnicode(str);

         QStringList parts = ba.split("\r\n");
         QTreeWidgetItem *node = new QTreeWidgetItem(tree);
         if(!flag)
         {
              paths[n]=parts[0];
             qDebug()<<n<<"n----"<<paths[n];
             n++;
             node->setText(0,parts[0]);
         }
         else
         {
             myplaylist->addMedia(QUrl::fromLocalFile(parts[0]));
             qDebug()<<"path"<<parts[0];
         }
         flag=(!flag);
         }

     player->setPlaylist(myplaylist);
     ui->treeWidget->setHeaderHidden("");
}

void MainWindow::updatePostion(qint64 position)
{
    ui->horizontalSlider->setValue(position);

    QTime duration(0, position / 60000, qRound((position % 60000) / 1000.0));

    ui->label_6->setText(duration.toString(tr("mm:ss")));
}

void MainWindow::updateDuration(qint64 duration)
{
    ui->horizontalSlider->setRange(0,duration); //设置范围
   ui->horizontalSlider->setEnabled(duration>0);
        ui->horizontalSlider->setPageStep(duration/10);//设置步长
//        ui->label_3->setText(QStringLiteral("%1:%2").arg(duration/60000,2,10,QLatin1Char('0')).arg(duration/1000,2,10,QLatin1Char('0')));
}

void MainWindow::itemDoubleClickedSlot(QTreeWidgetItem *item, int)
{
    this->selectItem = item;

}

void MainWindow::on_toolButton_6_clicked() ///循环方式
{
    if(xunhuan==0)
    {
        xunhuan=1;
       myplaylist->setPlaybackMode(QMediaPlaylist::Loop); //列表循环
    }
    else if(xunhuan==1)
    {
         myplaylist->setPlaybackMode(QMediaPlaylist::Random); //随机播放
        ui->toolButton_6->setStyleSheet("border-image: url(:/resource/按键10.png);background-image: url(:/resource/61V58PICDXw.jpg);border:2px groove gray;border-radius:10px;padding:2px 4px");
        xunhuan=2;
    }
    else if(xunhuan==2)
    {
        ui->toolButton_6->setStyleSheet("border-image: url(:/resource/按键12.png);background-image: url(:/resource/61V58PICDXw.jpg);border:2px groove gray;border-radius:10px;padding:2px 4px");
      myplaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop); //单曲循环
        xunhuan=0;
    }

}
