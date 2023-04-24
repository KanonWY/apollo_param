#include "../include/apollo_base.h"
#include "../include/apollo_request.h"
#include "../include/apollo_url.h"
#include "yaml-cpp/yaml.h"
#include "../include/apollo_yaml_tmp.h"

namespace apollo_param
{
std::vector<NamespaceInfo> apollo_open_base_api::getAllNamespaceInfo(const std::string &portal_address,
                                                                     const std::string &env,
                                                                     const std::string &appid,
                                                                     const std::string &cluster,
                                                                     const std::string &token)
{
    //TODO:检查输入的长度是否URL限制
    std::vector<NamespaceInfo> res;
    auto response = execHttpRequest(getAllNamespaceInfoUrl(portal_address, env, appid, cluster),
                                    buildGetAllNamespaceInfoReq(token));
    if (response.status_code() == web::http::status_codes::OK) {
        auto json_data_from_server = response.extract_json().get();
        YAML::Node node = YAML::Load(json_data_from_server.serialize().c_str());
        if (node.Type() != YAML::NodeType::Sequence) {
            SPDLOG_ERROR("getAllNamespaceInfo return json is not sequence!");
        } else {
            for (auto &&i : node) {
                res.emplace_back(i.as<NamespaceInfo>());
            }
        }
        return res;
    } else {
        SPDLOG_ERROR("getAllNamespaceInfo error: {}", response.status_code());
        return res;
    }
}

std::vector<NamespaceInfo> apollo_open_base_api::getAllNamespaceInfo(const open_api_param &param)
{
    return getAllNamespaceInfo(param.portal_address, param.env, param.appid, param.cluster, param.token);
}

bool apollo_open_base_api::createNewNamespace(const std::string &portal_address,
                                              const std::string &appid,
                                              const std::string &token,
                                              const std::string &ns,
                                              const std::string &format,
                                              bool isPublic,
                                              const std::string &dataChangeCreatedBy,
                                              const std::string &comment)
{
    auto response = execHttpRequest(getCreateNewNamespaceUrl(portal_address, appid),
                                    BuildCreateNewNamespaceReq(token, appid, ns, format, isPublic, dataChangeCreatedBy, comment));
    if (response.status_code() == web::http::status_codes::OK) {
        return true;
    } else {
        SPDLOG_ERROR("createNewNamespace error: {}", response.status_code());
        return false;
    }
}

NamespaceInfo apollo_open_base_api::getOneNamespaceInfo(const open_api_param &param)
{
    auto response = execHttpRequest(getOneNamespaceInfoUrl(param.portal_address, param.env, param.appid, param.cluster, param.ns),
                                    BuildGetOneNamespaceInfoReq(param.token));
    NamespaceInfo res;
    if (response.status_code() == web::http::status_codes::OK) {
        auto json_data_from_server = response.extract_json().get();
        YAML::Node node = YAML::Load(json_data_from_server.serialize().c_str());
        if (node.Type() != YAML::NodeType::Map) {
            SPDLOG_ERROR("getOneNamespaceInfo return json is not Map!");
            return res;
        } else {
            res = node.as<NamespaceInfo>();
            return res;
        }
    } else {
        SPDLOG_ERROR("createNewNamespace error: {}", response.status_code());
        return res;
    }
}

bool apollo_open_base_api::addConfig(const open_api_param &param,
                                     const std::string &key,
                                     const std::string &value,
                                     const std::string &dataChangeCreatedBy,
                                     const std::string &comment)
{
    auto response = execHttpRequest(addConfigUrl(param.portal_address, param.env, param.appid, param.cluster, param.ns),
                                    BuildAddConfigReq(param.token, key, value, dataChangeCreatedBy, comment));
    if (response.status_code() == web::http::status_codes::OK) {
        return true;
    } else {
        SPDLOG_ERROR("addConfig error: {}\n{}", response.status_code(), response.extract_json().get().serialize().c_str());
        return false;
    }
}
bool apollo_open_base_api::deleteConfig(const open_api_param &param,
                                        const std::string &key,
                                        const std::string &op_person)
{
    auto response = execHttpRequest(deleteConfigUrl(param.portal_address, param.env, param.appid, param.cluster, param.ns, key),
                                    BuildDeleteConfigReq(param.token, key, op_person));
    if (response.status_code() == web::http::status_codes::OK) {
        SPDLOG_INFO("{}\n{}", response.status_code(), response.extract_json().get().serialize().c_str());
        return true;
    } else {
        SPDLOG_ERROR("deleteConfig error: {}\n{}", response.status_code(), response.extract_json().get().serialize().c_str());
        return false;
    }
}

bool apollo_open_base_api::modifyConfig(const open_api_param &param,
                                        const std::string &key,
                                        const std::string &value,
                                        bool createIfNotExists,
                                        const std::string &dataChangeLastModifiedBy,
                                        const std::string &comment,
                                        const std::string &dataChangeCreatedBy)
{
    auto response = execHttpRequest(modifyConfigUrl(param.portal_address, param.env, param.appid, param.cluster, param.ns, key),
                                    BuildModifyConfigReq(param.token, key, value, createIfNotExists, dataChangeCreatedBy, comment, dataChangeCreatedBy));

    if (response.status_code() == web::http::status_codes::OK) {
        return true;
    } else {
        SPDLOG_ERROR("modifyConfig error: {}\n{}", response.status_code(), response.extract_json().get().serialize().c_str());
        return false;
    }
}
bool apollo_open_base_api::publishConfig(const open_api_param &param,
                                         const std::string &releaseTitle,
                                         const std::string &releasedBy,
                                         const std::string &releaseComment)
{
    auto response = execHttpRequest(publishConfigUrl(param.portal_address, param.env, param.appid, param.cluster, param.ns),
                                    BuildPublishConfigReq(param.token, releaseTitle, releasedBy, releaseComment));
    if (response.status_code() == web::http::status_codes::OK) {
        return true;
    } else {
        SPDLOG_ERROR("publishConfig error: {}", response.status_code());
        return false;
    }
}
std::string apollo_open_base_api::getConfig(const open_api_param &param,
                                            const std::string &key)
{
    return std::string();
}
}; // namespace apollo_param
