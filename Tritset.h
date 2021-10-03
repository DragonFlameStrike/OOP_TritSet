//
// Created by 1 on 12.09.2021.
//

#ifndef TRITS_TRITSET_H
#define TRITS_TRITSET_H

#include "Trit.h"

#include <iostream>
#include <cstdlib>

const unsigned int Trit_U_Int = sizeof(unsigned int)*4;


class ProxyTrit;
class TritSet {
    friend class ProxyTrit;


private:
    std::vector<unsigned int> set;
    unsigned int size_b;
    unsigned int capasity;
public:
    TritSet();

    explicit TritSet(unsigned int size);

    friend std::ostream &operator<<(std::ostream &out, const Trit &pTrit);

    friend std::ostream &operator<<(std::ostream &out, const TritSet &pTritSet);

    TritSet(const TritSet &set);

    ~TritSet();

    unsigned int getSize() const;

    unsigned int length() const;

    Trit get(unsigned int position) const;

    void resize(size_t lastIndex);

    unsigned int getCapacity() const;

    void push(unsigned int position, Trit t);

    unsigned int cmp_size_b(TritSet const &obj) const;

    unsigned int cmp_capasity(TritSet const &obj) const;

    TritSet operator&(const TritSet  &obj) const;

    TritSet operator|(const TritSet &obj)const;

    TritSet operator!() const;

    bool operator==(const TritSet &obj) const;

    bool operator!=(const TritSet &obj) const;

    TritSet& operator=(TritSet const & t);

    Trit operator[](unsigned int i) const;

    ProxyTrit operator[](unsigned int i);

};
class ProxyTrit
{
private:
    TritSet &tritset;
    unsigned int index;

public:
    explicit ProxyTrit(TritSet & t, unsigned int i): tritset(t), index(i){}


    ~ProxyTrit()
    = default;

    ProxyTrit & operator=(Trit const & t)
    {
        if(!tritset.set.empty())
        {
            tritset = TritSet(index);
        }
        unsigned int tmp = TrittoInt(t);
        unsigned int sdvig = (index % Trit_U_Int)*2;
        unsigned int mask = tmp << sdvig;
        unsigned int res = tritset.set[index / Trit_U_Int];
        res &= ~(0x03 << sdvig);
        res |= mask;
        tritset.set[index / Trit_U_Int] = res;

        return *this;
    }

    bool operator==(const Trit & t) const
    {
        Trit k = tritset.get(index);
        if(k == t)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

#endif //TRITS_TRITSET_H
