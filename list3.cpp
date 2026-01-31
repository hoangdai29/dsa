#include <bits/stdc++.h>
using namespace std;

// Cấu trúc 1 cuốn sách
struct Sach {
    string maSach;
    string tenSach;
    string tacGia;
    int namXB;
    Sach* next;
};

// Danh sách liên kết
struct DanhSachSach {
    Sach* head = nullptr;
};

// 1. Tạo node sách mới
Sach* taoSach(string ma, string ten, string tacGia, int nam) {
    Sach* s = new Sach;
    s->maSach  = ma;
    s->tenSach = ten;
    s->tacGia  = tacGia;
    s->namXB   = nam;
    s->next    = nullptr;
    return s;
}

// 2. Hàm nhập n cuốn sách (thêm vào cuối danh sách)
void nhapDanhSach(DanhSachSach &ds, int n) {
    for (int i = 1; i <= n; i++) {
        cout << "\n--- Nhap thong tin cuon sach thu " << i << " ---\n";

        string ma, ten, tacGia;
        int nam;

        cout << "Ma sach        : "; getline(cin, ma);
        cout << "Ten sach       : "; getline(cin, ten);
        cout << "Tac gia        : "; getline(cin, tacGia);
        cout << "Nam xuat ban   : "; cin >> nam;
        cin.ignore(); // xóa bộ đệm sau khi nhập số

        Sach* s = taoSach(ma, ten, tacGia, nam);

        // Thêm vào cuối danh sách
        if (ds.head == nullptr) {
            ds.head = s;
        } else {
            Sach* p = ds.head;
            while (p->next != nullptr) {
                p = p->next;
            }
            p->next = s;
        }
    }
}

// 3. Hàm hiển thị toàn bộ danh sách sách
void hienThiDanhSach(const DanhSachSach &ds) {
    if (ds.head == nullptr) {
        cout << "Danh sach rong!\n";
        return;
    }

    cout << "\nDANH SACH CAC CUON SACH:\n";
    cout << left
         << setw(12) << "Ma sach"
         << setw(30) << "Ten sach"
         << setw(20) << "Tac gia"
         << setw(10) << "Nam XB" << endl;
    cout << string(72, '-') << endl;

    Sach* p = ds.head;
    while (p != nullptr) {
        cout << left
             << setw(12) << p->maSach
             << setw(30) << p->tenSach
             << setw(20) << p->tacGia
             << setw(10) << p->namXB << endl;
        p = p->next;
    }
    cout << endl;
}

// 4. Hàm hiển thị các sách của tác giả "Quach Tuan Ngoc"
void hienThiSachCuaTacGia(const DanhSachSach &ds, string tacGiaCanTim) {
    if (ds.head == nullptr) {
        cout << "Danh sach rong!\n";
        return;
    }

    bool timThay = false;
    cout << "\nCAC CUON SACH CUA TAC GIA \"" << tacGiaCanTim << "\":\n";
    cout << left
         << setw(12) << "Ma sach"
         << setw(30) << "Ten sach"
         << setw(10) << "Nam XB" << endl;
    cout << string(52, '-') << endl;

    Sach* p = ds.head;
    while (p != nullptr) {
        if (p->tacGia == tacGiaCanTim) {
            cout << left
                 << setw(12) << p->maSach
                 << setw(30) << p->tenSach
                 << setw(10) << p->namXB << endl;
            timThay = true;
        }
        p = p->next;
    }

    if (!timThay) {
        cout << "Khong tim thay sach nao cua tac gia \"" << tacGiaCanTim << "\".\n";
    }
    cout << endl;
}

// 5. Giải phóng bộ nhớ
void giaiPhong(DanhSachSach &ds) {
    Sach* p = ds.head;
    while (p != nullptr) {
        Sach* temp = p;
        p = p->next;
        delete temp;
    }
    ds.head = nullptr;
}
// Xóa tất cả sách có mã sách trùng với maXoa
// Trả về số lượng sách đã xóa
int xoaSachTheoMa(DanhSachSach &ds, string maXoa) {
    if (ds.head == nullptr) return 0;

    int count = 0;
    Sach* p = ds.head;
    Sach* prev = nullptr;

    while (p != nullptr) {
        if (p->maSach == maXoa) {
            Sach* temp = p;

            if (prev == nullptr) {
                // Xóa đầu danh sách
                ds.head = p->next;
            } else {
                prev->next = p->next;
            }

            p = p->next;
            delete temp;
            count++;
        } else {
            prev = p;
            p = p->next;
        }
    }

    return count;
}
// Chèn một cuốn sách mới vào vị trí thứ k (1 = đầu danh sách, 2 = sau phần tử đầu, ...)
// Nếu k lớn hơn độ dài danh sách → chèn vào cuối
// Trả về true nếu chèn thành công, false nếu vị trí không hợp lệ (k <= 0)
bool chenSachVaoViTri(DanhSachSach &ds, int k, string ma, string ten, string tacGia, int nam) {
    if (k <= 0) return false;

    Sach* s = taoSach(ma, ten, tacGia, nam);
    if (s == nullptr) return false; // không cấp phát được

    // Trường hợp chèn vào đầu (k == 1)
    if (k == 1) {
        s->next = ds.head;
        ds.head = s;
        return true;
    }

    // Duyệt đến vị trí k-1
    Sach* p = ds.head;
    int i = 1;
    while (p != nullptr && i < k - 1) {
        p = p->next;
        i++;
    }

    // Nếu p == nullptr → chèn vào cuối
    if (p == nullptr) {
        // Tìm phần tử cuối
        Sach* last = ds.head;
        while (last->next != nullptr) last = last->next;
        last->next = s;
        return true;
    }

    // Chèn vào giữa: sau p
    s->next = p->next;
    p->next = s;
    return true;
}

int main() {
    DanhSachSach ds;
    int n;

    cout << "Nhap so luong sach can nhap (n >= 1): ";
    cin >> n;
    cin.ignore(); // xóa bộ đệm

    if (n < 1) {
        cout << "So luong phai >= 1 theo de bai!\n";
        return 0;
    }

    nhapDanhSach(ds, n);

    cout << "\n=== DANH SACH SAU KHI NHAP ===\n";
    hienThiDanhSach(ds);

    cout << "\n=== CAC CUON SACH CUA TAC GIA QUACH TUAN NGOC ===\n";
    hienThiSachCuaTacGia(ds, "Quach Tuan Ngoc");

    giaiPhong(ds);
    cout << "Da giai phong bo nho.\n";

    return 0;
    cout << "\nNhap ma sach can xoa: ";
string maXoa;
getline(cin, maXoa);

int soLuongXoa = xoaSachTheoMa(ds, maXoa);
cout << "Da xoa " << soLuongXoa << " cuon sach co ma " << maXoa << endl;
hienThiDanhSach(ds);
cout << "\n=== CHEN SACH MOI VAO VI TRI ===\n";
int viTri;
string ma, ten, tacGia;
int nam;

cout << "Nhap vi tri can chen (1-based): "; cin >> viTri; cin.ignore();
cout << "Ma sach        : "; getline(cin, ma);
cout << "Ten sach       : "; getline(cin, ten);
cout << "Tac gia        : "; getline(cin, tacGia);
cout << "Nam xuat ban   : "; cin >> nam; cin.ignore();

bool chenOK = chenSachVaoViTri(ds, viTri, ma, ten, tacGia, nam);
if (chenOK) {
    cout << "Chen thanh cong!\n";
} else {
    cout << "Vi tri khong hop le!\n";
}

hienThiDanhSach(ds);
}
