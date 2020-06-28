
#include <iostream>
#include <fstream>
#include <memory>
#include <string>

#include <grpc++/security/credentials.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/support/channel_arguments.h>

#include "helloworld.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

const char servercert_path[] = "./2602795_api.zncode.com.pem";
const char serverkey_path[] = "./2602795_api.zncode.com.key";

class GreeterServiceImpl final : public Greeter::Service
{
  Status SayHello(ServerContext *context, const HelloRequest *request,
                  HelloReply *reply) override
  {
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());
    return Status::OK;
  }
};

static std::string get_file_contents(const char *fpath)
{
  std::ifstream finstream(fpath);
  std::string contents;
  contents.assign((std::istreambuf_iterator<char>(finstream)),
                  std::istreambuf_iterator<char>());
  finstream.close();
  return contents;
}

void RunServer()
{
  std::string server_address("0.0.0.0:9090");
  GreeterServiceImpl service;

  auto servercert = get_file_contents(servercert_path);
  auto serverkey = get_file_contents(serverkey_path);

  //auto channel_creds = grpc::SslCredentials(grpc::SslCredentialsOptions());
  // auto channel = grpc::CreateChannel("myservice.example.com", channel_creds);
  // std::unique_ptr<Greeter::Stub> stub(Greeter::NewStub(channel));

  std::shared_ptr<grpc::ServerCredentials> creds;

  grpc::SslServerCredentialsOptions::PemKeyCertPair pkcp = {
      serverkey.c_str(), servercert.c_str()};
  grpc::SslServerCredentialsOptions ssl_opts; //GRPC_SSL_REQUEST_CLIENT_CERTIFICATE_BUT_DONT_VERIFY GRPC_SSL_DONT_REQUEST_CLIENT_CERTIFICATE
  ssl_opts.pem_root_certs = "";
  ssl_opts.pem_key_cert_pairs.push_back(pkcp);
  creds = grpc::SslServerCredentials(ssl_opts);

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  ServerBuilder builder;
  builder.AddListeningPort(server_address, creds);
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  server->Wait();
}

int main(int argc, char **argv)
{
  RunServer();

  return 0;
}
