#include "Trit.h"



Trit inttoTrit (unsigned int x)
{

    switch(x)
    {
        case 0:
            return Trit::U;
        case 1:
            return Trit::F;
        case 2:
            return Trit::T;
        default:
            return Trit::U;
    }
}

unsigned int TrittoInt(Trit a)
{
    if(a == Trit::T)
    {
        return 2;
    }
    if(a == Trit::U)
    {
        return 0;
    }
    if(a == Trit::F)
    {
        return 1;
    }
    return 0;
}


Trit operator &(Trit a,Trit b)
{
    if( (a == Trit::F) || (b == Trit::F))
    {
        return Trit::F;
    }
    else if((a == Trit:: U) || (b == Trit::U))
    {
        return Trit::U;
    }
    else
    {
        return Trit::T;
    }
}

Trit operator |(Trit a, Trit b)
{
    if((a == Trit::T) || (b == Trit::T))
    {
        return Trit::T;
    }
    else if((a == Trit:: U) || (b == Trit::U))
    {
        return Trit::U;
    }
    else
    {
        return Trit::F;
    }
}

Trit operator !(Trit a)
{
    Trit b;
    switch(a)
    {
        case Trit::U:
            b = Trit::U;
            break;
        case Trit::T:
            b = Trit::F;
            break;
        case Trit::F:
            b = Trit::T;
            break;
    }

    return b;
}
