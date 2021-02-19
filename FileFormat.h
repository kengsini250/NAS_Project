#ifndef FILEFORMAT_H
#define FILEFORMAT_H

#include <QString>
#include <QList>

class FileFormat{
public:
    FileFormat(QString a,QString b);
    QString getType() const;
    QString getName() const;

    static QList<FileFormat> makeFileFormat(const QString&);
private:
    QString type;
    QString name;
};

#endif // FILEFORMAT_H
