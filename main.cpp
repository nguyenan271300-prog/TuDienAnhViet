#include <iostream>
#include <string>
#include "include/Dictionary.h"
#include "include/Utils.h"
using namespace std;

void showMenu() {
    cout << "\n========== TU DIEN ANH - VIET ==========\n"
         << "1. Tra tu\n2. Them tu moi\n3. Sua thong tin tu\n4. Xoa tu\n"
         << "5. Goi y tu theo tien to\n6. Danh dau / bo danh dau yeu thich\n"
         << "7. Xem danh sach tu yeu thich\n8. Xem lich su tra tu\n"
         << "9. Liet ke tat ca tu (A-Z)\n10. Thong ke bang bam\n11. Thuc nghiem so sanh AVL va Hash\n"
         << "0. Luu va thoat\nLua chon: ";
}
Word inputWord() {
    Word w;
    cout << "Tu tieng Anh: "; getline(cin, w.word);
    cout << "Tu loai: "; getline(cin, w.pos);
    cout << "Phien am: "; getline(cin, w.pronunciation);
    cout << "Nghia tieng Viet: "; getline(cin, w.meaning);
    cout << "Vi du: "; getline(cin, w.example);
    w.flag = 0;
    return w;
}
int main() {
    Dictionary dictionary("data/dictionary.txt");
    if (!dictionary.load()) {
        cout << "Khong mo duoc data/dictionary.txt. Hay chay chuong trinh tu thu muc project.\n";
    } else {
        cout << "Da nap " << dictionary.size() << " tu.\n";
    }
    int choice;
    do {
        showMenu();
        if (!(cin >> choice)) { cin.clear(); cin.ignore(10000, '\n'); choice = -1; }
        cin.ignore(10000, '\n');
        string key;
        Word item;
        switch (choice) {
        case 1:
            cout << "Nhap tu can tra: "; getline(cin, key);
            if (dictionary.findWord(key, item)) item.print();
            else cout << "Khong tim thay tu.\n";
            break;
        case 2:
            item = inputWord();
            if (dictionary.addWord(item)) cout << "Them tu thanh cong.\n";
            else cout << "Tu da ton tai hoac du lieu khong hop le.\n";
            break;
        case 3:
            cout << "Nhap tu can sua: "; getline(cin, key);
            if (!dictionary.findWord(key, item, false)) { cout << "Khong tim thay tu.\n"; break; }
            cout << "Nhap thong tin moi (tu tieng Anh se duoc giu nguyen):\n";
            { Word updated = inputWord();
              if (dictionary.updateWord(key, updated)) cout << "Cap nhat thanh cong.\n";
              else cout << "Cap nhat that bai.\n"; }
            break;
        case 4:
            cout << "Nhap tu can xoa: "; getline(cin, key);
            cout << (dictionary.deleteWord(key) ? "Da xoa tu.\n" : "Khong tim thay tu.\n");
            break;
        case 5:
            cout << "Nhap tien to: "; getline(cin, key); dictionary.suggestPrefix(key); break;
        case 6:
            cout << "Nhap tu: "; getline(cin, key);
            cout << (dictionary.toggleFavorite(key) ? "Da thay doi trang thai yeu thich.\n" : "Khong tim thay tu.\n");
            break;
        case 7: dictionary.showFavoriteWords(); break;
        case 8: dictionary.showHistory(); break;
        case 9: dictionary.showAll(); break;
        case 10: dictionary.showHashStats(); break;
        case 11: dictionary.comparePerformance(); break;
        case 0:
            if (dictionary.save()) cout << "Da luu tu dien. Tam biet!\n";
            else cout << "Loi: khong the luu tep tu dien.\n";
            break;
        default: cout << "Lua chon khong hop le.\n";
        }
    } while (choice != 0);
    return 0;
}
