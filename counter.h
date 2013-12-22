#ifndef COUNTER_H
#define COUNTER_H

#include <atomic>
#include <array>


namespace utl
{
template<int dim>
class Counter
{
    typedef std::array<int, dim - 1> Borders;
public:
    typedef std::array<int, dim> array;

    Counter(const Borders& b) : counter(0), borders(b) {}
    Counter() : counter(0) { borders[0] = INT_MAX; }

    void changeBorder(const Borders& b) { borders = b;}

    array operator ++(int);
    operator array() const;


private:
    inline array longToArray(long);
    std::atomic_int_fast64_t counter;
    Borders borders;
};

template<int dim>
typename Counter<dim>::array Counter<dim>::operator ++(int){
    return longToArray(counter++);
}

template<int dim>
Counter<dim>::operator array() const{
    return longToArray(counter);
}


template<int dim>
typename Counter<dim>::array Counter<dim>::longToArray(long c)
{
    std::array<int, dim> cs;
    for (int i = 0 ; i < dim - 1; i++){
        cs[i] = c % borders[i];
        c /= borders[i];
    }
    return cs;
}

template<>
Counter<2>::operator array() const{
    long c = counter;
    return {c % borders[0], c / borders[0]};
}

template<>
typename Counter<2>::array Counter<2>::operator++(int){
    long c = counter++;
    return {c % borders[0], c / borders[0]};
}

}
#endif // COUNTER_H
