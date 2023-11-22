#include <json_parser.h>
#include <optional>
#include <stdexcept>

using namespace json;

std::optional<Token> json::Tokenizer::getToken() {
    while (pos < text.size() && isspace(text[pos])) {
        ++pos;
    }

    if (pos == text.size()) {
        return std::nullopt;
    }

    Token token;
    if (text[pos] == '{') {
        token.type = Token::Type::OBJECT_OPEN;
        ++pos;
    } else if (text[pos] == '}') {
        token.type = Token::Type::OBJECT_CLOSE;
        ++pos;
    } else if (text[pos] == '[') {
        token.type = Token::Type::ARRAY_OPEN;
        ++pos;
    } else if (text[pos] == ']') {
        token.type = Token::Type::ARRAY_CLOSE;
        ++pos;
    } else if (text[pos] == ':') {
        token.type = Token::Type::COLON;
        ++pos;
    } else if (text[pos] == ';') {
        token.type = Token::Type::SEMI;
        ++pos;
    } else if (text[pos] == ',') {
        token.type = Token::Type::COMMA;
        ++pos;
    } else if (text[pos] == '"') {
        // 解析字符串
        size_t start = ++pos;  // 跳过开头的引号
        while (pos < text.size() && text[pos] != '"') {
            ++pos;
        }
        if (pos == text.size()) {
            // 字符串没有结束引号
            return std::nullopt;
        }
        std::string str = std::string(text.substr(start, pos - start));
        token.type = Token::Type::STRING;
        token.value = str;
        ++pos;  // 跳过结尾的引号
    } else if (isdigit(text[pos]) || text[pos] == '-') {
        // 解析数字
        size_t start = pos;
        while (pos < text.size() &&
               (isdigit(text[pos]) || text[pos] == '.' || text[pos] == 'e' || text[pos] == 'E' || text[pos] == '-')) {
            ++pos;
        }
        std::string num_str = std::string(text.substr(start, pos - start));
        try {
            double num = std::stod(num_str);
            token.type = Token::Type::NUMBER;
            token.value = num;
        } catch (const std::invalid_argument &) {
            // 数字格式错误
            return std::nullopt;
        }
    } else if (text.substr(pos, 4) == "true") {
        token.type = Token::Type::BOOLEAN;
        token.value = true;
        pos += 4;  // 跳过"true"
    } else if (text.substr(pos, 5) == "false") {
        token.type = Token::Type::BOOLEAN;
        token.value = false;
        pos += 5;  // 跳过"false"
    } else if (text.substr(pos, 4) == "null") {
        token.type = Token::Type::NULL_VALUE;
        token.value = nullptr;
        pos += 4;  // 跳过"null"
    } else {
        // 无法识别的Token类型
        return std::nullopt;
    }
    return token;
}

std::ostream &operator<<(std::ostream &out, const Token &token) {
    if (token.type == Token::Type::OBJECT_OPEN) {
        return out << "Token" "{";
    } else if (token.type == Token::Type::OBJECT_CLOSE) {
        return out << "Token" "}";
    } else if (token.type == Token::Type::ARRAY_OPEN) {
        return out << "Token" "[";
    } else if (token.type == Token::Type::ARRAY_CLOSE) {
        return out << "Token" "]";
    } else if (token.type == Token::Type::COLON) {
        return out << "Token" ":";
    } else if (token.type == Token::Type::SEMI) {
        return out << "Token" ";";
    } else if (token.type == Token::Type::COMMA) {
        return out << "Token" ",";
    } else if (token.type == Token::Type::STRING) {
        return out << "Token" "STRING: " << std::get<std::string>(token.value);
    } else if (token.type == Token::Type::NUMBER) {
        return out << "Token" "NUMBER: " << std::get<double>(token.value);
    } else if (token.type == Token::Type::BOOLEAN) {
        return out << "Token" "BOOLEAN: " << std::boolalpha << std::get<bool>(token.value);
    }
    return out;
}
