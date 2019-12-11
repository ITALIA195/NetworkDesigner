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

size_t designer::sorted::insertIndex(designer::network net)
{
    int left = 0;
    int right = (int)this->networks_.size() - 1;
    while (left <= right)
    {
        size_t median = (size_t)left + (((size_t)right - (size_t)left) >> 1);
        auto current = this->networks_[median];
        if (current.subnet.bits == net.subnet.bits)
            return median;
        else if (current.subnet.bits < net.subnet.bits)
            left = median + 1;
        else
            right = median - 1;
    }

    return left;
}

void designer::sorted::add(uint32_t hosts)
{
    ip::subnet sub = subnetFromHosts(hosts);
    designer::network lastnet = this->lastNetwork();

    ip::subnet netsub = std::min(sub, lastnet.subnet);
    ip::address ip = lastnet.ip.next_net(netsub);

    designer::network network{ip, sub};

    auto index = this->insertIndex(network);
    this->networks_.insert(this->networks_.begin() + index, network);
}
