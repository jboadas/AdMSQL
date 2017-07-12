#ifndef WINDOW_H
#define WINDOW_H

#include <QSystemTrayIcon>
#include <QDialog>

QT_BEGIN_NAMESPACE
class QAction;
class QGroupBox;
class QLabel;
class QPushButton;
class QTextEdit;
class QMenu;
class QProcess;

QT_END_NAMESPACE

//! [0]
class Window : public QDialog
{
    Q_OBJECT

public:
    Window();

    void setVisible(bool visible);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void setIcon(int);
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void showMessage();
    void messageClicked();
    QString iniProceso(int);
    void instalarProceso();
    void iniciarProceso();
    void detenerProceso();
    void borrarProceso();
    void statusProceso();

private:
    void createIconGroupBox();
    void createMessageGroupBox();
    void createActions();
    void createTrayIcon();

    QGroupBox *iconGroupBox;
    QGroupBox *messageGroupBox;
    QTextEdit *bodyEdit;
    QPushButton *insServButton;
    QPushButton *iniServButton;
    QPushButton *detServButton;
    QPushButton *delServButton;
    QPushButton *verServButton;
    QPushButton *showMessageButton;
    QProcess *proc;

    QAction *instalarAction;
    QAction *iniciarAction;
    QAction *detenerAction;
    QAction *borrarAction;
    QAction *statusAction;
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
};
//! [0]


#endif // WINDOW_H
