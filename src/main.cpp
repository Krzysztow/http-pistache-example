#include <string>
#include <iostream>
#include <pistache/endpoint.h>

using namespace Pistache;

struct HelloHandler:
       	public Http::Handler 
{
  HTTP_PROTOTYPE(HelloHandler)

  void onRequest(const Http::Request&, Http::ResponseWriter writer) override
  {
    std::cout << "Handling request\n";
    writer.send(Http::Code::Ok, "Hello, World!");
  }
};

int main() 
{
  constexpr char address[] = "*:9080";
  std::cout << "Starting server at " << address << '\n';
  Http::listenAndServe<HelloHandler>(Pistache::Address(address));
}
