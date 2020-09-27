#include "key.h"

QChar Mere::Store::Key::SEPARATOR = QChar(58);

Mere::Store::Key::Key(const QString &key)
    : QString(key)
{

}
