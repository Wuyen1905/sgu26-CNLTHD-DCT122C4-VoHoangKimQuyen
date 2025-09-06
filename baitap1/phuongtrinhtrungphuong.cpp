#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

int solveQuartic(double a, double b, double c, double x[]) {
    if (a == 0 && b == 0 && c == 0) {
return -1;
}
    if (a == 0 && b == 0) {
return 0;
}
    if (a == 0) {
double y = -c / b;
    if (y < 0) return 0;
x[0] = sqrt(y);
x[1] = -sqrt(y);
return 2;
}
double delta = b * b - 4 * a * c;
    if (delta < 0) return 0;
double y1 = (-b + sqrt(delta)) / (2 * a);
double y2 = (-b - sqrt(delta)) / (2 * a);
int count = 0;
    if (y1 >= 0) {
x[count++] = sqrt(y1);
x[count++] = -sqrt(y1);
}
    if (y2 >= 0 && y2 != y1) {
x[count++] = sqrt(y2);
x[count++] = -sqrt(y2);
}
return count;
}

// Hàm tiện ích so sánh nghiệm (dùng sai số epsilon để tránh lỗi số thực)
bool compareSolutions(vector<double> actual, vector<double> expected) {
    if (actual.size() != expected.size()) return false;
    sort(actual.begin(), actual.end());
    sort(expected.begin(), expected.end());
    for (size_t i = 0; i < actual.size(); i++) {
        if (fabs(actual[i] - expected[i]) > 1e-6) return false;
    }
    return true;
}

// Cấu trúc lưu test case
struct TestCase {
    double a, b, c;
    int expectedCount;
    vector<double> expectedSolutions; // để trống nếu không cần so nghiệm
    string description;
};

int main() {
// double a, b, c;
//         cin >> a >> b >> c;
// double x[4];
// int n = solveQuartic(a, b, c, x);
//     if (n == -1) {
//         cout << " Infinite solutions." << endl;
// } else if (n == 0) {
//         cout << "No solution." << endl;
// } else {
//         cout << " The equation has " << n << " real solution(s): ";
// for (int i = 0; i < n; i++) {
//         cout << x[i] << " ";
// }

//         cout << endl;
// }
// return 0 ;
    vector<TestCase> tests = {
        // ✅ PASS
        {1, -5, 4, 4, {2, -2, 1, -1}, "Phuong trinh co 4 nghiem thuc"},
        {1, 0, -1, 4, {1, -1, 0, 0}, "Phuong trinh co 4 nghiem (y^2-1=0)"},

        // ❌ FAIL: mong đợi sai số nghiệm
        {1, 0, -1, 2, {1, -1}, "FAIL: chi khai bao 2 nghiem nhung thuc te co 4"},
        {0, 1, -1, 2, {1, -1}, "Phuong trinh bac 2 -> co 2 nghiem hop le"}, 
        {0, 1, -1, 2, {2, -2}, "FAIL: mong doi nghiem khac thuc te"},
        
        // ❌ FAIL: vô nghiệm nhưng test case lại đòi có nghiệm
        {1, 1, 1, 2, {1, -1}, "FAIL: thuc te vo nghiem"}
    };

    int passCount = 0;
    for (size_t i = 0; i < tests.size(); i++) {
        double x[4];
        int n = solveQuartic(tests[i].a, tests[i].b, tests[i].c, x);

        vector<double> actual;
        if (n > 0) {  // chỉ lưu nghiệm khi có nghiệm thực
            actual.assign(x, x+n);
        }

        bool ok = (n == tests[i].expectedCount);
        if (ok && n > 0 && tests[i].expectedSolutions.size() > 0) {
            ok = compareSolutions(actual, tests[i].expectedSolutions);
        }

        cout << "Test " << i+1 << " (" << tests[i].description << "): ";
        if (ok) {
            cout << "PASS\n";
            passCount++;
        } else {
            cout << "FAIL (expected " << tests[i].expectedCount << " solutions)\n";
        }
    }

    cout << "\nSummary: " << passCount << "/" << tests.size() << " tests passed.\n";
    return 0;
}
