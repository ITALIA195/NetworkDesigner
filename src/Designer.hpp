#pragma once

#include "IPAddress.hpp"
#include <vector>
#include <map>
#include <set>
#include <cmath>

namespace designer
{
    typedef struct {
        ip::address ip;
        ip::subnet subnet;
    } network;

    ip::subnet subnetFromHosts(uint32_t hosts);

    class linear
    {
    private:
        std::vector<network> networks_;
        network base_;

    public:
        linear(ip::address net, ip::subnet sub)
            : base_{ net, sub }
            , networks_{}
        {
            
        }

        linear(network net)
            : base_{ net }
            , networks_{}
        {
            
        }

        void add(uint32_t hosts);

        network lastNetwork() const {
            if (this->networks_.size() != 0)
                return this->networks_.back();
            return this->base_;
        }

        std::vector<network> networks() const {
            return this->networks_;
        }
    };

    class sorted
    {
    private:
        std::multiset<ip::subnet> subnets_;
        network base_;

    public:
        sorted(ip::address net, ip::subnet sub)
            : base_{ net, sub }
            , subnets_{}
        {
            
        }

        sorted(network net)
            : base_{ net }
            , subnets_{}
        {
            
        }

        void add(uint32_t hosts);
        std::vector<network> createNetworks() const;
    };
}
