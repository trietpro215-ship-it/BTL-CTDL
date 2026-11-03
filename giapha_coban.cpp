// ============================================================
//  QUẢN LÝ GIA PHẢ GIA TỘC MINI 
//  Cây đa phân biểu diễn bằng cây nhị phân LCRS
//     firstChild  = con đầu tiên
//     nextSibling = anh/chị/em kế tiếp.
// 
//  BẢN MỞ RỘNG (chỉ bổ sung, không bỏ chức năng cũ):
//   - Chọn thành viên bằng mã / họ tên / danh sách (hàm dùng chung chonThanhVien).
//   - Quan hệ vợ/chồng: thêm con trỏ spouse trong Node, lưu RIÊNG với quan hệ
//     cha/mẹ - con (firstChild/nextSibling) nên BFS, DFS, LCA không bị ảnh hưởng.
//   - Xem quan hệ gia đình, suy ra cách gọi: cha/mẹ, ông/bà, anh/chị/em,
//     cô/dì/chú/bác/cậu... (xem PHẦN 6 ở cuối file).
//   - Menu gọn: mục 1-14 như cũ (11 và 14 được mở rộng), 15 = Quản lý quan hệ vợ chồng.
//     Chọn thành viên bằng mã/họ tên/danh sách do hàm dùng chung chonThanhVien() đảm nhiệm.
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
    Node* spouse;        // [MỚI] vợ/chồng (NULL = chưa có). Lưu riêng, không nằm trong danh sách con
};

Node* root = NULL;       // NULL nghĩa là gia phả rỗng
Node* dsNgoai = NULL;    // [MỚI] danh sách người nhập gia (vợ/chồng chưa có cha/mẹ trong gia phả),
                         //        nối bằng nextSibling, KHÔNG thuộc cây huyết thống

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
Node* nhapThanhVienMoi(Node* cha, char gtBatBuoc);   // [SỬA] thêm tham số gtBatBuoc ('\0' = hỏi giới tính)
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
// --- PHẦN 6 (MỚI)
bool laNguoiNgoai(Node* n);
int demNgoai();
int tongThanhVien();
void themNgoai(Node* n);
void goNgoai(Node* n);
void giaiPhongNgoai();
void donNgoaiNeuCayRong();
Node* timThanhVien(string ma);
void ketHon(Node* a, Node* b);
void huyKetHon(Node* a);
void goQuanHeVoChongTrongCay(Node* n);
bool laHuyetThongGan(Node* a, Node* b);
string kiemTraKetHon(Node* a, Node* b);
string tenHienThi(Node* n);
string chuThuong(string s);
string boDauHaiCham(string s);
bool canTrongCay(Node* n);
int layDanhSach(Node* ds[]);
string moTaQuanHeBang(Node* n);
void hienThiBangChon();
void thuThapTheoTen(Node* n, string tuKhoaThuong, Node* kq[], int& so);
void inMotDong(Node* n);
Node* chonTheoMa();
Node* chonTheoTen();
Node* chonTheoDanhSach();
Node* chonThanhVien(string tieuDe, bool chiTrongCay);
void themQuanHeVoChong();
void taoVoChongMoi();
void huyQuanHeVoChong();
void menuVoChong();
string tenBacChuCoDiCau(Node* s, Node* m);
string tenAnhChiEm(Node* a, Node* b, bool ho);
void xacDinhChaMe(Node* n, Node*& cha, Node*& me, bool& chaSuyRa, bool& meSuyRa);
bool xacDinhQuanHe(Node* a, Node* b, string& ten, string& coSo);
void traCuuHaiNguoi();
void inDuongQuanHe(Node* a, Node* b, bool kemMoTaChung);
Node* themVoChongMau(Node* nguoi, string id, string ten, int nam, char gt);
void inChaMe(string nhan, Node* n, bool suyRa);
void xemQuanHeThanhVien();
void timTheoTenNgoai(string tuKhoa, int& soKetQua);
void thongKeNgoai(int& nam, int& nu, int& namNho);
void inNguoiSinhNamNgoai(int nam, bool& laDauTien);
int demCoVoChongTrongCay(Node* n);
int demCapVoChong();
void inO(string noiDung, int doRong);
void inDuongKe(int w1, int w2, int w3, int w4, int w5, int w6);


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
    n->spouse = NULL;
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

// [SỬA] Chọn thành viên: giờ dùng hàm chung chonThanhVien (theo mã / họ tên / danh sách).
// Mọi chức năng cũ vẫn gọi hàm này như trước; NULL = không chọn (hủy).
Node* hoiThanhVien(string loiNhac) {
    return chonThanhVien(loiNhac, false);
}

void inThongTin(Node* n) {
    Node* cha = timCha(root, n);
    cout << "  Mã: " << n->id << " | Tên: " << n->name
         << " | Năm sinh: " << n->birthYear
         << " | Giới tính: " << tenGioiTinh(n->gender) << "\n";
    cout << "  Cha/mẹ: ";
    if (laNguoiNgoai(n)) cout << "(chưa có trong gia phả - người nhập gia)";
    else if (cha == NULL) cout << "(người gốc)";
    else cout << cha->name << " [" << cha->id << "]";
    cout << " | Số con: " << demCon(n) << " | Thế hệ: ";
    if (laNguoiNgoai(n)) cout << "(không thuộc cây huyết thống)";
    else cout << tinhTheHe(root, n, 1);
    cout << "\n";
    cout << "  Vợ/chồng: ";                                       // [MỚI]
    if (n->spouse == NULL) cout << "(chưa có)";
    else cout << n->spouse->name << " [" << n->spouse->id << "]";
    cout << "\n";
}

// Dữ liệu mẫu (khai báo trực tiếp trong code): 10 người trong cây, 4 thế hệ,
// cộng 4 người nhập gia (vợ/chồng) G011-G014 để thử quan hệ vợ chồng.
//   G001 (gốc) -> G002, G003, G004
//   G002 -> G005, G006     G003 -> G007, G008     G005 -> G009, G010
// Mỗi người được tạo đúng một lần và gắn vào đúng một cha/mẹ.
void taoDuLieuMau() {
    xoaCay(root);
    giaiPhongNgoai();                                            // [MỚI] bỏ luôn người nhập gia cũ
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

    // [MỚI] Vợ/chồng nhập gia: nút độc lập, chưa có cha/mẹ trong cây, nằm trong dsNgoai
    // (KHÔNG nằm trong danh sách con của ai), nối với người đã có bằng spouse hai chiều.
    // themVoChongMau bỏ qua nếu mã đã tồn tại và từ chối nếu vi phạm quy tắc kết hôn.
    themVoChongMau(g002, "G011", "Tran Thi Mai", 1966, 'F');       // vợ của G002
    themVoChongMau(g005, "G012", "Le Thi Huong", 1992, 'F');       // vợ của G005
    themVoChongMau(g008, "G013", "Pham Van Son", 1991, 'M');       // chồng của G008 (G007 là Nam nên không thể)
    themVoChongMau(g003, "G014", "Nguyen Van Long", 1967, 'M');    // chồng của G003
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
        giaiPhongNgoai();
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
    cout << "11. Tra cứu thông tin và quan hệ họ hàng\n";
    cout << "12. Tính bậc thế hệ\n";
    cout << "13. Thống kê gia phả\n";
    cout << "14. Xuất gia phả (cây phân cấp / bảng danh sách)\n";
    cout << "15. Quản lý quan hệ vợ chồng\n";
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
        chon = docSoNguyen("Chọn chức năng (0-15): ", 0, 15);
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
            case 15: menuVoChong();         break;
            case 0:
                if (!xacNhan("Thoát chương trình? (dữ liệu chỉ nằm trong bộ nhớ nên sẽ mất)")) chon = -1;   // không thoát
                break;
        }
    }
    xoaCay(root);      // trả bộ nhớ trước khi kết thúc
    giaiPhongNgoai();
    cout << "Tạm biệt!\n";
    return 0;
}


