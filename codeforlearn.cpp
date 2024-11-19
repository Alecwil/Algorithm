#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
using namespace std;

string standardizeName(const string& name) {
    string result = "";
    bool capitalize = true;

    for (char c : name) {
        if (c == ' ') {
            // Giữ khoảng trắng và chuyển trạng thái chuẩn bị viết hoa ký tự sau
            result += c;
            capitalize = true;
        }
        else {
            // Kiểm tra nếu cần viết hoa ký tự đầu từ
            if (capitalize) {
                result += toupper(c);  // Viết hoa ký tự
                capitalize = false;
            }
            else {
                result += tolower(c);  // Viết thường ký tự
            }
        }
    }

    return result;
}
char findLeastExistingChar(const string& str) {
    vector<int> frequency(26, 0); // Tần suất ký tự từ 'a' đến 'z'

    // Đếm tần suất các ký tự (không phân biệt chữ hoa/thường)
    for (char c : str) {
        if (isalpha(c)) {
            char lowerC = tolower(c);
            frequency[lowerC - 'a']++;
        }
    }

    // Tìm ký tự có tần suất nhỏ nhất
    int minFreq = 1001; // Đặt một giá trị lớn hơn độ dài chuỗi tối đa
    char result = 'Z' + 1; // Giá trị lớn hơn 'Z' để dễ so sánh

    for (int i = 0; i < 26; i++) {
        if (frequency[i] > 0 && frequency[i] < minFreq) {
            minFreq = frequency[i];
            result = 'A' + i; // Đổi về ký tự in hoa
        }
        else if (frequency[i] > 0 && frequency[i] == minFreq) {
            result = min(result, static_cast<char>('A' + i)); // Ưu tiên thứ tự từ điển nhỏ hơn
        }
    }

    return result;
}
int countUniqueCharacters(const string& str) {
    bool seen[52] = { false }; // Mảng đánh dấu cho 26 chữ hoa và 26 chữ thường
    int uniqueCount = 0;

    for (char c : str) {
        if (isalpha(c)) { // Chỉ xử lý các ký tự chữ
            int index;
            if (islower(c)) {
                index = c - 'a'; // Chữ thường, chỉ số từ 0 đến 25
            }
            else {
                index = c - 'A' + 26; // Chữ hoa, chỉ số từ 26 đến 51
            }

            if (!seen[index]) {
                seen[index] = true; // Đánh dấu đã gặp
                uniqueCount++; // Tăng số ký tự phân biệt
            }
        }
    }

    return uniqueCount;
}

int main() {
    int N;
    cin >> N;
    cin.ignore(); // Bỏ qua ký tự xuống dòng sau khi nhập số
    string name;
    int count = 0;

    for (int i = 0; i < N; i++) {
        getline(cin, name);
        cout << standardizeName(name) << endl;
        cout << findLeastExistingChar(name) << endl;
        cout << countUniqueCharacters(name) << endl;
        // Count numeric characters in the name
        for (char c : name) {
            if (c >= '0' && c <= '9') {
                count++;
            }
        }
    }

    // Output the count of numeric characters
    cout << count << endl;

    return 0;
}