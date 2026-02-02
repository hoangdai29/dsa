#include <bits/stdc++.h>
using namespace std;

const int MAX = 100;  // Kích thước tối đa của mảng (cố định)

// Cấu trúc thông tin sinh viên
struct SinhVien {
    int stt;
    char ten[50];
    float diem;
};

// Danh sách dùng mảng
struct DanhSach {
    SinhVien ds[MAX];   // mảng lưu trữ các phần tử
    int n;              // số phần tử hiện tại
};

// 1. Khởi tạo danh sách rỗng
void KhoiTao(DanhSach &L) {
    L.n = 0;
}

// 2. Khởi tạo danh sách mẫu (hard-code)
void KhoiTaoDanhSachMau(DanhSach &L) {
    KhoiTao(L);
    
    L.ds[0] = {1, "Nguyen Van A", 7.5};
    L.ds[1] = {2, "Tran Thi B", 8.2};
    L.ds[2] = {3, "Le Van C", 6.8};
    L.ds[3] = {4, "Pham Thi D", 9.0};
    
    L.n = 4;
}

// 3. Hiển thị danh sách
void HienThi(const DanhSach &L) {
    if (L.n == 0) {
        cout << "Danh sach rong!\n";
        return;
    }
    
    cout << left;
    cout << setw(6) << "STT"
         << setw(25) << "Ho va ten"
         << setw(10) << "Diem TB" << endl;
    cout << string(50, '-') << endl;
    
    for (int i = 0; i < L.n; i++) {
        cout << setw(6) << (i+1)
             << setw(25) << L.ds[i].ten
             << setw(10) << fixed << setprecision(1) << L.ds[i].diem << endl;
    }
    cout << endl;
}

// 4. Thêm một sinh viên vào cuối danh sách
bool ThemCuoi(DanhSach &L, SinhVien sv) {
    if (L.n >= MAX) {
        cout << "Danh sach da day!\n";
        return false;
    }
    
    L.ds[L.n] = sv;
    L.n++;
    return true;
}

// 5. Xóa sinh viên tại vị trí pos (0-based)
bool XoaTaiViTri(DanhSach &L, int pos) {
    if (pos < 0 || pos >= L.n) return false;
    
    // Dời các phần tử sau pos lên trước 1 vị trí
    for (int i = pos; i < L.n - 1; i++) {
        L.ds[i] = L.ds[i + 1];
    }
    L.n--;
    return true;
}

// 6. Xóa sinh viên có điểm < 5.0
void XoaYeuKem(DanhSach &L) {
    int i = 0;
    while (i < L.n) {
        if (L.ds[i].diem < 5.0) {
            // Xóa tại vị trí i (không tăng i vì phần tử sau đã dời lên)
            for (int j = i; j < L.n - 1; j++) {
                L.ds[j] = L.ds[j + 1];
            }
            L.n--;
        } else {
            i++;
        }
    }
    cout << "Da xoa cac sinh vien yeu kem (diem < 5.0)\n";
}

// 7. Sửa điểm theo tên
void SuaDiemTheoTen(DanhSach &L, const char* ten, float diem_moi) {
    bool found = false;
    for (int i = 0; i < L.n; i++) {
        if (strcmp(L.ds[i].ten, ten) == 0) {
            L.ds[i].diem = diem_moi;
            found = true;
            cout << "Da sua diem cua " << ten << " thanh " << diem_moi << endl;
        }
    }
    if (!found) {
        cout << "Khong tim thay sinh vien: " << ten << endl;
    }
}

// ================= MAIN =================
int main() {
    DanhSach L;
    
    // Bước 1: Khởi tạo danh sách mẫu
    cout << "1. Khoi tao danh sach mau:\n";
    KhoiTaoDanhSachMau(L);
    HienThi(L);
    
    // Bước 2: Thêm một sinh viên mới vào cuối
    cout << "\n2. Them mot sinh vien moi vao cuoi:\n";
    SinhVien svMoi = {5, "Hoang Van E", 8.7};
    if (ThemCuoi(L, svMoi)) {
        cout << "Da them thanh cong!\n";
    }
    HienThi(L);
    
    // Bước 3: Sửa điểm của một bạn
    cout << "\n3. Sua diem cua mot sinh vien:\n";
    SuaDiemTheoTen(L, "Le Van C", 7.9);
    HienThi(L);
    
    // Bước 4: Thêm một bạn điểm thấp để test xóa
    cout << "\n4. Them sinh vien diem yeu de test xoa:\n";
    SinhVien svYeu = {6, "Nguyen Thi F", 4.2};
    ThemCuoi(L, svYeu);
    HienThi(L);
    
    // Bước 5: Xóa sinh viên yếu kém
    cout << "\n5. Xoa sinh vien diem yeu kem:\n";
    XoaYeuKem(L);
    HienThi(L);
    
    // Bước 6: Xóa tại vị trí cụ thể (ví dụ xóa vị trí 1 - 0-based)
    cout << "\n6. Xoa sinh vien tai vi tri 1 (0-based):\n";
    if (XoaTaiViTri(L, 1)) {
        cout << "Da xoa thanh cong!\n";
    }
    HienThi(L);
    
    cout << "\nKet thuc chuong trinh.\n";
    return 0;
}