#include "../include/apollo_base.h"
#include "config.h"
#include <iostream>

using namespace apollo_param;

void Test_getAllNamespaceInfo()
{
    open_api_param param;
    param.token = test_token;
    param.appid = appid;
    auto res = apollo_open_base_api::getAllNamespaceInfo(param);
}

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

int main()
{
    open_api_param param;
    param.token = test_token;
    param.appid = appid;
    param.ns = "application";
    auto res = apollo_open_base_api::getOneNamespaceInfo(param);
    std::cout << res << std::endl;
    return 0;
}