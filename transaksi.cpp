// transaksi.cpp - Modul Transaksi (baru alokasi dan pembebasan memori)
// pinjamBuku, kembalikanBuku, total denda, dan rekap dikerjakan di Milestone 3.
#include "sipus.h"

void inisialisasi(DaftarTransaksi& d, int kapasitasAwal) {
    if (kapasitasAwal < 1) kapasitasAwal = 1;
    if (kapasitasAwal > KAPASITAS_AWAL) kapasitasAwal = KAPASITAS_AWAL;
    d.data = new Transaksi[kapasitasAwal];
    d.n = 0;
    d.kapasitas = kapasitasAwal;
}

void bebaskan(DaftarTransaksi& d) {
    delete[] d.data;
    d.data = nullptr;
    d.n = 0;
    d.kapasitas = 0;
}
