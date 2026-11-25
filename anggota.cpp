// anggota.cpp - Modul Anggota (F2): tambah, ubah, cari, tampil
#include <iostream>
#include <iomanip>
#include "sipus.h"

static void perbesar(DaftarAnggota& d) {
    int kapasitasBaru = d.kapasitas * 2;
    Anggota* baru = new Anggota[kapasitasBaru];
    for (int i = 0; i < d.n; i++) baru[i] = d.data[i];
    delete[] d.data;
    d.data = baru;
    d.kapasitas = kapasitasBaru;
    cout << "[info] Kapasitas array anggota membesar menjadi " << kapasitasBaru << "\n";
}

void inisialisasi(DaftarAnggota& d, int kapasitasAwal) {
    if (kapasitasAwal < 1) kapasitasAwal = 1;
    if (kapasitasAwal > KAPASITAS_AWAL) kapasitasAwal = KAPASITAS_AWAL;
    d.data = new Anggota[kapasitasAwal];
    d.n = 0;
    d.kapasitas = kapasitasAwal;
}

void bebaskan(DaftarAnggota& d) {
    delete[] d.data;
    d.data = nullptr;
    d.n = 0;
    d.kapasitas = 0;
}

Anggota* cariAnggota(DaftarAnggota& d, const string& id) {
    for (int i = 0; i < d.n; i++)
        if (d.data[i].id == id) return &d.data[i];
    return nullptr;
}

bool tambahAnggota(DaftarAnggota& d, const Anggota& a) {
    if (cariAnggota(d, a.id) != nullptr) return false;  // ID harus unik
    if (d.n == d.kapasitas) perbesar(d);
    d.data[d.n] = a;
    d.n++;
    return true;
}

bool ubahAnggota(DaftarAnggota& d, const string& id,
                 const string& namaBaru, const string& prodiBaru) {
    Anggota* p = cariAnggota(d, id);
    if (p == nullptr) return false;
    p->nama  = namaBaru;
    p->prodi = prodiBaru;
    return true;
}

void tampilAnggota(const DaftarAnggota& d) {
    if (d.n == 0) {
        cout << "Belum ada data anggota.\n";
        return;
    }
    cout << left << setw(9) << "ID" << setw(26) << "Nama" << setw(22) << "Prodi"
         << "Sedang Pinjam\n";
    cout << string(70, '-') << "\n";
    for (int i = 0; i < d.n; i++) {
        const Anggota& a = d.data[i];
        cout << left << setw(9) << a.id << setw(26) << a.nama << setw(22) << a.prodi
             << a.sedangPinjam << "/" << MAKS_PINJAM << "\n";
    }
    cout << "Total: " << d.n << " anggota\n";
}
