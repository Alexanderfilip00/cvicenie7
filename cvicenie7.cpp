#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <chrono>
#define RangeExceededException 1

class Timer { //meranie vypoctoveho casu pomocou STL <chrono>
public:
    static std::chrono::time_point<std::chrono::high_resolution_clock> t_start;
    static std::chrono::time_point<std::chrono::high_resolution_clock> t_end;
    static void start() { t_start = std::chrono::high_resolution_clock::now(); }
    static void end(std::string s) { t_end = std::chrono::high_resolution_clock::now(); print(s); }
    static void print(std::string s) {
        std::cout << std::fixed << std::setprecision(2) << s
            << std::chrono::duration<double, std::milli>(t_end - t_start).count()
            << " ms\n";
    }
};
std::chrono::time_point<std::chrono::high_resolution_clock> Timer::t_start = std::chrono::high_resolution_clock::now();
std::chrono::time_point<std::chrono::high_resolution_clock> Timer::t_end = std::chrono::high_resolution_clock::now();


template <class T>
class myVector {

private:
    T* data;
    int Length;
public:
    myVector() { Length = 0; data = nullptr; };
    myVector(int n, T def_value);
    ~myVector() { delete[] data; };
    void Print();

    void Resize(int n);
    T& At(int n);
    T& operator [](int n);
    void PushBack(T v);
    T& Begin() { return data[0]; };
    T& End() { return data[Length - 1]; };
    void Clear();
};

template<class T>
myVector<T>::myVector(int n, T def_value)
{
    int i;
    Length = n;
    data = new T[n];
    for (i = 0; i < n; i++) {
        data[i] = def_value;
    }
}

template<class T>
void myVector<T>::Print()
{
    int i;
    for (i = 0; i < Length; i++) {
        std::cout << data[i] << std::endl;
    }
    
}

template<class T>
void myVector<T>::Resize(int n)
{
    
    int i;                               
    T* temp_data = new T[Length];        //vytvorenie kopie povodneho pola vektorov
    

    for (i = 0; i < Length; i++) {
        temp_data[i] = data[i];
    }
    
    delete[] data;
    data = new T[n];         //vytvorenie noveho smernika pre pole vektorov

    if (n > Length) {
        for (i = 0; i < Length; i++) {       //prekopirovanie vektorov naspat do noveho pola
            data[i] = temp_data[i];
        }

        for (i = Length; i < n; i++) {       //doplnenie prazdnych hodnot, ak je to vacsie
            data[i] = NULL;
        }

    }
    else if (n <= Length) {
        for (i = 0; i < n; i++) {       //prekopirovanie vektorov naspat do noveho pola
            data[i] = temp_data[i];
        }
    }

    delete[] temp_data;      //poriadky
    Length = n;           
   
}

template<class T>
T& myVector<T>::At(int n)
{
        if (n >= Length || n < 0) {
            throw RangeExceededException;
        }
        return data[n];
    }

template<class T>
T& myVector<T>::operator[](int n)
{
    return data[n];
}

template<class T>
void myVector<T>::PushBack(T v)
{
    int i;                                  //vytvorenie kopie povodneho pola vektorov
    T* temp_data = new T[Length];

    for (i = 0; i < Length; i++) {
        temp_data[i] = data[i];
    }

    delete[] data;
    data = new T[Length+1];         //vytvorenie noveho smernika pre pole vektorov

    for (i = 0; i < Length; i++) {       //prekopirovanie vektorov naspat do noveho pola
        data[i] = temp_data[i];
    }
    data[Length] = v;

    Length = Length + 1;
    delete[] temp_data;
}

template<class T>
void myVector<T>::Clear()
{
    int i;
    for (i = 0; i < Length; i++) {
        data[i] = NULL;
    }
    delete[] data;
    data = nullptr;
}



int main()
{
    int m;
    std::cout << "Zadajte pocet prvkov (odporucam medzi 10 000-50 000):\n";
    std::cin >> m;
    
    int i, tmp=0;


    Timer::start();     //ZACIATOK----------------------
    myVector<int> Pole;
    Pole.Resize(2*m);

    for (i = 0; i < m; i++) {
        tmp += Pole[i] + ( Pole[i] * Pole[i] );
    }
    tmp = 0;
    try {
        for (i = 0; i < m; i++) {
            tmp += Pole.At(i) + (Pole.At(i) * Pole.At(i));
        }
    }
        
    catch (int error) {
       if (error == RangeExceededException) {
           std::cout << "\nPozadovany prvok je mimo rozsahu pola. \n";
        }
    }

    tmp = 0;
    for (i = 0; i < m/2; i++) {
        Pole.PushBack(i);
    }
       
    tmp = Pole.Begin() + Pole.End();
    Pole.Clear();

    Timer::end("Vseobecna funkcionalita mojich metod pre vektor trvala ");      //KONIEC---------------------------


   

    Timer::start();     //ZACIATOK-------------------

    std::vector<int> Pole2;
 
    Pole2.resize(2 * m);
    for (i = 0; i < m; i++) {
        tmp += Pole2[i] + (Pole2[i] * Pole2[i]);
    }
    tmp = 0;
    try {
        for (i = 0; i < m; i++) {
            tmp += Pole2.at(i) + (Pole2.at(i) * Pole2.at(i));
        }
    }

    catch (int error) {
        if (error == RangeExceededException) {
            std::cout << "\nPozadovany prvok je mimo rozsahu pola. \n";
        }
    }

    tmp = 0;
    for (i = 0; i < m / 2; i++) {
        Pole2.push_back(i);
    }

    tmp = *Pole2.begin() + *Pole2.rbegin();
    Pole2.clear();


    Timer::end("Vseobecna funkcionalita vstavanych metod pre vektor trvala ");

    return 0;
}