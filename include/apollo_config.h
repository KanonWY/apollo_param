#ifndef APOLLO_CPP_CLIENT_APOLLO_CONFIG_H
#define APOLLO_CPP_CLIENT_APOLLO_CONFIG_H

#include <string>
#include <vector>

namespace apollo_param
{

#define SET_METHOD_CHAIN(var)                                  \
    inline apolloConfig &Set##var##value(const std::string &v) \
    {                                                          \
        this->var = v;                                         \
        return *this;                                          \
    }

#define SET_METHOD_CHAIN_2(var)                                    \
    inline apolloOpenConfig &Set##var##value(const std::string &v) \
    {                                                              \
        this->var = v;                                             \
        return *this;                                              \
    }

struct apolloConfig
{
    std::string address_{"http://localhost:8080"};
    std::string appid_{"SampleApp"};
    std::string cluster_{"default"};
    std::string env_{"DEV"};
    std::vector<std::string> namespace_;
    bool is_backup_config_ = false;

    apolloConfig() = default;

    //method chain
    SET_METHOD_CHAIN(address_)

    SET_METHOD_CHAIN(appid_)

    SET_METHOD_CHAIN(cluster_)

    SET_METHOD_CHAIN(env_);

    inline apolloConfig &SetNamespace(const std::vector<std::string> &ns)
    {
        this->namespace_ = ns;
        return *this;
    }

    inline apolloConfig &ClearNamespace()
    {
        this->namespace_.clear();
        return *this;
    }

    inline apolloConfig &SetBackUp(bool flag)
    {
        this->is_backup_config_ = flag;
        return *this;
    }
};

struct apolloOpenConfig
{
    std::string address_{"http://localhost:8080"};
    std::string portal_address_{"http://localhost:8070"};
    std::string appid_{"SampleApp"};
    std::string cluster_{"default"};
    std::string env_{"DEV"};
    std::vector<std::string> namespace_;
    bool is_backup_config_ = false;
    std::string token_{};
    short port_{};
    std::string server_address_;

    apolloOpenConfig() = default;

    //method chain
    SET_METHOD_CHAIN_2(address_)

    SET_METHOD_CHAIN_2(portal_address_)

    SET_METHOD_CHAIN_2(server_address_)

    SET_METHOD_CHAIN_2(appid_)

    SET_METHOD_CHAIN_2(cluster_)

    SET_METHOD_CHAIN_2(token_)

    SET_METHOD_CHAIN_2(env_);

    inline apolloOpenConfig &SetNamespace(const std::vector<std::string> &ns)
    {
        this->namespace_ = ns;
        return *this;
    }

    inline apolloOpenConfig &ClearNamespace()
    {
        this->namespace_.clear();
        return *this;
    }

    inline apolloOpenConfig &SetBackUp(bool flag)
    {
        this->is_backup_config_ = flag;
        return *this;
    }

    inline apolloOpenConfig &SetPort(short v)
    {
        this->port_ = v;
        return *this;
    }
};
} // namespace apollo_param
#endif //APOLLO_CPP_CLIENT_APOLLO_CONFIG_H
