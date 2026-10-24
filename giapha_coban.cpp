// ============================================================
//  QUẢN LÝ GIA PHẢ GIA TỘC MINI 
//  Cây đa phân biểu diễn bằng cây nhị phân LCRS
//     firstChild  = con đầu tiên
//     nextSibling = anh/chị/em kế tiếp.
// 
//  Chỉ dùng kiến thức C++ phổ thông: biến, if/for/while, hàm,
//  mảng, struct, con trỏ, đệ quy, string.
//  (không dùng vector, auto, nullptr, lambda, STL queue...)
//  "dữ liệu mẫu" hoặc "tự nhập gia phả mới".
#include <iostream>
#include <string>
#include <cstdlib>    // atoi, exit
#include <cctype>     // isalnum, tolower
#ifdef _WIN32
#include <windows.h>  // để chỉnh console hiển thị tiếng Việt
#endif
using namespace std;

const int MAX_NODE = 1000;              // số thành viên tối đa
const int NAM_NHO_NHAT = 1000;
const int NAM_LON_NHAT = 2100;

// ------------------------------------------------------------
// CẤU TRÚC NÚT (dùng chung cho cả nhóm)
// ------------------------------------------------------------
struct Node {
    string id;           // mã định danh (duy nhất)
    string name;         // họ tên
    int birthYear;       // năm sinh
    char gender;         // 'M' = Nam, 'F' = Nữ
    Node* firstChild;    // con đầu tiên
    Node* nextSibling;   // anh/chị/em kế tiếp
};

Node* root = NULL;       // NULL nghĩa là gia phả rỗng

// ------------------------------------------------------------
// KHAI BÁO TRƯỚC CÁC HÀM (để mỗi người viết phần của mình
// theo thứ tự nào cũng được)
// ------------------------------------------------------------
// --- PHẦN 1
string catKhoangTrang(string s);
string docDong(string loiNhac);
bool laSoNguyen(string s);
int docSoNguyen(string loiNhac, int nho, int lon);
bool xacNhan(string cauHoi);
string tenGioiTinh(char g);
bool maHopLe(string ma);
bool tenHopLe(string ten);
Node* taoNode(string id, string name, int nam, char gt);
void xoaCay(Node* n);
Node* timTheoMa(Node* n, string ma);
Node* timCha(Node* n, Node* dich);
bool namTrongCayCon(Node* goc, Node* dich);
int demCon(Node* n);
int demThanhVien(Node* n);
void themConCuoi(Node* cha, Node* con);
void thayTheTrongDanhSach(Node* cha, Node* x, Node* thayThe);
void tachNode(Node* cha, Node* x);
Node* hoiThanhVien(string loiNhac);
void inThongTin(Node* n);
void taoDuLieuMau();
void menuKhoiTao();
void hienHuongDanNhap();
void hienMenu();
// --- PHẦN 2
Node* nhapThanhVienMoi(Node* cha);
void themThanhVien();
void timTheoTen(Node* n, string tuKhoa, int& soKetQua);
void timKiem();
void suaThanhVien();
void xoaThanhVien();
// --- PHẦN 3
void chuyenNhanh();
void themConVaQuanHe();
void hienThiDanhSachCon();
void hienThiAnhChiEm();
void inMoTaQuanHe(int da, int db);
void traCuuQuanHe();
// --- PHẦN 4
int tinhTheHe(Node* n, Node* dich, int doSau);
void dfsDeQuy(Node* n, int doSau);
void menuDFS();
void menuBFS();
Node* timLCA(Node* goc, Node* a, Node* b);
bool timDuongDi(Node* n, Node* dich, Node* duong[], int& soLuong);
void menuLCA();
void menuTheHe();
// --- PHẦN 5
int chieuCao(Node* n);
void demGioiTinh(Node* n, int& nam, int& nu);
void timNamSinhNhoNhat(Node* n, int& namNho);
void inNguoiSinhNam(Node* n, int nam, bool& laDauTien);
void thongKe();
void inCayPhanCap(Node* n, string tienTo, bool laCuoi, bool laGoc);
int doRongHienThi(string s);
string soSangChuoi(int v);
void hienThiBangThanhVien();
void xuatGiaPha();


// Cắt khoảng trắng ở đầu và cuối chuỗi
string catKhoangTrang(string s) {
    int dau = 0;
    int cuoi = (int)s.length() - 1;
    while (dau <= cuoi && (s[dau] == ' ' || s[dau] == '\t' || s[dau] == '\r' || s[dau] == '\n'))
        dau++;
    while (cuoi >= dau && (s[cuoi] == ' ' || s[cuoi] == '\t' || s[cuoi] == '\r' || s[cuoi] == '\n'))
        cuoi--;
    return s.substr(dau, cuoi - dau + 1);
}

// In lời nhắc, đọc cả dòng, cắt khoảng trắng thừa
string docDong(string loiNhac) {
    cout << loiNhac;
    string s;
    if (!getline(cin, s)) {            // hết dữ liệu nhập
        cout << "\n(Hết dữ liệu nhập, thoát chương trình)\n";
        exit(0);
    }
    return catKhoangTrang(s);
}

// Chuỗi chỉ gồm chữ số (và không rỗng)?
bool laSoNguyen(string s) {
    if (s.length() == 0) return false;
    for (int i = 0; i < (int)s.length(); i++) {
        if (s[i] < '0' || s[i] > '9') return false;
    }
    return true;
}

// Đọc số nguyên trong đoạn [nho, lon], nhập sai thì hỏi lại
int docSoNguyen(string loiNhac, int nho, int lon) {
    while (true) {
        string s = docDong(loiNhac);
        if (laSoNguyen(s) && s.length() <= 9) {
            int v = atoi(s.c_str());
            if (v >= nho && v <= lon) return v;
        }
        cout << "  ! Hãy nhập số nguyên từ " << nho << " đến " << lon << ".\n";
    }
}

