#ifndef WORD_H
#define WORD_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "Utils.h"

struct Word {
    std::string word;
    std::string pos;
    std::string pronunciation;
    std::string meaning;
    std::string example;
    int flag = 0;

    // Đọc từ 1 dòng TSV
    static bool fromLine(const std::string& line, Word& out) {
        if (line.empty()) return false;
        auto cols = Utils::split(line, '\t');
        if (cols.size() < 6) return false;

        out.word          = Utils::trim(cols[0]);
        out.pos           = Utils::trim(cols[1]);
        out.pronunciation = Utils::trim(cols[2]);
        out.meaning       = Utils::trim(cols[3]);
        out.example       = Utils::trim(cols[4]);
        try { out.flag    = std::stoi(Utils::trim(cols[5])); }
        catch (...) { out.flag = 0; }
        
        return !out.word.empty();
    }

    // Xuất ra dòng TSV
    std::string toLine() const {
        return word + "\t" + pos + "\t" + pronunciation + "\t" + 
               meaning + "\t" + example + "\t" + std::to_string(flag);
    }

    // In ra màn hình
    void print() const {
        std::cout << "Từ          : " << word << "\n"
                  << "Từ loại     : " << pos << "\n"
                  << "Phiên âm    : " << pronunciation << "\n"
                  << "Nghĩa       : " << meaning << "\n"
                  << "Ví dụ       : " << example << "\n"
                  << "Đã đánh dấu : " << (flag ? "Có" : "Không") << "\n";
    }
};

#endif // WORD_H