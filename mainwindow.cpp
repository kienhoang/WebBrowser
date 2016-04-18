#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWebKitWidgets/QWebView>
#include <QUrl>
#include <QIcon>
#include <QDebug>
#include <QSettings>
#include <QtWebKit>
#include "settingdialog.h"
#include <QFile>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*Load last settings*/
    LoadSetting();

    /*Connect Event*/
    connect(ui->lineEdit, SIGNAL(returnPressed()),ui->pushButton,SLOT(click()));
    connect(ui->webView,SIGNAL(urlChanged(QUrl)),this,SLOT(setchangeurl()));
    connect(ui->webView,SIGNAL(loadFinished(bool)),this,SLOT(changetitle()));
    /*Enable plugin*/
    ui->webView->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    ui->webView->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    ui->webView->settings()->setAttribute(QWebSettings::AutoLoadImages, true);
    /*Enable Cookie*/
    mCookieJar = new myCookie();
    nam = new QNetworkAccessManager();
    nam->setCookieJar(mCookieJar);
    ui->webView->page()->setNetworkAccessManager(nam);
    /*Load homepage*/
    ui->webView->load(home);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString url=ui->lineEdit->text();
    if(url.left(7).compare("http://") !=0 ){
        url="http://" + url;
    }
    ui->webView->load(QUrl(url));
}
void MainWindow::setchangeurl(){
    ui->lineEdit->setText(ui->webView->url().toString());

}
void MainWindow::SaveSetting(){
    QSettings settings("HK","WebSwimming");
    settings.beginGroup("Save Size");
    settings.setValue("state",this->saveState());
    settings.setValue("mainWindowGeometry", saveGeometry());
    settings.setValue("homepage",this->home);
    settings.endGroup();
}

void MainWindow::LoadSetting(){
    QSettings settings("HK","WebSwimming");
    settings.beginGroup("Save Size");
    this->restoreState(settings.value("state").toByteArray());
    restoreGeometry(settings.value("mainWindowGeometry").toByteArray());
    home=settings.value("homepage").toUrl();
    qDebug() << home;
    settings.endGroup();
}
void MainWindow::closeEvent(QCloseEvent *event){
    SaveSetting();
    //mCookieJar->saveCookie();
}
void MainWindow::changetitle(){
    this->setWindowTitle(ui->webView->title()+" - Web Swimming");
}


void MainWindow::on_btnBack_clicked()
{
    ui->webView->back();
}

void MainWindow::on_btnForward_clicked()
{
    ui->webView->forward();
}

void MainWindow::on_btnHome_clicked()
{
    ui->webView->load(home);
}

void MainWindow::on_btnReload_clicked()
{
    ui->webView->reload();
}

void MainWindow::on_btnSetting_clicked()
{
    SettingDialog * mSettingDialog = new SettingDialog(this);
    mSettingDialog->setVisible(false);
    mSettingDialog->setcrnthomepage(home.toString());
    mSettingDialog->exec();
    home = QUrl(mSettingDialog->gethomepage());
    delete mSettingDialog;
}

QList<QNetworkCookie> myCookie::myAllCookies(){
    return allCookies();
}
void myCookie::saveCookie(){
    QFile file("cookie.ini");
    if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
        for(int i=0; i< allCookies().count();i++){
            QTextStream out(&file);
            out << allCookies().at(i).domain()<<"\n";
            out << allCookies().at(i).expirationDate().toString()<<"\n";
            out << allCookies().at(i).name() << "\n";
            out << allCookies().at(i).path() <<"\n";
            out << allCookies().at(i).value() << "\n";
            qDebug() << allCookies().at(i).name();
            qDebug() << allCookies().at(i).value();

        }
        file.close();
    }
}

void myCookie::loadCookie(){
    QList<QNetworkCookie> cookielist;
    QFile file("cookie.ini");
    int i=0;
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        while (!file.atEnd()) {
                QByteArray name = file.readLine();
                QByteArray value = file.readLine();
                QNetworkCookie cookie;
                cookie.setName(name);
                cookie.setValue(value);
                //cookielist.insert(i,line)
                qDebug() << name;
                qDebug() << value;
                //QDateTime d;
                //d.setDate(QDate(5));
                i++;
            }
        setAllCookies(cookielist);
    }
}

