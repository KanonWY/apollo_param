#ifndef APOLLO_CPP_CLIENT_SRPC_BACK_SERVER_H
#define APOLLO_CPP_CLIENT_SRPC_BACK_SERVER_H

#include "apollo_param_server.h"
#include "message.srpc.h"
#include "message.pb.h"

namespace apollo_param
{

class srpcServer;

class PropertiesServiceImpl : public ParamService::Service
{
public:
    void paramRequest(ParamRequest *request, ParamResponse *response,
                      srpc::RPCContext *ctx) override;

    void setRawPtr(srpcServer *ptr)
    {
        m_ptr = ptr;
    }

private:
    srpcServer *m_ptr{nullptr};
};

class srpcServer : public PropertiesPolicyServer<srpcServer>
{
public:
    bool initImp(short port, const std::string &address);

private:
    srpc::SRPCServer m_server;
    PropertiesServiceImpl *m_imp{nullptr};
};

class srpcClient
{
public:
    void init(const std::string &appid,
              const std::string &ns,
              const std::string &address,
              short port);

    template <typename T>
    void getConfig(const std::string &key, T &outStore)
    {
        using InputType = std::remove_reference_t<T>;

        auto type_name = apollo_param::yaml_type_name<InputType>::value;
        m_req.set_struct_string(type_name);
        m_req.set_op(apollo_param::OPERATOR::GET);
        m_req.set_key(key);
        m_client->paramRequest(&m_req, [&outStore](apollo_param::ParamResponse *response, srpc::RPCContext *ctx) {
            if (ctx->success()) {
                printf("%s\n", response->DebugString());
                YAML::Node node = YAML::Load(response->value());
                outStore = node.as<InputType>();
            } else {
                printf("status[%d], error[%d], errmsg:%s\n", ctx->get_status_code(), ctx->get_error(), ctx->get_errmsg());
            }
        });
    }

    template <typename T>
    bool setConfig(const std::string &key, T value)
    {
        // 1. 根据结构体T获取其类型
        using ToType = std::remove_reference_t<T>;
        auto name = apollo_param::yaml_type_name<ToType>::value;
        std::cout << "name = " << name << std::endl;
        m_req.set_struct_string(name);
        m_req.set_key(key);
        YAML::Node node;
        node["tmp"] = value;
        std::stringstream ss;
        ss << node["tmp"];
        std::cout << "ss.str = " << ss.str() << std::endl;
        m_req.set_value(ss.str());
        m_req.set_op(apollo_param::OPERATOR::SET);
        bool res{false};
        m_client->paramRequest(&m_req, [&res](apollo_param::ParamResponse *response, srpc::RPCContext *ctx) {
            if (ctx->success()) {
                printf("%s\n", response->DebugString());
                res = true;
            } else {
                printf("status[%d], error[%d], errmsg:%s\n", ctx->get_status_code(), ctx->get_error(), ctx->get_errmsg());
            }
        });
        return res;
    }
    template <typename T>
    bool setConfig(const char *key, T value)
    {
        // 1. 根据结构体T获取其类型
        using ToType = std::remove_reference_t<T>;
        auto name = apollo_param::yaml_type_name<ToType>::value;
        std::cout << "name = " << name << std::endl;
        m_req.set_struct_string(name);
        m_req.set_key(key);
        YAML::Node node;
        node["tmp"] = value;
        std::stringstream ss;
        ss << node["tmp"];
        std::cout << "ss.str = " << ss.str() << std::endl;
        m_req.set_value(ss.str());
        m_req.set_op(apollo_param::OPERATOR::SET);
        bool res{false};
        m_client->paramRequest(&m_req, [&res](apollo_param::ParamResponse *response, srpc::RPCContext *ctx) {
            if (ctx->success()) {
                std::cout << response->DebugString() << std::endl;
                res = true;
            } else {
                printf("status[%d], error[%d], errmsg:%s\n", ctx->get_status_code(), ctx->get_error(), ctx->get_errmsg());
            }
        });
        return res;
    }

    ~srpcClient()
    {
        if (m_client != nullptr) {
            delete m_client;
            m_client = nullptr;
        }
    }

private:
    ParamRequest m_req;
    ParamService::SRPCClient *m_client;
    std::string m_server_ip;
    short m_port;
};

} // namespace apollo_param

#endif //APOLLO_CPP_CLIENT_SRPC_BACK_SERVER_H
