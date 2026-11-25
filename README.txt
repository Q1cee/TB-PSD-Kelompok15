SiPus - Sistem Peminjaman Perpustakaan Mini
Kelompok : 15   Kelas : Pemrograman dan Struktur Data Kelas E
Anggota  : Qays Huraibi / 260530911095
Repo Git : https://github.com/Q1cee/TB-PSD-Kelompok15.git

Kompilasi (C++17, tanpa warning):
  g++ -std=c++17 -Wall -o sipus main.cpp buku.cpp anggota.cpp transaksi.cpp util.cpp

Kompilasi + cek memori (AddressSanitizer):
  g++ -std=c++17 -Wall -g -fsanitize=address -o sipus main.cpp buku.cpp anggota.cpp transaksi.cpp util.cpp

Jalankan:
  ./sipus   (Windows: sipus.exe)

Status: Milestone 1-2 -> F1 (kelola buku) dan F2 (kelola anggota) berfungsi.