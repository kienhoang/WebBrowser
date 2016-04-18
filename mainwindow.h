#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrl>
#include <QNetworkCookieJar>
#include <QNetworkAccessManager>
namespace Ui {
class MainWindow;
}
class myCookie: public QNetworkCookieJar{
public:
    QList<QNetworkCookie> myAllCookies();
    void saveCookie();
    void loadCookie();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void setchangeurl();
    void changetitle();


    void on_btnBack_clicked();

    void on_btnForward_clicked();

    void on_btnHome_clicked();

    void on_btnReload_clicked();

    void on_btnSetting_clicked();

private:
    Ui::MainWindow *ui;
    void SaveSetting();
    void LoadSetting();
    QUrl home;
    myCookie *mCookieJar;
    QNetworkAccessManager *nam;
protected :
    void closeEvent(QCloseEvent *event);
};


#endif // MAINWINDOW_H
