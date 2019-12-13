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
        network(const ip::address ip, const ip::subnet subnet)
            : address{ ip }
            , subnet_{ subnet }
        {
        }

        network(const std::array<uint8_t, 4> &bytes, const ip::subnet subnet)
            : address{ bytes }
            , subnet_{ subnet }
        {
        }

        static ip::network from_address(const ip::address addr, const ip::subnet subnet);
        ip::network next_net(const subnet &curnet) const;

        ip::subnet subnet() const {
            return subnet_;
        }
    };
}