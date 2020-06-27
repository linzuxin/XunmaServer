/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

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

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

const char servercert_path[] = "./2602795_api.zncode.com.pem";
const char serverkey_path[] = "./2602795_api.zncode.com.key";
// Logic and data behind the server's behavior.
class GreeterServiceImpl final : public Greeter::Service
{
  Status SayHello(ServerContext *context, const HelloRequest *request,
                  HelloReply *reply) override
  {
    std::string prefix("Hello ");
    //context->AddInitialMetadata("Access-Control-Allow-Origin", "*");
		//context->AddInitialMetadata("Access-Control-Allow-Methods", "POST, GET, OPTIONS, PUT, DELETE");
		//context->AddInitialMetadata("Access-Control-Allow-Headers", "Accept, Content-Type, Content-Length, Accept-Encoding, X-CSRF-Token, Authorization, x-user-agent, x-grpc-web, grpc-status, grpc-message");
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

  bool enable_ssl = true;
  if (enable_ssl)
  {
    grpc::SslServerCredentialsOptions::PemKeyCertPair pkcp = {
        serverkey.c_str(), servercert.c_str()};
    grpc::SslServerCredentialsOptions ssl_opts;//GRPC_SSL_REQUEST_CLIENT_CERTIFICATE_BUT_DONT_VERIFY GRPC_SSL_DONT_REQUEST_CLIENT_CERTIFICATE
    ssl_opts.pem_root_certs = "";
    ssl_opts.pem_key_cert_pairs.push_back(pkcp);
    creds = grpc::SslServerCredentials(ssl_opts);
  }
  else
  {
    creds = grpc::InsecureServerCredentials();
  }

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, creds);
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char **argv)
{
  RunServer();

  return 0;
}
