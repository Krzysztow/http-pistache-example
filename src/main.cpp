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

int main(int argc, const char* argv[]) 
{
  const ulong port = argc >= 2 ?
    std::stoul(argv[1]) :
    8080;

  std::cout << "Starting server at port " << port << '\n';
  Http::listenAndServe<HelloHandler>(Pistache::Address(Ipv4::any(), port));
}
