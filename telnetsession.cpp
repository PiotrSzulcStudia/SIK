#include "telnetsession.h"

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

TelnetSession::TelnetSession(boost::asio::io_service& io_service)
    : mSocket(io_service)
{
}

void TelnetSession::start()
{
    mSocket.async_read_some(boost::asio::buffer(data, max_length),
                            boost::bind(&TelnetSession::handle_read, this,
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred()));
}

void TelnetSession::handle_read(const boost::system::error_code& error, size_t bytes_transferred)
{
    if (!error)
    {
        std::cout << "TelnetSession::handle_read" << (int) bytes_transferred << "bytes\n";
        boost::asio::async_write(mSocket,
                                 boost::asio::buffer(data, bytes_transferred),
                                 boost::bind(&TelnetSession::handle_write, this, boost::asio::placeholders::error));
    }
    else
    {
        std::cout << "TelnetSession::handle_read error: " << error << std::endl;
        delete this;
    }
}

void TelnetSession::handle_write(const boost::system::error_code& error)
{
    if (!error)
    {
        std::cout << "TelnetSession::handle_write\n";
        mSocket.async_read_some(boost::asio::buffer(data, max_length),
                                boost::bind(&TelnetSession::handle_read, this,
                                            boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }
    else
    {
        std::cout << "TelnetSession::handle_write error: " << error << std::endl;
        delete this;
    }
}
