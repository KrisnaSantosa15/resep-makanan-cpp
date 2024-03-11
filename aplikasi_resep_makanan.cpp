/**********************************************
 *                                            *
 *    Aplikasi Resep Makanan By:              *
 *    			Kelompok 8                    *
 * 	  Krisna Santosa       - 2209092		  *
 * 	  Alfia April Riani    - 2209367		  *
 * 	  Anggo Maulana Putra  - 2200125		  *
 *    Muhammad Rafif Aiman - 2205911		  *
 *                                            *
 **********************************************/
#include <iostream>
#include <conio.h>	 // untuk getch()
#include <fstream>	 // library file handling
#include <sstream>	 // untuk stringstream [fungsinya adalah untuk mengakses setiap karakter dalam sebuah string]
#include <algorithm> // library untuk fungsi replace()
#include <windows.h> // agar bisa membuka link tutorial pada browser windows

using namespace std;

// Utils
void banner(string title, string author, int tolerance);
void tampilan_pembatas(int size);
string center(string input, int width);
string generate_kode_resep();

// Main Program
void login();
// void register_account();
void dashboard(string username);
void mainPage();
void main_menu_resep();
void kelola_resep_saya();
void list_semua_resep();
void list_resep_saya();
void tambah_resep_saya();
void detail_resep_saya(string kode_resep);
void detail_resep_general(string kode_resep);
void beri_rating(string kode_resep);
void edit_resep_saya(string kode_resep);

void tips_memasak();

void cari_resep();

struct Tampilan
{
	int jumlahPembatas;
};

struct Akun
{
	string username;
};

// Declare
Tampilan tampilan;
Akun akun;

int main()
{
	// Check if file bin/resep.dat is there or not, if not create a new one and insert RSP100#Ayam Bakar|Kompor,Sendok|Minyak,Ayam|Masukan Minyak,Masukan ayam|https://google.com|@admin
	ifstream file("bin/resep.dat");
	if (!file)
	{
		// Membuat folder
		CreateDirectory("bin", NULL);

		// Membuat file
		ofstream file("bin/resep.dat");
		file << "RSP100#Ayam Bakar|Kompor,Sendok|Minyak,Ayam|Masukan Minyak,Masukan ayam|https://google.com|@admin" << endl;
		file.close();
	}

	system("title Aplikasi Resep Makanan - Kelompok 8");
	mainPage();
	getch();
	return 0;
}

void mainPage()
{
	string menu;
	system("cls");

	banner("SELAMAT DATANG DI", "Aplikasi Resep Makanan - Kelompok 8", 10);
	cout << endl;

	cout << " [1] Login" << endl;
	// cout << " [2] Registrasi" << endl;
	cout << " [2] Keluar" << endl;

	cout << endl;
	tampilan_pembatas(tampilan.jumlahPembatas);
	cout << " Pilih menu : ";

	getline(cin, menu);
	if (menu == "1")
	{
		system("cls");
		login();
	}
	// else if (menu == "2")
	// {
	// 	system("cls");
	// 	register_account();
	// }
	else if (menu == "2")
	{
		system("cls");
		banner("Terima Kasih Sudah Menggunakan Aplikasi Kami!", "Kelompok 8 - PAMIT", 0);
		cout << " App Developed By: " << endl;
		cout << " Krisna Santosa       - 2209092" << endl;
		cout << " Alfia April Riani    - 2209367" << endl;
		cout << " Anggo Maulana Putra  - 2200125" << endl;
		cout << " Muhammad Rafif Aiman - 2205911" << endl;
		cout << " ";
		tampilan_pembatas(tampilan.jumlahPembatas);
		cout << " Tekan tombol apapun untuk keluar..." << endl;
		getch();
		exit(0);
	}
	else
	{
		system("cls");
		banner("Menu tidak ditemukan.", "Tekan tombol apapun untuk melanjutkan...", 0);
		getch();
		main();
	}
}

