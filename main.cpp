#include <iostream>
#include <vector>
#include "Tritset.h"


#include "Trit.h"
//TritSet Methods
TritSet::TritSet() {

    size_b=0;
    capasity=0;
}//Пустой конструктор
TritSet::TritSet(unsigned int size){
    size_b = size + Trit_U_Int - (size % Trit_U_Int); // выравнивание
    capasity = size;

    if(size_b > 0)
    {
        //set = new unsigned int [size_b / Trit_U_Int]; // size_b bite
        set.reserve((size_b / Trit_U_Int));
        for(unsigned int i = 0; i < size_b / Trit_U_Int; ++i)
        {
                set.push_back(0);
        }
    }
}//Конструктор на size элементов
TritSet::TritSet(const TritSet & t) {
    size_b = t.size_b;
    capasity = t.capasity;
    std::vector<unsigned int> new_set;

    for (unsigned int i = 0; i < size_b / Trit_U_Int; i++) {
        new_set[i] = t.set[i];
    }
    set = new_set;
} //Конструктор копирования
TritSet::~TritSet(){

    set.clear();
    size_b = 0;
    capasity = 0;

} // Диструктор
unsigned int TritSet::getSize() const
{
    return size_b;
} //DOne
unsigned int TritSet::getCapacity() const {
    return capasity;
} //DOne
unsigned int TritSet::length() const
{
    if(!set.empty())
    {
        for(unsigned int i = capasity; i != 0; i--)
        {
            if(get(i) != Trit::U)
            {
                return i;
            }
        }
        return 0;
    }
    return 0;
} // Done
void TritSet::resize(size_t lastIndex)
{
    set.resize(lastIndex/Trit_U_Int + 1,0);
    size_b=set.size()*Trit_U_Int;
    if(capasity< size_b){
        capasity=lastIndex;
    }
    else
        capasity = size_b;

} //Done
void TritSet::push(unsigned int position, Trit t)
{
    unsigned int tmp = TrittoInt(t);

    if(t == Trit::T || t == Trit::F)
    {
        if(set.empty())
        {
            size_b = position + Trit_U_Int - (position % Trit_U_Int);
            set.resize((size_b / Trit_U_Int),0);

        }
        else if(position > size_b)
        {
            unsigned int new_size_b = position + Trit_U_Int - (position % Trit_U_Int);
            set.resize(new_size_b / Trit_U_Int,0);
            size_b = new_size_b;
        }
    }

    unsigned int sdvig = (position % Trit_U_Int)*2;
    unsigned int mask = tmp << sdvig;
    unsigned int res = set[position/Trit_U_Int];
    res &= ~(0x03 << sdvig);
    res |= mask;
    set[position/Trit_U_Int] = res;
    if(capasity<position){
        capasity=position;
    }
} //Done
Trit TritSet::get(unsigned int position) const
{
    if(set.empty())
    {
        return Trit::U;
    }
    if(size_b < position)
    {
        return Trit::U;
    }

    unsigned int sdvig = (position % Trit_U_Int)*2;
    unsigned int tmp = (set[position/Trit_U_Int]  >>  sdvig) & 0x03;
    Trit res = inttoTrit(tmp);
    return res;
} //Done
unsigned int TritSet::cmp_size_b(TritSet const &obj) const
{
    if(size_b > obj.size_b)
    {
        return size_b;
    }
    else
    {
        return obj.size_b;
    }
} //Done
unsigned int TritSet::cmp_capasity(TritSet const &obj) const
{
    if(capasity > obj.capasity)
    {
        return capasity;
    }
    else
    {
        return obj.capasity;
    }
} //Done
TritSet TritSet::operator&(const TritSet &obj)const
{
    unsigned int size = obj.cmp_capasity(*this);
    TritSet tmp (size);
    for(unsigned int i = 0; i < size; i++)
    {
        tmp.push(i, this->get(i) & obj.get(i));
    }
    return tmp;
} //Done
TritSet TritSet::operator|(const TritSet &obj) const
{
    unsigned int size = obj.cmp_capasity(*this);
    TritSet tmp(size);
    for(unsigned int i = 0; i < size; i++)
    {
        tmp.push(i, get(i) | obj.get(i));
    }
    return tmp;
} //Done
TritSet TritSet::operator!() const
{
    TritSet tmp(capasity);
    for(unsigned int i = 0; i < size_b; i++)
    {
        tmp.push(i,!(this->get(i)));
    }
    return tmp;
} //Done
bool TritSet::operator==(const TritSet&obj) const
{
    if(this->length() != obj.length())
    {
        return false;
    }
    else
    {
        for(unsigned int i = 0; i < (this->size_b)/Trit_U_Int;i++)
        {
            if(this->set[i] != obj.set[i])
            {
                return false;
            }
        }
    }
    return true;
} //Done
bool TritSet::operator!=(const TritSet&obj) const
{
    if(this->length() != obj.length())
    {
        return true;
    }
    else
    {
        for(unsigned int i = 0; i < this->length();i++)
        {
            if(this->set[i] != obj.set[i])
            {
                return true;
            }
        }
    }
    return false;
} //Done
TritSet& TritSet::operator=(TritSet const & t) {
    if (this == &t)
    {
        return *this;
    }

    size_b = t.size_b;
    capasity = t.capasity;
    std::vector<unsigned int> new_set;
    new_set.reserve(size_b / Trit_U_Int);

    for(unsigned int i = 0; i < size_b / Trit_U_Int; ++i)
    {
        new_set.push_back(t.set[i]);
    }

    set = new_set;

    return *this;
} //Done
Trit TritSet::operator[](unsigned int i) const
{
    return get(i);
} //Done
ProxyTrit TritSet::operator[](unsigned int i)
{
    ProxyTrit m(*this, i);
    Trit t = get(i);
    m = t;
    return m;
} //Done
std::ostream &operator <<(std:: ostream &out, const Trit &t)
{
    switch(t)
    {
        case(Trit::T):
            out << "T";
            break;
        case(Trit::F):
            out << "F";
            break;
        case(Trit::U):
            out << "U";
            break;
        default:
            out << "U";
    }
    return out;
} //Done
std::ostream &operator <<(std:: ostream &out, const TritSet &t)
{
    for(unsigned int i = 0; i < t.getSize(); i++)
    {
        unsigned int now = TrittoInt(t.get(i));
        if(now==2){
            out << "T";
        }
        if(now==1){
            out << "F";
        }
        if(now==0){
            out << "U";
        }

    }

    return out;
} //Done



