#include "Qavita.h"
#include <QDir>
#include <QLockFile>
#include <QtWidgets/QApplication>

int main(int argc, char* argv[]) {
    QString lockPath = QDir::temp().absoluteFilePath("Qavita.lock");
    QLockFile lockFile{ lockPath };

    if (!lockFile.tryLock(100)) {
        return 0;
    }

    QApplication a(argc, argv);
    Qavita w;
    return a.exec();
}
