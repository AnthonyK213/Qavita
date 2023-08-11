#include "Qavita.h"

Qavita::Qavita(QWidget* parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    m_sysTrayIcon = new QSystemTrayIcon(this);
    QString icon_path = qApp->applicationDirPath() + "/icons/icon.png";
    m_sysTrayIcon->setIcon(QIcon(icon_path));
    m_sysTrayIcon->setToolTip(QString("Qavita"));

    m_restartAction = new QAction(tr("Restart"), this);
    connect(m_restartAction, &QAction::triggered, this, &Qavita::restart);

    m_quitAction = new QAction(tr("Quit"), this);
    connect(m_quitAction, &QAction::triggered, this, &Qavita::on_Quit);

    m_menu = new QMenu(QApplication::desktopFileName());
    m_menu->addAction(m_restartAction);
    m_menu->addSeparator();
    m_menu->addAction(m_quitAction);

    m_sysTrayIcon->setContextMenu(m_menu);
    m_sysTrayIcon->show();

    m_kavita_dir = qApp->applicationDirPath() + "/bin/Kavita/";
    m_kavita = new QProcess();
    m_kavita->setWorkingDirectory(m_kavita_dir);

    start();
}

void Qavita::start() {
    m_kavita->start(m_kavita_dir + "Kavita");
}

void Qavita::close() {
    m_kavita->terminate();
}

void Qavita::restart() {
    if (m_kavita->state() == QProcess::Running) {
        m_kavita->kill();
        m_kavita->waitForFinished();
    }
    start();
}

void Qavita::on_Quit() {
    if (nullptr != m_kavita) {
        close();
        delete m_kavita;
    }
    qApp->quit();
}

Qavita::~Qavita() {}
