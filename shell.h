#ifndef SHELL_H
#define SHELL_H

#include <QString>

class shell
{
public:
    static QString And;

    static QString ssh;
    static QString ls;
    static QString ls_a,ls_al;

    static QString isfile,isdir;

    static QString Next(const QString&);
    static QString NextUpdate(const QString&);
    static QString remove(const QString&);
};


#endif // SHELL_H