bool xacNhan(string cauHoi) {
    string s = docDong(cauHoi + " (c/k): ");
    return (s == "c" || s == "C" || s == "y" || s == "Y");
}

string tenGioiTinh(char g) {
    if (g == 'M') return "Nam";
    return "Nữ";
}

// Mã hợp lệ: không rỗng, chỉ gồm chữ, số, '_' hoặc '-', ký tự đầu là chữ/số
bool maHopLe(string ma) {
    if (ma.length() == 0) return false;
    if (!isalnum((unsigned char)ma[0])) return false;
    for (int i = 0; i < (int)ma.length(); i++) {
        unsigned char c = (unsigned char)ma[i];
        if (!isalnum(c) && c != '_' && c != '-') return false;
    }
    return true;
}

// Tên hợp lệ: không rỗng và không chứa dấu '|' (vì '|' dùng để ngăn cách trong tệp)
bool tenHopLe(string ten) {
    if (ten.length() == 0) return false;
    if (ten.find('|') != string::npos) return false;
    return true;
}

// ---------- Thao tác cơ bản trên cây LCRS ----------

Node* taoNode(string id, string name, int nam, char gt) {
    Node* n = new Node;
    n->id = id;
    n->name = name;
    n->birthYear = nam;
    n->gender = gt;
    n->firstChild = NULL;
    n->nextSibling = NULL;
    return n;
}

// Giải phóng nút n, mọi con cháu của n VÀ các em kế tiếp của n.
// Vì vậy chỉ gọi khi n đã được tách khỏi danh sách anh em.
void xoaCay(Node* n) {
    if (n == NULL) return;
    xoaCay(n->firstChild);
    xoaCay(n->nextSibling);
    delete n;
}

// Tìm theo mã: xét nút này -> tìm ở con đầu -> tìm ở em kế tiếp
Node* timTheoMa(Node* n, string ma) {
    if (n == NULL) return NULL;
    if (n->id == ma) return n;
    Node* kq = timTheoMa(n->firstChild, ma);
    if (kq != NULL) return kq;
    return timTheoMa(n->nextSibling, ma);
}

// Tìm cha/mẹ của nút dich (trả về NULL nếu dich là gốc)
Node* timCha(Node* n, Node* dich) {
    if (n == NULL) return NULL;
    Node* c;
    for (c = n->firstChild; c != NULL; c = c->nextSibling) {
        if (c == dich) return n;          // c là con của n
    }
    for (c = n->firstChild; c != NULL; c = c->nextSibling) {
        Node* kq = timCha(c, dich);
        if (kq != NULL) return kq;
    }
    return NULL;
}

// dich có nằm trong cây con có gốc "goc" không? (kể cả dich == goc)
bool namTrongCayCon(Node* goc, Node* dich) {
    if (goc == NULL) return false;
    if (goc == dich) return true;
    for (Node* c = goc->firstChild; c != NULL; c = c->nextSibling) {
        if (namTrongCayCon(c, dich)) return true;
    }
    return false;
}

// Số con trực tiếp của n: đi qua con đầu rồi các em của con đầu
int demCon(Node* n) {
    int dem = 0;
    for (Node* c = n->firstChild; c != NULL; c = c->nextSibling) dem++;
    return dem;
}

// Đếm n + toàn bộ con cháu + các em của n (toàn bộ cây LCRS bắt đầu từ n)
int demThanhVien(Node* n) {
    if (n == NULL) return 0;
    return 1 + demThanhVien(n->firstChild) + demThanhVien(n->nextSibling);
}

// Thêm "con" vào CUỐI danh sách con của "cha"
void themConCuoi(Node* cha, Node* con) {
    con->nextSibling = NULL;
    if (cha->firstChild == NULL) {
        cha->firstChild = con;
    } else {
        Node* t = cha->firstChild;
        while (t->nextSibling != NULL) t = t->nextSibling;
        t->nextSibling = con;
    }
}

// Trong danh sách con của "cha", thay nút x bằng chuỗi "thayThe"
void thayTheTrongDanhSach(Node* cha, Node* x, Node* thayThe) {
    if (cha->firstChild == x) {
        cha->firstChild = thayThe;
    } else {
        Node* truoc = cha->firstChild;
        while (truoc != NULL && truoc->nextSibling != x) truoc = truoc->nextSibling;
        if (truoc != NULL) truoc->nextSibling = thayThe;
    }
}

// Tách x (cùng con cháu của x) ra khỏi danh sách con của cha
void tachNode(Node* cha, Node* x) {
    thayTheTrongDanhSach(cha, x, x->nextSibling);   // anh nối thẳng sang em của x
    x->nextSibling = NULL;
}

// Hỏi mã và tìm thành viên; báo lỗi nếu không thấy
Node* hoiThanhVien(string loiNhac) {
    string ma = docDong(loiNhac);
    Node* n = timTheoMa(root, ma);
    if (n == NULL) cout << "  ! Không tìm thấy thành viên có mã '" << ma << "'.\n";
    return n;
}

void inThongTin(Node* n) {
    Node* cha = timCha(root, n);
    cout << "  Mã: " << n->id << " | Tên: " << n->name
         << " | Năm sinh: " << n->birthYear
         << " | Giới tính: " << tenGioiTinh(n->gender) << "\n";
    cout << "  Cha/mẹ: ";
    if (cha == NULL) cout << "(người gốc)";
    else cout << cha->name << " [" << cha->id << "]";
    cout << " | Số con: " << demCon(n)
         << " | Thế hệ: " << tinhTheHe(root, n, 1) << "\n";
}

