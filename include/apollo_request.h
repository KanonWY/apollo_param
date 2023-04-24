#ifndef APOLLO_CPP_CLIENT_APOLLO_REQUEST_H
#define APOLLO_CPP_CLIENT_APOLLO_REQUEST_H

#include <cpprest/http_client.h>

namespace apollo_param
{
web::http::http_request buildGetAllNamespaceInfoReq(const std::string &token);

web::http::http_request BuildCreateNewNamespaceReq(const std::string &token,
                                                   const std::string &appid,
                                                   const std::string &ns,
                                                   const std::string &format,
                                                   bool isPublic,
                                                   const std::string &dataChangeCreatedBy,
                                                   const std::string &comment);

web::http::http_request BuildGetOneNamespaceInfoReq(const std::string &token);

web::http::http_request BuildAddConfigReq(const std::string &token,
                                          const std::string &key,
                                          const std::string &value,
                                          const std::string &dataChangeCreatedBy,
                                          const std::string &comment);

web::http::http_request BuildDeleteConfigReq(const std::string &token,
                                             const std::string &key,
                                             const std::string &op_person);

web::http::http_request BuildModifyConfigReq(const std::string &token,
                                             const std::string &key,
                                             const std::string &value,
                                             bool createIfNotExists,
                                             const std::string &dataChangeLastModifiedBy,
                                             const std::string &comment,
                                             const std::string &dataChangeCreatedBy);

web::http::http_request BuildGetConfigReq(const std::string &token);

web::http::http_request BuildPublishConfigReq(const std::string &token,
                                              const std::string &releaseTitle,
                                              const std::string &releasedBy,
                                              const std::string &releaseComment);

web::http::http_response execHttpRequest(const std::string &base_url, const web::http::http_request &req);

}; // namespace apollo_param

#endif //APOLLO_CPP_CLIENT_APOLLO_REQUEST_H
