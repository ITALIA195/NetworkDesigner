#include "Designer.hpp"
#include <iostream>

ip::subnet designer::subnetFromHosts(uint32_t hosts)
{
    auto hostbits = (int)ceil(log2(hosts + 2));
    return ip::subnet(32 - hostbits);
}

void designer::linear::add(uint32_t hosts)
{
    ip::subnet sub = subnetFromHosts(hosts);
    ip::network lastnet = this->lastNetwork();

    ip::subnet netsub = std::min(sub, lastnet.subnet());
    ip::address ip = lastnet.next_net(netsub);

    this->networks_.push_back({ ip, sub });
}

void designer::sorted::add(uint32_t hosts)
{
    ip::subnet sub = subnetFromHosts(hosts);
    this->subnets_.emplace(sub);
}

std::vector<ip::network> designer::sorted::createNetworks() const
{
    std::vector<ip::network> nets;
    ip::network lastNet = this->base_;
    for (auto it = this->subnets_.begin(); it != this->subnets_.end(); it++)
    {
        ip::subnet sub = *it;
        
        ip::address ip = lastNet.next_net(sub);
        nets.push_back(lastNet = ip::network{ ip, sub });
    }

    return nets;
}
