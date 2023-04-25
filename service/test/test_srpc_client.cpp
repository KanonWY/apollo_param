#include "service/srpc_back_server.h"
#include "workflow/WFFacilities.h"

static WFFacilities::WaitGroup wait_group(1);

using namespace apollo_param;

int main()
{
    srpcClient client;
    client.init("SampleApp", "application", "127.0.0.1", 8822);
    TestConfig var;
    var.Name = "helloworld";
    var.a = 200;
    client.setConfig("word", var);

    wait_group.wait();
    return 0;
}