void login()
{

	int max_attempt = 3;
	string username;
	string password;
	string user = "admin";
	string pass = "admin";

	for (int i = 1; i <= max_attempt; i++)
	{
		banner("Aplikasi Resep Makanan", "LOGIN", 10);
		cout << " Masukan '#' untuk kembali!" << endl;
		cout << " Username: ";
		getline(cin, username);

		if (username == "#")
		{
			mainPage();
			return;
		}

		cout << " Password: ";
		getline(cin, password);

		if (username == user && password == pass)
		{
			cout << " Selamat Datang di Aplikasi Resep Makanan." << endl;
			akun.username = username;
			dashboard(username);
			break;
		}
		else if (i == max_attempt)
		{
			banner("Kesempatan Login anda sudah HABIS!!", "Tekan tombol apapun untuk melanjutkan...", 0);
		}
		else
		{
			int kesempatan = max_attempt - i;
			banner("Username atau Password Salah!", "Kesempatan anda tersisa: " + to_string(kesempatan) + " kali lagi!", 10);
			getch();
			system("cls");
		}
	}
}

void dashboard(string username)
{
	string pilih;
	system("cls");
	banner("Selamat Datang di Dashboard", username, 10);
	cout << endl;

	cout << " [1] Resep" << endl;
	cout << " [2] Tips" << endl;
	cout << " [3] Cari Resep" << endl;
	cout << " [4] Logout" << endl;

	cout << endl;
	tampilan_pembatas(tampilan.jumlahPembatas);

	cout << "Pilih Menu : ";
	getline(cin, pilih);

	if (pilih == "1")
	{
		main_menu_resep();
	}
	else if (pilih == "2")
	{
		system("cls");
		tips_memasak();
	}
	else if (pilih == "3")
	{
		system("cls");
		cari_resep();
	}
	else if (pilih == "4")
	{
		main();
	}
	else
	{
		banner("Menu tidak ditemukan.", "Tekan tombol apapun untuk melanjutkan...", 0);
		getch();
		dashboard(username);
	}
}

// void register_account()
// {
// 	banner("MOHON MAAF!", "Fitur ini belum tersedia.", 10);
// 	getch();
// 	mainPage();
// }

void main_menu_resep()
{
	string menu;
	system("cls");

	banner("Aplikasi Resep Makanan", "MENU RESEP", 10);
	cout << endl;

	cout << " [1] Menu Resep Makanan" << endl;
	cout << " [2] Kelola Resep Saya" << endl;

	cout << endl;
	cout << " [0] Kembali" << endl;

	tampilan_pembatas(tampilan.jumlahPembatas);
	cout << endl;

	cout << "Pilih Menu : ";
	getline(cin, menu);

	if (menu == "1")
	{
		system("cls");
		list_semua_resep();
	}
	else if (menu == "2")
	{
		system("cls");
		kelola_resep_saya();
	}
	else if (menu == "0")
	{
		dashboard("admin");
	}
	else
	{
		banner("Menu tidak ditemukan.", "Tekan tombol apapun untuk melanjutkan...", 0);
		getch();
		main_menu_resep();
	}
}

void kelola_resep_saya()
{
	string menu;
	system("cls");

	banner("Aplikasi Resep Makanan", "KELOLA RESEP SAYA", 10);
	cout << endl;

	cout << " [1] Lihat Resep Saya" << endl;
	cout << " [2] Buat Resep Baru" << endl;

	cout << endl;
	cout << " [0] Kembali" << endl;

	tampilan_pembatas(tampilan.jumlahPembatas);
	cout << endl;

	cout << "Pilih Menu : ";
	getline(cin, menu);

	if (menu == "1")
	{
		system("cls");
		list_resep_saya();
		return;
	}
	else if (menu == "2")
	{
		system("cls");
		tambah_resep_saya();
	}
	else if (menu == "0")
	{
		main_menu_resep();
	}
	else
	{
		banner("Menu tidak ditemukan.", "Tekan tombol apapun untuk melanjutkan...", 0);
		getch();
		kelola_resep_saya();
	}
}

