#include "IPAddress.hpp"
#include "Designer.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    ip::address baseNet(172, 16, 0, 0);
    ip::subnet baseSub(16);

    designer::sorted designer(baseNet, baseSub);

    designer.add(16777200);
    designer.add(24);
    designer.add(24);
    designer.add(128);

    auto networks = designer.networks();
    for (size_t i = 0; i < networks.size(); i++)
    {
        std::cout << networks[i].ip.to_string() << '\t' << networks[i].subnet.to_string() << std::endl;
    }
    return 0;
}
