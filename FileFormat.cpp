#include "FileFormat.h"

FileFormat::FileFormat(QString a, QString b)
{
    type=a;name=b;
}

QString FileFormat::getType() const
{
    return type;
}

QString FileFormat::getName() const
{
    return name;
}

QList<FileFormat> FileFormat::makeFileFormat(const QString &data)
{
    QList<FileFormat> currFileList;
    int startPos = data.indexOf("\n");
    QString curr = data.mid(startPos + 1);
    QStringList currList = curr.split("\n");

    QStringList out;
    for(auto p = currList.begin(); p != currList.end()-1; p++){
        QString format = (*p).split(" ").first();
        QString currName = (*p).split(" ").last();
        out<< currName;
        currFileList.push_back(FileFormat(format,currName));
    }
    return currFileList;
}
