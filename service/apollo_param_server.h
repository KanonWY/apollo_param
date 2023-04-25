#ifndef APOLLO_CPP_CLIENT_APOLLO_PARAM_SERVER_H
#define APOLLO_CPP_CLIENT_APOLLO_PARAM_SERVER_H

#include "../include/apollo_openapi_client.h"

namespace apollo_param
{
template <typename BACK_SERVER, typename CLIENT_TYPE>
class Base_Server
{
};

template <typename BACK_SERVER>
class Base_Server<BACK_SERVER, PropertiesPolicyClient>
{
public:
    bool init(const apolloOpenConfig &config)
    {
        m_config = config;
        m_client.init(config);
        return static_cast<BACK_SERVER *>(this)->initImp(m_config.port_, m_config.server_address_);
    }

    std::optional<std::string> getStringConfig(const std::string &appid, const std::string &ns, const std::string &key, const std::string &struct_name)
    {
        return m_client.getStringConfig_(ns, key, struct_name);
    }

    bool setConfig(const std::string &appid, const std::string &ns, const std::string &key, const std::string &value, const std::string &struct_name)
    {
        return m_client.setStringConfig_(ns, key, value, struct_name);
    }

    virtual ~Base_Server() = default;

private:
    apolloOpenConfig m_config;
    // TODO: 可能存在一个Service管理多个appid
    PropertiesPolicyClient m_client;
};

template <typename BACK_SERVER>
using PropertiesPolicyServer = Base_Server<BACK_SERVER, PropertiesPolicyClient>;

} // namespace apollo_param

#endif //APOLLO_CPP_CLIENT_APOLLO_PARAM_SERVER_H