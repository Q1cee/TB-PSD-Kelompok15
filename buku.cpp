// buku.cpp - Modul Buku (F1): tambah, ubah, hapus, cari kode, tampil
#include <iostream>
#include <iomanip>
#include "sipus.h"

const string NAMA_KATEGORI[JML_KATEGORI] = {
    "Pemrograman", "Basis Data", "Jaringan", "Matematika", "Umum"};

// Pembesaran kapasitas: array baru 2x lebih besar, salin isi, hapus array lama
static void perbesar(DaftarBuku& d) {
    int kapasitasBaru = d.kapasitas * 2;
    Buku* baru = new Buku[kapasitasBaru];
    for (int i = 0; i < d.n; i++) baru[i] = d.data[i];
    delete[] d.data;
    d.data = baru;
    d.kapasitas = kapasitasBaru;
    cout << "[info] Kapasitas array buku membesar menjadi " << kapasitasBaru << "\n";
}

void inisialisasi(DaftarBuku& d, int kapasitasAwal) {
    if (kapasitasAwal < 1) kapasitasAwal = 1;
    if (kapasitasAwal > KAPASITAS_AWAL) kapasitasAwal = KAPASITAS_AWAL;
    d.data = new Buku[kapasitasAwal];
    d.n = 0;
    d.kapasitas = kapasitasAwal;
}

void bebaskan(DaftarBuku& d) {
    delete[] d.data;
    d.data = nullptr;
    d.n = 0;
    d.kapasitas = 0;
}

// Mengembalikan alamat record buku, atau nullptr jika kode tidak ada
Buku* cariKode(DaftarBuku& d, const string& kode) {
    for (int i = 0; i < d.n; i++)
        if (d.data[i].kode == kode) return &d.data[i];
    return nullptr;
}

bool tambahBuku(DaftarBuku& d, const Buku& b) {
    if (cariKode(d, b.kode) != nullptr) return false;  // kode harus unik
    if (d.n == d.kapasitas) perbesar(d);
    d.data[d.n] = b;
    d.n++;
    return true;
}

// Kode tidak diubah. totalDipinjam dan sedangDipinjam tetap dipertahankan
bool ubahBuku(DaftarBuku& d, const string& kode, const Buku& baru) {
    Buku* p = cariKode(d, kode);
    if (p == nullptr) return false;
    p->judul    = baru.judul;
    p->penulis  = baru.penulis;
    p->kategori = baru.kategori;
    p->tahun    = baru.tahun;
    p->stok     = baru.stok;
    return true;
}

bool hapusBuku(DaftarBuku& d, const string& kode) {
    int pos = -1;
    for (int i = 0; i < d.n && pos < 0; i++)
        if (d.data[i].kode == kode) pos = i;

    if (pos < 0) return false;                          // tidak ditemukan
    if (d.data[pos].sedangDipinjam > 0) return false;   // masih dipinjam

    for (int i = pos; i < d.n - 1; i++)                 // geser data ke kiri
        d.data[i] = d.data[i + 1];
    d.n--;
    return true;
}

void tampilBuku(const DaftarBuku& d) {
    if (d.n == 0) {
        cout << "Belum ada data buku.\n";
        return;
    }
    cout << left << setw(9) << "Kode" << setw(28) << "Judul" << setw(16) << "Penulis"
         << setw(13) << "Kategori" << setw(7) << "Tahun" << setw(6) << "Stok"
         << "Total Dipinjam\n";
    cout << string(92, '-') << "\n";
    for (int i = 0; i < d.n; i++) {
        const Buku& b = d.data[i];
        cout << left << setw(9) << b.kode << setw(28) << b.judul << setw(16) << b.penulis
             << setw(13) << NAMA_KATEGORI[b.kategori] << setw(7) << b.tahun
             << setw(6) << b.stok << b.totalDipinjam << "\n";
    }
    cout << "Total: " << d.n << " judul buku\n";
}
