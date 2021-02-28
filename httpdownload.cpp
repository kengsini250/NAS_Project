#include "httpdownload.h"

QStringList Reg(const QString &r)
{
    QStringList out;
    QRegularExpression regex("<a href=\"(.*?|/)\"");
    auto i = regex.globalMatch(r);
    while(i.hasNext()){
        auto match = i.next();
        auto s = match.captured(1);
        if(s == "&nbsp;" || s == "?C=N;O=D" || s == "?C=M;O=A" || s == "?C=S;O=A" || s == "?C=D;O=A" ){}
        else{
            auto t =match.captured(1);
            out<<t;
        }
    }
    out.removeAt(0);
    return out;
}
