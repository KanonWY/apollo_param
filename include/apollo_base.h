#ifndef APOLLO_CPP_CLIENT_APOLLO_BASE_H
#define APOLLO_CPP_CLIENT_APOLLO_BASE_H

#include <vector>
#include <map>
#include <string>
#include "apollo_yaml_tmp.h"

namespace apollo_param
{

class apolloOpenConfig;

class apollo_base_api
{
public:
    std::map<std::string, std::string> getAllPropertiesConfig_(const std::string &config_server_url,
                                                               const std::string &appid,
                                                               const std::string &ns,
                                                               const std::string &cluster);

    std::string getPropertiesConfigByKey_(const std::string &config_server_url,
                                          const std::string &appid,
                                          const std::string &ns,
                                          const std::string &cluster,
                                          const std::string &key);

    std::string getNoPropertiesConfig(const std::string &config_server_url,
                                      const std::string &appid,
                                      const std::string &ns,
                                      const std::string &cluster);
};

struct open_api_param
{
    std::string portal_address{"http://localhost:8070"};
    std::string env{"DEV"};
    std::string appid{};
    std::string cluster{"default"};
    std::string token;
    std::string ns;
};

class apollo_open_base_api
{
public:
    /**
     * @brief 获取所有信息appid下所有的命名空间信息
     * @param portal_address
     * @param env
     * @param appid
     * @param cluster
     * @param token
     * @return
     */
    static std::vector<NamespaceInfo> getAllNamespaceInfo(const std::string &portal_address,
                                                          const std::string &env,
                                                          const std::string &appid,
                                                          const std::string &cluster,
                                                          const std::string &token);

    static std::vector<NamespaceInfo> getAllNamespaceInfo(const open_api_param &param);

    /**
     * @brief 创建一个新的命名空间
     * @param portal_address
     * @param appid
     * @param ns
     * @param format
     * @param isPublic
     * @param dataChangeCreatedBy
     * @param comment
     * @return
     */
    static bool createNewNamespace(const std::string &portal_address,
                                   const std::string &appid,
                                   const std::string &token,
                                   const std::string &ns,
                                   const std::string &format,
                                   bool isPublic,
                                   const std::string &dataChangeCreatedBy,
                                   const std::string &comment);

    /**
     * @brief 获取一个命名空间的所有信息
     * @param param
     * @return
     */
    static NamespaceInfo getOneNamespaceInfo(const open_api_param &param);

    /**
     * @brief 新增一个配置
     * @param param
     * @param key
     * @param value
     * @param dataChangeCreatedBy
     * @param comment
     * @return
     */
    static bool addConfig(const open_api_param &param,
                          const std::string &key,
                          const std::string &value,
                          const std::string &dataChangeCreatedBy,
                          const std::string &comment);

    /**
     * @brief 删除一个配置
     * @param param
     * @param key
     * @param op_person
     * @return
     */
    static bool deleteConfig(const open_api_param &param,
                             const std::string &key,
                             const std::string &op_person);

    /**
     * @brief 修改一个配置
     * @param param
     * @param key
     * @param value
     * @param createIfNotExists
     * @param dataChangeLastModifiedBy
     * @param comment
     * @param dataChangeCreatedBy
     * @return
     */
    static bool modifyConfig(const open_api_param &param,
                             const std::string &key,
                             const std::string &value,
                             bool createIfNotExists,
                             const std::string &dataChangeLastModifiedBy,
                             const std::string &comment,
                             const std::string &dataChangeCreatedBy);

    /**
     * @brief 获取一个配置
     * @param param
     * @param key
     * @return
     */
    static std::string getConfig(const open_api_param &param,
                                 const std::string &key);

    /**
     * @brief 发布某一个namespace
     * @param param
     * @return
     */
    static bool publishConfig(const open_api_param &param,
                              const std::string &releaseTitle,
                              const std::string &releasedBy,
                              const std::string &releaseComment);
};

} // namespace apollo_param

#endif // APOLLO_CPP_CLIENT_APOLLO_BASE_H
