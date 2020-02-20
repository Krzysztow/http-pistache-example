#include <string>
#include <iostream>
#include <pistache/endpoint.h>
#include <argparse.hpp>

using namespace Pistache;


ulong parse_port(const std::string& in) 
{
  std::size_t consumed{0};
  const auto result = std::stoul(in, &consumed);

  if (consumed != in.size()) {
    throw std::runtime_error("Invalid number: '" + in + "'");
  }

  return result;
}

std::optional<argparse::ArgumentParser> parse_args(int argc, const char* argv[])
{
  argparse::ArgumentParser program{"http-server"};

  program.add_argument("port")
    .help("Port to listen on")
    .default_value(8080)
    .action(parse_port);

  try {
    program.parse_args(argc, argv);
  }
  catch (const std::runtime_error& err) {
    std::cout << "Error occured while parsing command line parameters:\n\t" << err.what() << "\n\n";
    std::cout << program;
    return {};
  }
  
  return program;
}

struct HelloHandler:
       	public Http::Handler 
{
  HTTP_PROTOTYPE(HelloHandler)

  void onRequest(const Http::Request&, Http::ResponseWriter writer) override
  {
    writer.send(Http::Code::Ok, "Hello, World!");
  }
};

void run_server(ulong port) 
{
  Pistache::Address address{Pistache::Ipv4::any(), port};

  std::cout << "Running server at " << address.port().toString() << '\n';
  Http::listenAndServe<HelloHandler>(address);
}

int main(int argc, const char* argv[]) 
{
  auto parse_result = parse_args(argc, argv);
  if (!parse_result) {
    return 1;
  }

  auto args = parse_result.value();
  run_server(args.get<ulong>("port"));
}
