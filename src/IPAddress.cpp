#include "IPAddress.hpp"
#include <sstream>

std::string ip::address::to_string() const
{
    std::ostringstream oss;
    oss << int{this->bytes[0]} << '.' <<
           int{this->bytes[1]} << '.' <<
           int{this->bytes[2]} << '.' <<
           int{this->bytes[3]};
    return oss.str();
}

ip::address ip::address::operator&(const ip::address &rhs) const
{
    return ip::address(
        this->bytes[0] & rhs.bytes[0],
        this->bytes[1] & rhs.bytes[1],
        this->bytes[2] & rhs.bytes[2],
        this->bytes[3] & rhs.bytes[3]);
}

bool ip::address::operator==(const ip::address &rhs) const
{
    for (int i = 0; i < 4; i++)
        if (this->bytes[i] != rhs.bytes[i])
            return false;
    return true;
}

bool ip::address::operator!=(const ip::address &rhs) const
{
    return !(*this == rhs);
}

ip::address ip::address::next() const
{
    ip::address addr(this->bytes);

    int i = 3;
    while (i >= 0 && addr.bytes[i] == 255) {
        addr.bytes[i] = 0;
        i--;
    }

    if (i > 0) // 0.0.0.0 if overflow
        addr.bytes[i]++;
    
    return addr;
}

ip::address ip::address::next_net(const ip::subnet& sub) const
{
    ip::address addr(this->bytes);

    uint8_t hostbits = 32 - sub.bits;
    int i = 3;
    while (hostbits >= 8) {
        addr.bytes[i--] = 0;
        hostbits -= 8;
    }

    uint16_t byte = (uint16_t)(addr.bytes[i] & ~((1 << hostbits) - 1)) + (1 << hostbits);
    if (byte < 256)
    {
        addr.bytes[i] = (uint8_t)byte;
    }
    else
    {
        addr.bytes[i--] = 0;
        while (i >= 0 && addr.bytes[i] == 255) {
            addr.bytes[i] = 0;
            i--;
        }

        if (i < 0)
            return ip::address(0, 0, 0, 0); // Overflow
        
        addr.bytes[i]++;
    }
    return addr;
}

ip::subnet::subnet(uint8_t bits) 
    : address(0, 0, 0, 0)
    , bits{bits}
{
    int i = 0;
    while (bits >= 8) {
        this->bytes[i++] = 255;
        bits -= 8;
    }
    this->bytes[i] = ((1 << bits) - 1) << (8 - bits);
}

bool ip::subnet::operator<(const ip::subnet &rhs) const
{
    return this->bits < rhs.bits;
}

bool ip::subnet::operator==(const ip::subnet &rhs) const
{
    return this->bits == rhs.bits;
}