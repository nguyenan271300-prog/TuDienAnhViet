#include <iostream>
#include <string>
#include "include/HashTable.h"
#include "include/Word.h"
#include "include/Utils.h"
int main() {
    std::cout << "Bat dau chuong trinh...\n";

    HashTable dict(101);
    std::cout << "Khoi tao HashTable thanh cong!\n";

    // Nạp dữ liệu
    auto lines = Utils::readLines("data/dictionary.txt");
    int count = 0;
    for (const auto& line : lines) {
        if (Utils::isBlank(line)) continue;
        
        Word w;
        if (Word::fromLine(line, w)) {
            dict.insert(Utils::normalize(w.word), w);
            count++;
        }
    }
    std::cout << "Da nap " << count << " tu vao HashTable.\n";
    
    // In thống kê
    dict.printStats();

    return 0;
}