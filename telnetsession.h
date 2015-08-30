#ifndef TELNETSESSION_H
#define TELNETSESSION_H

#include <boost/asio.hpp>

class TelnetSession
{
public:
    TelnetSession(boost::asio::io_service& io_service);
    boost::asio::ip::tcp::socket& socket() { return mSocket; }
    void start();
    enum { max_length = 10 };

private:
    void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
    void handle_write(const boost::system::error_code& error);
    boost::asio::ip::tcp::socket mSocket;
    char data[max_length];
};

#endif // TELNETSESSION_H
