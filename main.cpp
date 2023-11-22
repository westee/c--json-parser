#include <iostream>
#include <json.h>

int main() {
  std::cout << "Hello, World!" << std::endl;
    {
        std::string text = R"(
    {"zhangsan" : "123"}
)";
        json::Tokenizer tokenizer(text);
        while (std::optional<json::Token> token = tokenizer.getToken()) {
            std::cout << token.value() << std::endl;
        }
    }
  return 0;
}