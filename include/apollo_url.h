#ifndef APOLLO_CPP_CLIENT_APOLLO_URL_H
#define APOLLO_CPP_CLIENT_APOLLO_URL_H

#include <string>
#include <sstream>
#include "spdlog/spdlog.h"
#include "cpprest/http_client.h"

#define URL_LIMIT 256

namespace apollo_param
{
inline static std::string getBaseConfigUrl(const std::string &config_server_url,
                                           const std::string &appid,
                                           const std::string &cluster_name,
                                           const std::string &namespace_name)
{
    std::ostringstream ss;
    ss << config_server_url
       << "/configs/"
       << appid << "/" << cluster_name << "/" << namespace_name;
    SPDLOG_INFO("url = {}", ss.str());
    return ss.str();
}

inline static web::http::http_headers getTokenHeader(const std::string &token)
{
    web::http::http_headers headers;
    headers.add(U("Authorization"), U(token.c_str()));
    headers.add(U("Content-Type"), U("application/json;charset=UTF-8"));
    return headers;
}

//sprintf(url, "%s/notifications/v2", env_.address_.c_str());
inline std::string getNotifyUrl(const std::string &config_server_url)
{
    return {config_server_url + (std::string("/notifications/v2"))};
}

////////////////////////////////////openapi//////////////////////

/**
 * @brief 获取集群下所有Namespace信息接口的URL
 *          URL : http://{portal_address}/openapi/v1/envs/{env}/apps/{appId}/clusters/{clusterName}/namespaces
 *          Method: GET
 * @param portal_address
 * @param env
 * @param appId
 * @param clusterName
 * @return
 */
std::string getAllNamespaceInfoUrl(const std::string &portal_address,
                                   const std::string &env,
                                   const std::string &appId,
                                   const std::string &clusterName);

/**
 * @brief 创建Namespace的URL
 *          URL ： http://{portal_address}/openapi/v1/apps/{appId}/appnamespaces
 *          Method ： POST
 * @param portal_address
 * @param appid
 * @return
 */
std::string getCreateNewNamespaceUrl(const std::string &portal_address,
                                     const std::string &appid);

/**
 * @brief 获取某个Namespace信息接口的URL
 *      URL ： http://{portal_address}/openapi/v1/envs/{env}/apps/{appId}/clusters/{clusterName}/namespaces/{namespaceName}
 *      Method ： GET
 * @param portal_address
 * @param env
 * @param appId
 * @param clusterName
 * @param ns
 * @return
 */
std::string getOneNamespaceInfoUrl(const std::string &portal_address,
                                   const std::string &env,
                                   const std::string &appId,
                                   const std::string &clusterName,
                                   const std::string &ns);

/**
 * @brief 新增配置的URL
 *        URL ： http://{portal_address}/openapi/v1/envs/{env}/apps/{appId}/clusters/{clusterName}/namespaces/{namespaceName}/items
 *        Method ： POST
 * @param portal_address
 * @param env
 * @param appId
 * @param clusterName
 * @param ns
 * @return
 */
std::string addConfigUrl(const std::string &portal_address,
                         const std::string &env,
                         const std::string &appId,
                         const std::string &clusterName,
                         const std::string &ns);

/**
 * @brief 删除配置的URL
 *          URL ： http://{portal_address}/openapi/v1/envs/{env}/apps/{appId}/clusters/{clusterName}/namespaces/{namespaceName}/items/{key}?operator={operator}
 *          Method ： DELETE
 * @param portal_address
 * @param env
 * @param appId
 * @param clusterName
 * @param ns
 * @return
 */
std::string deleteConfigUrl(const std::string &portal_address,
                            const std::string &env,
                            const std::string &appId,
                            const std::string &clusterName,
                            const std::string &ns);

/**
 * @brief 修改配置的URL
 *      URL ： http://{portal_address}/openapi/v1/envs/{env}/apps/{appId}/clusters/{clusterName}/namespaces/{namespaceName}/items/{key}
 *      Method ： PUT
 * @param portal_address
 * @param env
 * @param appId
 * @param clusterName
 * @param ns
 * @return
 */
std::string modifyConfigUrl(const std::string &portal_address,
                            const std::string &env,
                            const std::string &appId,
                            const std::string &clusterName,
                            const std::string &ns,
                            const std::string &key);

/**
 * @brief 发布配置的URL
 *          URL ： http://{portal_address}/openapi/v1/envs/{env}/apps/{appId}/clusters/{clusterName}/namespaces/{namespaceName}/releases
 *          Method ： POST
 * @param portal_address
 * @param env
 * @param appId
 * @param clusterName
 * @param ns
 * @return
 */
std::string publishConfigUrl(const std::string &portal_address,
                             const std::string &env,
                             const std::string &appId,
                             const std::string &clusterName,
                             const std::string &ns);

} // namespace apollo_param

#endif //APOLLO_CPP_CLIENT_APOLLO_URL_H