void list_resep_saya()
{
	string menu;
	system("cls");

	banner("Aplikasi Resep Makanan", "LIHAT RESEP SAYA", 10);
	cout << endl;

	// Mendapatkan data dari bin/resep.dat ketika data di baris tersebut memiliki @admin yang berarti data tersebut milik pribadi
	ifstream file;
	file.open("bin/resep.dat");

	string line, nama_resep;
	int num = 1;
	string author = ("@" + akun.username);

	while (getline(file, line))
	{
		if (line.find(author) != string::npos) // string::npos adalah sebuah nilai error ketika line.find tidak menemukan yang dicarinya
		{
			stringstream ss(line);
			getline(ss, nama_resep, '|');
			cout << " [" << num++ << "] " << nama_resep << endl;
		}
	}

	file.close();
	cout << endl;

	cout << " [0] Kembali" << endl;

	tampilan_pembatas(tampilan.jumlahPembatas);
	cout << endl;

	cout << "Lihat detail resep : ";
	getline(cin, menu);

	if (menu == "0")
	{
		kelola_resep_saya();
	}
	int menus;

	// Menggunakan Try Catch untuk menghindari error ketika user berusaha menginputkan karakter padahal ada stoi yang berfungsi untuk mengkonversi string ke int
	try
	{
		menus = stoi(menu);
	}
	catch (const std::exception &e) // default parameter dari try catch yaitu exception
	{
		banner("Menu tidak ditemukan.", "Tekan tombol apapun untuk melanjutkan...", 0);
		getch();
		list_resep_saya();
	}

	if (menus < 0 || menus > (num - 1))
	{
		banner("Menu tidak ditemukan.", "Tekan tombol apapun untuk melanjutkan...", 0);
		getch();
		list_resep_saya();
	}
	else
	{
		system("clear");
		// ambil kode resep dari menu resep yang dipilih
		ifstream fileKodeResep;
		fileKodeResep.open("bin/resep.dat");

		string lineKodeResep, kodeResep;
		int numKodeResep = 1;

		while (getline(fileKodeResep, lineKodeResep))
		{
			if (lineKodeResep.find(author) != string::npos)
			{
				if (numKodeResep == menus)
				{
					stringstream ss(lineKodeResep);
					getline(ss, kodeResep, '#');
					break;
				}
				numKodeResep++;
			}
		}

		fileKodeResep.close();
		detail_resep_saya(kodeResep);
	}
}

void tambah_resep_saya()
{
	string nama_resep, alat, bahan, langkah, link_tutorial;
	system("cls");

	banner("Aplikasi Resep Makanan", "TAMBAH RESEP SAYA", 10);
	cout << endl;

	cout << "Gunakan koma ',' untuk memisahkan antar poin! Contoh:" << endl;
	cout << "Alat: Kompor,Sendok,Piring" << endl;
	cout << "Link tutorial wajib menggunakan 'http://' atau 'https://' contoh: https://google.com" << endl;
	cout << "Gunakan '#' dalam nama resep untuk kembali!" << endl
		 << endl;

	// insert data to file, each data separated by space
	ofstream file;
	file.open("bin/resep.dat", ios::app);

	cout << "Nama Resep : ";
	getline(cin, nama_resep);

	// inputan tidak boleh kosong
	if (nama_resep == "")
	{
		banner("Nama resep tidak boleh kosong.", "Tekan tombol apapun untuk melanjutkan...", 0);
		getch();
		tambah_resep_saya();
	}

	if (nama_resep == "#")
	{
		kelola_resep_saya();
	}

	string kode_resep = generate_kode_resep();

	cout << "Alat : ";
	getline(cin, alat);
	if (alat == "")
	{
		banner("Alat tidak boleh kosong.", "Tekan tombol apapun untuk melanjutkan...", 0);
		getch();
		tambah_resep_saya();
	}

	cout << "Bahan : ";
	getline(cin, bahan);
	if (bahan == "")
	{
		banner("Bahan tidak boleh kosong.", "Tekan tombol apapun untuk melanjutkan...", 0);
		getch();
		tambah_resep_saya();
	}

	cout << "Langkah : ";
	getline(cin, langkah);
	if (langkah == "")
	{
		banner("Langkah tidak boleh kosong.", "Tekan tombol apapun untuk melanjutkan...", 0);
		getch();
		tambah_resep_saya();
	}

	cout << "Link Tutorial : ";
	getline(cin, link_tutorial);
	if (link_tutorial == "")
	{
		banner("Link Tutorial tidak boleh kosong.", "Tekan tombol apapun untuk melanjutkan...", 0);
		getch();
		tambah_resep_saya();
	}

	file << kode_resep << "#";
	file << nama_resep << "|";
	file << alat << "|";
	file << bahan << "|";
	file << langkah << "|";
	file << link_tutorial << "|";
	// Author
	file << "@" << akun.username << endl;

	file.close();

	banner("SUKSES", "Resep Berhasil Ditambahkan!", 0);
	getch();
	// kelola_resep_saya();
	// detail_resep_general(kode_resep);
	list_resep_saya();
}

