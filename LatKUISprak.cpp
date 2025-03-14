#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Buku {
    int id;
    string judul;
    string penulis;
    int stok;
};

const int MAX_BUKU = 100;
Buku bukuList[MAX_BUKU];
int jumlahBuku = 0;

bool login() {
    string username, password;
    while (true) {
        cout << "Masukkan username: ";
        cin >> username;
        cout << "Masukkan password: ";
        cin >> password;
        if (username == "nathiq" && password == "141") {
            return true;
        } else {
            cout << "Username atau Password Salah." << endl;
        }
    }
}

void tambahBuku() {
    if (jumlahBuku >= MAX_BUKU) {
        cout << "Kapasitas buku penuh." << endl;
        return;
    }

    Buku buku;
    cout << "===== Tambah Data Buku =====" << endl;
    cout << "Masukkan ID buku: ";
    cin >> buku.id;
    cin.ignore();
    cout << "Masukkan judul buku: ";
    getline(cin, buku.judul);
    cout << "Masukkan penulis buku: ";
    getline(cin, buku.penulis);
    cout << "Masukkan stok buku: ";
    cin >> buku.stok;
    bukuList[jumlahBuku++] = buku;

    ofstream file("data.dat", ios::app);
    file << buku.id << "|" << buku.judul << "|" << buku.penulis << "|" << buku.stok << endl;
    file.close();

    cout << "Buku berhasil ditambahkan!" << endl;
}

void tampilkanBuku() {
    ifstream file("data.dat");
    jumlahBuku = 0;
    Buku buku;
    while (file >> buku.id) {
        file.ignore();
        getline(file, buku.judul, '|');
        getline(file, buku.penulis, '|');
        file >> buku.stok;
        bukuList[jumlahBuku++] = buku;
    }
    file.close();

    for (int i = 0; i < jumlahBuku - 1; ++i) {
        for (int j = 0; j < jumlahBuku - i - 1; ++j) {
            if (bukuList[j].id > bukuList[j + 1].id) {
              // Menukar elemen menggunakan variabel sementara
              Buku temp = bukuList[j];
              bukuList[j] = bukuList[j + 1];
              bukuList[j + 1] = temp;
          }
      }
  }

    cout << "ID\tJudul\tPenulis\tStok" << endl;
    for (int i = 0; i < jumlahBuku; ++i) {
        cout << bukuList[i].id << "\t" << bukuList[i].judul << "\t" << bukuList[i].penulis << "\t" << bukuList[i].stok << endl;
    }
}

void cariBuku() {
    string kataKunci;
    cout << "Masukkan kata kunci judul buku: ";
    cin.ignore();
    getline(cin, kataKunci);

    bool ditemukan = false;
    for (int i = 0; i < jumlahBuku; ++i) {
        if (bukuList[i].judul.find(kataKunci) != string::npos) {
            cout << "ID: " << bukuList[i].id << ", Judul: " << bukuList[i].judul << ", Penulis: " << bukuList[i].penulis << ", Stok: " << bukuList[i].stok << endl;
            ditemukan = true;
        }
    }
    if (!ditemukan) {
        cout << "Buku tidak ditemukan." << endl;
    }
}

void hapusBuku() {
    int id;
    cout << "Masukkan ID buku yang akan dihapus: ";
    cin >> id;

    int index = -1;
    for (int i = 0; i < jumlahBuku; ++i) {
        if (bukuList[i].id == id) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        for (int i = index; i < jumlahBuku - 1; ++i) {
            bukuList[i] = bukuList[i + 1];
        }
        jumlahBuku;

        ofstream file("data.dat");
        for (int i = 0; i < jumlahBuku; ++i) {
            file << bukuList[i].id << "|" << bukuList[i].judul << "|" << bukuList[i].penulis << "|" << bukuList[i].stok << endl;
        }
        file.close();
        cout << "Buku berhasil dihapus!" << endl;
    } else {
        cout << "Buku tidak ditemukan." << endl;
    }
}

bool balikKeMenu() {
    char pilihan;
    cout << "Balik ke Menu? (Y/N): ";
    cin >> pilihan;
    return (pilihan == 'Y' || pilihan == 'y');

}

int main() {
    string username;
    if (!login()) {
        return 0;
    }
    cout << "Halo, nathiq!" << username << " SELAMAT DATANG DI DATABASE PERPUSTAKAAN INFORMATIKA" << endl;

    int pilihan;
    do {
        cout << "1. Tambah Buku" << endl;
        cout << "2. Tampilkan Buku" << endl;
        cout << "3. Cari Buku" << endl;
        cout << "4. Hapus Buku" << endl;
        cout << "5. Keluar" << endl;
        cout << "Masukkan pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahBuku();
                if (!balikKeMenu()) return 0;
                break;
            case 2:
                tampilkanBuku();
                if (!balikKeMenu()) return 0;
                break;
            case 3:
                cariBuku();
                if (!balikKeMenu()) return 0;
                break;
            case 4:
                hapusBuku();
                if (!balikKeMenu()) return 0;
                break;
            case 5:
                cout << "program akan ditutup." << endl;
                break;
            default:
                cout << "Pilihan tidak valid, silakan coba lagi." << endl;
                if (!balikKeMenu()) return 0;
        }
    } while (pilihan != 5);

    return 0;
}