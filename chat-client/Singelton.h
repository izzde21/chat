#ifndef SINGELTON_H
#define SINGELTON_H
#include"global.h"
#include<mutex>
#include"QDebug"
template<typename T>
class Singelton
{
protected:
    Singelton()=default;
    Singelton &operator=(Singelton<T>&)=delete;
    Singelton(Singelton<T>&)=delete;
    static std::shared_ptr<T> _instance;
public:
    static std::shared_ptr<T> GetInstance(){
        static std::once_flag _flag;
        std::call_once(_flag,[&](){
            _instance=std::shared_ptr<T> (new T);
        });
        return _instance;
    }

    ~Singelton(){
        qDebug()<<"Singelton destruct"<<Qt::endl;
    }

};
template<typename T>
std::shared_ptr<T> Singelton<T>::_instance=NULL;
#endif // SINGELTON_H
