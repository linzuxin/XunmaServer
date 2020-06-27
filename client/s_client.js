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

var PROTO_PATH = __dirname + '/helloworld.proto';

var grpc = require('grpc');
var fs = require('fs');
var protoLoader = require('@grpc/proto-loader');
var packageDefinition = protoLoader.loadSync(
  PROTO_PATH,
  {
    keepCase: true,
    longs: String,
    enums: String,
    defaults: true,
    oneofs: true
  });
var hello_proto = grpc.loadPackageDefinition(packageDefinition).helloworld;

function main() {
  //var creds = grpc.ssl_channel_credentials(f.read())
  const caCrt = fs.readFileSync(__dirname + "/2602795_api.zncode.com.pem");
  const clientKey = fs.readFileSync(__dirname + "/2602795_api.zncode.com.key");
  const clientCrt = fs.readFileSync(__dirname + "/2602795_api.zncode.com.pem");

  var client = new hello_proto.Greeter('api.zncode.com:9090',grpc.credentials.createInsecure());
  //grpc.credentials.createSsl(clientCrt, clientKey, clientCrt,{ "grpc.ssl_target_name_override": "api.zncode.com", "grpc.default_authority": "api.zncode.com" }))
  var user;
  if (process.argv.length >= 3) {
    user = process.argv[2];
  } else {
    user = 'world';
  }
  client.sayHello({ name: user }, function (err, response) {
    console.log('Greeting:', err, response);
  });
}

main();
