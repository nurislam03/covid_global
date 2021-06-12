#include <cpp-httplib/httplib.h>
#include <json/json.hpp>

using json = nlohmann::json;

int main(void)
{
  using namespace httplib;

  Server svr;

  svr.set_logger([](const auto& req, const auto& res) {
    //std::cout << req << " " << res << std::endl;
  });

  svr.Get("/hi", [](const Request& req, Response& res) {
    res.set_content("Hello World!", "text/plain");
  });

  svr.Get(R"(/numbers/(\d+))", [&](const Request& req, Response& res) {
    auto numbers = req.matches[1];
    res.set_content(numbers, "text/plain");
  });

  svr.Post("/body-header-param", [](const Request& req, Response& res) {
    if (req.has_header("Content-Length")) {
      auto val = req.get_header_value("Content-Length");
      std::cout << "Content-Length: " << val << std::endl;
    }

    if (req.has_param("key")) {
      auto val = req.get_param_value("key");
      std::cout << "param, key: " << val << std::endl;
    }

    std::cout << "body: " << req.body << std::endl;
    auto jsn = json::parse(req.body);
    std::cout << "json body: " << jsn.dump(2) << std::endl;
    res.set_content(jsn.dump(2), "application/json");
  });

  svr.Get("/stop", [&](const Request& req, Response& res) {
    svr.stop();
  });

  svr.listen("localhost", 1234);
}