#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <variant>

namespace json {
    class JsonNode;

    using JsonObject = std::unordered_map<std::string, std::shared_ptr<JsonNode>>;
    using JsonArray = std::vector<std::shared_ptr<JsonNode>>;

    class JsonNode {
    public:
        JsonObject getObject() {
            return std::get<JsonObject>(value);
        }

        void setObject(JsonObject obj) {
            value = std::move(obj);
        }

        double &getNumber() {
            return std::get<double>(value);
        }

        void setNumber(double number) {
            this->type = Type::NUMBER;
            this->value = number;
        }

        std::string &getString() {
            return std::get<std::string>(value);
        }

        void setString(const std::string &str) {
            this->type = Type::STRING;
            this->value = str;
        }

        bool &getBoolean() {
            return std::get<bool>(value);
        }

        void setBoolean(bool boolean) {
            this->type = Type::BOOLEAN;
            this->value = boolean;
        }

        std::nullptr_t getNull() {
            return std::get<std::nullptr_t>(value);
        }

        void setNull() {
            this->type = Type::NULL_VALUE;
            this->value = nullptr;
        }

        JsonArray &getArray() {
            return std::get<JsonArray>(value);
        }

        void setArray(JsonArray array) {
            this->type = Type::ARRAY;
            this->value = std::move(array);
        }

        void print(std::ostream &out, int indent);

    private:
        enum class Type {
            NULL_VALUE,
            BOOLEAN,
            NUMBER,
            STRING,
            ARRAY,
            OBJECT
        } type;
        std::variant<JsonObject, JsonArray, std::string, double, bool, std::nullptr_t> value;
    };
}
