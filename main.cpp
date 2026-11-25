// main.cpp - program utama SiPus (menu). Milestone 1-2: F1 dan F2
#include <iostream>
#include "sipus.h"

static void tampilPilihanKategori() {
    for (int i = 0; i < JML_KATEGORI; i++)
        cout << "  " << (i + 1) << ". " << NAMA_KATEGORI[i] << "\n";
}

// Mengisi data buku dari pengguna (dipakai oleh menu tambah dan menu ubah)
static void isiDataBuku(Buku& b, const string& akhiran) {
    b.judul    = bacaTeks("Judul" + akhiran + " : ");
    b.penulis  = bacaTeks("Penulis" + akhiran + " : ");
    tampilPilihanKategori();
    b.kategori = bacaInt("Kategori (1-5) : ", 1, JML_KATEGORI) - 1;
    b.tahun    = bacaInt("Tahun terbit : ", 1000, 2100);
    b.stok     = bacaInt("Stok : ", 0, 1000);
}

static void menuTambahBuku(DaftarBuku& d) {
    string kode = bacaKode("Kode buku (BK-xxx): ", "BK-");
    if (kode.empty()) return;
    if (cariKode(d, kode) != nullptr) {
        cout << ">> Gagal. Kode " << kode << " sudah dipakai.\n";
        return;
    }
    Buku b;
    b.kode = kode;
    isiDataBuku(b, "");
    b.totalDipinjam = 0;
    b.sedangDipinjam = 0;
    if (tambahBuku(d, b)) cout << ">> Buku berhasil ditambahkan.\n";
    else cout << ">> Gagal menambahkan buku.\n";
}

static void menuUbahBuku(DaftarBuku& d) {
    string kode = bacaKode("Kode buku yang diubah: ", "BK-");
    if (kode.empty()) return;
    Buku* p = cariKode(d, kode);
    if (p == nullptr) {
        cout << ">> Buku tidak ditemukan.\n";
        return;
    }
    cout << "Mengubah: " << p->judul << " (isi ulang semua data)\n";
    Buku b = *p;
    isiDataBuku(b, " baru");
    ubahBuku(d, kode, b);
    cout << ">> Data buku berhasil diubah.\n";
}

static void menuHapusBuku(DaftarBuku& d) {
    string kode = bacaKode("Kode buku yang dihapus: ", "BK-");
    if (kode.empty()) return;
    Buku* p = cariKode(d, kode);
    if (p == nullptr) {
        cout << ">> Buku tidak ditemukan.\n";
        return;
    }
    if (p->sedangDipinjam > 0) {
        cout << ">> Gagal. Buku masih dipinjam, tidak boleh dihapus.\n";
        return;
    }
    if (bacaInt("Yakin hapus \"" + p->judul + "\"? (1=Ya, 0=Batal): ", 0, 1) == 1) {
        hapusBuku(d, kode);
        cout << ">> Buku dihapus.\n";
    } else {
        cout << ">> Dibatalkan.\n";
    }
}

static void menuBuku(DaftarBuku& d) {
    int pilih;
    do {
        cout << "\n--- Kelola Buku ---\n"
             << "1. Tambah  2. Ubah  3. Hapus  4. Tampilkan  0. Kembali\n";
        pilih = bacaInt("Pilihan: ", 0, 4);
        switch (pilih) {
            case 1: menuTambahBuku(d); break;
            case 2: menuUbahBuku(d);   break;
            case 3: menuHapusBuku(d);  break;
            case 4: tampilBuku(d);     break;
        }
    } while (pilih != 0);
}

static void menuTambahAnggota(DaftarAnggota& d) {
    string id = bacaKode("ID anggota (AG-xxx): ", "AG-");
    if (id.empty()) return;
    if (cariAnggota(d, id) != nullptr) {
        cout << ">> Gagal. ID " << id << " sudah dipakai.\n";
        return;
    }
    Anggota a;
    a.id = id;
    a.nama = bacaTeks("Nama : ");
    a.prodi = bacaTeks("Prodi : ");
    a.sedangPinjam = 0;
    if (tambahAnggota(d, a)) cout << ">> Anggota berhasil ditambahkan.\n";
    else cout << ">> Gagal menambahkan anggota.\n";
}

static void menuUbahAnggota(DaftarAnggota& d) {
    string id = bacaKode("ID anggota yang diubah: ", "AG-");
    if (id.empty()) return;
    Anggota* p = cariAnggota(d, id);
    if (p == nullptr) {
        cout << ">> Anggota tidak ditemukan.\n";
        return;
    }
    cout << "Mengubah: " << p->nama << "\n";
    string nama  = bacaTeks("Nama baru : ");
    string prodi = bacaTeks("Prodi baru : ");
    ubahAnggota(d, id, nama, prodi);
    cout << ">> Data anggota berhasil diubah.\n";
}

static void menuAnggota(DaftarAnggota& d) {
    int pilih;
    do {
        cout << "\n--- Kelola Anggota ---\n"
             << "1. Tambah  2. Ubah  3. Tampilkan  0. Kembali\n";
        pilih = bacaInt("Pilihan: ", 0, 3);
        switch (pilih) {
            case 1: menuTambahAnggota(d); break;
            case 2: menuUbahAnggota(d);   break;
            case 3: tampilAnggota(d);     break;
        }
    } while (pilih != 0);
}

int main() {
    DaftarBuku buku;
    DaftarAnggota anggota;
    DaftarTransaksi transaksi;
    inisialisasi(buku, 4);       // kapasitas awal kecil agar pembesaran teruji
    inisialisasi(anggota, 4);
    inisialisasi(transaksi, 4);

    int pilihan;
    do {
        cout << "\n===== SiPus: Perpustakaan Mini =====\n"
             << "1. Kelola Buku      5. Kembalikan Buku\n"
             << "2. Kelola Anggota   6. Cari Buku\n"
             << "3. Daftar Buku      7. Laporan Bulanan\n"
             << "4. Pinjam Buku      0. Keluar\n";
        pilihan = bacaInt("Pilihan: ", 0, 7);
        switch (pilihan) {
            case 1: menuBuku(buku);       break;
            case 2: menuAnggota(anggota); break;
            case 3: tampilBuku(buku);     break;
            case 4: case 5: case 6: case 7:
                cout << ">> Fitur ini dikerjakan pada milestone berikutnya.\n";
                break;
        }
    } while (pilihan != 0);

    bebaskan(buku);
    bebaskan(anggota);
    bebaskan(transaksi);
    cout << "Sampai jumpa!\n";
    return 0;
}
