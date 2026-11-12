#ifndef HISTORY_H
#define HISTORY_H

#include <cstddef>
#include <string>
#include <vector>

class History {
private:
    std::vector<std::string> searches;
    std::size_t maxItems;

public:
    explicit History(std::size_t limit = 20);

    // Them tu vua duoc tim vao dau danh sach lich su.
    void addSearch(const std::string& english);

    // In lich su tu moi nhat den cu nhat.
    void display() const;

    void clear();
    bool isEmpty() const;
    std::size_t size() const;
};

#endif