// Dữ liệu mẫu (khai báo trực tiếp trong code): 10 người, 4 thế hệ
//   G001 (gốc) -> G002, G003, G004
//   G002 -> G005, G006     G003 -> G007, G008     G005 -> G009, G010
// Mỗi người được tạo đúng một lần và gắn vào đúng một cha/mẹ.
void taoDuLieuMau() {
    xoaCay(root);
    root = taoNode("G001", "Nguyen Van An", 1940, 'M');
    Node* g002 = taoNode("G002", "Nguyen Van Binh", 1965, 'M');
    Node* g003 = taoNode("G003", "Nguyen Thi Lan", 1968, 'F');
    Node* g004 = taoNode("G004", "Nguyen Van Dung", 1972, 'M');
    Node* g005 = taoNode("G005", "Nguyen Van Cuong", 1990, 'M');
    Node* g006 = taoNode("G006", "Nguyen Thi Dao", 1993, 'F');
    Node* g007 = taoNode("G007", "Tran Van Duc", 1992, 'M');
    Node* g008 = taoNode("G008", "Tran Thi Em", 1995, 'F');
    Node* g009 = taoNode("G009", "Nguyen Van Khoa", 2015, 'M');
    Node* g010 = taoNode("G010", "Nguyen Thi Hoa", 2018, 'F');
    themConCuoi(root, g002);
    themConCuoi(root, g003);
    themConCuoi(root, g004);
    themConCuoi(g002, g005);
    themConCuoi(g002, g006);
    themConCuoi(g003, g007);
    themConCuoi(g003, g008);
    themConCuoi(g005, g009);
    themConCuoi(g005, g010);
}

// Hướng dẫn nhập thành viên (hiện khi chọn tự nhập gia phả mới)
void hienHuongDanNhap() {
    cout << "\n========== HUONG DAN NHAP THANH VIEN ==========\n\n";
    cout << "Moi thanh vien can co cac thong tin:\n";
    cout << "1. Ma thanh vien: Ma rieng, khong duoc trung.\n";
    cout << "2. Ho va ten: Nhap day du ho ten.\n";
    cout << "3. Nam sinh: Nhap nam sinh hop le.\n";
    cout << "4. Gioi tinh: Chon Nam hoac Nu theo quy uoc cua chuong trinh.\n";
    cout << "5. Ma cha/me: Nhap ma cua thanh vien cha/me da ton tai.\n\n";
    cout << "Luu y:\n";
    cout << "- Thanh vien dau tien se la goc cua gia pha.\n";
    cout << "- Thanh vien dau tien khong can nhap ma cha/me.\n";
    cout << "- Tu thanh vien thu hai tro di, can nhap ma cha/me da ton tai.\n";
    cout << "- Neu nhap sai, chuong trinh phai thong bao va cho nhap lai.\n";
}

// Menu chọn dữ liệu ban đầu khi khởi động chương trình
//  1: gọi taoDuLieuMau() (đúng 1 lần) rồi hiển thị bảng thành viên
//  2: root = NULL -> cây rỗng, hiện hướng dẫn nhập
// Không đọc/ghi bất kỳ tệp nào.
void menuKhoiTao() {
    cout << "\n========== KHOI TAO GIA PHA ==========\n";
    cout << "1. Su dung du lieu mau\n";
    cout << "2. Tu nhap du lieu gia pha moi\n";
    int chon = docSoNguyen("Lua chon cua ban: ", 1, 2);
    if (chon == 1) {
        taoDuLieuMau();
        cout << "\n";
        hienThiBangThanhVien();
    } else {
        xoaCay(root);          // lúc khởi động root đang là NULL nên không có gì để xóa
        root = NULL;           // cây hoàn toàn rỗng
        hienHuongDanNhap();
    }
}

void hienMenu() {
    cout << "\n================ QUẢN LÝ GIA PHẢ GIA TỘC MINI ================\n";
    cout << " 1. Thêm thành viên\n";
    cout << " 2. Tìm kiếm thành viên\n";
    cout << " 3. Sửa thông tin thành viên\n";
    cout << " 4. Xóa thành viên\n";
    cout << " 5. Thêm con và thiết lập quan hệ gia đình\n";
    cout << " 6. Hiển thị danh sách con\n";
    cout << " 7. Hiển thị anh/chị/em\n";
    cout << " 8. Duyệt cây DFS\n";
    cout << " 9. Duyệt cây BFS\n";
    cout << "10. Tìm tổ tiên chung gần nhất LCA\n";
    cout << "11. Tra cứu quan hệ họ hàng\n";
    cout << "12. Tính bậc thế hệ\n";
    cout << "13. Thống kê gia phả\n";
    cout << "14. Xuất gia phả dạng cây phân cấp\n";
    cout << " 0. Thoát chương trình\n";
    cout << "==============================================================\n";
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);   // console Windows hiển thị UTF-8
#endif
    // Khởi động: cho người dùng chọn dữ liệu mẫu hoặc cây rỗng
    menuKhoiTao();

    int chon = -1;
    while (chon != 0) {
        hienMenu();
        chon = docSoNguyen("Chọn chức năng (0-14): ", 0, 14);
        cout << "\n";
        switch (chon) {
            case 1:  themThanhVien();       break;
            case 2:  timKiem();             break;
            case 3:  suaThanhVien();        break;
            case 4:  xoaThanhVien();        break;
            case 5:  themConVaQuanHe();     break;
            case 6:  hienThiDanhSachCon();  break;
            case 7:  hienThiAnhChiEm();     break;
            case 8:  menuDFS();             break;
            case 9:  menuBFS();             break;
            case 10: menuLCA();             break;
            case 11: traCuuQuanHe();        break;
            case 12: menuTheHe();           break;
            case 13: thongKe();             break;
            case 14: xuatGiaPha();          break;
            case 0:
                if (!xacNhan("Thoát chương trình? (dữ liệu chỉ nằm trong bộ nhớ nên sẽ mất)")) chon = -1;   // không thoát
                break;
        }
    }
    xoaCay(root);      // trả bộ nhớ trước khi kết thúc
    cout << "Tạm biệt!\n";
    return 0;
}


