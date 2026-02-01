#pragma once

#include "structs.h"
#include "json.hpp"

// Namespace functions for automatic JSON conversion
namespace nlohmann {
    using json = nlohmann::json;
    template <>
    struct adl_serializer<Point> {
        static void to_json(json& j, const Point& p) {
            j = json{{"x", p.x}, {"y", p.y}};
        }
        static void from_json(const json& j, Point& p) {
            j.at("x").get_to(p.x);
            j.at("y").get_to(p.y);
        }
    };

    template <>
    struct adl_serializer<Line> {
        static void to_json(json& j, const Line& l) {
            j = json{{"a", l.a}, {"b", l.b}};
        }
        static void from_json(const json& j, Line& l) {
            j.at("a").get_to(l.a);
            j.at("b").get_to(l.b);
        }
    };

    template <>
    struct adl_serializer<Action> {
        static void to_json(json& j, const Action& a) {
            j = json{
                {"tool", a.tool},
                {"line", a.line},
                {"width", a.width},
                {"color", a.color}
            };
        }
        static void from_json(const json& j, Action& a) {
            j.at("tool").get_to(a.tool);
            j.at("line").get_to(a.line);
            j.at("width").get_to(a.width);
            j.at("color").get_to(a.color);
        }
    };
}