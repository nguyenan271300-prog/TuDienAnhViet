#include "History.h"

#include <iostream>

History::History(std::size_t limit) : maxItems(limit) {}

void History::addSearch(const std::string& english) {
    if (english.empty() || maxItems == 0) return;

    // Dua tu moi nhat len dau danh sach.
    searches.insert(searches.begin(), english);

    // Chi giu toi da maxItems muc gan nhat.
    if (searches.size() > maxItems) {
        searches.pop_back();
    }
}

void History::display() const {
    if (isEmpty()) {
        std::cout << "Chua co lich su tim kiem.\n";
        return;
    }

    std::cout << "Lich su tim kiem (moi nhat truoc):\n";
    for (std::size_t i = 0; i < searches.size(); ++i) {
        std::cout << i + 1 << ". " << searches[i] << '\n';
    }
}

void History::clear() {
    searches.clear();
}

bool History::isEmpty() const {
    return searches.empty();
}

std::size_t History::size() const {
    return searches.size();
}
