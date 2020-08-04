#include "textstream.h"

Tg::TextStream::TextStream() : QTextStream()
{
}

QTextStream &Tg::TextStream::operator<<(const std::string &string)
{
    QTextStream::operator<<(QString::fromStdString(string));
    return (*this);
}
