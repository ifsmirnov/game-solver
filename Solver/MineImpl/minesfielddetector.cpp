#include "minesfielddetector.hpp"

MinesFieldDetector::MinesFieldDetector()
{
}

int MinesFieldDetector::numberOfOccurrences(const HashString &str, int pos, int len)
{
    // return number of non-overlapping occurrences of a substr [pos, pos+len) in str

    int res = 0;
    HashString::hash_t hash = str.getHash(pos, len);

    for (int i = 0; i + len <= str.length(); i++)
    {
        if (str.getHash(i, len) == hash)
        {
            ++res;
            i += len-1;
        }
    }
    return res;
}

void MinesFieldDetector::detect(QImage image)
{
    if (image.width()) { }
}
