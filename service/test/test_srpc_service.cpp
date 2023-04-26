#include "service/srpc_back_server.h"
#include "service/apollo_param_server.h"
#include "workflow/WFFacilities.h"
#include <memory>
#include "test/config.h"
using namespace apollo_param;

static WFFacilities::WaitGroup wait_group(1);
static void sig_handler(int signo)
{
    wait_group.done();
}

int main()
{
    apolloOpenConfig config;
    config.Settoken_value(test_token).SetPort(8822);
    std::shared_ptr<PropertiesPolicyServer<srpcServer>> sp = std::make_shared<srpcServer>();
    sp->init(config);
    sp->setConfig(config.appid_, "application", "testKey", "value222", "unknow");

    wait_group.wait();
    return 0;
}
