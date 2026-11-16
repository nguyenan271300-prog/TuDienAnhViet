#include "../include/Utils.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>

namespace Utils {

bool isPrime(std::size_t n) {
    if (n < 2) return false;
    if (n < 4) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (std::size_t i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

std::string toLower(const std::string& s) {
    std::string r = s;
    std::transform(r.begin(), r.end(), r.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return r;
}

std::string toUpper(const std::string& s) {
    std::string r = s;
    std::transform(r.begin(), r.end(), r.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return r;
}

std::string trim(const std::string& s) {
    std::size_t b = 0, e = s.size();
    while (b < e && std::isspace(static_cast<unsigned char>(s[b]))) ++b;
    while (e > b && std::isspace(static_cast<unsigned char>(s[e - 1]))) --e;
    return s.substr(b, e - b);
}

std::string normalize(const std::string& s) {
    std::string t = trim(s);
    std::string out;
    out.reserve(t.size());
    bool lastSpace = false;
    for (unsigned char c : t) {
        if (std::isspace(c)) {
            if (!lastSpace) { out.push_back(' '); lastSpace = true; }
        } else {
            out.push_back(static_cast<char>(std::tolower(c)));
            lastSpace = false;
        }
    }
    return out;
}

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> out;
    std::string token;
    std::istringstream iss(s);
    while (std::getline(iss, token, delimiter)) out.push_back(token);
    return out;
}

std::string join(const std::vector<std::string>& parts, const std::string& sep) {
    std::string out;
    for (std::size_t i = 0; i < parts.size(); ++i) {
        if (i) out += sep;
        out += parts[i];
    }
    return out;
}

bool isBlank(const std::string& s) {
    for (unsigned char c : s)
        if (!std::isspace(c)) return false;
    return true;
}

std::vector<std::string> readLines(const std::string& path) {
    std::vector<std::string> lines;
    std::ifstream in(path);
    if (!in) return lines;
    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        lines.push_back(line);
    }
    return lines;
}

bool writeLines(const std::string& path, const std::vector<std::string>& lines) {
    std::ofstream out(path);
    if (!out) return false;
    for (const auto& l : lines) out << l << '\n';
    return true;
}

} // namespace Utils