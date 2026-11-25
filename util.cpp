// util.cpp - fungsi bantu untuk membaca masukan dengan validasi
#include <iostream>
#include <cctype>
#include "sipus.h"

// Membuang spasi di awal dan akhir teks
static string rapikan(const string& s) {
    size_t awal = s.find_first_not_of(" \t\r\n");
    if (awal == string::npos) return "";
    size_t akhir = s.find_last_not_of(" \t\r\n");
    return s.substr(awal, akhir - awal + 1);
}

// Format kode: awalan + tepat 3 angka, contoh "BK-001"
bool formatKodeValid(const string& s, const string& awalan) {
    if (s.size() != awalan.size() + 3) return false;
    if (s.compare(0, awalan.size(), awalan) != 0) return false;
    for (size_t i = awalan.size(); i < s.size(); i++)
        if (!isdigit((unsigned char)s[i])) return false;
    return true;
}

// Membaca satu baris sebagai teks, lalu memeriksa isinya angka dan dalam rentang
int bacaInt(const string& prompt, int minVal, int maxVal) {
    while (true) {
        cout << prompt;
        string s;
        if (!getline(cin, s)) return minVal;   // masukan habis (EOF)
        s = rapikan(s);

        bool angka = !s.empty() && s.size() <= 9;
        for (size_t i = 0; angka && i < s.size(); i++)
            if (!isdigit((unsigned char)s[i])) angka = false;

        if (angka) {
            int nilai = stoi(s);
            if (nilai >= minVal && nilai <= maxVal) return nilai;
        }
        cout << ">> Masukan harus angka " << minVal << " sampai " << maxVal << ".\n";
    }
}

// Membaca teks yang tidak boleh kosong
string bacaTeks(const string& prompt) {
    while (true) {
        cout << prompt;
        string s;
        if (!getline(cin, s)) return "";       // masukan habis (EOF)
        s = rapikan(s);
        if (!s.empty()) return s;
        cout << ">> Tidak boleh kosong.\n";
    }
}

// Membaca kode berformat benar; huruf kecil otomatis diubah jadi huruf besar
string bacaKode(const string& prompt, const string& awalan) {
    while (true) {
        string s = bacaTeks(prompt);
        if (s.empty()) return "";              // masukan habis (EOF)
        for (size_t i = 0; i < s.size(); i++)
            s[i] = (char)toupper((unsigned char)s[i]);
        if (formatKodeValid(s, awalan)) return s;
        cout << ">> Format salah. Contoh: " << awalan << "001\n";
    }
}
