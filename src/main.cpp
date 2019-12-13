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

    std::cout << baseNet.to_string() << ' ' << std::to_string(baseSub.bits) << std::endl;
    auto networks = designer.createNetworks();
    for (size_t i = 0; i < networks.size(); i++)
    {
        std::cout << networks[i].to_string() << '\t' << std::to_string(networks[i].subnet().bits) << std::endl;
    }
    return 0;
}
