#include "FileFormat.h"

FileFormat::FileFormat(FileFormat::Format a, QString b)
{
    type=a;name=b;
}

FileFormat::Format FileFormat::getType() const
{
    return type;
}

QString FileFormat::getName() const
{
    return name;
}

QString FileFormat::getDir() const
{
    return dir;
}

QList<FileFormat> FileFormat::makeFileFormat(const QString &data)
{
    QList<FileFormat> currFileList;
    int startPos = data.indexOf("\n");
    QString curr = data.mid(startPos + 1);
    QStringList currList = curr.split("\n");

    for(auto p = currList.begin(); p != currList.end()-1; p++){
        QString format = (*p).split(" ").first();
        QString currName = (*p).split(" ").last();
        if(format[0] == "d")
            currFileList.push_back(FileFormat(Format::DIR,currName));
        if(format[0] == "-")
            currFileList.push_back(FileFormat(Format::FILE,currName));
    }
    return currFileList;
}
