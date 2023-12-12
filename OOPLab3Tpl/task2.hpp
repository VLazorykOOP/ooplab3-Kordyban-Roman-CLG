//2.10 completed
#include <iostream>
using namespace std;
class RepeatedRangeSet
{
private:
    unsigned int *set;
    unsigned int beg;
    unsigned int end;
    int state;
public:
    RepeatedRangeSet(): beg(0),end(100),state(0)
    {
        set=new unsigned int[getSize()]();
        if(!set) { state=1; }
    }
    RepeatedRangeSet(unsigned int end): beg(0),end(end),state(0)
    {
        set=new unsigned int[getSize()]();
        if(!set) { state=1; }
    }
    RepeatedRangeSet(unsigned int beg,unsigned int end): beg(beg),end(end),state(0)
    {
        if(beg>=end) { state=3; }
        else
        {
            set=new unsigned int[getSize()]();
            if(!set) { state=1; }
        }
    }
    RepeatedRangeSet(unsigned int beg,unsigned int end,unsigned int value): beg(beg),end(end),state(0)
    {
        if(beg>=end) { state=3; }
        else
        {
            set=new unsigned int[getSize()];
            if(!set) { state=1; }
            else { for(unsigned int i=0; i<getSize(); ++i) { set[i]=value; } }
        }
    }
    RepeatedRangeSet(const RepeatedRangeSet &other): beg(other.beg),end(other.end),state(other.state)
    {
        set=new unsigned int[getSize()];
        if(!set) { state=1; }
        else { for(unsigned int i=0; i<getSize(); ++i) { set[i]=other.set[i]; } }
    }
    ~RepeatedRangeSet() { delete[] set; }
    RepeatedRangeSet &operator=(const RepeatedRangeSet &other)
    {
        if(this!=&other)
        {
            delete[] set;
            beg=other.beg;
            end=other.end;
            state=other.state;
            set=new unsigned int[getSize()];
            if(!set) { state=1; }
            else { for(unsigned int i=0; i<getSize(); ++i) { set[i]=other.set[i]; } }
        }
        return *this;
    }
    void setValue(unsigned int index,unsigned int value=0)
    {
        if(index>=beg&&index<end) { set[index-beg]=value; }
        else { state=2; }
    }
    unsigned int getRepetitionCount(unsigned int index)
    {
        if(index>=beg&&index<end) { return set[index-beg]; }
        else { state=2; return 0; }
    }
    void printSet() const
    {
        for(unsigned int i=0; i<getSize(); ++i) { cout<<set[i]<<" "; }
        cout<<endl;
    }
    RepeatedRangeSet setUnion(RepeatedRangeSet &other)
    {
        unsigned int newBeg=min(beg,other.beg);
        unsigned int newEnd=max(end,other.end);
        RepeatedRangeSet result(newBeg,newEnd);
        for(unsigned int i=newBeg; i<newEnd; ++i) { result.setValue(i,max(getRepetitionCount(i),other.getRepetitionCount(i))); }
        return result;
    }
    RepeatedRangeSet setIntersection(RepeatedRangeSet &other)
    {
        unsigned int newBeg=max(beg,other.beg);
        unsigned int newEnd=min(end,other.end);
        RepeatedRangeSet result(newBeg,newEnd);
        for(unsigned int i=newBeg; i<newEnd; ++i) { result.setValue(i,min(getRepetitionCount(i),other.getRepetitionCount(i))); }
        return result;
    }
    RepeatedRangeSet setDifference(RepeatedRangeSet &other)
    {
        unsigned int newBeg=min(beg,other.beg);
        unsigned int newEnd=max(end,other.end);
        RepeatedRangeSet result(newBeg,newEnd);
        for(unsigned int i=newBeg; i<newEnd; ++i) { result.setValue(i,getRepetitionCount(i)-other.getRepetitionCount(i)); }
        return result;
    }
    bool operator==(const RepeatedRangeSet &other) const
    {
        if(beg==other.beg&&end==other.end)
        {
            for(unsigned int i=0; i<getSize(); ++i) { if(set[i]!=other.set[i]) { return false; } }
            return true;
        }
        else { return false; }
    }
    bool operator!=(const RepeatedRangeSet &other) const { return !(*this==other); }
    bool operator<(const RepeatedRangeSet &other) const
    {
        if(getSize()<other.getSize()) { return true; }
        return false;
    }
    bool operator>(const RepeatedRangeSet &other) const
    {
        if(getSize()>other.getSize()) { return true; }
        return false;
    }
    bool operator<=(const RepeatedRangeSet &other) const { return !(*this>other); }
    bool operator>=(const RepeatedRangeSet &other) const { return !(*this<other); }
    int getState() const { return state; }
    unsigned int getSize() const { return end-beg; }
};

int task2()
{
    RepeatedRangeSet set1;
    RepeatedRangeSet set2(50);
    RepeatedRangeSet set3(30,80,4);
    RepeatedRangeSet set4(10,90,2);

    cout<<"set1:\t\t";
    set1.printSet();

    cout<<"set2:\t\t";
    set2.printSet();

    cout<<"set3:\t\t";
    set3.printSet();

    cout<<"set4:\t\t";
    set4.printSet();

    RepeatedRangeSet unionSet=set2.setUnion(set3);
    cout<<"set2+set3:\t";
    unionSet.printSet();

    RepeatedRangeSet intersectionSet=set3.setIntersection(set4);
    cout<<"set3==set4:\t";
    intersectionSet.printSet();

    RepeatedRangeSet differenceSet=set3.setDifference(set2);
    cout<<"set3!=set4:\t";
    differenceSet.printSet();

    if(set1==set2) { cout<<"set1==set2\n"; }
    else { cout<<"set1!=set2\n"; }
    if(set3>set4) { cout<<"set3>set4\n"; }
    else { cout<<"set3<=set4\n"; }
    cout<<"set1.getState(): "<<set1.getState()<<endl;
    return 0;
}

/*
Створити тип даних - клас множина з повторенням діапазону цілих чисел.
У класі визначити вказівник на unsigned int(для збереження множини), числа beg (початок) та end(кінець) діапазону типу unsigned int (beg<end) і змінну стану.
У множині створюється масив розміром size = getSize(), який кількість повторень елемента множини.

У класі визначити:
o конструктор без параметрів(виділяє місце для множини чисел beg=0 до end=100 та ініціалізує його в нуль);
o конструктор з одним параметром - end (beg=0, виділяє місце та інінціалізує масив значенням нуль);
o конструктор із двома параметрами beg та end (виділяє місце та інінціалізує масив значенням нуль);
o конструктор із трьома параметрами beg, end та value(виділяє місце та інінціалізує масив значенням value);
o конструктор копій та операцію присвоєння; // !!!
o деструктор звільняє пам'ять;
o визначити функцію, яка присвоює елементу множини деяке значення value (параметр за замовчуванням);
o функцію яка одержує кількість повторення елементу множини;
o визначити функції друку, об’єднання, перетину та різниці, які здійснюють ці арифметичні операції з даними цього класу;
o визначити функції порівняння: більше, менше, нерівно або рівно, які повертають true або false.

У змінну стани встановлювати код помилки, коли не вистачає пам'яті, виходить за межі множини, ініціалізація числом, яке є за межами діапазону множини.
Передбачити можливість підрахунку числа об'єктів даного типу. Написати програму тестування всіх можливостей цього класу.
*/