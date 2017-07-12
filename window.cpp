#include <QtGui>
#include <QVBoxLayout>
#include "window.h"
#include <QtScript/QtScript>



//! [0]
Window::Window()
{
    createIconGroupBox();
    createMessageGroupBox();

    createActions();
    createTrayIcon();

    connect(insServButton, SIGNAL(clicked()), this, SLOT(instalarProceso()));
    connect(iniServButton, SIGNAL(clicked()), this, SLOT(iniciarProceso()));
    connect(detServButton, SIGNAL(clicked()), this, SLOT(detenerProceso()));
    connect(delServButton, SIGNAL(clicked()), this, SLOT(borrarProceso()));
    connect(verServButton, SIGNAL(clicked()), this, SLOT(statusProceso()));

    //connect(showMessageButton, SIGNAL(clicked()), this, SLOT(showMessage()));
    //connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(messageClicked()));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(iconGroupBox);
    mainLayout->addWidget(messageGroupBox);
    setLayout(mainLayout);

    trayIcon->show();

    setWindowTitle(tr("AdMySQL"));
    resize(400, 300);
    statusProceso();
}
//! [0]

//! [1]
void Window::setVisible(bool visible)
{
    minimizeAction->setEnabled(visible);
    maximizeAction->setEnabled(!isMaximized());
    restoreAction->setEnabled(isMaximized() || !visible);
    QDialog::setVisible(visible);
}
//! [1]

//! [2]
void Window::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible()) {
        showMessage();
        hide();
        event->ignore();
    }
}
//! [2]

//! [3]
void Window::setIcon(int index)
{
    QIcon icon;
    if(index==0){
        //aplicacion
        icon = QIcon(":/images/aplicacion.svg");
    }else if(index == 1){
        icon = QIcon(":/images/aplplay.svg");
    }else if(index==2){
        icon = QIcon(":/images/aplpause.svg");
    }else if(index==3){
        icon = QIcon(":/images/apldel.svg");
    }else{
        icon = QIcon(":/images/apicacion.svg");
    }
    trayIcon->setIcon(icon);
    setWindowIcon(QIcon(":/images/aplicacion.svg"));

    trayIcon->setToolTip(tr("AdMySQL"));
}
//! [3]

//! [4]
void Window::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        showNormal();
        break;
    case QSystemTrayIcon::MiddleClick:
        showNormal();
        break;
    default:
        ;
    }
}
//! [4]

//! [5]
void Window::showMessage()
{
    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);

    trayIcon->showMessage("AdMySQL", bodyEdit->toPlainText(), icon);
}
//! [5]

//! [6]
void Window::messageClicked()
{
    QMessageBox::information(0, tr("AdMySQL"),tr("No tengo respuestas ."));
}
//! [6]

void Window::createIconGroupBox()
{
    QIcon iconCR = QIcon(":/images/instalar.svg");
    QIcon iconIN = QIcon(":/images/iniciar.svg");
    QIcon iconDE = QIcon(":/images/parar.svg");
    QIcon iconBO = QIcon(":/images/borrar.svg");
    QIcon iconDT = QIcon(":/images/status.svg");
    iconGroupBox = new QGroupBox(tr("Panel de Control"));
    insServButton = new QPushButton(iconCR,tr("Crear"));
    iniServButton = new QPushButton(iconIN,tr("Iniciar"));
    detServButton = new QPushButton(iconDE,tr("Detener"));
    delServButton = new QPushButton(iconBO,tr("Borrar"));
    verServButton = new QPushButton(iconDT,tr("Status"));

    QHBoxLayout *iconLayout = new QHBoxLayout;
    iconLayout->addWidget(insServButton);
    iconLayout->addWidget(iniServButton);
    iconLayout->addWidget(detServButton);
    iconLayout->addWidget(delServButton);
    iconLayout->addWidget(verServButton);
    iconLayout->addStretch();
    iconGroupBox->setLayout(iconLayout);
}

void Window::createMessageGroupBox()
{
    messageGroupBox = new QGroupBox(tr("Mensajes:"));

    bodyEdit = new QTextEdit;
    bodyEdit->setPlainText(tr("AdMySQL continuara en le bandeja del sistema"));

    //showMessageButton = new QPushButton(tr("Mostrar Mensajes"));
    //showMessageButton->setDefault(true);

    QGridLayout *messageLayout = new QGridLayout;
    messageLayout->addWidget(bodyEdit, 3, 1, 2, 4);
    //messageLayout->addWidget(showMessageButton, 5, 4);
    messageLayout->setColumnStretch(3, 1);
    messageLayout->setRowStretch(4, 1);
    messageGroupBox->setLayout(messageLayout);
}

