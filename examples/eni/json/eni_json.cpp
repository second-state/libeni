/*==- examples/eni/reverse/eni_reverse.cpp ---------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include <eni.h>
#include <json/Parser.h>

#include "jsmn/jsmn.h"

namespace {
std::string parseString(const std::string& raw) { return json::Parser(raw).getRoot().toString(); }
std::vector<jsmntok_t> internalParse(const char* data, int start, int end) {
    jsmn_parser p;
    p.pos = start;
    p.toknext = 0;
    p.toksuper = -1;
    int len = jsmn_parse(&p, data, end, 0, 0);
    std::vector<jsmntok_t> result(len);
    p.pos = start;
    p.toknext = 0;
    p.toksuper = -1;
    jsmn_parse(&p, data, end, result.data(), len);
    return result;
}
std::string encodeToken(const jsmntok_t& tok) {
    union {
        char s[8];
        uint32_t v[2];
    };
    v[0] = htobe32(tok.start - (tok.type == JSMN_STRING));
    v[1] = htobe32(tok.end + (tok.type == JSMN_STRING));
    return std::string(s, 8);
}
std::vector<jsmntok_t> arrayTokens(const char* data, int start, int end) {
    auto tokens = internalParse(data, start, end);
    std::vector<jsmntok_t> result;
    int after = tokens[0].start;
    int before = tokens[0].end;
    for (int i = 1; i < tokens.size(); i++) {
        if (tokens[i].start < after) {
            continue;
        }
        if (tokens[i].start > before) {
            break;
        }
        result.push_back(tokens[i]);
        after = tokens[i].end;
    }
    return result;
}
std::string parseArray(const char* data, int start, int end) {
    std::string result;
    for (const auto& tok: arrayTokens(data, start, end)) {
        result += encodeToken(tok);
    }
    return result;
}
std::string arrayGet(const char* data, int start, int end, int index) {
    auto tokens = arrayTokens(data, start, end);
    return encodeToken(tokens[index]);
}

std::map<std::string, jsmntok_t> objectTokens(const char* data, int start, int end) {
    auto tokens = internalParse(data, start, end);
    std::map<std::string, jsmntok_t> result;
    int after = tokens[0].start;
    int before = tokens[0].end;
    int key_token = 0;
    auto getkey = [&] {
        auto& tok = tokens[key_token];
        return parseString(std::string(data + tok.start - 1, data + tok.end + 1));
    };
    for (int i = 1; i < tokens.size(); i++) {
        if (tokens[i].start < after) {
            continue;
        }
        if (tokens[i].start > before) {
            break;
        }
        if (key_token == 0) {
            key_token = i;
        } else {
            result[getkey()] = tokens[i];
        }
        after = tokens[i].end;
    }
    return result;
}

std::string objectGet(const char* data, int start, int end, const std::string& key) {
    auto tokens = objectTokens(data, start, end);
    return encodeToken(tokens[key]);
}
}  // namespace

class JSON : public eni::EniBase {
public:
    JSON(const std::string& pArgStr) : eni::EniBase(pArgStr) {}

    ~JSON() {}

private:
    bool parse(const json::Array& pArgs) override {
        std::string op = pArgs[0].toString();
        std::string data = pArgs[1].toString();
        int begin = (int)pArgs[2].toInteger();
        int end = (int)pArgs[3].toInteger();
        if (op == "parseString") {
            m_Str = parseString(std::string(data.data(), begin, end));
        } else if (op == "parseArray") {
            m_Str = parseArray(data.data(), begin, end);
        } else if (op == "arrayGet") {
            m_Str = arrayGet(data.data(), begin, end, (int)pArgs[4].toInteger());
        } else if (op == "objectGet") {
            m_Str = objectGet(data.data(), begin, end, pArgs[4].toString());
        } else {
            return false;
        }
        return true;
    }

    eni::Gas gas() const override { return m_Str.length() * 10; }

    bool run(json::Array& pRetVal) override {
        pRetVal.emplace_back(m_Str);
        return true;
    }

private:
    std::string m_Str;
};

ENI_C_INTERFACE(json, JSON)