// Nhập thông tin một thành viên mới; "cha" = NULL nếu là người gốc.
// Trả về NULL nếu người dùng hủy (để trống mã).
Node* nhapThanhVienMoi(Node* cha) {
    string id;
    while (true) {
        id = docDong("Mã định danh (chữ/số/_/-, Enter để hủy): ");
        if (id == "") return NULL;
        if (!maHopLe(id)) {
            cout << "  ! Mã không hợp lệ (không có khoảng trắng hoặc ký tự lạ).\n";
        } else if (timTheoMa(root, id) != NULL) {
            cout << "  ! Mã này đã tồn tại, hãy chọn mã khác.\n";
        } else {
            break;
        }
    }
    string ten;
    while (true) {
        ten = docDong("Họ tên: ");
        if (tenHopLe(ten)) break;
        cout << "  ! Tên không được để trống và không chứa ký tự '|'.\n";
    }
    int nam;
    while (true) {
        nam = docSoNguyen("Năm sinh: ", NAM_NHO_NHAT, NAM_LON_NHAT);
        if (cha != NULL && nam <= cha->birthYear) {
            cout << "  ! Năm sinh phải lớn hơn năm sinh của cha/mẹ (" << cha->birthYear << ").\n";
        } else {
            break;
        }
    }
    int gt = docSoNguyen("Giới tính (1 = Nam, 2 = Nữ): ", 1, 2);
    char kyHieu = 'F';
    if (gt == 1) kyHieu = 'M';
    return taoNode(id, ten, nam, kyHieu);
}

// Chức năng 1: thêm thành viên
void themThanhVien() {
    if (demThanhVien(root) >= MAX_NODE) {
        cout << "  ! Đã đạt số thành viên tối đa (" << MAX_NODE << ").\n";
        return;
    }
    Node* cha = NULL;
    if (root == NULL) {
        cout << "Gia phả đang rỗng: thành viên đầu tiên sẽ là NGƯỜI GỐC.\n";
    } else {
        cout << "(Mỗi người, trừ người gốc, phải có cha/mẹ trong gia phả)\n";
        string maCha = docDong("Mã cha/mẹ (Enter để hủy): ");
        if (maCha == "") return;
        cha = timTheoMa(root, maCha);
        if (cha == NULL) {
            cout << "  ! Không tìm thấy cha/mẹ có mã '" << maCha << "'.\n";
            return;
        }
    }
    Node* moi = nhapThanhVienMoi(cha);
    if (moi == NULL) {
        cout << "  Đã hủy.\n";
        return;
    }
    if (cha == NULL) {
        root = moi;
        cout << "  => Đã tạo người gốc: " << moi->name << "\n";
    } else {
        themConCuoi(cha, moi);
        cout << "  => Đã thêm " << moi->name << " làm con của " << cha->name << ".\n";
    }
}

// Tìm theo tên: in mọi thành viên có tên chứa "tuKhoa" (phân biệt hoa/thường)
void timTheoTen(Node* n, string tuKhoa, int& soKetQua) {
    if (n == NULL) return;
    if (n->name.find(tuKhoa) != string::npos) {
        inThongTin(n);
        soKetQua++;
    }
    timTheoTen(n->firstChild, tuKhoa, soKetQua);
    timTheoTen(n->nextSibling, tuKhoa, soKetQua);
}

// Chức năng 2: tìm kiếm
void timKiem() {
    if (root == NULL) {
        cout << "  ! Gia phả đang rỗng.\n";
        return;
    }
    int cach = docSoNguyen("Tìm theo: 1 = Mã, 2 = Tên : ", 1, 2);
    if (cach == 1) {
        string ma = docDong("Nhập mã: ");
        Node* n = timTheoMa(root, ma);
        if (n == NULL) cout << "  ! Không tìm thấy thành viên có mã '" << ma << "'.\n";
        else inThongTin(n);
    } else {
        string tuKhoa = docDong("Nhập tên (hoặc một phần tên): ");
        if (tuKhoa == "") {
            cout << "  ! Bạn chưa nhập tên.\n";
            return;
        }
        int soKetQua = 0;
        timTheoTen(root, tuKhoa, soKetQua);
        if (soKetQua == 0) cout << "  ! Không tìm thấy thành viên nào.\n";
        else cout << "  => Tìm thấy " << soKetQua << " thành viên.\n";
    }
}

// Chức năng 3: sửa thông tin (không cho sửa mã)
void suaThanhVien() {
    if (root == NULL) {
        cout << "  ! Gia phả đang rỗng.\n";
        return;
    }
    Node* n = hoiThanhVien("Mã thành viên cần sửa: ");
    if (n == NULL) return;
    inThongTin(n);
    Node* cha = timCha(root, n);

    string s = docDong("Tên mới (Enter = giữ nguyên): ");
    if (s != "") {
        if (tenHopLe(s)) n->name = s;
        else cout << "  ! Tên không hợp lệ, giữ nguyên.\n";
    }

    s = docDong("Năm sinh mới (Enter = giữ nguyên): ");
    if (s != "") {
        bool hopLe = laSoNguyen(s) && s.length() <= 4;
        int nam = 0;
        if (hopLe) {
            nam = atoi(s.c_str());
            if (nam < NAM_NHO_NHAT || nam > NAM_LON_NHAT) hopLe = false;
        }
        if (hopLe && cha != NULL && nam <= cha->birthYear) hopLe = false;     // phải sau cha/mẹ
        for (Node* c = n->firstChild; hopLe && c != NULL; c = c->nextSibling) {
            if (c->birthYear <= nam) hopLe = false;                           // phải trước các con
        }
        if (hopLe) n->birthYear = nam;
        else cout << "  ! Năm sinh không hợp lệ hoặc mâu thuẫn với cha/mẹ - con, giữ nguyên.\n";
    }

    s = docDong("Giới tính mới (1 = Nam, 2 = Nữ, Enter = giữ nguyên): ");
    if (s == "1") n->gender = 'M';
    else if (s == "2") n->gender = 'F';
    else if (s != "") cout << "  ! Lựa chọn không hợp lệ, giữ nguyên.\n";

    cout << "  => Thông tin sau khi sửa:\n";
    inThongTin(n);
}

