#include "../include/apollo_openapi_client.h"
#include "config.h"

int main()
{
    apollo_param::apolloOpenConfig config;
    config.Settoken_value(test_token);

    apollo_param::PropertiesPolicyClient client;
    client.init(config);

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}