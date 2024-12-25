#include <iostream>
#include <stack>
#include <unordered_map>
#include <string>
#include <sstream>

using namespace std;

bool isValidExpression(const string& expr) {
    stack<char> s;
    for (char ch : expr) {
        if (ch == '(') {
            s.push(ch);
        } else if (ch == ')') {
            if (s.empty() || s.top() != '(') return false;
            s.pop(); 
        }
    }
    return s.empty();
}

bool evaluateExpression(const string& expr, const unordered_map<char, bool>& values) {
    stack<bool> s;

    for (int i = expr.length() - 1; i >= 0; --i) {
        char ch = expr[i];

        if (isalpha(ch)) {
            s.push(values.at(ch)); 
        } else if (ch == '¬') {
            bool val = s.top(); s.pop();
            s.push(!val); 
        } else if (ch == '∧') {
            bool val1 = s.top(); s.pop();
            bool val2 = s.top(); s.pop();
            s.push(val1 && val2); 
        } else if (ch == '∨') {
            bool val1 = s.top(); s.pop();
            bool val2 = s.top(); s.pop();
            s.push(val1 || val2); 
        } else if (ch == '→') {
            bool val1 = s.top(); s.pop();
            bool val2 = s.top(); s.pop();
            s.push(!val1 || val2); 
        }
    }
    return s.top(); 
}

int main() {
    string expression;
    cout << "Nhap bieu thuc logic: ";
    getline(cin, expression);

    if (!isValidExpression(expression)) {
        cout << "Bieu thuc khong hop le!" << endl;
        return 1;
    }

    unordered_map<char, bool> values;
    string input;

    cout << "Nhap gia tri cho cac bien (vd: A=True, B=False, C=True):" << endl;
    cout << "Nhap 'q' de thoat." << endl;

    while (true) {
        cout << "Nhap: ";
        getline(cin, input);
        if (input == "q") break;

        char var;
        bool val;
        char separator; // Dùng để đọc dấu '='

        stringstream ss(input);
        ss >> var >> separator >> boolalpha >> val; // Đọc biến và giá trị

        // Kiểm tra định dạng nhập
        if (separator == '=' && (val == true || val == false)) {
            values[var] = val;
        } else {
            cout << "Nhap khong hop le! Vui long nhap theo dinh dang A=True." << endl;
        }
    }

    // Tính giá trị biểu thức
    bool result = evaluateExpression(expression, values);
    cout << "Gia tri bieu thuc: " << (result ? "true" : "false") << endl;

    return 0;
}