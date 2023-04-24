#include "../include/apollo_request.h"
#include "../include/apollo_url.h"

namespace apollo_param
{

web::http::http_request buildGetAllNamespaceInfoReq(const std::string &token)
{
    web::http::http_request request(web::http::methods::GET);
    auto headers = getTokenHeader(token);
    request.headers() = headers;
    return request;
}

web::http::http_request BuildCreateNewNamespaceReq(const std::string &token,
                                                   const std::string &appid,
                                                   const std::string &ns,
                                                   const std::string &format,
                                                   bool isPublic,
                                                   const std::string &dataChangeCreatedBy,
                                                   const std::string &comment)
{
    web::http::http_request request(web::http::methods::POST);
    auto headers = getTokenHeader(token);
    web::json::value data;
    data[U("name")] = web::json::value::string(ns);
    data[U("appId")] = web::json::value::string(appid);
    data[U("format")] = web::json::value::string(format);
    data[U("isPublic")] = web::json::value::boolean(isPublic);
    data[U("comment")] = web::json::value::string(comment);
    data[U("dataChangeCreatedBy")] = web::json::value::string(dataChangeCreatedBy);
    request.headers() = headers;
    request.set_body(data);
    return request;
}

web::http::http_request BuildGetOneNamespaceInfoReq(const std::string &token)
{
    web::http::http_request request(web::http::methods::GET);
    auto headers = getTokenHeader(token);
    request.headers() = headers;
    return request;
}

web::http::http_request BuildAddConfigReq(const std::string &token,
                                          const std::string &key,
                                          const std::string &value,
                                          const std::string &dataChangeCreatedBy,
                                          const std::string &comment)
{
    web::http::http_request request(web::http::methods::POST);
    auto headers = getTokenHeader(token);
    web::json::value data;
    data[U("key")] = web::json::value::string(key);
    data[U("value")] = web::json::value::string(value);
    data[U("comment")] = web::json::value::string(comment);
    data[U("dataChangeCreatedBy")] = web::json::value::string(dataChangeCreatedBy);
    request.headers() = headers;
    request.set_body(data);
    return request;
}

web::http::http_request BuildDeleteConfigReq(const std::string &token,
                                             const std::string &key,
                                             const std::string &op_person)
{
    web::http::http_request request(web::http::methods::DEL);
    auto headers = getTokenHeader(token);
    web::http::uri_builder builder;
    builder.append_query(U("key"), key);
    builder.append_query(U("operator"), op_person);
    request.set_request_uri(builder.to_string());
    request.headers() = headers;
    return request;
}

web::http::http_request BuildModifyConfigReq(const std::string &token,
                                             const std::string &key,
                                             const std::string &value,
                                             bool createIfNotExists,
                                             const std::string &dataChangeLastModifiedBy,
                                             const std::string &comment,
                                             const std::string &dataChangeCreatedBy)
{
    web::http::http_request request(web::http::methods::PUT);
    auto headers = getTokenHeader(token);
    request.headers() = headers;

    web::json::value data;
    data[U("key")] = web::json::value::string(key);
    data[U("value")] = web::json::value::string(value);
    data[U("comment")] = web::json::value::string(comment);
    data[U("dataChangeLastModifiedBy")] = web::json::value::string(dataChangeLastModifiedBy);
    if (createIfNotExists) {
        web::http::uri_builder builder;
        builder.append_query(U("createIfNotExists"), createIfNotExists);
        request.set_request_uri(builder.to_string());
        data[U("dataChangeCreatedBy")] = web::json::value::string(dataChangeCreatedBy);
    }
    request.set_body(data);
    return request;
}

web::http::http_request BuildGetConfigReq(const std::string &token)
{
    web::http::http_request request(web::http::methods::GET);
    auto headers = getTokenHeader(token);
    request.headers() = headers;
    return request;
}

web::http::http_request BuildPublishConfigReq(const std::string &token,
                                              const std::string &releaseTitle,
                                              const std::string &releasedBy,
                                              const std::string &releaseComment)
{
    web::http::http_request request(web::http::methods::POST);
    auto headers = getTokenHeader(token);
    web::json::value data;
    data[U("releaseTitle")] = web::json::value::string(releaseTitle);
    data[U("releasedBy")] = web::json::value::string(releasedBy);
    data[U("releaseComment")] = web::json::value::string(releaseComment);
    request.headers() = headers;
    request.set_body(data);
    return request;
}

web::http::http_response execHttpRequest(const std::string &base_url, const web::http::http_request &req)
{
    try {
        auto requestClient = web::http::client::http_client(base_url);
        return requestClient.request(req).get();
    } catch (std::exception &e) {
        SPDLOG_ERROR("Exception: {}", e.what());
        return {};
    }
}

}; // namespace apollo_param