// Nhập thông tin một thành viên mới; "cha" = NULL nếu là người gốc.
// Trả về NULL nếu người dùng hủy (để trống mã).
// gtBatBuoc = 'M'/'F': giới tính được ấn định (vd. khi tạo vợ/chồng); '\0': hỏi người dùng.
Node* nhapThanhVienMoi(Node* cha, char gtBatBuoc) {
    string id;
    while (true) {
        id = docDong("Mã định danh (chữ/số/_/-, Enter để hủy): ");
        if (id == "") return NULL;
        if (!maHopLe(id)) {
            cout << "  ! Mã không hợp lệ (không có khoảng trắng hoặc ký tự lạ).\n";
        } else if (timThanhVien(id) != NULL) {
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
    char kyHieu = gtBatBuoc;
    if (kyHieu == '\0') {
        int gt = docSoNguyen("Giới tính (1 = Nam, 2 = Nữ): ", 1, 2);
        kyHieu = 'F';
        if (gt == 1) kyHieu = 'M';
    } else {
        cout << "Giới tính: " << tenGioiTinh(kyHieu) << " (tự xác định theo quy ước vợ chồng)\n";
    }
    return taoNode(id, ten, nam, kyHieu);
}

// Chức năng 1: thêm thành viên
void themThanhVien() {
    if (tongThanhVien() >= MAX_NODE) {
        cout << "  ! Đã đạt số thành viên tối đa (" << MAX_NODE << ").\n";
        return;
    }
    Node* cha = NULL;
    if (root == NULL) {
        cout << "Gia phả đang rỗng: thành viên đầu tiên sẽ là NGƯỜI GỐC.\n";
    } else {
        cout << "(Mỗi người, trừ người gốc, phải có cha/mẹ trong gia phả)\n";
        cha = chonThanhVien("Chọn cha/mẹ của thành viên mới", true);   // [SỬA] chọn theo mã/tên/danh sách
        if (cha == NULL) return;
    }
    Node* moi = nhapThanhVienMoi(cha, '\0');
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
        Node* n = timThanhVien(ma);
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
        timTheoTenNgoai(tuKhoa, soKetQua);          // [MỚI] cả người nhập gia
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
    if (s == "1" || s == "2") {
        char gMoi = 'F';
        if (s == "1") gMoi = 'M';
        if (n->spouse != NULL && n->spouse->gender == gMoi)      // [MỚI] vợ chồng phải một Nam một Nữ
            cout << "  ! Không đổi được: sẽ cùng giới tính với vợ/chồng (" << n->spouse->name << "), giữ nguyên.\n";
        else n->gender = gMoi;
    } else if (s != "") cout << "  ! Lựa chọn không hợp lệ, giữ nguyên.\n";

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
    if (laNguoiNgoai(x)) {                                       // [MỚI] người nhập gia: không có con cháu trong cây
        if (!xacNhan("Xóa " + x->name + " (người nhập gia)?")) {
            cout << "  Đã hủy.\n";
            return;
        }
        huyKetHon(x);                                            // gỡ quan hệ vợ/chồng hai phía
        goNgoai(x);
        delete x;
        cout << "  => Đã xóa; quan hệ vợ chồng liên quan (nếu có) đã được gỡ.\n";
        return;
    }
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
            goQuanHeVoChongTrongCay(root);   // [MỚI] gỡ vợ/chồng trước khi giải phóng
            xoaCay(root);
            root = NULL;
            donNgoaiNeuCayRong();
        } else {
            tachNode(cha, x);      // tách khỏi danh sách anh em trước
            goQuanHeVoChongTrongCay(x);      // [MỚI] cả nhánh bị xóa: không để vợ/chồng trỏ vào nút đã xóa
            xoaCay(x);
        }
        cout << "  => Đã xóa " << soNguoi << " thành viên.\n";
        return;
    }

    // ----- cách 1 -----
    if (cha == NULL) {                               // x là người gốc
        if (x->firstChild == NULL) {
            huyKetHon(x);                                  // [MỚI]
            delete x;
            root = NULL;
            donNgoaiNeuCayRong();
        } else if (x->firstChild->nextSibling == NULL) {   // gốc chỉ có 1 con
            Node* moi = x->firstChild;
            huyKetHon(x);                                  // [MỚI]
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
    huyKetHon(x);                                          // [MỚI] gỡ vợ/chồng trước khi xóa
    delete x;
    cout << "  => Đã xóa; con cháu được chuyển lên làm con của " << cha->name << ".\n";
}




// Chuyển một thành viên (cùng hậu duệ) sang làm con của người khác
void chuyenNhanh() {
    if (root == NULL) {
        cout << "  ! Gia phả đang rỗng.\n";
        return;
    }
    Node* con = chonThanhVien("Thành viên cần chuyển", true);        // [SỬA] chọn theo mã/tên/danh sách
    if (con == NULL) return;
    Node* chaMoi = chonThanhVien("Cha/mẹ mới", true);
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
    // [MỚI] không để việc chuyển nhánh làm sai quan hệ vợ/chồng
    if (con->spouse == chaMoi) {
        cout << "  ! Từ chối: " << chaMoi->name << " là vợ/chồng của " << con->name
             << " nên không thể trở thành cha/mẹ của người này.\n";
        return;
    }
    if (con->spouse != NULL && namTrongCayCon(con->spouse, chaMoi)) {
        cout << "  ! Từ chối: " << chaMoi->name << " là hậu duệ của " << con->spouse->name
             << " (vợ/chồng của " << con->name << "), chuyển như vậy sẽ làm sai quan hệ vợ chồng.\n";
        return;
    }
    if (chaMoi->spouse != NULL && namTrongCayCon(con, chaMoi->spouse)) {
        cout << "  ! Từ chối: vợ/chồng của " << chaMoi->name << " (" << chaMoi->spouse->name
             << ") là hậu duệ của " << con->name << ".\n";
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
        if (n->spouse != NULL && n->spouse->firstChild != NULL)          // [MỚI]
            cout << "  (Vợ/chồng " << n->spouse->name << " có con trong gia phả; xem ở chức năng 11.)\n";
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
    if (!canTrongCay(n)) return;                       // [MỚI] người nhập gia: chưa có dữ liệu cha/mẹ
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

// In đường quan hệ A -> tổ tiên chung -> B (logic cũ của chức năng 11, giữ nguyên).
// a và b phải thuộc cây huyết thống. kemMoTaChung = true: in thêm mô tả chung kiểu cũ
// (dùng khi chưa xác định được cách gọi cụ thể).
void inDuongQuanHe(Node* a, Node* b, bool kemMoTaChung) {
    Node* l = timLCA(root, a, b);                 // tổ tiên chung gần nhất
    Node* duongA[MAX_NODE];
    Node* duongB[MAX_NODE];
    int soA = 0, soB = 0;
    timDuongDi(root, a, duongA, soA);             // đường từ gốc đến A
    timDuongDi(root, b, duongB, soB);             // đường từ gốc đến B

    int theHeL = tinhTheHe(root, l, 1);
    int da = soA - theHeL;                        // số đời từ A lên L
    int db = soB - theHeL;                        // số đời từ B lên L

    if (kemMoTaChung) {
        cout << "  Mô tả chung: " << a->name << " là ";
        inMoTaQuanHe(da, db);
        cout << " của " << b->name << ".\n";
    }

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

// Chức năng 11: Tra cứu thông tin và quan hệ họ hàng
//   1 = xem thông tin + quan hệ của MỘT thành viên
//   2 = tra cứu quan hệ giữa HAI thành viên (cách gọi + đường quan hệ)
void traCuuQuanHe() {
    if (tongThanhVien() == 0) {
        cout << "  ! Gia phả đang rỗng.\n";
        return;
    }
    cout << "  1 = Xem thông tin và quan hệ của MỘT thành viên (cha, mẹ, vợ/chồng, con, anh/chị/em...)\n";
    cout << "  2 = Tra cứu quan hệ giữa HAI thành viên (ông, bà, chú, bác, cô, dì, cậu, cháu...)\n";
    cout << "  0 = Quay lại\n";
    int chon = docSoNguyen("Chọn: ", 0, 2);
    if (chon == 1) xemQuanHeThanhVien();
    else if (chon == 2) traCuuHaiNguoi();
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
    if (!canTrongCay(a) || !canTrongCay(b)) return;    // [MỚI]
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
    if (!canTrongCay(n)) return;                       // [MỚI]
    int g = tinhTheHe(root, n, 1);
    cout << "  " << n->name << " thuộc thế hệ " << g;
    if (g == 1) cout << " (người gốc).\n";
    else cout << " (cách người gốc " << g - 1 << " đời).\n";
}


// Số thế hệ = chiều cao của cây
int chieuCao(Node* n) {
    if (n == NULL) return 0;
    int hCon = 1 + chieuCao(n->firstChild);    // xuống một thế hệ
    int hEm = chieuCao(n->nextSibling);        // sang em: cùng thế hệ
    if (hCon > hEm) return hCon;
    return hEm;
}

void demGioiTinh(Node* n, int& nam, int& nu) {
    if (n == NULL) return;
    if (n->gender == 'M') nam++;
    else nu++;
    demGioiTinh(n->firstChild, nam, nu);
    demGioiTinh(n->nextSibling, nam, nu);
}

void timNamSinhNhoNhat(Node* n, int& namNho) {
    if (n == NULL) return;
    if (n->birthYear < namNho) namNho = n->birthYear;
    timNamSinhNhoNhat(n->firstChild, namNho);
    timNamSinhNhoNhat(n->nextSibling, namNho);
}

// In tất cả những người sinh năm "nam" (có thể nhiều người trùng năm)
void inNguoiSinhNam(Node* n, int nam, bool& laDauTien) {
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
    thongKeNgoai(nam, nu, namNho);                   // [MỚI] tính cả người nhập gia

    cout << "--- Thống kê gia phả ---\n";
    cout << "  Tổng số thành viên : " << tongThanhVien() << "\n";
    cout << "  Số thế hệ          : " << chieuCao(root) << "\n";
    cout << "  Nam / Nữ           : " << nam << " / " << nu << "\n";
    cout << "  Người lớn tuổi nhất (sinh năm " << namNho << "): ";
    bool laDauTien = true;
    inNguoiSinhNam(root, namNho, laDauTien);
    inNguoiSinhNamNgoai(namNho, laDauTien);
    cout << "\n";
    if (dsNgoai != NULL)                              // [MỚI] chỉ hiện khi có người nhập gia
        cout << "  Người nhập gia     : " << demNgoai() << " (không thuộc cây huyết thống)\n";
    if (demCapVoChong() > 0)
        cout << "  Số cặp vợ chồng    : " << demCapVoChong() << "\n";

    string ma = docDong("Nhập mã để xem số con trực tiếp (Enter = bỏ qua): ");
    if (ma != "") {
        Node* n = timThanhVien(ma);
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

// Hiển thị bảng thành viên (dùng ở lúc khởi động và chức năng 14).
// [SỬA] Bảng giờ do hienThiBangChon() vẽ (STT, Mã, Họ tên, Năm sinh, Giới tính, Quan hệ)
// và gồm CẢ người nhập gia. Cây rỗng: giữ thông báo hướng dẫn cũ.
void hienThiBangThanhVien() {
    if (root == NULL) {
        cout << "Gia pha chua co du lieu.\n";
        cout << "Hay chon chuc nang 1 de them thanh vien dau tien (nguoi goc),\n";
        cout << "sau do them cac thanh vien khac bang cach nhap ma cha/me.\n";
        return;
    }
    hienThiBangChon();
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


// ============================================================
// PHẦN 6 (MỚI): chọn thành viên dùng chung, quan hệ vợ/chồng,
// cách gọi họ hàng.
// Chỉ dùng: struct, con trỏ, mảng, đệ quy, string (như phần cũ).
//
// CÁCH LƯU QUAN HỆ VỢ/CHỒNG
//  - Mỗi người có thêm con trỏ "spouse" trỏ tới vợ/chồng (một chiều
//    mỗi người, luôn đối xứng: a->spouse == b  <=>  b->spouse == a).
//  - Vợ và chồng là HAI nút riêng, KHÔNG nằm trong danh sách con của
//    nhau => firstChild/nextSibling không đổi => BFS, DFS, LCA,
//    tính thế hệ, chiều cao... chạy y như cũ.
//  - Người vợ/chồng "nhập gia" (chưa có cha/mẹ trong gia phả) được giữ
//    trong danh sách riêng dsNgoai (nối bằng nextSibling), KHÔNG nằm
//    trong cây huyết thống. Người này vẫn có mã, tên, năm sinh, giới tính
//    riêng và vẫn chọn/tìm/sửa/xóa được như mọi thành viên khác.
//
// CÁCH XÁC ĐỊNH QUAN HỆ HỌ HÀNG
//  - Quan hệ ĐƯỢC LƯU: cha/mẹ - con (theo cây), vợ - chồng (spouse).
//  - Quan hệ SUY RA: cha/mẹ còn lại (= vợ/chồng của cha/mẹ trong cây),
//    ông/bà (nội/ngoại), anh/chị/em, cô/dì/chú/bác/cậu, cháu, anh chị em
//    họ... được suy ra từ cây + giới tính + năm sinh. Thiếu dữ liệu thì
//    báo "chưa xác định", KHÔNG đoán.
//  - Quy ước cách gọi (bên cha: anh của cha = bác, em trai của cha = chú,
//    chị/em gái của cha = cô; bên mẹ: anh/em trai của mẹ = cậu,
//    chị/em gái của mẹ = dì). Muốn đổi quy ước chỉ cần sửa hàm
//    tenBacChuCoDiCau().
// ============================================================

// ---------- Danh sách người nhập gia (dsNgoai) ----------

bool laNguoiNgoai(Node* n) {
    for (Node* t = dsNgoai; t != NULL; t = t->nextSibling) {
        if (t == n) return true;
    }
    return false;
}

int demNgoai() {
    int dem = 0;
    for (Node* t = dsNgoai; t != NULL; t = t->nextSibling) dem++;
    return dem;
}

// Tổng số thành viên = trong cây + người nhập gia
int tongThanhVien() {
    return demThanhVien(root) + demNgoai();
}

// Thêm n vào CUỐI danh sách người nhập gia
void themNgoai(Node* n) {
    n->firstChild = NULL;
    n->nextSibling = NULL;
    if (dsNgoai == NULL) {
        dsNgoai = n;
        return;
    }
    Node* t = dsNgoai;
    while (t->nextSibling != NULL) t = t->nextSibling;
    t->nextSibling = n;
}

// Gỡ n khỏi danh sách người nhập gia (KHÔNG delete)
void goNgoai(Node* n) {
    if (dsNgoai == n) {
        dsNgoai = n->nextSibling;
    } else {
        Node* t = dsNgoai;
        while (t != NULL && t->nextSibling != n) t = t->nextSibling;
        if (t != NULL) t->nextSibling = n->nextSibling;
    }
    n->nextSibling = NULL;
}

// Xóa toàn bộ người nhập gia (chỉ gọi khi cây huyết thống không còn)
void giaiPhongNgoai() {
    while (dsNgoai != NULL) {
        Node* t = dsNgoai;
        dsNgoai = t->nextSibling;
        delete t;
    }
}

// Cây huyết thống đã trống thì người nhập gia không còn nơi gắn vào => dọn luôn
void donNgoaiNeuCayRong() {
    if (root == NULL && dsNgoai != NULL) {
        cout << "  (Gia phả không còn cây huyết thống nên " << demNgoai()
             << " người nhập gia cũng được xóa theo.)\n";
        giaiPhongNgoai();
    }
}

// Tìm theo mã trong TOÀN BỘ thành viên (cây + người nhập gia)
Node* timThanhVien(string ma) {
    Node* n = timTheoMa(root, ma);
    if (n != NULL) return n;
    for (Node* t = dsNgoai; t != NULL; t = t->nextSibling) {
        if (t->id == ma) return t;
    }
    return NULL;
}

// ---------- Quan hệ vợ/chồng ----------

void ketHon(Node* a, Node* b) {
    a->spouse = b;
    b->spouse = a;
}

// Gỡ quan hệ vợ/chồng của a (nếu có), cả hai phía => không còn con trỏ treo
void huyKetHon(Node* a) {
    if (a->spouse != NULL) {
        a->spouse->spouse = NULL;
        a->spouse = NULL;
    }
}

// Gỡ quan hệ vợ/chồng của mọi nút trong cây con n (và các em của n).
// Gọi TRƯỚC khi xoaCay để không còn con trỏ spouse trỏ vào nút đã xóa.
void goQuanHeVoChongTrongCay(Node* n) {
    if (n == NULL) return;
    huyKetHon(n);
    goQuanHeVoChongTrongCay(n->firstChild);
    goQuanHeVoChongTrongCay(n->nextSibling);
}

// a và b là cha/mẹ - con (đời trên/đời dưới trực tiếp) hoặc anh/chị/em cùng cha/mẹ?
bool laHuyetThongGan(Node* a, Node* b) {
    if (namTrongCayCon(a, b) || namTrongCayCon(b, a)) return true;
    Node* pa = timCha(root, a);
    return (pa != NULL && pa == timCha(root, b));
}

// Trả về chuỗi rỗng nếu được phép kết hôn; ngược lại là lý do từ chối
string kiemTraKetHon(Node* a, Node* b) {
    if (a == b) return "Một người không thể kết hôn với chính mình.";
    if (a->spouse == b) return a->name + " và " + b->name + " đã là vợ chồng.";
    if (a->spouse != NULL) return a->name + " đã có vợ/chồng là " + a->spouse->name + ".";
    if (b->spouse != NULL) return b->name + " đã có vợ/chồng là " + b->spouse->name + ".";
    if (a->gender == b->gender) {
        return "Theo quy ước của chương trình, vợ chồng phải gồm một Nam và một Nữ (cả hai đang là "
               + tenGioiTinh(a->gender) + ").";
    }
    if (laHuyetThongGan(a, b)) {
        return "Không thể kết hôn vì hai người là cha/mẹ - con/hậu duệ hoặc anh/chị/em cùng cha/mẹ.";
    }
    return "";
}

// ---------- Hàm tiện ích hiển thị ----------

string tenHienThi(Node* n) {
    return n->name + " [" + n->id + "]";
}

string chuThuong(string s) {            // chỉ đổi chữ cái ASCII, byte UTF-8 giữ nguyên
    for (int i = 0; i < (int)s.length(); i++) s[i] = (char)tolower((unsigned char)s[i]);
    return s;
}

string boDauHaiCham(string s) {         // "Mã cần sửa: " -> "Mã cần sửa"
    int cuoi = (int)s.length() - 1;
    while (cuoi >= 0 && (s[cuoi] == ' ' || s[cuoi] == ':')) cuoi--;
    return s.substr(0, cuoi + 1);
}

// Chức năng chỉ áp dụng cho thành viên trong cây huyết thống
bool canTrongCay(Node* n) {
    if (!laNguoiNgoai(n)) return true;
    cout << "  ! " << tenHienThi(n) << " là người nhập gia (chỉ có quan hệ vợ/chồng,\n"
         << "    chưa có cha/mẹ trong gia phả) nên chức năng này không áp dụng được.\n"
         << "    Hãy dùng chức năng 11 để xem quan hệ của người này.\n";
    return false;
}

// Danh sách mọi thành viên: duyệt theo thế hệ (BFS bằng mảng) rồi đến người nhập gia.
// Trả về số phần tử.
int layDanhSach(Node* ds[]) {
    int cuoi = 0;
    if (root != NULL) {
        int dau = 0;
        ds[cuoi] = root;
        cuoi++;
        while (dau < cuoi) {
            Node* n = ds[dau];
            dau++;
            for (Node* c = n->firstChild; c != NULL; c = c->nextSibling) {
                ds[cuoi] = c;
                cuoi++;
            }
        }
    }
    for (Node* t = dsNgoai; t != NULL; t = t->nextSibling) {
        ds[cuoi] = t;
        cuoi++;
    }
    return cuoi;
}

// Cột "Quan hệ" của bảng: quan hệ ĐƯỢC LƯU của thành viên
string moTaQuanHeBang(Node* n) {
    string kq = "";
    Node* tp = timCha(root, n);
    if (n == root) kq = "Người gốc";
    else if (tp != NULL) kq = (n->gender == 'M' ? "Con trai của " : "Con gái của ") + tp->name;
    if (n->spouse != NULL) {
        string vc = (n->gender == 'M' ? "Chồng của " : "Vợ của ") + n->spouse->name;
        if (kq == "") kq = vc;
        else kq += "; " + vc;
    }
    if (kq == "") kq = "Chưa có quan hệ";
    return kq;
}

// Bảng thành viên: STT | Mã thành viên | Họ tên | Năm sinh | Giới tính | Quan hệ
void hienThiBangChon() {
    Node* ds[MAX_NODE];
    string qh[MAX_NODE];
    int tong = layDanhSach(ds);
    if (tong == 0) {
        cout << "  ! Gia phả đang rỗng.\n";
        return;
    }
    int wStt = (int)soSangChuoi(tong).length();
    if (wStt < 3) wStt = 3;
    int wMa = doRongHienThi("Mã thành viên");
    int wTen = doRongHienThi("Họ tên");
    int wNam = doRongHienThi("Năm sinh");
    int wGt = doRongHienThi("Giới tính");
    int wQh = doRongHienThi("Quan hệ");
    int i;
    for (i = 0; i < tong; i++) {
        qh[i] = moTaQuanHeBang(ds[i]);
        int d = doRongHienThi(ds[i]->id);
        if (d > wMa) wMa = d;
        d = doRongHienThi(ds[i]->name);
        if (d > wTen) wTen = d;
        d = doRongHienThi(qh[i]);
        if (d > wQh) wQh = d;
    }
    cout << "\n===== DANH SÁCH THÀNH VIÊN =====\n";
    inDuongKe(wStt, wMa, wTen, wNam, wGt, wQh);
    inO("STT", wStt);  inO("Mã thành viên", wMa);  inO("Họ tên", wTen);
    inO("Năm sinh", wNam);  inO("Giới tính", wGt);  inO("Quan hệ", wQh);
    cout << "|\n";
    inDuongKe(wStt, wMa, wTen, wNam, wGt, wQh);
    for (i = 0; i < tong; i++) {
        inO(soSangChuoi(i + 1), wStt);
        inO(ds[i]->id, wMa);
        inO(ds[i]->name, wTen);
        inO(soSangChuoi(ds[i]->birthYear), wNam);
        inO(tenGioiTinh(ds[i]->gender), wGt);
        inO(qh[i], wQh);
        cout << "|\n";
    }
    inDuongKe(wStt, wMa, wTen, wNam, wGt, wQh);
    cout << "Tổng số thành viên: " << tong;
    if (dsNgoai != NULL) cout << " (trong đó " << demNgoai() << " người nhập gia, không thuộc cây huyết thống)";
    cout << "\n";
}

// ---------- HÀM DÙNG CHUNG: CHỌN THÀNH VIÊN ----------

// Thu thập mọi nút TRONG CÂY có tên chứa tuKhoaThuong (không phân biệt hoa/thường)
void thuThapTheoTen(Node* n, string tuKhoaThuong, Node* kq[], int& so) {
    if (n == NULL) return;
    if (chuThuong(n->name).find(tuKhoaThuong) != string::npos) {
        kq[so] = n;
        so++;
    }
    thuThapTheoTen(n->firstChild, tuKhoaThuong, kq, so);
    thuThapTheoTen(n->nextSibling, tuKhoaThuong, kq, so);
}

void inMotDong(Node* n) {
    cout << tenHienThi(n) << " - " << n->birthYear << ", " << tenGioiTinh(n->gender)
         << " (" << moTaQuanHeBang(n) << ")\n";
}

// Cách 1: nhập mã. NULL = chưa chọn được (đã báo lỗi hoặc người dùng quay lại)
Node* chonTheoMa() {
    string ma = docDong("Nhập mã định danh (Enter = quay lại): ");
    if (ma == "") return NULL;
    Node* n = timThanhVien(ma);
    if (n == NULL) cout << "  ! Không tìm thấy thành viên có mã '" << ma << "'. Hãy thử lại.\n";
    return n;
}

// Cách 2: nhập họ tên / một phần họ tên. Nhiều kết quả => bắt buộc chọn, không tự lấy người đầu.
Node* chonTheoTen() {
    string tu = docDong("Nhập họ tên hoặc một phần họ tên (Enter = quay lại): ");
    if (tu == "") return NULL;
    string tuThuong = chuThuong(tu);
    Node* kq[MAX_NODE];
    int so = 0;
    thuThapTheoTen(root, tuThuong, kq, so);
    for (Node* t = dsNgoai; t != NULL; t = t->nextSibling) {
        if (chuThuong(t->name).find(tuThuong) != string::npos) {
            kq[so] = t;
            so++;
        }
    }
    if (so == 0) {
        cout << "  ! Không tìm thấy thành viên nào có tên chứa '" << tu << "'. Hãy thử lại.\n";
        return NULL;
    }
    if (so == 1) {
        cout << "  Tìm thấy 1 người: ";
        inMotDong(kq[0]);
        return kq[0];
    }
    cout << "  Có " << so << " người phù hợp, hãy chọn chính xác:\n";
    for (int i = 0; i < so; i++) {
        cout << "   " << (i + 1) << ". ";
        inMotDong(kq[i]);
    }
    int stt = docSoNguyen("Nhập STT người cần chọn (0 = tìm lại): ", 0, so);
    if (stt == 0) return NULL;
    return kq[stt - 1];
}

// Cách 3: xem bảng rồi chọn theo STT
Node* chonTheoDanhSach() {
    hienThiBangChon();
    Node* ds[MAX_NODE];
    int tong = layDanhSach(ds);
    if (tong == 0) return NULL;
    int stt = docSoNguyen("Nhập STT thành viên cần chọn (0 = quay lại): ", 0, tong);
    if (stt == 0) return NULL;
    return ds[stt - 1];
}

// Chọn một thành viên (dùng cho MỌI chức năng cần chọn người).
//   chiTrongCay = true : chỉ nhận người thuộc cây huyết thống (dùng khi chọn cha/mẹ).
// Trả về NULL nếu người dùng hủy. Tìm sai thì báo lỗi và cho chọn lại.
Node* chonThanhVien(string tieuDe, bool chiTrongCay) {
    tieuDe = boDauHaiCham(tieuDe);
    while (true) {
        cout << "\n--- CHỌN THÀNH VIÊN: " << tieuDe << " ---\n";
        cout << "  1 = Nhập mã định danh\n";
        cout << "  2 = Tìm theo họ tên (hoặc một phần họ tên)\n";
        cout << "  3 = Xem danh sách thành viên rồi chọn\n";
        cout << "  0 = Hủy\n";
        int cach = docSoNguyen("Chọn cách tìm: ", 0, 3);
        if (cach == 0) {
            cout << "  Đã hủy.\n";
            return NULL;
        }
        Node* n = NULL;
        if (cach == 1) n = chonTheoMa();
        else if (cach == 2) n = chonTheoTen();
        else n = chonTheoDanhSach();
        if (n == NULL) continue;                       // báo lỗi rồi cho chọn lại
        if (chiTrongCay && laNguoiNgoai(n)) {
            cout << "  ! " << tenHienThi(n) << " là người nhập gia (không thuộc cây huyết thống) nên không\n"
                 << "    thể làm cha/mẹ trong cây.";
            if (n->spouse != NULL) cout << " Hãy chọn vợ/chồng của người này: " << tenHienThi(n->spouse) << ".";
            cout << "\n";
            continue;
        }
        cout << "  => Đã chọn: " << tenHienThi(n) << "\n";
        return n;
    }
}

// (Chức năng "chọn/tìm thành viên" riêng đã bỏ khỏi menu vì trùng với chức năng 2;
//  việc chọn người cho mọi chức năng do chonThanhVien() ở trên đảm nhiệm.)

// ---------- Chức năng 15: quản lý quan hệ vợ chồng ----------

void themQuanHeVoChong() {
    Node* a = chonThanhVien("Chọn người thứ nhất", false);
    if (a == NULL) return;
    Node* b = chonThanhVien("Chọn người thứ hai", false);
    if (b == NULL) return;
    string loi = kiemTraKetHon(a, b);
    if (loi != "") {
        cout << "  ! " << loi << "\n";
        return;
    }
    ketHon(a, b);
    Node* chong = a;
    Node* vo = b;
    if (a->gender == 'F') {
        chong = b;
        vo = a;
    }
    cout << "  => Đã thiết lập: " << chong->name << " là chồng của " << vo->name << ".\n";
}

// Tạo thành viên MỚI (nút độc lập, không cha/mẹ trong gia phả) làm vợ/chồng
void taoVoChongMoi() {
    if (tongThanhVien() >= MAX_NODE) {
        cout << "  ! Đã đạt số thành viên tối đa (" << MAX_NODE << ").\n";
        return;
    }
    Node* a = chonThanhVien("Chọn thành viên đã có (người sẽ có thêm vợ/chồng)", true);
    if (a == NULL) return;
    if (a->spouse != NULL) {
        cout << "  ! " << a->name << " đã có vợ/chồng là " << a->spouse->name << ".\n";
        return;
    }
    char gt = 'F';
    if (a->gender == 'F') gt = 'M';
    cout << "Nhập thông tin " << (gt == 'F' ? "người vợ" : "người chồng") << " mới của " << a->name << ":\n";
    cout << "(Đây là thành viên độc lập, chưa có cha/mẹ trong gia phả.)\n";
    Node* moi = nhapThanhVienMoi(NULL, gt);
    if (moi == NULL) {
        cout << "  Đã hủy.\n";
        return;
    }
    themNgoai(moi);
    ketHon(a, moi);
    cout << "  => Đã thêm " << moi->name << " và thiết lập là " << (gt == 'F' ? "vợ" : "chồng")
         << " của " << a->name << ".\n";
}

void huyQuanHeVoChong() {
    Node* a = chonThanhVien("Chọn thành viên cần hủy quan hệ vợ chồng", false);
    if (a == NULL) return;
    if (a->spouse == NULL) {
        cout << "  " << a->name << " chưa có vợ/chồng.\n";
        return;
    }
    Node* b = a->spouse;
    if (!xacNhan("Hủy quan hệ vợ chồng giữa " + a->name + " và " + b->name + " (hai người vẫn ở trong gia phả)?")) {
        cout << "  Đã hủy.\n";
        return;
    }
    huyKetHon(a);
    cout << "  => Đã hủy quan hệ vợ chồng giữa " << a->name << " và " << b->name << ".\n";
}

void menuVoChong() {
    if (root == NULL) {
        cout << "  ! Gia phả đang rỗng.\n";
        return;
    }
    cout << "  1 = Thêm quan hệ vợ chồng giữa hai thành viên đã có\n";
    cout << "  2 = Tạo thành viên mới làm vợ/chồng của một thành viên\n";
    cout << "  3 = Hủy quan hệ vợ chồng\n";
    cout << "  0 = Quay lại\n";
    int chon = docSoNguyen("Chọn: ", 0, 3);
    if (chon == 1) themQuanHeVoChong();
    else if (chon == 2) taoVoChongMoi();
    else if (chon == 3) huyQuanHeVoChong();
}

// ---------- Cách gọi họ hàng (suy ra) ----------

// s là anh/chị/em của m; m là cha/mẹ (trong cây) của một người cháu. s được cháu gọi là gì?
string tenBacChuCoDiCau(Node* s, Node* m) {
    if (m->gender == 'M') {                            // bên cha
        if (s->gender == 'F') return "cô";
        if (s->birthYear < m->birthYear) return "bác";
        if (s->birthYear > m->birthYear) return "chú";
        return "bác/chú (cùng năm sinh với cha nên chưa phân biệt được)";
    }
    if (s->gender == 'M') return "cậu";                // bên mẹ
    return "dì";
}

// a là anh/chị/em (ho = false) hoặc anh/chị/em họ (ho = true) của b. Phân biệt theo năm sinh.
string tenAnhChiEm(Node* a, Node* b, bool ho) {
    if (a->birthYear < b->birthYear) {
        if (ho) return (a->gender == 'M') ? "anh họ" : "chị họ";
        return (a->gender == 'M') ? "anh trai" : "chị gái";
    }
    if (a->birthYear > b->birthYear) {
        if (ho) return "em họ";
        return (a->gender == 'M') ? "em trai" : "em gái";
    }
    if (ho) return "anh/chị/em họ (cùng năm sinh nên chưa phân biệt được)";
    return "anh/chị/em (cùng năm sinh nên chưa phân biệt được)";
}

// Cha/mẹ của n. Người là cha/mẹ trong cây => "lưu trực tiếp"; người còn lại
// (vợ/chồng của người đó) => "suy ra". Không có dữ liệu thì để NULL.
void xacDinhChaMe(Node* n, Node*& cha, Node*& me, bool& chaSuyRa, bool& meSuyRa) {
    cha = NULL;
    me = NULL;
    chaSuyRa = false;
    meSuyRa = false;
    Node* tp = timCha(root, n);
    if (tp == NULL) return;
    if (tp->gender == 'M') {
        cha = tp;
        me = tp->spouse;
        meSuyRa = true;
    } else {
        me = tp;
        cha = tp->spouse;
        chaSuyRa = true;
    }
}

// "a là <ten> của b". Trả về false nếu chưa đủ dữ liệu (ten chứa lý do).
// coSo cho biết quan hệ được lưu trực tiếp hay suy ra.
bool xacDinhQuanHe(Node* a, Node* b, string& ten, string& coSo) {
    if (a == b) {
        ten = "cùng một người";
        coSo = "hai lựa chọn trùng nhau";
        return true;
    }
    if (a->spouse == b) {
        ten = (a->gender == 'M') ? "chồng" : "vợ";
        coSo = "lưu trực tiếp (quan hệ vợ chồng)";
        return true;
    }
    Node* tpA = timCha(root, a);
    Node* tpB = timCha(root, b);
    if (tpB != NULL && tpB->spouse == a) {
        ten = (a->gender == 'M') ? "cha" : "mẹ";
        coSo = "suy ra: là vợ/chồng của " + tpB->name + ", người được ghi là cha/mẹ của " + b->name;
        return true;
    }
    if (tpA != NULL && tpA->spouse == b) {
        ten = (a->gender == 'M') ? "con trai" : "con gái";
        coSo = "suy ra: " + b->name + " là vợ/chồng của " + tpA->name + ", người được ghi là cha/mẹ của " + a->name;
        return true;
    }
    if (laNguoiNgoai(a) || laNguoiNgoai(b)) {
        ten = "một trong hai người là người nhập gia, gia phả chưa ghi cha/mẹ của người đó nên chỉ biết quan hệ vợ/chồng";
        return false;
    }
    Node* l = timLCA(root, a, b);
    int theHeL = tinhTheHe(root, l, 1);
    int da = tinhTheHe(root, a, 1) - theHeL;      // số đời từ a lên tổ tiên chung
    int db = tinhTheHe(root, b, 1) - theHeL;      // số đời từ b lên tổ tiên chung
    coSo = "suy ra từ cây gia phả";
    if (da == 0) {                                // a là tổ tiên của b
        if (db == 1) {
            ten = (a->gender == 'M') ? "cha" : "mẹ";
            coSo = "lưu trực tiếp (cha/mẹ - con trong cây)";
        } else if (db == 2) {
            string ben = (tpB->gender == 'M') ? "nội" : "ngoại";
            ten = ((a->gender == 'M') ? "ông " : "bà ") + ben;
        } else if (db == 3) {
            string ben = (tpB->gender == 'M') ? "nội" : "ngoại";
            ten = ((a->gender == 'M') ? "cụ ông (bên " : "cụ bà (bên ") + ben + ")";
        } else {
            ten = "tổ tiên (cách " + soSangChuoi(db) + " đời)";
        }
        return true;
    }
    if (db == 0) {                                // a là hậu duệ của b
        if (da == 1) {
            ten = (a->gender == 'M') ? "con trai" : "con gái";
            coSo = "lưu trực tiếp (cha/mẹ - con trong cây)";
        } else if (da == 2) {
            ten = (tpA->gender == 'M') ? "cháu nội" : "cháu ngoại";
        } else if (da == 3) {
            ten = "chắt";
        } else {
            ten = "hậu duệ (cách " + soSangChuoi(da) + " đời)";
        }
        return true;
    }
    if (da == 1 && db == 1) {
        ten = tenAnhChiEm(a, b, false);
        coSo = "suy ra: cùng cha/mẹ trong cây (" + tpA->name + ")";
        return true;
    }
    if (da == 1 && db == 2) {                     // a là anh/chị/em của cha/mẹ b
        ten = tenBacChuCoDiCau(a, tpB);
        coSo = "suy ra: " + a->name + " là anh/chị/em của " + tpB->name + ", người được ghi là cha/mẹ của " + b->name;
        return true;
    }
    if (da == 2 && db == 1) {                     // a là con của anh/chị/em của b
        ten = "cháu";
        coSo = "suy ra: " + a->name + " là con của " + tpA->name + ", anh/chị/em của " + b->name
               + "; " + a->name + " gọi " + b->name + " là " + tenBacChuCoDiCau(b, tpA);
        return true;
    }
    if (da == 2 && db == 2) {
        ten = tenAnhChiEm(a, b, true);
        coSo = "suy ra: cha/mẹ của hai người là anh/chị/em";
        return true;
    }
    ten = "họ hàng xa, chương trình chưa xác định cách gọi (" + a->name + " cách tổ tiên chung "
          + soSangChuoi(da) + " đời, " + b->name + " cách " + soSangChuoi(db) + " đời)";
    return false;
}

// Chức năng 11 (mục 2): tra cứu quan hệ giữa hai thành viên
void traCuuHaiNguoi() {
    if (tongThanhVien() == 0) {
        cout << "  ! Gia phả đang rỗng.\n";
        return;
    }
    Node* a = chonThanhVien("Chọn người A", false);
    if (a == NULL) return;
    Node* b = chonThanhVien("Chọn người B", false);
    if (b == NULL) return;
    if (a == b) {
        cout << "  ! Hai lựa chọn là cùng một người: " << a->name << ".\n";
        return;
    }
    string ten, coSo;
    bool xacDinh = xacDinhQuanHe(a, b, ten, coSo);
    if (xacDinh) {
        cout << "  " << a->name << " là " << ten << " của " << b->name << ".\n";
        cout << "    Cơ sở: " << coSo << "\n";
        string ten2, coSo2;
        if (xacDinhQuanHe(b, a, ten2, coSo2))
            cout << "  Ngược lại: " << b->name << " là " << ten2 << " của " << a->name << ".\n";
    } else {
        cout << "  Chưa thể xác định quan hệ giữa " << a->name << " và " << b->name << ": " << ten << ".\n";
    }
    if (!laNguoiNgoai(a) && !laNguoiNgoai(b))        // cả hai trong cây: in thêm đường quan hệ (logic cũ)
        inDuongQuanHe(a, b, !xacDinh);
}

// Tạo một người nhập gia và nối quan hệ vợ/chồng hai chiều với "nguoi" (dùng cho dữ liệu mẫu).
// Không tạo lại nếu mã đã tồn tại; không kết hôn nếu vi phạm quy tắc (cùng giới, đã có vợ/chồng...).
Node* themVoChongMau(Node* nguoi, string id, string ten, int nam, char gt) {
    if (timThanhVien(id) != NULL) return NULL;
    Node* moi = taoNode(id, ten, nam, gt);
    if (kiemTraKetHon(nguoi, moi) != "") {
        delete moi;
        return NULL;
    }
    themNgoai(moi);
    ketHon(nguoi, moi);
    return moi;
}

// ---------- Chức năng 11 (mục 1): xem thông tin và các mối quan hệ của một thành viên ----------

void inChaMe(string nhan, Node* n, bool suyRa) {
    cout << "  " << nhan;
    if (n == NULL) cout << "chưa xác định (gia phả chưa có dữ liệu)\n";
    else cout << tenHienThi(n) << (suyRa ? "  [suy ra: vợ/chồng của cha/mẹ trong cây]" : "  [lưu trực tiếp]") << "\n";
}

void xemQuanHeThanhVien() {
    if (tongThanhVien() == 0) {
        cout << "  ! Gia phả đang rỗng.\n";
        return;
    }
    Node* n = chonThanhVien("Chọn thành viên cần xem quan hệ", false);
    if (n == NULL) return;
    bool ngoai = laNguoiNgoai(n);
    Node* tp = timCha(root, n);

    cout << "\n===== THÔNG TIN VÀ QUAN HỆ CỦA " << n->name << " =====\n";
    cout << "  Mã định danh : " << n->id << "\n";
    cout << "  Họ tên       : " << n->name << "\n";
    cout << "  Năm sinh     : " << n->birthYear << "\n";
    cout << "  Giới tính    : " << tenGioiTinh(n->gender) << "\n";
    if (ngoai) cout << "  Thế hệ       : không thuộc cây huyết thống (người nhập gia)\n";
    else cout << "  Thế hệ       : " << tinhTheHe(root, n, 1) << "\n";

    Node* cha;
    Node* me;
    bool chaSR, meSR;
    xacDinhChaMe(n, cha, me, chaSR, meSR);
    inChaMe("Cha          : ", cha, chaSR);
    inChaMe("Mẹ           : ", me, meSR);

    cout << "  Vợ/chồng     : ";
    if (n->spouse == NULL) cout << "chưa có\n";
    else cout << tenHienThi(n->spouse) << " (" << (n->spouse->gender == 'M' ? "chồng" : "vợ") << ")  [lưu trực tiếp]\n";

    cout << "  Các con      : ";
    int soCon = 0;
    Node* c;
    for (c = n->firstChild; c != NULL; c = c->nextSibling) {
        cout << (soCon == 0 ? "" : "                 ") << tenHienThi(c) << " (" << (c->gender == 'M' ? "con trai" : "con gái")
             << ")  [lưu trực tiếp]\n";
        soCon++;
    }
    if (n->spouse != NULL) {
        for (c = n->spouse->firstChild; c != NULL; c = c->nextSibling) {
            cout << (soCon == 0 ? "" : "                 ") << tenHienThi(c) << " (" << (c->gender == 'M' ? "con trai" : "con gái")
                 << ")  [suy ra: con của vợ/chồng " << n->spouse->name << " trong cây]\n";
            soCon++;
        }
    }
    if (soCon == 0) cout << "chưa có con trong dữ liệu\n";

    cout << "  Anh chị em   : ";
    if (ngoai) {
        cout << "chưa xác định (chưa có dữ liệu cha/mẹ)\n";
    } else if (tp == NULL) {
        cout << "không có (người gốc, chưa có dữ liệu cha/mẹ)\n";
    } else {
        int dem = 0;
        for (c = tp->firstChild; c != NULL; c = c->nextSibling) {
            if (c == n) continue;
            cout << (dem == 0 ? "" : "                 ") << tenHienThi(c) << " (" << tenAnhChiEm(c, n, false)
                 << ")  [suy ra: cùng cha/mẹ " << tp->name << "]\n";
            dem++;
        }
        if (dem == 0) cout << "không có (con một trong dữ liệu)\n";
    }

    cout << "  Ông/bà       : ";
    Node* ong = NULL;
    if (tp != NULL) ong = timCha(root, tp);
    if (ong == NULL) {
        cout << "chưa xác định (gia phả chưa có dữ liệu ông/bà)\n";
    } else {
        string ten, coSo;
        xacDinhQuanHe(ong, n, ten, coSo);
        cout << tenHienThi(ong) << " (" << ten << ")  [suy ra từ cây]\n";
    }

    cout << "  Cô/dì/chú/bác/cậu: ";
    if (tp == NULL) {
        cout << "chưa xác định (chưa có dữ liệu cha/mẹ của " << n->name << ")\n";
    } else if (ong == NULL) {
        cout << "chưa xác định (chưa có dữ liệu cha/mẹ của " << tp->name << ", nên chưa biết anh/chị/em của người này)\n";
    } else {
        int dem = 0;
        for (c = ong->firstChild; c != NULL; c = c->nextSibling) {
            if (c == tp) continue;
            cout << (dem == 0 ? "" : "                     ") << tenHienThi(c) << " ("
                 << tenBacChuCoDiCau(c, tp) << ")  [suy ra: anh/chị/em của " << tp->name << "]\n";
            dem++;
        }
        if (dem == 0) cout << "không có (" << tp->name << " là con một trong dữ liệu)\n";
    }
    if (tp != NULL) cout << "  (Họ hàng bên cha/mẹ còn lại: chưa xác định - gia phả chỉ ghi nhánh của "
                         << tp->name << ".)\n";
}

// ---------- Hỗ trợ thống kê / tìm kiếm có tính người nhập gia ----------

void timTheoTenNgoai(string tuKhoa, int& soKetQua) {
    for (Node* t = dsNgoai; t != NULL; t = t->nextSibling) {
        if (t->name.find(tuKhoa) != string::npos) {
            inThongTin(t);
            soKetQua++;
        }
    }
}

void thongKeNgoai(int& nam, int& nu, int& namNho) {
    for (Node* t = dsNgoai; t != NULL; t = t->nextSibling) {
        if (t->gender == 'M') nam++;
        else nu++;
        if (t->birthYear < namNho) namNho = t->birthYear;
    }
}

void inNguoiSinhNamNgoai(int nam, bool& laDauTien) {
    for (Node* t = dsNgoai; t != NULL; t = t->nextSibling) {
        if (t->birthYear == nam) {
            if (!laDauTien) cout << ", ";
            cout << t->name << " [" << t->id << "]";
            laDauTien = false;
        }
    }
}

// Số nút trong cây (từ n, gồm cả các em) đang có vợ/chồng
int demCoVoChongTrongCay(Node* n) {
    if (n == NULL) return 0;
    int dem = 0;
    if (n->spouse != NULL) dem = 1;
    return dem + demCoVoChongTrongCay(n->firstChild) + demCoVoChongTrongCay(n->nextSibling);
}

int demCapVoChong() {
    int dem = demCoVoChongTrongCay(root);
    for (Node* t = dsNgoai; t != NULL; t = t->nextSibling) {
        if (t->spouse != NULL) dem++;
    }
    return dem / 2;
}
