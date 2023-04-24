#ifndef APOLLO_CPP_CLIENT_APOLLO_OPENAPI_CLIENT_H
#define APOLLO_CPP_CLIENT_APOLLO_OPENAPI_CLIENT_H

#include "../include/apollo_config.h"

namespace apollo_param
{
class apollo_openapi_client_base
{
public:
    bool init();

private:
    apolloOpenConfig m_config;
};
}; // namespace apollo_param

#endif //APOLLO_CPP_CLIENT_APOLLO_OPENAPI_CLIENT_H
