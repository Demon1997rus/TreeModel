#include <QApplication>
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QDomDocument>

#include "src/treeview.h"

QString searchModelData()
{
    QString binDir = QCoreApplication::applicationDirPath();
    QString appName = QCoreApplication::applicationName();
    QString fileName("data.txt");

    QStringList searchList;
    searchList.append(binDir);
    searchList.append(binDir + "/data");
    searchList.append(binDir + "/../data");
    searchList.append(binDir + "/../" + appName + "/data");     // for development with shadow build (Linux)
    searchList.append(binDir + "/../../" + appName + "/data");  // for development with shadow build (Windows)
    searchList.append(QDir::rootPath() + "data/opt");
    searchList.append(QDir::rootPath() + "data");

    foreach (QString dir, searchList)
    {
        QFile file(dir + "/" + fileName);
        if (file.exists())
        {
            fileName = QDir(file.fileName()).canonicalPath();
            qDebug("Using model data file %s", qPrintable(fileName));
            return fileName;
        }
    }

    // not found
    foreach (QString dir, searchList)
    {
        qWarning("%s/%s not found", qPrintable(dir), qPrintable(fileName));
    }
    qFatal("Cannot find model data file %s", qPrintable(fileName));
    return nullptr;
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QFile file(searchModelData());
    file.open(QIODevice::ReadOnly);
    TreeExample::TreeView w(file.readAll());
    file.close();
    w.show();
    return app.exec();
}
