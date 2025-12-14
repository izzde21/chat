#pragma once
#include<iostream>
template<typename T>
class Singelton
{
protected:
    Singelton() = default;
    Singelton& operator=(Singelton<T>&) = delete;
    Singelton(Singelton<T>&) = delete;
    static std::shared_ptr<T> _instance;
public:
    static std::shared_ptr<T> GetInstance() {
        static std::once_flag _flag;
        std::call_once(_flag, [&]() {
            _instance = std::shared_ptr<T>(new T);
            });
        return _instance;
    }

    ~Singelton() {
       std::cout << "Singelton destruct" << std::endl;
    }

};
template<typename T>
std::shared_ptr<T> Singelton<T>::_instance = NULL;