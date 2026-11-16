#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <cstddef>

namespace Utils {

    // ----- Số học -----
    bool isPrime(std::size_t n);

    // ----- Xử lý chuỗi -----
    std::string toLower(const std::string& s);
    std::string toUpper(const std::string& s);
    std::string trim(const std::string& s);
    std::string normalize(const std::string& s); // trim + lower + gộp khoảng trắng

    // Tách chuỗi theo delimiter
    std::vector<std::string> split(const std::string& s, char delimiter);

    // Ghép vector<string> thành 1 chuỗi
    std::string join(const std::vector<std::string>& parts, const std::string& sep);

    // Kiểm tra chuỗi rỗng hoặc chỉ gồm khoảng trắng
    bool isBlank(const std::string& s);

    // ----- Xử lý file -----
    std::vector<std::string> readLines(const std::string& path);
    bool writeLines(const std::string& path, const std::vector<std::string>& lines);

} // namespace Utils

#endif // UTILS_H