// Chức năng 4: xóa thành viên
// Quy định xử lý hậu duệ:
//   Cách 1: chỉ xóa người này, con cháu được nối lên cho cha/mẹ của người bị xóa
//   Cách 2: xóa cả nhánh (có hỏi xác nhận)
void xoaThanhVien() {
    if (root == NULL) {
        cout << "  ! Gia phả đang rỗng.\n";
        return;
    }
    Node* x = hoiThanhVien("Mã thành viên cần xóa: ");
    if (x == NULL) return;
    inThongTin(x);
    cout << "Cách xóa:\n";
    cout << "  1 = Chỉ xóa người này (con cháu được nối lên cho cha/mẹ của họ)\n";
    cout << "  2 = Xóa cả nhánh (người này và toàn bộ hậu duệ)\n";
    int cach = docSoNguyen("Chọn: ", 1, 2);
    Node* cha = timCha(root, x);

    if (cach == 2) {
        int soNguoi = 1 + demThanhVien(x->firstChild);     // x + toàn bộ hậu duệ
        cout << "  Sẽ xóa " << soNguoi << " người.\n";
        if (!xacNhan("Xác nhận xóa cả nhánh?")) {
            cout << "  Đã hủy.\n";
            return;
        }
        if (cha == NULL) {
            xoaCay(root);
            root = NULL;
        } else {
            tachNode(cha, x);      // tách khỏi danh sách anh em trước
            xoaCay(x);
        }
        cout << "  => Đã xóa " << soNguoi << " thành viên.\n";
        return;
    }

    // ----- cách 1 -----
    if (cha == NULL) {                               // x là người gốc
        if (x->firstChild == NULL) {
            delete x;
            root = NULL;
        } else if (x->firstChild->nextSibling == NULL) {   // gốc chỉ có 1 con
            Node* moi = x->firstChild;
            delete x;
            root = moi;
            cout << "  (" << moi->name << " trở thành người gốc mới)\n";
        } else {
            cout << "  ! Người gốc có nhiều con nên không thể chỉ xóa riêng người gốc\n";
            cout << "    (sẽ tạo ra nhiều cây). Hãy chọn cách 2.\n";
            return;
        }
        cout << "  => Đã xóa.\n";
        return;
    }
    if (!xacNhan("Xóa " + x->name + " (con cháu chuyển lên " + cha->name + ")?")) {
        cout << "  Đã hủy.\n";
        return;
    }
    Node* conDau = x->firstChild;
    Node* emKe = x->nextSibling;
    Node* thayThe = emKe;
    if (conDau != NULL) {
        // nối chuỗi con của x vào trước em kế tiếp của x
        Node* cuoi = conDau;
        while (cuoi->nextSibling != NULL) cuoi = cuoi->nextSibling;
        cuoi->nextSibling = emKe;
        thayThe = conDau;
    }
    thayTheTrongDanhSach(cha, x, thayThe);
    delete x;
    cout << "  => Đã xóa; con cháu được chuyển lên làm con của " << cha->name << ".\n";
}




// Chuyển một thành viên (cùng hậu duệ) sang làm con của người khác
void chuyenNhanh() {
    if (root == NULL) {
        cout << "  ! Gia phả đang rỗng.\n";
        return;
    }
    Node* con = hoiThanhVien("Mã thành viên cần chuyển: ");
    if (con == NULL) return;
    Node* chaMoi = hoiThanhVien("Mã cha/mẹ mới: ");
    if (chaMoi == NULL) return;

    if (con == root) {
        cout << "  ! Người gốc không thể trở thành con của ai.\n";
        return;
    }
    if (con == chaMoi) {
        cout << "  ! Một người không thể là cha/mẹ của chính mình.\n";
        return;
    }
    if (namTrongCayCon(con, chaMoi)) {
        cout << "  ! Từ chối: " << chaMoi->name << " là hậu duệ của " << con->name
             << " nên sẽ tạo chu trình.\n";
        return;
    }
    Node* chaCu = timCha(root, con);
    if (chaCu == chaMoi) {
        cout << "  ! " << con->name << " đã là con của " << chaMoi->name << ".\n";
        return;
    }
    if (con->birthYear <= chaMoi->birthYear) {
        cout << "  ! Năm sinh của con phải lớn hơn năm sinh của cha/mẹ mới.\n";
        return;
    }
    tachNode(chaCu, con);        // gỡ khỏi chỗ cũ -> không nằm ở 2 nhánh
    themConCuoi(chaMoi, con);
    cout << "  => Đã chuyển " << con->name << " (cùng hậu duệ) sang làm con của "
         << chaMoi->name << ".\n";
}

// Chức năng 5
void themConVaQuanHe() {
    cout << "  1 = Tạo thành viên mới làm con\n";
    cout << "  2 = Chuyển thành viên đã có sang làm con của người khác\n";
    int chon = docSoNguyen("Chọn: ", 1, 2);
    if (chon == 1) themThanhVien();
    else chuyenNhanh();
}

// Chức năng 6: danh sách con
void hienThiDanhSachCon() {
    if (root == NULL) {
        cout << "  ! Gia phả đang rỗng.\n";
        return;
    }
    Node* n = hoiThanhVien("Mã cha/mẹ: ");
    if (n == NULL) return;
    if (n->firstChild == NULL) {
        cout << "  " << n->name << " chưa có con.\n";
        return;
    }
    cout << "  Con của " << n->name << " (" << demCon(n) << " người):\n";
    int stt = 1;
    for (Node* c = n->firstChild; c != NULL; c = c->nextSibling) {
        cout << "   " << stt << ". " << c->name << " [" << c->id << "] - "
             << c->birthYear << ", " << tenGioiTinh(c->gender) << "\n";
        stt++;
    }
}

