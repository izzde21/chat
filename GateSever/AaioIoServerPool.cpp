#include "AaioIoServerPool.h"
AaioIoServerPool::AaioIoServerPool(std::size_t size) :_IoServer(size), _Work(size), NextIoServer(0) {
    for (int i = 0; i < size; ++i) {
        _Work[i] = std::make_unique<Work>(_IoServer[i].get_executor());
    }

    for (std::size_t i = 0; i < _IoServer.size(); ++i) {
        _threads.emplace_back([this, i]() {
            _IoServer[i].run();
            });
    }
}

   void AaioIoServerPool::stop(){
        for (auto& work : _Work) {
            //把服务先停止
            work.reset();
        }

        for (auto& t : _threads) {
            t.join();
        }
    }

   net::io_context& AaioIoServerPool::GetIoServer() {
       auto& ioserver=_IoServer[NextIoServer++];
       if (NextIoServer == _IoServer.size()) {
           NextIoServer = 0;
       }
       return ioserver;
   }


   AaioIoServerPool::~AaioIoServerPool() {
       stop();
   }

