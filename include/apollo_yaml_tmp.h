#ifndef APOLLO_CPP_CLIENT_APOLLO_YAML_TMP_H
#define APOLLO_CPP_CLIENT_APOLLO_YAML_TMP_H

#include <yaml-cpp/yaml.h>
#include "yaml_struct/yaml_struct.h"

struct NamespaceInfo
{
    std::string appId;
    std::string clusterName;
    std::string namespaceName;
    std::string comment;
    std::string format;
    bool isPublic;
    std::vector<std::map<std::string, std::string>> items;
    std::string dataChangeCreatedBy;
    std::string dataChangeLastModifiedBy;
    std::string dataChangeCreatedTime;
    std::string dataChangeLastModifiedTime;
};

namespace YAML
{
template <>
struct convert<NamespaceInfo>
{
    static Node encode(const NamespaceInfo &store)
    {
        Node node;
        node["appId"] = store.appId;
        node["clusterName"] = store.clusterName;
        node["namespaceName"] = store.namespaceName;
        node["comment"] = store.comment;
        node["format"] = store.format;
        node["isPublic"] = store.isPublic;
        node["dataChangeCreatedBy"] = store.dataChangeCreatedBy;
        node["dataChangeLastModifiedBy"] = store.dataChangeLastModifiedBy;
        node["dataChangeCreatedTime"] = store.dataChangeCreatedTime;
        node["dataChangeLastModifiedTime"] = store.dataChangeLastModifiedTime;

        Node items_node;
        for (const auto &item : store.items) {
            Node item_node;
            for (const auto &kv : item) {
                item_node[kv.first] = kv.second;
            }
            items_node.push_back(item_node);
        }
        node["items"] = items_node;

        return node;
    }

    static bool decode(const Node &node, NamespaceInfo &store)
    {
        if (!node.IsMap()) {
            return false;
        }

        store.appId = node["appId"].as<std::string>();
        store.clusterName = node["clusterName"].as<std::string>();
        store.namespaceName = node["namespaceName"].as<std::string>();
        store.comment = node["comment"].as<std::string>();
        store.format = node["format"].as<std::string>();
        store.isPublic = node["isPublic"].as<bool>();
        store.dataChangeCreatedBy = node["dataChangeCreatedBy"].as<std::string>();
        store.dataChangeLastModifiedBy = node["dataChangeLastModifiedBy"].as<std::string>();
        store.dataChangeCreatedTime = node["dataChangeCreatedTime"].as<std::string>();
        store.dataChangeLastModifiedTime = node["dataChangeLastModifiedTime"].as<std::string>();

        const auto &items_node = node["items"];
        store.items.reserve(items_node.size());
        for (const auto &item_node : items_node) {
            std::map<std::string, std::string> item;
            for (const auto &kv : item_node) {
                item[kv.first.as<std::string>()] = kv.second.as<std::string>();
            }
            store.items.push_back(std::move(item));
        }
        return true;
    }
};
}; // namespace YAML

#endif //APOLLO_CPP_CLIENT_APOLLO_YAML_TMP_H