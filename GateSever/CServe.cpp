#include "CServe.h"
#include"HttpConnect.h"
#include"AaioIoServerPool.h"
CServe::CServe(net::io_context& ioc, unsigned short port) :_acceptor(ioc,tcp::endpoint(tcp::v4(),port)),_ioc(ioc)
{

}

void CServe::Start() {
	auto self = shared_from_this();
	auto& IoServer =AaioIoServerPool::GetInstance()->GetIoServer();
	std::shared_ptr<HttpConnect> newcon = std::make_shared<HttpConnect>(IoServer);
	_acceptor.async_accept(newcon->GetSocket(), [self, newcon](boost::system::error_code ec) {
			try {
				if (ec) {
					self->Start();
					return;
				}
				newcon->Start();
				self->Start();
			}
			catch (std::exception & ec) {
				std::cout << "error is:" << ec.what() << std::endl;
				self->Start(); 
			}
	});

}