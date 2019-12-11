#pragma once

#include <array>
#include <string>

namespace ip
{
    class address;
    class subnet;

    class address
    {
    protected:
        std::array<uint8_t, 4> bytes;

    public:
        address(const std::array<uint8_t, 4> &bytes) 
            : bytes{ bytes }
        {
        }

        address(uint8_t first, uint8_t second, uint8_t third, uint8_t fourth)
            : bytes{ { first, second, third, fourth } }
        {
        }

        address(const address& base) 
            : bytes{ base.bytes }
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
}