// Chức năng 7: anh/chị/em = các con khác của cùng cha/mẹ
void hienThiAnhChiEm() {
    if (root == NULL) {
        cout << "  ! Gia phả đang rỗng.\n";
        return;
    }
    Node* n = hoiThanhVien("Mã thành viên: ");
    if (n == NULL) return;
    Node* cha = timCha(root, n);
    if (cha == NULL) {
        cout << "  " << n->name << " là người gốc nên không có anh/chị/em.\n";
        return;
    }
    int dem = 0;
    for (Node* c = cha->firstChild; c != NULL; c = c->nextSibling) {
        if (c == n) continue;                // bỏ qua chính mình
        if (dem == 0)
            cout << "  Anh/chị/em của " << n->name << " (cùng cha/mẹ " << cha->name << "):\n";
        cout << "   - " << c->name << " [" << c->id << "] - " << c->birthYear
             << ", " << tenGioiTinh(c->gender) << "\n";
        dem++;
    }
    if (dem == 0) cout << "  " << n->name << " là con một (không có anh/chị/em).\n";
}

// da, db = số đời từ A (và B) lên tổ tiên chung. In "A là ... của B"
void inMoTaQuanHe(int da, int db) {
    if (da == 0 && db == 0) {
        cout << "cùng một người";
    } else if (da == 0) {                          // A là tổ tiên của B
        if (db == 1) cout << "cha/mẹ";
        else if (db == 2) cout << "ông/bà";
        else if (db == 3) cout << "cụ";
        else cout << "tổ tiên (cách " << db << " đời)";
    } else if (db == 0) {                          // A là hậu duệ của B
        if (da == 1) cout << "con";
        else if (da == 2) cout << "cháu";
        else if (da == 3) cout << "chắt";
        else cout << "hậu duệ (cách " << da << " đời)";
    } else if (da == 1 && db == 1) {
        cout << "anh/chị/em (cùng cha/mẹ)";
    } else if (da == 1 && db == 2) {
        cout << "chú/bác/cô/cậu/dì (anh/chị/em của cha/mẹ)";
    } else if (da == 2 && db == 1) {
        cout << "cháu (con của anh/chị/em)";
    } else if (da == 2 && db == 2) {
        cout << "anh/chị/em họ";
    } else {
        cout << "họ hàng (A cách tổ tiên chung " << da << " đời, B cách " << db << " đời)";
    }
}

// Chức năng 11: tra cứu quan hệ họ hàng giữa A và B
void traCuuQuanHe() {
    if (root == NULL) {
        cout << "  ! Gia phả đang rỗng.\n";
        return;
    }
    Node* a = hoiThanhVien("Mã thành viên A: ");
    if (a == NULL) return;
    Node* b = hoiThanhVien("Mã thành viên B: ");
    if (b == NULL) return;

    Node* l = timLCA(root, a, b);                 // tổ tiên chung gần nhất
    Node* duongA[MAX_NODE];
    Node* duongB[MAX_NODE];
    int soA = 0, soB = 0;
    timDuongDi(root, a, duongA, soA);             // đường từ gốc đến A
    timDuongDi(root, b, duongB, soB);             // đường từ gốc đến B

    int theHeL = tinhTheHe(root, l, 1);
    int da = soA - theHeL;                        // số đời từ A lên L
    int db = soB - theHeL;                        // số đời từ B lên L

    cout << "  " << a->name << " là ";
    inMoTaQuanHe(da, db);
    cout << " của " << b->name << ".\n";

    cout << "  Đường quan hệ: ";
    int i;
    for (i = soA - 1; i >= theHeL - 1; i--) {     // từ A đi lên đến L
        cout << duongA[i]->name;
        if (i > theHeL - 1) cout << " -> ";
    }
    for (i = theHeL; i < soB; i++) {              // từ L đi xuống B
        cout << " -> " << duongB[i]->name;
    }
    cout << "\n  (Tổ tiên chung gần nhất: " << l->name << ")\n";
}




// Bậc thế hệ của "dich" (gốc = 1).
//  - đi xuống con đầu (firstChild): thế hệ + 1
//  - đi sang em kế tiếp (nextSibling): CÙNG thế hệ
// Trả về -1 nếu không thấy.
int tinhTheHe(Node* n, Node* dich, int doSau) {
    if (n == NULL) return -1;
    if (n == dich) return doSau;
    int kq = tinhTheHe(n->firstChild, dich, doSau + 1);
    if (kq != -1) return kq;
    return tinhTheHe(n->nextSibling, dich, doSau);   // em: không tăng thế hệ
}

// DFS tiền thứ tự: thăm nút -> thăm con -> thăm em
void dfsDeQuy(Node* n, int doSau) {
    if (n == NULL) return;
    cout << string(doSau * 3, ' ') << "- [" << n->id << "] " << n->name
         << " (" << n->birthYear << ", " << tenGioiTinh(n->gender)
         << ") - thế hệ " << doSau + 1 << "\n";
    dfsDeQuy(n->firstChild, doSau + 1);
    dfsDeQuy(n->nextSibling, doSau);
}

void menuDFS() {
    if (root == NULL) {
        cout << "  ! Gia phả đang rỗng.\n";
        return;
    }
    cout << "--- Duyệt DFS (theo chiều sâu) ---\n";
    dfsDeQuy(root, 0);
}

// BFS: dùng hàng đợi làm bằng mảng (dau = vị trí lấy ra, cuoi = vị trí thêm vào)
void menuBFS() {
    if (root == NULL) {
        cout << "  ! Gia phả đang rỗng.\n";
        return;
    }
    cout << "--- Duyệt BFS (theo thế hệ) ---\n";
    Node* hang[MAX_NODE];        // hàng đợi các nút
    int mucNut[MAX_NODE];        // thế hệ của từng nút trong hàng đợi
    int dau = 0, cuoi = 0;
    hang[cuoi] = root;
    mucNut[cuoi] = 1;
    cuoi++;
    int mucHienTai = 0;
    while (dau < cuoi) {
        Node* n = hang[dau];     // lấy phần tử đầu hàng đợi
        int muc = mucNut[dau];
        dau++;
        if (muc != mucHienTai) { // sang thế hệ mới thì xuống dòng
            if (mucHienTai != 0) cout << "\n";
            cout << "Thế hệ " << muc << ": ";
            mucHienTai = muc;
        }
        cout << n->name << " [" << n->id << "]   ";
        // đẩy tất cả CON của n vào hàng đợi (con đầu rồi các em của con đầu)
        for (Node* c = n->firstChild; c != NULL; c = c->nextSibling) {
            hang[cuoi] = c;
            mucNut[cuoi] = muc + 1;
            cuoi++;
        }
    }
    cout << "\n";
}