void Window::createActions()
{
    instalarAction = new QAction(QIcon(":/images/instalar.svg"),"Instalar Servicio",this);
    connect(instalarAction, SIGNAL(triggered()), this, SLOT(instalarProceso()));

    iniciarAction = new QAction(QIcon(":/images/iniciar.svg"),"Iniciar Servicio",this);
    connect(iniciarAction, SIGNAL(triggered()), this, SLOT(iniciarProceso()));

    detenerAction = new QAction(QIcon(":/images/parar.svg"),"Detener Servicio",this);
    connect(detenerAction, SIGNAL(triggered()), this, SLOT(detenerProceso()));

    borrarAction = new QAction(QIcon(":/images/borrar.svg"),"Desinstalar Servicio",this);
    connect(borrarAction, SIGNAL(triggered()), this, SLOT(borrarProceso()));

    statusAction = new QAction(QIcon(":/images/status.svg"),"Status Servicio",this);
    connect(statusAction, SIGNAL(triggered()), this, SLOT(statusProceso()));

    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void Window::createTrayIcon()
{
    QIcon icon = QIcon(":/images/aplicacion.svg");
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(instalarAction);
    trayIconMenu->addAction(iniciarAction);
    trayIconMenu->addAction(detenerAction);
    trayIconMenu->addAction(borrarAction);
    trayIconMenu->addAction(statusAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(minimizeAction);
    //trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);


    trayIcon = new QSystemTrayIcon(icon,this);
    trayIcon->setContextMenu(trayIconMenu);
    setIcon(0);
}

void Window::instalarProceso()
{
    //Install MySQLD
    if(iniProceso(4)=="NOEXISTE"){
        QString res = iniProceso(0);
        if(res == "NEGADO"){
            bodyEdit->append("Debe iniciar el programa como Administrador");
        }
    }else{
        bodyEdit->append("SERVICIO MYSQL YA ESTA INSTALADO");
    }
}
void Window::iniciarProceso()
{
    //Iniciar servicio MySQL
    if(iniProceso(4)=="DETENIDO"){
        iniProceso(1);
    }else{
        bodyEdit->append("NO SE PUEDE INICIAR EL SERVICIO MYSQL");
    }
}
void Window::detenerProceso()
{
    //Detener Servicio MySQL
    if(iniProceso(4)=="INICIADO"){
        iniProceso(2);
    }else{
        bodyEdit->append("NO SE PUEDE DETENER EL SERVICIO MYSQL");
    }

}
void Window::borrarProceso()
{
    //Borrar Servicio MySql
    if(iniProceso(4)=="DETENIDO"){
        iniProceso(3);
    }else{
        bodyEdit->append("NO SE PUEDE BORRAR EL SERVICIO MYSQL");
    }
}
void Window::statusProceso()
{
    //Verifica el status del servicio
    QString status = iniProceso(4);
    if(status=="DESCONOCIDO"){
        bodyEdit->append("estatus del servicio: DESCONOCIDO");
    }else if(status=="INSTALADO"){
        bodyEdit->append("estatus del servicio: INSTALADO");
    }else if(status=="DETENIENDOSE"){
        bodyEdit->append("estatus del servicio: DETENIENDOSE");
    }else if(status=="INICIADO"){
        bodyEdit->append("estatus del servicio: INICIADO");
    }else if(status=="INICIANDO"){
        bodyEdit->append("estatus del servicio: INICIANDO");
    }else if(status=="DETENIDO"){
        bodyEdit->append("estatus del servicio: DETENIDO");
    }else if(status=="NOEXISTE"){
        bodyEdit->append("estatus del servicio: NO EXISTE");
    }else if(status=="BORRADO"){
        bodyEdit->append("estatus del servicio: BORRADO");
    }else if(status=="NEGADO"){
        bodyEdit->append("Debe Iniciar el programa como Administrador");
    }else{
        bodyEdit->append("estatus del servicio: ERROR 9941");
    }

}

QString Window::iniProceso(int i){

    // QProcess related code
    proc = new QProcess( this );

    QString program;
    QStringList arguments;
    QString resultado;
    QString status;

    bodyEdit->clear();

    if(i==0){
        program = "mysqld";
        arguments << "--install";
    }
    else if(i==1){
        program = "sc.exe";
        arguments << "start" << "MySQL";
    }
    else if(i==2){
        program = "sc.exe";
        arguments << "stop" << "MySQL";
    }
    else if(i==3){
        program = "sc.exe";
        arguments << "delete" << "MySQL";
    }
    else if(i==4){
        program = "sc.exe";
        arguments << "query" << "MySQL";
    }
    else{
        resultado = "Error 1000: Argumentos no validos";
    }

    proc->start(program,arguments);

    if (proc->waitForStarted(1000) == false)
    resultado.append("ERROR INICIANDO PROGRAMA EXTERNO");

    else
    resultado.append("PROGRAMA EXTERNO FUNCIONANDO");

    proc->waitForReadyRead(100);
    proc->waitForFinished(100);
    resultado.append(proc->readAllStandardOutput());

    //bodyEdit->append(resultado);

    QScriptEngine interpreter;

    QString nombreFile(":/mensajes.js");
    QFile file(nombreFile);
    if (!file.open(QIODevice::ReadOnly)) {
        bodyEdit->append(file.fileName()+"\n No puedo leer el Script");
        status = "FALLA";
        return status;
    }
    interpreter.evaluate(file.readAll(), nombreFile);
    file.close();

    QScriptValue verifText = interpreter.evaluate("verificarTexto");
    QScriptValueList text;
    text << resultado;
    QScriptValue resTexto = verifText.call(QScriptValue(),text);
    status = resTexto.toString();

    if(status=="INICIADO" || status=="INICIANDO"){
        setIcon(1);
    }else if(status=="INSTALADO" || status=="DETENIENDOSE" || status=="DETENIDO"){
        setIcon(2);
    }else if(status=="NEGADO" || status=="BORRADO" || status=="NOEXISTE"){
        setIcon(3);
    }else{
        setIcon(0);
    }

    bodyEdit->append("El Servicio esta: "+status);
    showMessage();

return status;

}

