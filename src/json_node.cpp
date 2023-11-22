#include <iostream>
#include <string>

#include <json_nodes.h>

using namespace json;

void JsonNode::print(std::ostream &out, int indent) {
    switch (type) {
        case Type::NULL_VALUE:
            out << "null";
            break;
        case Type::BOOLEAN:
            out << (std::get<bool>(value) ? "true" : "false");
            break;
        case Type::NUMBER:
            out << std::get<double>(value);
            break;
        case Type::STRING:
            out << "\"" << std::get<std::string>(value) << "\"";
            break;
        case Type::ARRAY: {
            const auto &jsonArray = std::get<JsonArray>(value);
            if (jsonArray.empty()) {
                out << "[]";
            } else {
                out << "[" << std::endl;
                for (const auto &element: jsonArray) {
                    out << std::string(indent + 2, ' ');
                    element->print(out, indent + 2);
                    out << "," << std::endl;
                }
                out << std::string(indent, ' ') << "]";
            }
        }
            break;
        case Type::OBJECT: {
            const auto &jsonObject = std::get<JsonObject>(value);
            if (jsonObject.empty()) {
                out << "{}";
            } else {
                out << "{" << std::endl;
                for (const auto &[key, val]: jsonObject) {
                    out << std::string(indent + 2, ' ') << "\"" << key << "\": ";
                    val->print(out, indent + 2);
                    out << "," << std::endl;
                }
                out << std::string(indent, ' ') << "}";
            }
        }
            break;
    }
}