#define DELETE(x) if(nullptr!=x)delete x;x=nullptr;

#include "Qavita.h"

Qavita::Qavita(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	m_sysTrayIcon = new QSystemTrayIcon(this);
	QString icon_path = qApp->applicationDirPath() + "/icons/icon.png";
	QIcon icon = QIcon(icon_path);
	m_sysTrayIcon->setIcon(icon);
	m_sysTrayIcon->setToolTip(QString::fromLocal8Bit("Qavita"));
	m_quitAction = new QAction(QString::fromLocal8Bit("Quit"), this);
	connect(m_quitAction, &QAction::triggered, this, &Qavita::on_Quit);
	m_menu = new QMenu(QApplication::desktopFileName());
	m_menu->addAction(m_quitAction);
	m_sysTrayIcon->setContextMenu(m_menu);
	m_sysTrayIcon->show();
	QString kavita_dir = qApp->applicationDirPath() + "/bin/Kavita/";
	m_kavita = new QProcess();
	m_kavita->setWorkingDirectory(kavita_dir);
	m_kavita->start(kavita_dir + "Kavita.exe");
}

void Qavita::on_Quit()
{
	if (nullptr != m_kavita)
	{
		//if (m_kavita->state() == QProcess::ProcessState::Running)
		m_kavita->terminate();
		delete m_kavita;
	}
	qApp->quit();
}

Qavita::~Qavita()
{
}
