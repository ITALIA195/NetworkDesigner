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
    designer::network lastnet = this->lastNetwork();

    ip::subnet netsub = std::min(sub, lastnet.subnet);
    ip::address ip = lastnet.ip.next_net(netsub);

    this->networks_.push_back({ ip, sub });
}

void designer::sorted::add(uint32_t hosts)
{
    ip::subnet sub = subnetFromHosts(hosts);
    this->subnets_.emplace(sub);
}

std::vector<designer::network> designer::sorted::createNetworks() const
{
    std::vector<designer::network> nets;
    designer::network lastNet = this->base_;
    for (auto it = this->subnets_.begin(); it != this->subnets_.end(); it++)
    {
        ip::subnet sub = *it;
        
        ip::address ip = lastNet.ip.next_net(sub); //TODO: Broken
        nets.push_back(lastNet = designer::network{ ip, sub });
    }

    return nets;
}