void detail_resep_saya(string kode_resep)
{
	string menu;
	// get 1 line resep by kode_resep from parameter
	ifstream file;
	file.open("bin/resep.dat");

	string line, nama_resep, alat, bahan, langkah, link_tutorial, author;
	stringstream ss;

	while (getline(file, line))
	{
		if (line.find(kode_resep) != string::npos)
		{
			ss << line;
			getline(ss, nama_resep, '|');
			getline(ss, alat, '|');
			getline(ss, bahan, '|');
			getline(ss, langkah, '|');
			getline(ss, link_tutorial, '|');
			getline(ss, author, '|');
			break;
		}
	}

	file.close();

	system("clear");
	banner("Menampilkan Resep", nama_resep + " by " + author, 10);
	cout << endl;

	replace(alat.begin(), alat.end(), ',', '\n');
	replace(bahan.begin(), bahan.end(), ',', '\n');
	replace(langkah.begin(), langkah.end(), ',', '\n');

	cout << "Alat : " << endl;
	cout << alat << endl
		 << endl;

	cout << "Bahan : " << endl;
	cout << bahan << endl
		 << endl;

	cout << "Langkah : " << endl;
	cout << langkah << endl
		 << endl;

	cout << "Link Tutorial : " << link_tutorial << endl;
	cout << endl;

	tampilan_pembatas(tampilan.jumlahPembatas);
	cout << endl;

	cout << " [1] Hapus Resep" << endl;
	cout << " [2] Edit Resep" << endl;
	cout << " [3] Lihat Tutorial" << endl;

	cout << endl;
	cout << " [0] Kembali" << endl;

	cout << endl;
	tampilan_pembatas(tampilan.jumlahPembatas);
	cout << endl;

	cout << "Pilih Menu : ";
	getline(cin, menu);
	if (menu == "0")
	{
		list_resep_saya();
	}
	else if (menu == "1")
	{
		// hapus 1 line resep from bin/resep.dat when input = number_of_line
		string konfirmasi;
		cout << "Yakin ingin menghapus resep ini? (Y/N) : ";
		getline(cin, konfirmasi);

		if (konfirmasi == "Y" || konfirmasi == "y")
		{
			// hapus resep berdasarkan kode_resep

			std::ifstream in("bin/resep.dat");
			std::string delete_records[100];
			std::string line;
			int numRecords = 0;

			// Read the file and store the records in an array
			while (std::getline(in, line))
				delete_records[numRecords++] = line;

			in.close();

			// Delete the record with id "12345"
			for (int i = 0; i < numRecords; i++)
			{
				if (delete_records[i].find(kode_resep) != std::string::npos)
					delete_records[i] = "";
			}

			std::ofstream out("bin/resep.dat");

			// Write the updated records back to the file
			for (int i = 0; i < numRecords; i++)
				if (delete_records[i] != "")
					out << delete_records[i] << "\n";

			out.close();

			// ifstream file;
			// file.open("bin/resep.dat");

			// string line, nama_resep, alat, bahan, langkah, link_tutorial, author;
			// stringstream ss;

			// ofstream fileTemp;
			// fileTemp.open("bin/resep_temp.dat");

			// while (getline(file, line))
			// {
			// 	if (line.find(kode_resep) != string::npos)
			// 	{
			// 		continue;
			// 	}
			// 	fileTemp << line << endl;
			// }

			// file.close();
			// fileTemp.close();

			// remove("bin/resep.dat");
			// rename("bin/resep_temp.dat", "bin/resep.dat");

			banner("Resep berhasil dihapus.", "Tekan tombol apapun untuk melanjutkan...", 0);
			getch();
			list_resep_saya();
		}
		else
		{
			system("cls");
			detail_resep_saya(kode_resep);
		}
	}
	else if (menu == "2")
	{
		// edit 1 line resep from bin/resep.dat when input = number_of_line
		string konfirmasi;
		cout << "Yakin ingin mengedit resep ini? (Y/N) : ";
		getline(cin, konfirmasi);

		if (konfirmasi == "Y" || konfirmasi == "y")
		{
			system("cls");
			edit_resep_saya(kode_resep);
		}
		else
		{
			system("cls");
			detail_resep_saya(kode_resep);
		}
	}
	else if (menu == "3")
	{
		ShellExecute(NULL, "open", link_tutorial.c_str(), NULL, NULL, SW_SHOWNORMAL);
		system("cls");
		detail_resep_saya(kode_resep);
	}
	else
	{
		banner("Menu tidak ditemukan .", "Tekan tombol apapun untuk melanjutkan...", 0);
		getch();
		system("cls");
		detail_resep_saya(kode_resep);
	}
}