// LCA: tổ tiên chung gần nhất của a và b (cả hai phải có trong cây).
// Nếu a là tổ tiên của b thì kết quả là a.
Node* timLCA(Node* goc, Node* a, Node* b) {
    if (goc == NULL) return NULL;
    if (goc == a || goc == b) return goc;
    Node* ketQua = NULL;
    int soNhanhThay = 0;
    for (Node* c = goc->firstChild; c != NULL; c = c->nextSibling) {  // chỉ xét CON của goc
        Node* x = timLCA(c, a, b);
        if (x != NULL) {
            soNhanhThay++;
            ketQua = x;
        }
    }
    if (soNhanhThay >= 2) return goc;    // a, b nằm ở hai nhánh con khác nhau
    return ketQua;
}

// Tìm đường đi từ n xuống "dich", ghi vào mảng duong (đệ quy quay lui)
bool timDuongDi(Node* n, Node* dich, Node* duong[], int& soLuong) {
    duong[soLuong] = n;
    soLuong++;
    if (n == dich) return true;
    for (Node* c = n->firstChild; c != NULL; c = c->nextSibling) {
        if (timDuongDi(c, dich, duong, soLuong)) return true;
    }
    soLuong--;                           // không đúng hướng: bỏ n ra khỏi đường đi
    return false;
}

// Chức năng 10
void menuLCA() {
    if (root == NULL) {
        cout << "  ! Gia phả đang rỗng.\n";
        return;
    }
    Node* a = hoiThanhVien("Mã thành viên thứ nhất: ");
    if (a == NULL) return;
    Node* b = hoiThanhVien("Mã thành viên thứ hai: ");
    if (b == NULL) return;
    Node* l = timLCA(root, a, b);
    if (l == NULL) {
        cout << "  ! Không tồn tại tổ tiên chung.\n";
    } else if (a == b) {
        cout << "  Hai mã là cùng một người: " << a->name << ".\n";
    } else if (l == a) {
        cout << "  " << a->name << " là tổ tiên của " << b->name
             << " nên LCA chính là " << l->name << ".\n";
    } else if (l == b) {
        cout << "  " << b->name << " là tổ tiên của " << a->name
             << " nên LCA chính là " << l->name << ".\n";
    } else {
        cout << "  Tổ tiên chung gần nhất của " << a->name << " và " << b->name
             << " là: " << l->name << " [" << l->id << "].\n";
    }
}

// Chức năng 12
void menuTheHe() {
    if (root == NULL) {
        cout << "  ! Gia phả đang rỗng.\n";
        return;
    }
    Node* n = hoiThanhVien("Mã thành viên: ");
    if (n == NULL) return;
    int g = tinhTheHe(root, n, 1);
    cout << "  " << n->name << " thuộc thế hệ " << g;
    if (g == 1) cout << " (người gốc).\n";
    else cout << " (cách người gốc " << g - 1 << " đời).\n";
}


// Số thế hệ = chiều cao của cây
int chieuCao(Node* n){
    if (n == NULL) return 0;
    int hCon = 1 + chieuCao(n->firstChild);    // xuống một thế hệ.
    int hEm = chieuCao(n->nextSibling);        // sang em: cùng thế hệ.
    if (hCon > hEm) return hCon;
    return hEm;
}

void demGioiTinh(Node* n, int& nam, int& nu){
    if (n == NULL) return;
    if (n->gender == 'M') nam++;
    else nu++;
    demGioiTinh(n->firstChild, nam, nu);
    demGioiTinh(n->nextSibling, nam, nu);
} 

void timNamSinhNhoNhat(Node* n, int& namNho){
    if (n == NULL) return;
    if (n->birthYear < namNho) namNho = n->birthYear;
    timNamSinhNhoNhat(n->firstChild, namNho);
    timNamSinhNhoNhat(n->nextSibling, namNho);
}

// In tất cả những người sinh năm "nam" (có thể nhiều người trùng năm).
void inNguoiSinhNam(Node* n, int nam, bool& laDauTien){
    if (n == NULL) return;
    if (n->birthYear == nam) {
        if (!laDauTien) cout << ", ";
        cout << n->name << " [" << n->id << "]";
        laDauTien = false;
    }
    inNguoiSinhNam(n->firstChild, nam, laDauTien);
    inNguoiSinhNam(n->nextSibling, nam, laDauTien);
}

// Chức năng 13
void thongKe() {
    if (root == NULL) {
        cout << "  ! Gia phả đang rỗng.\n";
        return;
    }
    int nam = 0, nu = 0;
    demGioiTinh(root, nam, nu);
    int namNho = NAM_LON_NHAT + 1;
    timNamSinhNhoNhat(root, namNho);

    cout << "--- Thống kê gia phả ---\n";
    cout << "  Tổng số thành viên : " << demThanhVien(root) << "\n";
    cout << "  Số thế hệ          : " << chieuCao(root) << "\n";
    cout << "  Nam / Nữ           : " << nam << " / " << nu << "\n";
    cout << "  Người lớn tuổi nhất (sinh năm " << namNho << "): ";
    bool laDauTien = true;
    inNguoiSinhNam(root, namNho, laDauTien);
    cout << "\n";

    string ma = docDong("Nhập mã để xem số con trực tiếp (Enter = bỏ qua): ");
    if (ma != "") {
        Node* n = timTheoMa(root, ma);
        if (n == NULL) cout << "  ! Không tìm thấy thành viên có mã '" << ma << "'.\n";
        else cout << "  " << n->name << " có " << demCon(n) << " con trực tiếp.\n";
    }
}