int main() {
    std::cout << "Hello, World!" << std::endl;
    TritSet set(8);
    TritSet other_set(16);
    TritSet empty_set;
    std::cout << "\n Size = "<< set.getSize()<<"\n Capasity = "<< set.getCapacity()<< std::endl;
    std::cout << "\n eSize = "<< empty_set.getSize()<<"\n eCapasity = "<< empty_set.getCapacity()<< std::endl;
    std::cout << "\n Length = "<< set.length()<<"\n empty_Length = "<< empty_set.length()<< std::endl;
    set.push(2,Trit::T);
    set.push(4,Trit::F);
    other_set.push(12,Trit::F);
    empty_set.push(2,Trit::T);
    empty_set.push(4,Trit::F);
    std::cout << "\n Length = "<< set.length()<<"\n empty_Length = "<< empty_set.length()<< std::endl;
    if(set==empty_set){
        std::cout << "\n set==empty_set "<< std::endl;
    }
    if(set!=other_set){
        std::cout << "\n set!=other_set "<< std::endl;
    }
    std::cout <<"\nset-\t\t" << set << std::endl;
    std::cout<<"\nother_set\t" << other_set<<std::endl;
    other_set=set;
    if(set==other_set){
        std::cout << "\n other_set=set "<< std::endl;
        std::cout <<"\nset-\t\t" << set << std::endl;
        std::cout<<"\nother_set\t" << other_set<<std::endl;
    }
    std::cout <<"\n!set\t\t" << !set << std::endl;
    other_set.push(1,Trit::F);
    TritSet big_set=set|other_set;
    std::cout<<"set\t\t" <<set<<std::endl;
    std::cout<<"other_set\t" <<other_set<<std::endl;
    std::cout<<"set|other_set\t" <<big_set<<std::endl;
    big_set=set&other_set;
    std::cout<<"set&other_set\t" <<big_set<<std::endl;





    return 0;
}
