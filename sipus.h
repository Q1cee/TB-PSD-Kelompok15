// sipus.h - definisi tipe data dan prototipe fungsi SiPus
// Kelompok: 15 | Qays Huraibi (260530911095)
#ifndef SIPUS_H
#define SIPUS_H

#include <string>
using namespace std;

const int JML_KATEGORI = 5;    // Ukuran baris rekap
const int JML_BULAN    = 12;   // Ukuran kolom rekap
const int MAKS_PINJAM  = 3;    // Batas buku per anggota
const int DENDA_HARIAN = 1000; // Rupiah per hari
const int KAPASITAS_AWAL = 4;  // Kapasitas awal maksimal array dinamis

struct Tanggal {
    int hari, bulan, tahun;
};

struct Buku {
    string kode;               // Format "BK-001"
    string judul;
    string penulis;
    int kategori;              // 0..JML_KATEGORI-1
    int tahun;
    int stok;                  // Eksemplar tersedia
    int totalDipinjam;         // Untuk statistik (tidak pernah berkurang)
    int sedangDipinjam = 0;    // TAMBAHAN: eksemplar yang belum dikembalikan
};

struct Anggota {
    string id;                 // Format "AG-001"
    string nama;
    string prodi;
    int sedangPinjam;          // Maksimum MAKS_PINJAM
};

struct Transaksi {
    int nomor;
    string idAnggota;
    string kodeBuku;
    Tanggal tglPinjam;
    Tanggal tglKembali;        // Diisi saat buku kembali
    bool selesai;
    int denda;
};

// Pembungkus array dinamis: alamat, isi, kapasitas
struct DaftarBuku {
    Buku* data; int n, kapasitas;
};
struct DaftarAnggota {
    Anggota* data; int n, kapasitas;
};
struct DaftarTransaksi {
    Transaksi* data; int n, kapasitas;
};

// Nama kategori (indeks 0..4), didefinisikan di buku.cpp
extern const string NAMA_KATEGORI[JML_KATEGORI];

// ---- Utilitas masukan (util.cpp) ----
int    bacaInt(const string& prompt, int minVal, int maxVal);
string bacaTeks(const string& prompt);
string bacaKode(const string& prompt, const string& awalan); // "BK-" atau "AG-"
bool   formatKodeValid(const string& s, const string& awalan);

// ---- Modul Buku (Mahasiswa A) : F1 ----
void  inisialisasi(DaftarBuku& d, int kapasitasAwal);
void  bebaskan(DaftarBuku& d);
bool  tambahBuku(DaftarBuku& d, const Buku& b);
bool  ubahBuku(DaftarBuku& d, const string& kode, const Buku& baru);
bool  hapusBuku(DaftarBuku& d, const string& kode);
Buku* cariKode(DaftarBuku& d, const string& kode);
void  tampilBuku(const DaftarBuku& d);

// ---- Modul Anggota (Mahasiswa B) : F2 ----
void     inisialisasi(DaftarAnggota& d, int kapasitasAwal);
void     bebaskan(DaftarAnggota& d);
bool     tambahAnggota(DaftarAnggota& d, const Anggota& a);
bool     ubahAnggota(DaftarAnggota& d, const string& id,
                     const string& namaBaru, const string& prodiBaru);
Anggota* cariAnggota(DaftarAnggota& d, const string& id);
void     tampilAnggota(const DaftarAnggota& d);

// ---- Modul Transaksi (Mahasiswa B) : alokasi memori saja ----
void inisialisasi(DaftarTransaksi& d, int kapasitasAwal);
void bebaskan(DaftarTransaksi& d);

// ---- Menyusul (Milestone 3 dan 4) ----
// bool pinjamBuku(DaftarTransaksi& t, DaftarBuku& b, DaftarAnggota& a,
//                 const string& idAg, const string& kodeBk, const Tanggal& tgl);
// bool kembalikanBuku(DaftarTransaksi& t, DaftarBuku& b, DaftarAnggota& a,
//                     int nomor, const Tanggal& tgl);
// int  selisihHari(const Tanggal& awal, const Tanggal& akhir);
// int  totalDendaRekursif(const Transaksi arr[], int n);
// void isiRekap(const DaftarTransaksi& t, const DaftarBuku& b, int rekap[][JML_BULAN]);
// void tampilRekap(const int rekap[][JML_BULAN], const string namaKategori[]);
// void cariJudul(const DaftarBuku& d, const string& kata);
// void urutkanKode(DaftarBuku& d);
// int  binarySearchKode(const Buku arr[], int kiri, int kanan, const string& kode);

#endif
