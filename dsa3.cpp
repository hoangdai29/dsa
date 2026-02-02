#include <bits/stdc++.h>
using namespace std;

// Cấu trúc thông tin (đổi tên cho phù hợp với ví dụ của thầy)
struct SinhVien {
    int stt;            // số thứ tự (có thể tự sinh hoặc nhập)
    char ten[50];       // họ tên
    float diem;         // điểm trung bình
};

// Node của danh sách liên kết
struct Node {
    SinhVien infor;
    Node* next;
};

typedef Node* Tro;

// 1. Khởi tạo danh sách rỗng
void KhoiTao(Tro &L) {
    L = NULL;
}

// 2. Tạo node mới
Tro TaoNode(SinhVien x) {
    Tro p = new Node;
    p->infor = x;
    p->next = NULL;
    return p;
}

// 3. Thêm vào cuối (dùng khi khởi tạo hoặc thêm mới)
void ChenCuoi(Tro &L, SinhVien x) {
    Tro p = TaoNode(x);
    if (L == NULL) {
        L = p;
        return;
    }
    Tro q = L;
    while (q->next != NULL) q = q->next;
    q->next = p;
}

// 4. Khởi tạo danh sách mẫu (hard-code)
void KhoiTaoDanhSachMau(Tro &L) {
    KhoiTao(L);
    
    SinhVien sv1 = {1, "Nguyen Van A", 7.5};
    SinhVien sv2 = {2, "Tran Thi B", 8.2};
    SinhVien sv3 = {3, "Le Van C", 6.8};
    SinhVien sv4 = {4, "Pham Thi D", 9.0};
    
    ChenCuoi(L, sv1);
    ChenCuoi(L, sv2);
    ChenCuoi(L, sv3);
    ChenCuoi(L, sv4);
}

// 5. Hiển thị danh sách
void HienThi(Tro L) {
    if (L == NULL) {
        cout << "Danh sach rong!\n";
        return;
    }
    
    cout << left;
    cout << setw(6) << "STT"
         << setw(25) << "Ho va ten"
         << setw(10) << "Diem TB" << endl;
    cout << string(50, '-') << endl;
    
    Tro q = L;
    int cnt = 1;
    while (q != NULL) {
        cout << setw(6) << cnt++
             << setw(25) << q->infor.ten
             << setw(10) << fixed << setprecision(1) << q->infor.diem << endl;
        q = q->next;
    }
    cout << endl;
}

// 6. Thêm một sinh viên mới vào cuối (ví dụ)
void ThemSinhVien(Tro &L, int stt, const char* ten, float diem) {
    SinhVien sv = {stt, "", diem};
    strcpy(sv.ten, ten);
    ChenCuoi(L, sv);
    cout << "Da them sinh vien: " << ten << " - Diem: " << diem << endl;
}

// 7. Xóa sinh viên có điểm < 5.0 (ví dụ xóa theo điều kiện)
void XoaYeuKem(Tro &L) {
    Tro q = L;
    Tro prev = NULL;
    
    while (q != NULL) {
        if (q->infor.diem < 5.0) {
            if (prev == NULL) {  // xóa đầu
                L = q->next;
                delete q;
                q = L;
            } else {
                prev->next = q->next;
                delete q;
                q = prev->next;
            }
        } else {
            prev = q;
            q = q->next;
        }
    }
    cout << "Da xoa cac sinh vien yeu kem (diem < 5.0)\n";
}

// 8. Sửa điểm của sinh viên theo tên (ví dụ)
void SuaDiemTheoTen(Tro L, const char* ten, float diem_moi) {
    Tro q = L;
    bool found = false;
    while (q != NULL) {
        if (strcmp(q->infor.ten, ten) == 0) {
            q->infor.diem = diem_moi;
            found = true;
            cout << "Da sua diem cua " << ten << " thanh " << diem_moi << endl;
        }
        q = q->next;
    }
    if (!found) {
        cout << "Khong tim thay sinh vien: " << ten << endl;
    }
}

// ================= MAIN =================
int main() {
    Tro L;
    
    // Bước 1: Khởi tạo danh sách mẫu (theo yêu cầu của thầy)
    cout << "1. Khoi tao danh sach mau:\n";
    KhoiTaoDanhSachMau(L);
    HienThi(L);
    
    // Bước 2: Thêm một sinh viên mới
    cout << "\n2. Them mot sinh vien moi:\n";
    ThemSinhVien(L, 5, "Hoang Van E", 8.7);
    HienThi(L);
    
    // Bước 3: Sửa điểm của một bạn
    cout << "\n3. Sua diem cua mot sinh vien:\n";
    SuaDiemTheoTen(L, "Le Van C", 7.9);
    HienThi(L);
    
    // Bước 4: Xóa sinh viên yếu kém (ví dụ)
    cout << "\n4. Xoa sinh vien diem yeu (< 5.0):\n";
    // Hiện tại chưa có ai dưới 5, nhưng nếu thêm thì sẽ xóa
    XoaYeuKem(L);
    HienThi(L);
    
    // Bước 5: Thêm một bạn điểm thấp để test xóa
    cout << "\n5. Them sinh vien diem yeu de test xoa:\n";
    ThemSinhVien(L, 6, "Nguyen Thi F", 4.2);
    HienThi(L);
    
    cout << "\n6. Xoa lai sinh vien yeu kem:\n";
    XoaYeuKem(L);
    HienThi(L);
    
    // Giải phóng bộ nhớ
    while (L != NULL) {
        Tro tam = L;
        L = L->next;
        delete tam;
    }
    
    cout << "\nKet thuc chuong trinh.\n";
    return 0;
}