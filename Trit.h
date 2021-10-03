//
// Created by 1 on 12.09.2021.
//

#ifndef TRITS_TRIT_H
#define TRITS_TRIT_H

#include <iostream>

enum class Trit
{
    F, U, T //0 1 2
};

unsigned int TrittoInt(Trit a);
Trit inttoTrit(unsigned int x);

Trit operator &(Trit a, Trit b);
Trit operator |(Trit a, Trit b);
Trit operator !(Trit a);


#endif //TRITS_TRIT_H
