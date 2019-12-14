#include "IPAddress.hpp"
#include <sstream>
#include <cassert>
#include <iostream>

std::string ip::address::to_string() const
{
    std::ostringstream oss;
    oss << int{this->bytes_[0]} << '.' <<
           int{this->bytes_[1]} << '.' <<
           int{this->bytes_[2]} << '.' <<
           int{this->bytes_[3]};
    return oss.str();
}

ip::address ip::address::operator&(const ip::address &rhs) const
{
    return ip::address(
        this->bytes_[0] & rhs.bytes_[0],
        this->bytes_[1] & rhs.bytes_[1],
        this->bytes_[2] & rhs.bytes_[2],
        this->bytes_[3] & rhs.bytes_[3]);
}

bool ip::address::operator==(const ip::address &rhs) const
{
    for (int i = 0; i < 4; i++)
        if (this->bytes_[i] != rhs.bytes_[i])
            return false;
    return true;
}

bool ip::address::operator!=(const ip::address &rhs) const
{
    return !(*this == rhs);
}

ip::address ip::address::next() const
{
    ip::address addr(this->bytes_);

    int i = 3;
    while (i >= 0 && addr.bytes_[i] == 255) {
        addr.bytes_[i] = 0;
        i--;
    }

    if (i > 0) // 0.0.0.0 if overflow
        addr.bytes_[i]++;
    
    return addr;
}

ip::network ip::network::from_address(const ip::address addr, const ip::subnet subnet)
{
    ip::address network_ip = addr & subnet;
    return ip::network{ network_ip, subnet };
}

ip::network ip::network::next_net(const ip::subnet& subnet) const
{
    assert(subnet.bits > 0);

    ip::address ip = static_cast<ip::address>(*this);
    ip::network net = network::from_address(ip, subnet);

    int index = (subnet.bits - 1) / 8;

    uint16_t byte = (uint16_t)net.bytes_[index] + (1U << ((32 - subnet.bits) % 8));
    if (byte < 256)
    {
        net.bytes_[index] = (uint8_t)byte;
    }
    else
    {
        for (--index; index >= 0; index--)
        {
            if (net.bytes_[index] != 255)
            {
                net.bytes_[index]++;
                break;
            }
            net.bytes_[index] = 0;
        }
        assert(index >= 0 && "Overflow");
    }

    return net;
}

ip::subnet::subnet(uint8_t bits) 
    : address(0, 0, 0, 0)
    , bits{bits}
{
    int i = 0;
    for (; bits >= 8; bits -= 8)
        this->bytes_[i++] = 255;
    this->bytes_[i] = 0xFF << (8 - bits);
}

bool ip::subnet::operator<(const ip::subnet &rhs) const
{
    return this->bits < rhs.bits;
}

bool ip::subnet::operator==(const ip::subnet &rhs) const
{
    return this->bits == rhs.bits;
}