#include "../include/apollo_url.h"

namespace apollo_param
{
// URL : http://{portal_address}/openapi/v1/envs/{env}/apps/{appId}/clusters/{clusterName}/namespaces
std::string getAllNamespaceInfoUrl(const std::string &portal_address,
                                   const std::string &env,
                                   const std::string &appId,
                                   const std::string &clusterName)
{
    std::ostringstream ss;
    ss << portal_address << "/openapi/v1/envs/" << env << "/apps/" << appId
       << "/clusters/" << clusterName << "/namespaces";
    SPDLOG_INFO("getAllNamespaceInfoUrl = {}", ss.str());
    return ss.str();
}

// URL ： http://{portal_address}/openapi/v1/apps/{appId}/appnamespaces
std::string getCreateNewNamespaceUrl(const std::string &portal_address,
                                     const std::string &appid)
{
    std::ostringstream ss;
    ss << portal_address << "/openapi/v1/apps/" << appid
       << "/appnamespaces";
    SPDLOG_INFO("getCreateNewNamespaceUrl = {}", ss.str());
    return ss.str();
}

//URL ： http://{portal_address}/openapi/v1/envs/{env}/apps/{appId}/clusters/{clusterName}/namespaces/{namespaceName}
std::string getOneNamespaceInfoUrl(const std::string &portal_address,
                                   const std::string &env,
                                   const std::string &appId,
                                   const std::string &clusterName,
                                   const std::string &ns)
{
    std::ostringstream ss;
    ss << portal_address << "/openapi/v1/envs/" << env << "/apps/" << appId
       << "/clusters/" << clusterName << "/namespaces/" << ns;
    SPDLOG_INFO("getOneNamespaceInfoUrl = {}", ss.str());
    //TODO: 在request中添加和在url中添加会有差异吗？
    return ss.str();
}

//http://{portal_address}/openapi/v1/envs/{env}/apps/{appId}/clusters/{clusterName}/namespaces/{namespaceName}/items
std::string addConfigUrl(const std::string &portal_address,
                         const std::string &env,
                         const std::string &appId,
                         const std::string &clusterName,
                         const std::string &ns)
{
    std::ostringstream ss;
    ss << portal_address << "/openapi/v1/envs/" << env << "/apps/" << appId
       << "/clusters/" << clusterName << "/namespaces/" << ns << "/items";
    SPDLOG_INFO("addConfigUrl = {}", ss.str());
    return ss.str();
}

//URL ： http://{portal_address}/openapi/v1/envs/{env}/apps/{appId}/clusters/{clusterName}/namespaces/{namespaceName}/items/{key}?operator={operator}
// 注意：这里的key应该拼接到url中，不能添加到请求参数中
std::string deleteConfigUrl(const std::string &portal_address,
                            const std::string &env,
                            const std::string &appId,
                            const std::string &clusterName,
                            const std::string &ns,
                            const std::string &key)
{
    std::ostringstream ss;
    ss << portal_address << "/openapi/v1/envs/" << env << "/apps/" << appId
       << "/clusters/" << clusterName << "/namespaces/" << ns << "/items/" << key;
    SPDLOG_INFO("deleteConfigUrl = {}", ss.str());
    return ss.str();
}

//URL ： http://{portal_address}/openapi/v1/envs/{env}/apps/{appId}/clusters/{clusterName}/namespaces/{namespaceName}/items/{key}
std::string modifyConfigUrl(const std::string &portal_address,
                            const std::string &env,
                            const std::string &appId,
                            const std::string &clusterName,
                            const std::string &ns,
                            const std::string &key)
{
    std::ostringstream ss;
    ss << portal_address << "/openapi/v1/envs/" << env << "/apps/" << appId
       << "/clusters/" << clusterName << "/namespaces/" << ns << "/items/" << key;
    SPDLOG_INFO("modifyConfigUrl = {}", ss.str());
    return ss.str();
}

//URL ： http://{portal_address}/openapi/v1/envs/{env}/apps/{appId}/clusters/{clusterName}/namespaces/{namespaceName}/releases
std::string publishConfigUrl(const std::string &portal_address,
                             const std::string &env,
                             const std::string &appId,
                             const std::string &clusterName,
                             const std::string &ns)
{
    std::ostringstream ss;
    ss << portal_address << "/openapi/v1/envs/" << env << "/apps/" << appId
       << "/clusters/" << clusterName << "/namespaces/" << ns << "/releases";
    SPDLOG_INFO("publishConfigUrl = {}", ss.str());
    return ss.str();
}

}; // namespace apollo_param