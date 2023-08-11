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
    void start();
    void close();
    void restart();
    void on_Quit();

private:
    Ui::QavitaClass ui;

    QSystemTrayIcon* m_sysTrayIcon;

    QMenu* m_menu;

    QAction* m_restartAction;
    QAction* m_quitAction;

    QProcess* m_kavita;
    QString m_kavita_dir;
};