// In cây phân cấp có thụt lề
void inCayPhanCap(Node* n, string tienTo, bool laCuoi, bool laGoc) {
    cout << tienTo;
    if (!laGoc) {
        if (laCuoi) cout << "`-- ";
        else cout << "|-- ";
    }
    cout << n->name << " [" << n->id << "] (" << n->birthYear << ", "
         << tenGioiTinh(n->gender) << ")\n";
    string tienToCon = tienTo;
    if (!laGoc) {
        if (laCuoi) tienToCon += "    ";
        else tienToCon += "|   ";
    }
    for (Node* c = n->firstChild; c != NULL; c = c->nextSibling) {
        inCayPhanCap(c, tienToCon, c->nextSibling == NULL, false);
    }
}

// Số cột hiển thị của chuỗi UTF-8: mỗi ký tự = 1 cột (bỏ qua byte nối 10xxxxxx)
// => bảng vẫn thẳng hàng khi tên có dấu tiếng Việt.
int doRongHienThi(string s) {
    int dem = 0;
    for (int i = 0; i < (int)s.length(); i++) {
        if (((unsigned char)s[i] & 0xC0) != 0x80) dem++;
    }
    return dem;
}

string soSangChuoi(int v) {
    if (v == 0) return "0";
    string kq = "";
    while (v > 0) {
        kq = string(1, (char)('0' + v % 10)) + kq;
        v = v / 10;
    }
    return kq;
}

// In một ô: "| " + nội dung + khoảng trắng bù cho đủ độ rộng cột + " "
void inO(string noiDung, int doRong) {
    cout << "| " << noiDung << string(doRong - doRongHienThi(noiDung), ' ') << " ";
}

void inDuongKe(int w1, int w2, int w3, int w4, int w5, int w6) {
    cout << "+" << string(w1 + 2, '-') << "+" << string(w2 + 2, '-')
         << "+" << string(w3 + 2, '-') << "+" << string(w4 + 2, '-')
         << "+" << string(w5 + 2, '-') << "+" << string(w6 + 2, '-') << "+\n";
}

// Hiển thị toàn bộ thành viên dưới dạng bảng ASCII (lấy trực tiếp từ cây,
// duyệt theo thế hệ bằng hàng đợi mảng nên cha luôn đứng trước con).
void hienThiBangThanhVien() {
    if (root == NULL) {
        cout << "Gia pha chua co du lieu.\n";
        cout << "Hay chon chuc nang 1 de them thanh vien dau tien (nguoi goc),\n";
        cout << "sau do them cac thanh vien khac bang cach nhap ma cha/me.\n";
        return;
    }
    // Bước 1: BFS để lấy danh sách nút và cha/mẹ của từng nút
    Node* hang[MAX_NODE];
    Node* chaNut[MAX_NODE];
    int dau = 0, cuoi = 0;
    hang[cuoi] = root;
    chaNut[cuoi] = NULL;
    cuoi++;
    while (dau < cuoi) {
        Node* n = hang[dau];
        dau++;
        for (Node* c = n->firstChild; c != NULL; c = c->nextSibling) {
            hang[cuoi] = c;
            chaNut[cuoi] = n;
            cuoi++;
        }
    }
    int tong = cuoi;

    // Bước 2: tính độ rộng từng cột theo dữ liệu thật (không thấp hơn tiêu đề)
    int wStt = (int)soSangChuoi(tong).length();
    if (wStt < 3) wStt = 3;                       // "STT"
    int wMa = 13;                                  // "Ma thanh vien"
    int wTen = 9;                                  // "Ho va ten"
    int wNam = 8;                                  // "Nam sinh"
    int wGt = 9;                                   // "Gioi tinh"
    int wCha = 9;                                  // "Ma cha/me"
    for (int i = 0; i < tong; i++) {
        int d = doRongHienThi(hang[i]->id);
        if (d > wMa) wMa = d;
        if (d > wCha) wCha = d;
        d = doRongHienThi(hang[i]->name);
        if (d > wTen) wTen = d;
    }
    if (wCha < 8) wCha = 8;                        // "Khong co"

    // Bước 3: in bảng
    cout << "======================= DANH SACH THANH VIEN GIA PHA =======================\n\n";
    inDuongKe(wStt, wMa, wTen, wNam, wGt, wCha);
    inO("STT", wStt);  inO("Ma thanh vien", wMa);  inO("Ho va ten", wTen);
    inO("Nam sinh", wNam);  inO("Gioi tinh", wGt);  inO("Ma cha/me", wCha);
    cout << "|\n";
    inDuongKe(wStt, wMa, wTen, wNam, wGt, wCha);
    for (int i = 0; i < tong; i++) {
        Node* n = hang[i];
        string gt = "Nu";
        if (n->gender == 'M') gt = "Nam";
        string maCha = "Khong co";
        if (chaNut[i] != NULL) maCha = chaNut[i]->id;
        inO(soSangChuoi(i + 1), wStt);
        inO(n->id, wMa);
        inO(n->name, wTen);
        inO(soSangChuoi(n->birthYear), wNam);
        inO(gt, wGt);
        inO(maCha, wCha);
        cout << "|\n";
    }
    inDuongKe(wStt, wMa, wTen, wNam, wGt, wCha);
    cout << "\nTong so thanh vien: " << tong << "\n";
}

// Chức năng 14
void xuatGiaPha() {
    if (root == NULL) {
        hienThiBangThanhVien();      // cây rỗng: thông báo và hướng dẫn thêm thành viên
        return;
    }
    cout << "  1 = Cây phân cấp\n";
    cout << "  2 = Bảng danh sách thành viên\n";
    int chon = docSoNguyen("Chọn: ", 1, 2);
    if (chon == 1) {
        cout << "--- GIA PHẢ ---\n";
        inCayPhanCap(root, "", true, true);
    } else {
        hienThiBangThanhVien();
    }
}
