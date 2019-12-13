#pragma once

#include <array>
#include <string>

namespace ip
{
    class address;
    class subnet;
    class network;

    class address
    {
    protected:
        std::array<uint8_t, 4> bytes_;

    public:
        address(const std::array<uint8_t, 4> &bytes)
            : bytes_{ bytes }
        {
        }

        address(uint8_t first, uint8_t second, uint8_t third, uint8_t fourth)
            : bytes_{ { first, second, third, fourth } }
        {
        }

        address(const address& base) 
            : bytes_{ base.bytes_ }
        {
        }

        address next() const;
        address next_net(const subnet &curnet) const;
        std::string to_string() const;
        address operator &(const address &rhs) const;
        bool operator ==(const address &rhs) const;
        bool operator !=(const address &rhs) const;
    };

    class subnet : public address
    {
    public:
        explicit subnet(uint8_t bits);
        uint8_t bits;
        bool operator <(const subnet &rhs) const;
        bool operator ==(const subnet &rhs) const;
    };

    class network : public address
    {
    private:
        ip::subnet subnet_;

    public:
        network(ip::address ip, ip::subnet subnet)
            : bytes_{ ip.bytes }
            , subnet_{ subnet }
        {
        }

        ip::subnet subnet() const {
            return subnet_;
        }
    }
}