void edit_resep_saya(string kode_resep)
{
	banner("Edit Resep", "Silahkan isi form berikut ini", 10);
	cout << endl;
	// Edit resep berdasarkan kode_resep
	string nama_resep, alat, bahan, langkah, link_tutorial, author;
	stringstream ss;

	cout << "Gunakan koma ',' untuk memisahkan antar poin! Contoh:" << endl;
	cout << "Alat: Kompor,Sendok,Piring" << endl;
	cout << "Link tutorial wajib menggunakan 'http://' atau 'https://' contoh: https://google.com" << endl
		 << endl;

	cout << "Nama Resep Baru : ";
	getline(cin, nama_resep);
	if (nama_resep == "")
	{
		banner("Nama resep tidak boleh kosong.", "Tekan tombol apapun untuk melanjutkan...", 0);
		getch();
		system("cls");
		edit_resep_saya(kode_resep);
	}

	cout << "Alat : ";
	getline(cin, alat);
	if (alat == "")
	{
		banner("Alat tidak boleh kosong.", "Tekan tombol apapun untuk melanjutkan...", 0);
		getch();
		system("cls");
		edit_resep_saya(kode_resep);
	}

	cout << "Bahan : ";
	getline(cin, bahan);
	if (bahan == "")
	{
		banner("Bahan tidak boleh kosong.", "Tekan tombol apapun untuk melanjutkan...", 0);
		getch();
		system("cls");
		edit_resep_saya(kode_resep);
	}

	cout << "Langkah : ";
	getline(cin, langkah);
	if (langkah == "")
	{
		banner("Langkah tidak boleh kosong.", "Tekan tombol apapun untuk melanjutkan...", 0);
		getch();
		system("cls");
		edit_resep_saya(kode_resep);
	}

	cout << "Link Tutorial : ";
	getline(cin, link_tutorial);
	if (link_tutorial == "")
	{
		banner("Link Tutorial tidak boleh kosong.", "Tekan tombol apapun untuk melanjutkan...", 0);
		getch();
		system("cls");
		edit_resep_saya(kode_resep);
	}

	author = "@" + akun.username;

	ss << kode_resep << "#" << nama_resep << "|" << alat << "|" << bahan << "|" << langkah << "|" << link_tutorial << "|" << author;

	// edit data resep from bin/resep.dat by kode_resep
	ifstream in("bin/resep.dat");
	string records[100];
	string line;
	int num_records = 0;

	// read the file and store the records in an array
	while (getline(in, line))
	{
		records[num_records++] = line;
	}
	in.close();

	// edit the record
	for (int i = 0; i < num_records; i++)
	{
		if (records[i].find(kode_resep) != std::string::npos)
		{
			// records[i] = "";
			records[i] = kode_resep + "#" + nama_resep + "|" + alat + "|" + bahan + "|" + langkah + "|" + link_tutorial + "|" + author;
		}
	}

	// write the records back to the file
	ofstream out("bin/resep.dat");
	for (int i = 0; i < num_records; i++)
	{
		out << records[i] << endl;
	}
	out.close();

	// // buat fileTemp yang isinya bin/resep.dat, trus ganti isi fileTemp tadi dengan update data baru, udah gitu hapus file original, rename fileTemp menjadi file originalnya
	// ifstream file;
	// file.open("bin/resep.dat");

	// string line;
	// stringstream ss2;

	// ofstream fileTemp;
	// fileTemp.open("bin/resep_temp.dat");

	// while (getline(file, line))
	// {
	// 	if (line.find(kode_resep) != string::npos)
	// 	{
	// 		fileTemp << ss.str() << endl;
	// 		continue;
	// 	}
	// 	fileTemp << line << endl;
	// }

	// file.close();
	// fileTemp.close();

	// remove("bin/resep.dat");
	// rename("bin/resep_temp.dat", "bin/resep.dat");

	banner("Resep berhasil diedit.", "Tekan tombol apapun untuk melanjutkan...", 0);
	getch();
	list_resep_saya();
}

