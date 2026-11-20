#ifndef WORD_H
#define WORD_H
#include <string>
#include <iostream>
#include "Utils.h"
using namespace std;

struct Word {
    string word;
    string pos;
    string pronunciation;
    string meaning;
    string example;
    int flag;

    Word() : flag(0) {}
    static bool fromLine(const string& line, Word& result) {
        if (line.empty()) return false;
        string fields[6];
        int field = 0;
        size_t start = 0;
        for (size_t i = 0; i <= line.size() && field < 6; ++i) {
            if (i == line.size() || line[i] == '\t') {
                fields[field++] = line.substr(start, i - start);
                start = i + 1;
            }
        }
        if (field < 6) return false;
        result.word = Utils::trim(fields[0]);
        result.pos = Utils::trim(fields[1]);
        result.pronunciation = Utils::trim(fields[2]);
        result.meaning = Utils::trim(fields[3]);
        result.example = Utils::trim(fields[4]);
        result.flag = (Utils::trim(fields[5]) == "1") ? 1 : 0;
        return !result.word.empty();
    }
    string toLine() const {
        return word + "\t" + pos + "\t" + pronunciation + "\t" + meaning + "\t" + example + "\t" + to_string(flag);
    }
    void print() const {
        cout << "\nTu: " << word << "\nTu loai: " << pos
             << "\nPhien am: " << pronunciation << "\nNghia: " << meaning
             << "\nVi du: " << example << "\nYeu thich: " << (flag ? "Co" : "Khong") << '\n';
    }
};
#endif
