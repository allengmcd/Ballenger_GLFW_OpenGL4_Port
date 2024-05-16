//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     Welcome data = nlohmann::json::parse(jsonString);

#pragma once


#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <stdexcept>
#include <regex>

namespace LevelFile {
    using nlohmann::json;

    #ifndef NLOHMANN_UNTYPED_LevelFile_HELPER
    #define NLOHMANN_UNTYPED_LevelFile_HELPER
    inline json get_untyped(const json & j, const char * property) {
        if (j.find(property) != j.end()) {
            return j.at(property).get<json>();
        }
        return json();
    }

    inline json get_untyped(const json & j, std::string property) {
        return get_untyped(j, property.data());
    }
    #endif

    class Color {
        public:
        Color() = default;
        virtual ~Color() = default;

        private:
        int64_t r;
        int64_t g;
        int64_t b;

        public:
        const int64_t & get_r() const { return r; }
        int64_t & get_mutable_r() { return r; }
        void set_r(const int64_t & value) { this->r = value; }

        const int64_t & get_g() const { return g; }
        int64_t & get_mutable_g() { return g; }
        void set_g(const int64_t & value) { this->g = value; }

        const int64_t & get_b() const { return b; }
        int64_t & get_mutable_b() { return b; }
        void set_b(const int64_t & value) { this->b = value; }
    };

    class Coord {
        public:
        Coord() = default;
        virtual ~Coord() = default;

        private:
        int64_t x;
        int64_t y;

        public:
        const int64_t & get_x() const { return x; }
        int64_t & get_mutable_x() { return x; }
        void set_x(const int64_t & value) { this->x = value; }

        const int64_t & get_y() const { return y; }
        int64_t & get_mutable_y() { return y; }
        void set_y(const int64_t & value) { this->y = value; }
    };

    class Column {
        public:
        Column() = default;
        virtual ~Column() = default;

        private:
        int64_t id;
        Color color;
        Coord coord;

        public:
        const int64_t & get_id() const { return id; }
        int64_t & get_mutable_id() { return id; }
        void set_id(const int64_t & value) { this->id = value; }

        const Color & get_color() const { return color; }
        Color & get_mutable_color() { return color; }
        void set_color(const Color & value) { this->color = value; }

        const Coord & get_coord() const { return coord; }
        Coord & get_mutable_coord() { return coord; }
        void set_coord(const Coord & value) { this->coord = value; }
    };

    class Lava {
        public:
        Lava() = default;
        virtual ~Lava() = default;

        private:
        int64_t bottom;
        int64_t top;
        int64_t interval;

        public:
        const int64_t & get_bottom() const { return bottom; }
        int64_t & get_mutable_bottom() { return bottom; }
        void set_bottom(const int64_t & value) { this->bottom = value; }

        const int64_t & get_top() const { return top; }
        int64_t & get_mutable_top() { return top; }
        void set_top(const int64_t & value) { this->top = value; }

        const int64_t & get_interval() const { return interval; }
        int64_t & get_mutable_interval() { return interval; }
        void set_interval(const int64_t & value) { this->interval = value; }
    };

    class Portal {
        public:
        Portal() = default;
        virtual ~Portal() = default;

        private:
        Coord coord;

        public:
        const Coord & get_coord() const { return coord; }
        Coord & get_mutable_coord() { return coord; }
        void set_coord(const Coord & value) { this->coord = value; }
    };

    class RespawnPoint {
        public:
        RespawnPoint() = default;
        virtual ~RespawnPoint() = default;

        private:
        int64_t id;
        Coord coord;

        public:
        const int64_t & get_id() const { return id; }
        int64_t & get_mutable_id() { return id; }
        void set_id(const int64_t & value) { this->id = value; }

        const Coord & get_coord() const { return coord; }
        Coord & get_mutable_coord() { return coord; }
        void set_coord(const Coord & value) { this->coord = value; }
    };

    class Terrain {
        public:
        Terrain() = default;
        virtual ~Terrain() = default;

        private:
        std::string heightmap;
        std::string horizontal_texture;
        std::string vertical_texture;

