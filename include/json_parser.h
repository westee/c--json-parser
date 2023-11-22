#include <json_nodes.h>
#include <variant>
#include <optional>
#include <iostream>

namespace json {
    struct Token {
        enum class Type {
            OBJECT_OPEN, OBJECT_CLOSE, ARRAY_OPEN, ARRAY_CLOSE, COLON, SEMI, COMMA, STRING, NUMBER, BOOLEAN, NULL_VALUE
        } type;
        std::variant<std::string, double, bool, std::nullptr_t> value = nullptr;
    };

    class Tokenizer {
    public:
        Tokenizer(std::string_view text) : text(text), pos(0){};

        std::optional<Token> getToken();

    private:
        std::string_view text;
        size_t pos = 0;
    };
}

std::ostream &operator << (std::ostream &out, const json::Token &);