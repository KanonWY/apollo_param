#ifndef APOLLO_CPP_CLIENT_APOLLO_OPENAPI_CLIENT_H
#define APOLLO_CPP_CLIENT_APOLLO_OPENAPI_CLIENT_H

#include <string>
#include <cstring>
#include <map>
#include <optional>
#include <yaml-cpp/yaml.h>

#include "../include/apollo_config.h"
#include "../include/apollo_base.h"
#include "../include/apollo_url.h"
#include "../include/apollo_yaml_tmp.h"

namespace apollo_param
{
/**
 * @brief 存储在属性表中，每一个属性表存储一个结构体
 */
class PropertiesPolicy
{
public:
    using StoreContainer = std::map<std::string, YAML::Node>;
    using StoreContainer_2 = std::map<std::string, std::string>;
    using StoreContainer_3 = std::map<std::string, std::map<std::string, std::string>>;
    using StoreContainer_4 = std::map<std::string, std::map<std::string, std::string>>;

    bool init_(const apolloOpenConfig &config)
    {
        m_config = config;
        //仅仅拉取的properties的
        auto res = apollo_open_base_api::getAllNamespaceInfo(config.portal_address_,
                                                             config.env_,
                                                             config.appid_,
                                                             config.cluster_,
                                                             config.token_);
        if (res.empty()) {
            return false;
        }
        for (auto &item : res) {
            if (strcmp(item.format.c_str(), "properties") != 0) {
                continue;
            } else {
                m_ns.push_back(item.namespaceName);
                m_notify_map.insert({item.namespaceName, -1});
                // namespace/key
                for (auto &it : item.items) {
                    m_container2.insert({(item.namespaceName + "/" + it["key"]), it["value"]});
                }
            }
        }
        m_status = true;
        return true;
    }

    web::http::status_code checkNotify(std::map<std::string, int> &changeInfo)
    {
        try {
            changeInfo.clear();
            auto base_url = getNotifyUrl(m_config.address_);
            web::http::client::http_client_config client_config;
            client_config.set_timeout(std::chrono::seconds(62));
            auto request_client = web::http::client::http_client(base_url, client_config);
            web::json::value notify_json_values;
            int json_array_index = 0;
            for (const auto &map_item : m_notify_map) {
                web::json::value tmp_json_value;
                tmp_json_value[U("namespaceName")] = web::json::value::string(map_item.first);
                tmp_json_value[U("notificationId")] = web::json::value::number(map_item.second);
                notify_json_values[U("param")][json_array_index] = tmp_json_value;
                json_array_index++;
            }
            auto ns_json_value = notify_json_values[U("param")];
            web::http::uri_builder builder;
            builder.append_query(U("notifications"), ns_json_value.serialize().c_str());
            builder.append_query(U("appId"), m_config.appid_.c_str());
            builder.append_query(U("cluster"), m_config.cluster_.c_str());
            auto response = request_client.request(web::http::methods::GET, builder.to_string()).get();
            if (response.status_code() == web::http::status_codes::OK) {
                auto json_data_from_server = response.extract_json().get();
                YAML::Node node = YAML::Load(json_data_from_server.serialize().c_str());
                if (node.Type() != YAML::NodeType::Sequence) {
                    SPDLOG_ERROR("getAllNamespaceInfo return json is not sequence!");
                    return web::http::status_codes::InternalError;
                } else {
                    for (auto &&item : node) {
                        auto notifyInfo = item.as<NotifyInfo>();
                        changeInfo[notifyInfo.namespaceName] = notifyInfo.notificationId;
                    }
                    return web::http::status_codes::OK;
                }
            } else if (response.status_code() == web::http::status_codes::NotModified) {
                return web::http::status_codes::NotModified;
            } else {
                return response.status_code();
            }
        } catch (std::exception &e) {
            SPDLOG_ERROR("checkNotify exception error: {}", e.what());
            return web::http::status_codes::InternalError;
        }
    }