        public:
        const std::string & get_heightmap() const { return heightmap; }
        std::string & get_mutable_heightmap() { return heightmap; }
        void set_heightmap(const std::string & value) { this->heightmap = value; }

        const std::string & get_horizontal_texture() const { return horizontal_texture; }
        std::string & get_mutable_horizontal_texture() { return horizontal_texture; }
        void set_horizontal_texture(const std::string & value) { this->horizontal_texture = value; }

        const std::string & get_vertical_texture() const { return vertical_texture; }
        std::string & get_mutable_vertical_texture() { return vertical_texture; }
        void set_vertical_texture(const std::string & value) { this->vertical_texture = value; }
    };

    class Data {
        public:
        Data() = default;
        virtual ~Data() = default;

        private:
        std::string skybox;
        Terrain terrain;
        Lava lava;
        std::vector<RespawnPoint> respawn_points;
        std::vector<Column> keys;
        std::vector<Column> columns;
        Portal portal;

        public:
        const std::string & get_skybox() const { return skybox; }
        std::string & get_mutable_skybox() { return skybox; }
        void set_skybox(const std::string & value) { this->skybox = value; }

        const Terrain & get_terrain() const { return terrain; }
        Terrain & get_mutable_terrain() { return terrain; }
        void set_terrain(const Terrain & value) { this->terrain = value; }

        const Lava & get_lava() const { return lava; }
        Lava & get_mutable_lava() { return lava; }
        void set_lava(const Lava & value) { this->lava = value; }

        const std::vector<RespawnPoint> & get_respawn_points() const { return respawn_points; }
        std::vector<RespawnPoint> & get_mutable_respawn_points() { return respawn_points; }
        void set_respawn_points(const std::vector<RespawnPoint> & value) { this->respawn_points = value; }

        const std::vector<Column> & get_keys() const { return keys; }
        std::vector<Column> & get_mutable_keys() { return keys; }
        void set_keys(const std::vector<Column> & value) { this->keys = value; }

        const std::vector<Column> & get_columns() const { return columns; }
        std::vector<Column> & get_mutable_columns() { return columns; }
        void set_columns(const std::vector<Column> & value) { this->columns = value; }

        const Portal & get_portal() const { return portal; }
        Portal & get_mutable_portal() { return portal; }
        void set_portal(const Portal & value) { this->portal = value; }
    };

    class Level {
        public:
        Level() = default;
        virtual ~Level() = default;

        private:
        std::string name;
        std::string id;
        Data data;

        public:
        const std::string & get_name() const { return name; }
        std::string & get_mutable_name() { return name; }
        void set_name(const std::string & value) { this->name = value; }

        const std::string & get_id() const { return id; }
        std::string & get_mutable_id() { return id; }
        void set_id(const std::string & value) { this->id = value; }

        const Data & get_data() const { return data; }
        Data & get_mutable_data() { return data; }
        void set_data(const Data & value) { this->data = value; }
    };

    class Welcome {
        public:
        Welcome() = default;
        virtual ~Welcome() = default;

        private:
        Level level;

        public:
        const Level & get_level() const { return level; }
        Level & get_mutable_level() { return level; }
        void set_level(const Level & value) { this->level = value; }
    };
}

namespace LevelFile {
    void from_json(const json & j, Color & x);
    void to_json(json & j, const Color & x);

    void from_json(const json & j, Coord & x);
    void to_json(json & j, const Coord & x);

    void from_json(const json & j, Column & x);
    void to_json(json & j, const Column & x);

    void from_json(const json & j, Lava & x);
    void to_json(json & j, const Lava & x);

    void from_json(const json & j, Portal & x);
    void to_json(json & j, const Portal & x);

    void from_json(const json & j, RespawnPoint & x);
    void to_json(json & j, const RespawnPoint & x);

    void from_json(const json & j, Terrain & x);
    void to_json(json & j, const Terrain & x);

    void from_json(const json & j, Data & x);
    void to_json(json & j, const Data & x);

    void from_json(const json & j, Level & x);
    void to_json(json & j, const Level & x);

    void from_json(const json & j, Welcome & x);
    void to_json(json & j, const Welcome & x);

    inline void from_json(const json & j, Color& x) {
        x.set_r(j.at("r").get<int64_t>());
        x.set_g(j.at("g").get<int64_t>());
        x.set_b(j.at("b").get<int64_t>());
    }

