#include "pairkey.h"

Mere::Store::PairKey::PairKey(const QString &key)
    : Key(key)
{

}

bool Mere::Store::PairKey::hasPart() const
{
    bool ok = false;

    int pos = 0;
    while (1)
    {
        pos = indexOf(SEPARATOR, pos);
        if (pos == -1) break;

        if (pos == 0 || at(pos - 1) != QChar(92))
        {
            ok = true;
            break;
        }
        pos++;
    }

    return ok;
}

int Mere::Store::PairKey::numberOfParts() const
{
    int numberOfParts = 0;

    int pos = 0;
    while (1)
    {
        pos = indexOf(SEPARATOR, pos);
        if (pos == -1) break;

        if (pos == 0 || at(pos - 1) != QChar(92))
        {
            numberOfParts++;
        }
        pos++;
    }

    return numberOfParts;
}

int Mere::Store::PairKey::indexOfNth(int nth) const
{
    int index = -1;

    int pos = 0;
    while (1)
    {
        pos = indexOf(SEPARATOR, pos);
        if (pos == -1) break;

        if (pos == 0 || at(pos - 1) != QChar(92))
        {
            if (--nth == 0)
            {
                index = pos;
                break;
            }
        }

        pos++;
    }

    return index;
}