    void BackThread()
    {
        while (m_b_start_thread) {
            std::map<std::string, int> changeMap;
            auto res_status = checkNotify(changeMap);
            if (res_status == web::http::status_codes::OK) {
                SPDLOG_INFO("------------------------------> Will Update Notify map");
                for (const auto &item : changeMap) {
                    m_notify_map[item.first] = item.second;
                }
                //                if (first_start) {
                //                    first_start = false;
                //                } else {
                //                    SPDLOG_INFO("------------------------------>  Update Namespace");
                //                    UpdateNamespace(changeMap);
                //                }
                UpdateNamespace(changeMap);
            } else if (res_status == web::http::status_codes::NotModified) {
                SPDLOG_INFO("checkNotify NotModified!");
                continue;
            } else {
                SPDLOG_INFO("checkNotify error! {}", res_status);
                break;
            }
        }
        SPDLOG_INFO("exit BackThread, m_b_start_thread = {}", m_b_start_thread);
        if (m_b_start_thread)
            m_b_start_thread = false;
    }

    void UpdateNamespace(const std::map<std::string, int> &changeMap)
    {
        std::lock_guard<std::mutex> locker(m_container_mt);

        for (const auto &item : changeMap) {
            open_api_param param;
            param.appid = m_config.appid_;
            param.token = m_config.token_;
            param.ns = item.first;
            param.portal_address = m_config.portal_address_;
            auto res = apollo_open_base_api::getOneNamespaceInfo(param);
            auto ns = res.namespaceName;
            auto items = res.items;
            m_container3[ns].clear();
            for (auto &&it : items) {
                m_container3[ns][it["key"]] = it["value"];
            }
        }
    }

    void start_thread()
    {
        m_b_start_thread = true;
        m_notifyThread = std::thread(&PropertiesPolicy::BackThread, this);
    }

    void stop_thread()
    {
        m_b_start_thread = false;
        m_notifyThread.join();
    }

    ~PropertiesPolicy()
    {
        if (m_notifyThread.joinable())
            m_notifyThread.join();
    }

    std::optional<std::string> getConfig_(const std::string &ns, const std::string &key, const std::string &struct_string)
    {
        if (m_status) {
            std::lock_guard<std::mutex> locker(m_container_mt);
            if (m_container3.count(ns) <= 0) {
                return {};
            }
            auto inner_map = m_container3[ns];
            if (inner_map.count(key) <= 0) {
                return {};
            }
            return inner_map[key];
        }
        return {};
    }

    bool setConfig_(const std::string &ns, const std::string &key, const std::string &value, const std::string &struct_string)
    {
        if (m_status) {
            open_api_param param;
            param.appid = m_config.appid_;
            param.token = m_config.token_;
            param.ns = ns;
            param.portal_address = m_config.portal_address_;
            auto res = apollo_open_base_api::modifyConfig(param, key, value, true, "apollo", "commit", "apollo");
            res &= apollo_open_base_api::publishConfig(param, "open api release!", "apollo", "comment");
            if (!res) {
                SPDLOG_ERROR("setConfig_ error");
                return false;
            }
            return true;
        } else {
            return false;
        }
    }

private:
    std::map<std::string, int>
        m_notify_map;
    std::vector<std::string> m_ns;

    StoreContainer m_container;
    StoreContainer_2 m_container2;
    StoreContainer_3 m_container3;
    StoreContainer_4 m_container4;

    apolloOpenConfig m_config;
    bool m_b_start_thread{false};
    std::thread m_notifyThread;
    bool first_start{true};
    bool m_status{false};
    std::mutex m_container_mt;
};

template <typename Policy = PropertiesPolicy>
class apolloOpenClientBase
{
public:
    /**
     * @brief
     * @param config
     */
    bool init(const apolloOpenConfig &config)
    {
        m_policy.init_(config);
        startThread();
        return true;
    }

    void startThread()
    {
        m_policy.start_thread();
    }

    std::optional<std::string> getStringConfig_(const std::string &ns, const std::string &key, const std::string &struct_name)
    {
        return m_policy.getConfig_(ns, key, struct_name);
    }

    bool setStringConfig_(const std::string &ns, const std::string &key, const std::string &value, const std::string &struct_name)
    {
        return m_policy.setConfig_(ns, key, value, struct_name);
    }

    void stopThread()
    {
        m_policy.stop_thread();
    }

private:
    Policy m_policy;
};

using PropertiesPolicyClient = apolloOpenClientBase<PropertiesPolicy>;
}; // namespace apollo_param

#endif //APOLLO_CPP_CLIENT_APOLLO_OPENAPI_CLIENT_H
