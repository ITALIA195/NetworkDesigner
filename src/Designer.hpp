#pragma once

#include "IPAddress.hpp"
#include <vector>
#include <map>
#include <set>
#include <cmath>

namespace designer
{
    ip::subnet subnetFromHosts(uint32_t hosts);

    class linear
    {
    private:
        std::vector<ip::network> networks_;
        ip::network base_;

    public:
        linear(ip::address net, ip::subnet sub)
            : base_{ net, sub }
            , networks_{}
        {
            
        }

        linear(ip::network net)
            : base_{ net }
            , networks_{}
        {
            
        }

        void add(uint32_t hosts);

        ip::network lastNetwork() const {
            if (this->networks_.size() != 0)
                return this->networks_.back();
            return this->base_;
        }

        std::vector<ip::network> networks() const {
            return this->networks_;
        }
    };

    class sorted
    {
    private:
        std::multiset<ip::subnet> subnets_;
        ip::network base_;

    public:
        sorted(ip::address net, ip::subnet sub)
            : base_{ net, sub }
            , subnets_{}
        {
            
        }

        sorted(ip::network net)
            : base_{ net }
            , subnets_{}
        {
            
        }

        void add(uint32_t hosts);
        std::vector<ip::network> createNetworks() const;
    };
}