void list_semua_resep()
{
	string menu;
	system("cls");

	banner("Aplikasi Resep Makanan", "List Semua Resep", 10);
	cout << endl;

	ifstream file;
	file.open("bin/resep.dat");

	string line, nama_resep;
	int num = 1;
	string author = ("@" + akun.username);

	while (getline(file, line))
	{
		stringstream ss(line);
		getline(ss, nama_resep, '|');
		cout << " [" << num++ << "] " << nama_resep << endl;
	}

	file.close();
	cout << endl;

	cout << " [0] Kembali" << endl;

	tampilan_pembatas(tampilan.jumlahPembatas);
	cout << endl;

	cout << "Lihat detail resep : ";
	getline(cin, menu);

	if (menu == "0")
	{
		main_menu_resep();
	}
	int menus;

	// Menggunakan Try Catch untuk menghindari error ketika user berusaha menginputkan karakter padahal ada stoi yang berfungsi untuk mengkonversi string ke int
	try
	{
		menus = stoi(menu);
	}
	catch (const std::exception &e) // default parameter dari try catch
	{
		banner("Menu tidak ditemukan.", "Tekan tombol apapun untuk melanjutkan...", 0);
		getch();
		list_semua_resep();
	}

	if (menus < 0 || menus > (num - 1))
	{
		banner("Menu tidak ditemukan.", "Tekan tombol apapun untuk melanjutkan...", 0);
		getch();
		list_semua_resep();
	}
	else
	{
		system("clear");
		// ambil kode resep dari menu resep yang dipilih
		ifstream fileKodeResep;
		fileKodeResep.open("bin/resep.dat");

		string lineKodeResep, kodeResep;
		int numKodeResep = 1;

		while (getline(fileKodeResep, lineKodeResep))
		{
			if (lineKodeResep.find(author) != string::npos)
			{
				if (numKodeResep == menus)
				{
					stringstream ss(lineKodeResep);
					getline(ss, kodeResep, '#');
					break;
				}
				numKodeResep++;
			}
		}

		fileKodeResep.close();
		detail_resep_general(kodeResep);
	}
}

void detail_resep_general(string kode_resep)
{
	string menu;
	// get 1 line resep by kode_resep from parameter
	ifstream file;
	file.open("bin/resep.dat");

	string line, nama_resep, alat, bahan, langkah, link_tutorial, author;
	stringstream ss;

	while (getline(file, line))
	{
		if (line.find(kode_resep) != string::npos)
		{
			ss << line;
			getline(ss, nama_resep, '|');
			getline(ss, alat, '|');
			getline(ss, bahan, '|');
			getline(ss, langkah, '|');
			getline(ss, link_tutorial, '|');
			getline(ss, author, '|');
			break;
		}
	}

	file.close();

	system("clear");
	banner("Menampilkan Resep", nama_resep + " by " + author, 10);
	cout << endl;

	replace(alat.begin(), alat.end(), ',', '\n');
	replace(bahan.begin(), bahan.end(), ',', '\n');
	replace(langkah.begin(), langkah.end(), ',', '\n');

	cout << "Alat : " << endl;
	cout << alat << endl
		 << endl;

	cout << "Bahan : " << endl;
	cout << bahan << endl
		 << endl;

	cout << "Langkah : " << endl;
	cout << langkah << endl
		 << endl;

	cout << "Link Tutorial : " << link_tutorial << endl;
	cout << endl;

	tampilan_pembatas(tampilan.jumlahPembatas);
	cout << endl;

	// cout << " [1] Beri Rating" << endl;
	cout << " [1] Lihat Tutorial" << endl;

	cout << endl;
	cout << " [0] Kembali" << endl;

	cout << endl;
	tampilan_pembatas(tampilan.jumlahPembatas);
	cout << endl;

	cout << "Pilih Menu : ";
	getline(cin, menu);
	if (menu == "0")
	{
		list_semua_resep();
	}
	// else if (menu == "1")
	// {
	// 	beri_rating(kode_resep);
	// }
	else if (menu == "1")
	{
		ShellExecute(NULL, "open", link_tutorial.c_str(), NULL, NULL, SW_SHOWNORMAL);
		system("cls");
		detail_resep_general(kode_resep);
	}
	else
	{
		banner("Menu tidak ditemukan .", "Tekan tombol apapun untuk melanjutkan...", 0);
		getch();
		system("cls");
		detail_resep_general(kode_resep);
	}
}

