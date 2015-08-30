#ifndef TELNETSERVER_H
#define TELNETSERVER_H

#include "telnetsession.h"
#include <stdint.h>
#include <boost/asio.hpp>

class TelnetServer
{
public:
    TelnetServer(boost::asio::io_service& io_service, uint16_t port);

private:
    void start_accept();
    void handle_accept(TelnetSession* new_session, const boost::system::error_code& error);
    boost::asio::io_service& io_service;
    boost::asio::ip::tcp::acceptor acceptor;
};

#endif // TELNETSERVER_H
