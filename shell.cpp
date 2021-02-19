#include "shell.h"

QString shell::And = " && ";
QString shell::ssh = "ssh ";
QString shell::ls = " ls ";
QString shell::ls_a = " ls -a ";
QString shell::ls_al = " ls -al ";

QString shell::isfile = "Not a directory";
QString shell::isdir = "not a regular file";

QString shell::Next(QString& name)
{
    return QString("cd "+name);
}

QString shell::NextUpdate(QString& name)
{
    return QString("cd "+name+And+ls_al);
}

QString shell::remove(const QString &f)
{
    return QString(" rm -r "+f);
}