    inline void to_json(json & j, const Color & x) {
        j = json::object();
        j["r"] = x.get_r();
        j["g"] = x.get_g();
        j["b"] = x.get_b();
    }

    inline void from_json(const json & j, Coord& x) {
        x.set_x(j.at("x").get<int64_t>());
        x.set_y(j.at("y").get<int64_t>());
    }

    inline void to_json(json & j, const Coord & x) {
        j = json::object();
        j["x"] = x.get_x();
        j["y"] = x.get_y();
    }

    inline void from_json(const json & j, Column& x) {
        x.set_id(j.at("id").get<int64_t>());
        x.set_color(j.at("color").get<Color>());
        x.set_coord(j.at("coord").get<Coord>());
    }

    inline void to_json(json & j, const Column & x) {
        j = json::object();
        j["id"] = x.get_id();
        j["color"] = x.get_color();
        j["coord"] = x.get_coord();
    }

    inline void from_json(const json & j, Lava& x) {
        x.set_bottom(j.at("bottom").get<int64_t>());
        x.set_top(j.at("top").get<int64_t>());
        x.set_interval(j.at("interval").get<int64_t>());
    }

    inline void to_json(json & j, const Lava & x) {
        j = json::object();
        j["bottom"] = x.get_bottom();
        j["top"] = x.get_top();
        j["interval"] = x.get_interval();
    }

    inline void from_json(const json & j, Portal& x) {
        x.set_coord(j.at("coord").get<Coord>());
    }

    inline void to_json(json & j, const Portal & x) {
        j = json::object();
        j["coord"] = x.get_coord();
    }

    inline void from_json(const json & j, RespawnPoint& x) {
        x.set_id(j.at("id").get<int64_t>());
        x.set_coord(j.at("coord").get<Coord>());
    }

    inline void to_json(json & j, const RespawnPoint & x) {
        j = json::object();
        j["id"] = x.get_id();
        j["coord"] = x.get_coord();
    }

    inline void from_json(const json & j, Terrain& x) {
        x.set_heightmap(j.at("heightmap").get<std::string>());
        x.set_horizontal_texture(j.at("horizontal_texture").get<std::string>());
        x.set_vertical_texture(j.at("vertical_texture").get<std::string>());
    }

    inline void to_json(json & j, const Terrain & x) {
        j = json::object();
        j["heightmap"] = x.get_heightmap();
        j["horizontal_texture"] = x.get_horizontal_texture();
        j["vertical_texture"] = x.get_vertical_texture();
    }

    inline void from_json(const json & j, Data& x) {
        x.set_skybox(j.at("skybox").get<std::string>());
        x.set_terrain(j.at("terrain").get<Terrain>());
        x.set_lava(j.at("lava").get<Lava>());
        x.set_respawn_points(j.at("respawnPoints").get<std::vector<RespawnPoint>>());
        x.set_keys(j.at("keys").get<std::vector<Column>>());
        x.set_columns(j.at("columns").get<std::vector<Column>>());
        x.set_portal(j.at("portal").get<Portal>());
    }

    inline void to_json(json & j, const Data & x) {
        j = json::object();
        j["skybox"] = x.get_skybox();
        j["terrain"] = x.get_terrain();
        j["lava"] = x.get_lava();
        j["respawnPoints"] = x.get_respawn_points();
        j["keys"] = x.get_keys();
        j["columns"] = x.get_columns();
        j["portal"] = x.get_portal();
    }

    inline void from_json(const json & j, Level& x) {
        x.set_name(j.at("name").get<std::string>());
        x.set_id(j.at("id").get<std::string>());
        x.set_data(j.at("data").get<Data>());
    }

    inline void to_json(json & j, const Level & x) {
        j = json::object();
        j["name"] = x.get_name();
        j["id"] = x.get_id();
        j["data"] = x.get_data();
    }

    inline void from_json(const json & j, Welcome& x) {
        x.set_level(j.at("Level").get<Level>());
    }

    inline void to_json(json & j, const Welcome & x) {
        j = json::object();
        j["Level"] = x.get_level();
    }
}