void beri_rating(string index)
{
	banner("MOHON MAAF!", "Fitur Sedang dalam Tahap Pengembangan.", 10);
	getch();
	detail_resep_general(index);
}

void cari_resep()
{
	banner("Cari Resep", "Masukkan kata kunci pencarian resep!", 10);
	cout << endl;

	cout << "Gunakan '#' untuk kembali" << endl;

	// mencari data dari bin/resep.dat sesuai keyword
	string keyword;
	cout << "Masukkan keyword : ";
	getline(cin, keyword);

	if (keyword == "")
	{
		banner("Peringatan!", "Keyword tidak boleh kosong!", 10);
		getch();
		system("cls");
		cari_resep();
	}

	if (keyword == "#")
	{
		dashboard(akun.username);
	}

	ifstream file;
	file.open("bin/resep.dat");

	string line, nama_resep, alat, bahan, langkah, link_tutorial, author;
	stringstream ss;
	
	while (getline(file, line))
	{
		if (line.find(keyword) != string::npos)
		{
			ss << line;
			getline(ss, nama_resep, '|');
			getline(ss, alat, '|');
			getline(ss, bahan, '|');
			getline(ss, langkah, '|');
			getline(ss, link_tutorial, '|');
			getline(ss, author, '|');

			replace(alat.begin(), alat.end(), ',', '\n');
			replace(bahan.begin(), bahan.end(), ',', '\n');
			replace(langkah.begin(), langkah.end(), ',', '\n');

			banner("Cari Resep", nama_resep + " by " + author, 10);
			cout << endl;

			cout << "Alat : " << endl;
			cout << alat << endl
				 << endl;

			cout << "Bahan : " << endl;
			cout << bahan << endl
				 << endl;

			cout << "Langkah : " << endl;
			cout << langkah << endl
				 << endl;

			cout << "Link Tutorial : " << link_tutorial << endl;
			cout << endl;

			tampilan_pembatas(tampilan.jumlahPembatas);
			cout << endl;

			cout << "Tekan tombol apapun untuk melanjutkan...";
			getch();
			system("cls");
			dashboard(akun.username);

			break;
		}
	}

	file.close();

	// if not found
	if (line.find(keyword) == string::npos)
	{
		banner("Keyword tidak ditemukan.", "Tekan tombol apapun untuk melanjutkan...", 0);
		getch();
		system("cls");
		cari_resep();
	}
}

void tips_memasak()
{
	string judul_tips[30] = {"Tips Membuat Gorengan Agar Renyah dan Tidak Berminyak", "Tips Menggoreng Tempe Agar Lebih Renyah dan Nikmat", "Bagaimana Cara Menyimpan Bawang Agar Tidak Mudah Busuk?", "Tips Membuat Teluar Dadar Padang yang Tebal Namun Empuk", "Tips Memasak Nasi agar Aromanya Nikmat"};
	string tips[30] = {
		// Gorengan
		"Gunakan Minyak Goreng Yang Berkualitas\n	  Minyak Dipanaskan Terlebih Dahulu\n	  Masukan Adonan Sedikit Demi Sedikit\n	  Tiriskan Gorengan Yang Sudah Matang.",
		// Tempe
		"Gunakan Minyak Bersih Ketika Menggoreng Tempe\n	  Gunakan Minyak yang Cukup Banyak, Agar Tempe Matang Dengan Sempurna\n	  Gunakan Api Kecil Supaya Tempe Tidak Gosong\n	  Irisan Tempe Jangan Terlalu Tipis atau Terlalu Tebal.",
		// Bawang
		"Simpan Bawang Yang Masih Utuh Di Tempat Terbuka\n	  Simpan Bawang Terpisah Dengan Sayuran Lainnya\n	  Hindari Bawang Terkena Matahari Langsung.",
		// Telur Dadar
		"Gunakan Minyak Goreng Yang Berkualitas\n	  Masukan Adonan Sedikit Demi Sedikit\n	  Tiriskan Gorengan Yang Sudah Matang.",
		// Nasi
		"Gunakan Air Yang Bersih Ketika Membuat Nasi\n	  Gunakan Daun Pandan, Serai, atau Mentega Ketika Menanak Nasi\n	  Hindari Menggunakan Beras Yang Sudah Lama atau Berkutu\n	  Masukan Bumbu Yang Sudah Di Haluskan."};
	string rating[30] = {"4.5", "4.2", "4.3", "4.1", "4.0"};

	banner("Tips", "Tips Membuat Resep", 10);
	cout << endl;

	for (int i = 0; i < 5; i++)
	{
		// [1] judul_tips[i]
		cout << " [" << i + 1 << "] " << judul_tips[i] << endl;
		// cout << "Rating : " << rating[i] << endl;
	}
	cout << endl;

	cout << " [0] Kembali" << endl;

	cout << endl;
	tampilan_pembatas(tampilan.jumlahPembatas);

	cout << "Masukkan nomor tips yang ingin dilihat : ";
	string index;
	getline(cin, index);

	int indexes;

	try
	{
		indexes = stoi(index);
	}
	catch (const std::exception &e)
	{
		banner("Menu tidak ditermukan.", "Tekan tombol apapun untuk melanjutkan!", 10);
		getch();
		system("cls");
		tips_memasak();
	}

	if (indexes == 0)
	{
		system("cls");
		dashboard(akun.username);
	}
	else if (indexes > 0 && indexes <= 5)
	{
		system("cls");
		banner("Tips", judul_tips[indexes - 1], 10);
		cout << endl;

		cout << " Rating : " << rating[indexes - 1] << endl
			 << endl;
		cout << " Tips   : " << tips[indexes - 1] << endl
			 << endl;

		cout << endl;
		tampilan_pembatas(tampilan.jumlahPembatas);
		cout << endl;

		cout << "Tekan tombol apapun untuk melanjutkan...";
		getch();
		system("cls");
		tips_memasak();
	}
	else
	{
		banner("Nomor tips tidak ditemukan.", "Tekan tombol apapun untuk melanjutkan...", 0);
		getch();
		system("cls");
		tips_memasak();
	}
}

