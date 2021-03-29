#include <Client.hpp>

int main() {
  Client c("127.0.0.1", "8080");
  std::cout << c.SendRequest("/v1/api/suggest", "hel") << std::endl;
}