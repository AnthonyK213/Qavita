#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qavita.h"
#include <QSystemTrayIcon>
#include <QProcess>

class Qavita : public QMainWindow
{
	Q_OBJECT

public:
	Qavita(QWidget* parent = nullptr);
	~Qavita();

 private slots:
	void on_Quit();

private:
	Ui::QavitaClass ui;
	QSystemTrayIcon* m_sysTrayIcon;
	QProcess* m_kavita;
	QAction* m_quitAction;
	QMenu* m_menu;
};
