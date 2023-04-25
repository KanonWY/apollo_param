#include "../include/apollo_base.h"
#include "config.h"
#include <iostream>

using namespace apollo_param;

/**
 * @brief 测试获取该appid下所有的命名空间信息
 * @return
 */
int Test_getAllNamespaceInfo()
{
    open_api_param param;
    param.token = test_token;
    param.appid = appid;
    auto res = apollo_open_base_api::getAllNamespaceInfo(param);
    return 0;
}

/**
 * @brief 测试新增一个namespace
 * @return
 */
int Test_createNewNamespace()
{
    open_api_param param;
    param.token = test_token;
    param.appid = appid;
    std::string format = "yaml";
    bool isPub = false;
    param.ns = "createNs";
    auto res = apollo_open_base_api::createNewNamespace(param.portal_address,
                                                        param.appid,
                                                        param.token,
                                                        param.ns,
                                                        format,
                                                        isPub, "apollo", "创建新ns");
    return 0;
}

int Test_getOneNamespaceInfo()
{
    open_api_param param;
    param.token = test_token;
    param.appid = appid;
    param.ns = "application";
    auto res = apollo_open_base_api::getOneNamespaceInfo(param);
    return 0;
}

/**
 * @brief 添加属性配置
 * @return
 */
int Test_addConfig()
{
    open_api_param param;
    param.token = test_token;
    param.appid = appid;
    param.ns = "application";
    auto res = apollo_open_base_api::addConfig(param, "llllll", "lpdlapdl", "apollo", "添加一个properties");
    return 0;
}

/**
 * @brief 对于yaml文件的增加配置，只有在新增一个namespace之后，才可以新增一次全量配置，否则无法生效。
 * @return
 */
int Test_addConfigYaml()
{
    open_api_param param;
    param.token = test_token;
    param.appid = appid;
    param.ns = "test_yaml.yaml";
    auto res = apollo_open_base_api::addConfig(param, "content", "dkloadkoakdioaudad", "apollo", "修改yaml");
    return 0;
}

/**
 * @brief 删除某一个配置（properties的）
 * @return
 */
int Test_deleteConfig()
{
    open_api_param param;
    param.token = test_token;
    param.appid = appid;
    param.ns = "application";
    auto res = apollo_open_base_api::deleteConfig(param, "key1", "apollo");
    return 0;
}

/**
 * @brief 对于非properties的配置文件，key只能为：content:
 *      否则会返回 {"exception":"com.ctrip.framework.apollo.common.exception.NotFoundException","message":"item not found for SampleApp default test_yaml.yaml key1","status":404,"timestamp":"2023-04-24T19:00:47.888"}
 *      如果成功不会返回任何值。
 * @return
 */
int Test_deleteConfig_yaml()
{
    open_api_param param;
    param.token = test_token;
    param.appid = appid;
    param.ns = "test_yaml.yaml";
    auto res = apollo_open_base_api::deleteConfig(param, "content", "apollo");
    return 0;
}

/**
 * @brief 修改 properties配置
 * @return
 */
int Test_modifyConfig()
{

    open_api_param param;
    param.token = test_token;
    param.appid = appid;
    param.ns = "application";
    auto res = apollo_open_base_api::modifyConfig(param, "key23", "value3lpdlpa3", true, "apollo", "修改key1", "apollo");

    return 0;
};

/**
 * @brief 发布某一个命名空间的所有修改
 * @return
 */
int Test_publishConfig()
{
    open_api_param param;
    param.token = test_token;
    param.appid = appid;
    param.ns = "application";
    auto res = apollo_open_base_api::publishConfig(param, "发布", "apollo", "apollo");
    return 0;
}

int main()
{
    Test_modifyConfig();
    return 0;
}