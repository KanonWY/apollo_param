#include "srpc_back_server.h"
#include "include/apollo_yaml_tmp.h"

namespace apollo_param
{

void PropertiesServiceImpl::paramRequest(ParamRequest *request, ParamResponse *response, srpc::RPCContext *ctx)
{
    std::cout << "req key = " << request->key() << std::endl;
    std::cout << "req value = " << request->value() << std::endl;
    std::cout << "struct type = " << request->struct_string() << std::endl;
    std::cout << "mehod = " << request->op() << std::endl;

    if (request->op() == apollo_param::OPERATOR::SET) {
        //TODO: 设置值
    } else if (request->op() == apollo_param::OPERATOR::GET) {
        m_ptr->getStringConfig(request->appid(), request->ns(), request->key(), request->struct_string());

    } else {
        SPDLOG_ERROR("error operate type!");
        response->set_success(false);
    }
}

bool srpcServer::initImp(short port, const std::string &address)
{
    m_imp = new PropertiesServiceImpl;
    m_imp->setRawPtr(this);
    m_server.add_service(m_imp);
    return m_server.start(port);
}

void srpcClient::init(const std::string &appid, const std::string &ns, const std::string &address, short port)

{
    m_server_ip = address,
    m_port = port;
    m_req.set_key(appid);
    m_req.set_ns(ns);
    m_client = new ParamService::SRPCClient(m_server_ip.c_str(), m_port);
}

} // namespace apollo_param