// Utils Functions
// Membuat Banner/title
void banner(string title, string author = "", int tolerance = 0)
{
	// Tolerance adalah varibale untuk menambahkan space size dalam banner, agar sesuai. Nilai Tolerance tidak boleh negatif
	if (tolerance < 0)
	{
		tolerance = 0;
	}
	int longestLength;
	// longest length
	if (title.length() > author.length())
	{
		longestLength = title.length() + tolerance;
	}
	else
	{
		longestLength = author.length() + tolerance;
	}

	// list of char
	char sym1 = 218; // ┌
	char sym2 = 196; // ─
	char sym3 = 191; // ┐
	char sym4 = 179; // │
	char sym5 = 192; // └
	char sym6 = 217; // ┘

	// make a border UI
	cout << sym1;
	for (int i = 0; i < (longestLength + 4); i++)
	{
		cout << sym2;
	}
	cout << sym3 << endl;

	cout << sym4 << " " << center(title, (longestLength + 3)) << "  " << string((longestLength - title.length()) / 2, ' ') + sym4 << endl;
	cout << sym4 << " " << center(author, (longestLength + 3)) << "  " << string((longestLength - author.length()) / 2, ' ') + sym4 << endl;
	cout << sym5;

	for (int i = 0; i < (longestLength + 4); i++)
	{
		cout << sym2;
	}
	cout << sym6 << endl;

	tampilan.jumlahPembatas = longestLength;

	return;
}

void tampilan_pembatas(int size = 0)
{
	char sym2 = 196; // ─
	for (int i = 0; i < (size + 4); i++)
	{
		cout << sym2;
	}
	cout << endl;
}

string center(string input, int width = 113) // agar text menjadi ke tengah dari default lebar 113
{
	return string((width - input.length()) / 2, ' ') + input;
}

string generate_kode_resep() // membuat kode_resep
{
	string kode_resep = "RSP100"; // kode resep default
	ifstream file;
	file.open("bin/resep.dat");

	string line, kodeResep;
	int num = 1;

	// membuka file untuk mendapatkan kode_resep paling tinggi
	while (getline(file, line))
	{
		stringstream ss(line);
		getline(ss, kodeResep, '#');
	}

	file.close();

	// stoi = ubah kode resep jadi integer
	int kodeResepInt = stoi(kodeResep.substr(3, 3));
	// increment kode_resep agar unik
	kodeResepInt++;
	kode_resep = "RSP" + to_string(kodeResepInt);

	return kode_resep;
}