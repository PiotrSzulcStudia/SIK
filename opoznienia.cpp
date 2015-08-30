#include "telnetserver.h"

#include <iostream>
#include <boost/asio.hpp>
#include <boost/program_options.hpp>

int main(int argc, char* argv[])
{
    boost::program_options::variables_map variables_map;
    boost::asio::io_service io_service;

    try
    {
        boost::program_options::options_description description;
        description.add_options()
                ("port,p", boost::program_options::value<uint16_t>()->default_value(21), "TCP port for Telnet server")
                ("help", "display help message and exit")
        ;

        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, description), variables_map);
        boost::program_options::notify(variables_map);

        if (variables_map.count("help"))
        {
            std::cout << "Usage: " << argv[0] << " [options]" << std::endl;
            std::cout << description;
            return 0;
        }
    }
    catch (std::exception& e)
    {
            std::cerr << "Error: " << e.what() << std::endl;
    }

    try
    {
        TelnetServer ts(io_service, variables_map["port"].as<uint16_t>());
        std::cout << "Before io_service.run()\n";
        io_service.run();
        std::cout << "After io_service.run()\n";
    }
    catch (std::exception& e)
    {
        std::cerr << "TELNET SERVER ERROR: " << e.what() << std::endl;
    }

    return 0;
}

