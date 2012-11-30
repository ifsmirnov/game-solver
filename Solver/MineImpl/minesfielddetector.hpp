#ifndef MINESFIELDDETECTOR_HPP
#define MINESFIELDDETECTOR_HPP

#include <QImage>
#include <vector>
#include <string>
#include <map>
#include <iostream>

class MinesFieldDetector
{
private:
    class HashString // should it be template class?
    {
    public:
        typedef unsigned long long hash_t;

    public:
        template<typename Iterator>
        HashString(Iterator begin, Iterator end, hash_t base = 42359)
        {
            int len = std::distance(begin, end);
            hash.resize(len);
            basePow.resize(len + 1);
            basePow[0] = 1;
            for (int i = 0; begin != end; ++begin)
            {
                basePow[i+1] = basePow[i] * base;
                hash[i] = *begin;
                if (i != 0)
                    hash[i] += hash[i-1] * base;
            }
        }
        hash_t getHash(int l, int len) const
        {
            int r = l + len - 1;
            if (l == r)
                return 0;
            else if (l > r || l < 0 || r >= (int)hash.size())
                throw;
            else
                return hash[r] - hash[l] * basePow[len];
        }
        int length() const
        {
            return hash.size();
        }


    private:
        std::vector<hash_t> hash;
        std::vector<hash_t> basePow;
    };

public:
    MinesFieldDetector();

    int numberOfOccurrences(const HashString& str, int pos, int len);

    template<typename Iterator>
    std::pair<int, std::vector<int> > longestFrequentSubstrs(Iterator first, Iterator last, int freq)
    {
        // find the substring of string [first, last) which has at least freq non-overlapping
        // occurrences and return all it's occurrences (their first positions)

        HashString str(first, last);

        int left = 0, right = str.length(), mid;
        while (left < right - 1)
        {
            mid = left + (right - left) / 2;

            if (mid == 0)
                left = 0;

            std::map<HashString::hash_t, std::vector<int> > occur;
            for (int i = 0; i+mid <= str.length(); i++)
                occur[str.getHash(i, mid)].push_back(i);
            int max = 0;
            std::cerr << "mid = " << mid << std::endl;
            for (const auto& i: occur)
            {
                const std::vector<int> &pos = i.second;
                int res = 0, last = -str.length();
                for (int j = 0; j < (int)pos.size(); j++)
                {
                    if (pos[j] >= last + mid)
                    {
                        std::cerr << pos[j] << " ";
                        ++res;
                        last = pos[j];
                    }
                }
                std::cerr << std::endl;
                max = std::max(max, res);
            }

            if (max >= freq)
                left = mid;
            else
                right = mid;
        }

        return std::make_pair(left, std::vector<int>());
    }

    void detect(QImage);
};

#endif // MINESFIELDDETECTOR_HPP
