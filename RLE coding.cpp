#include <iostream>
#include <string>
#include <vector>

using namespace std;

string toBinaryCode(string str) {
    string outStr = "";

    for (long long i = 0; i < str.length(); i++) {
        int charInt = str[i];
        string tStrChar = "";

        for (int e = 0; e < 8; e++) {
            tStrChar = to_string(charInt % 2) + tStrChar;
            charInt /= 2;
        }

        outStr += tStrChar;
    }

    return outStr;
}

string intToBinary(int n) {
    string str = "";
    for (int i = 0; i < 7; i++) {
        str = to_string(n % 2) + str;
        n /= 2;
    }
    return str;
}

int fromBinaryToInt(string str) {
    int n = 0;

    for (int i = 1; i < str.length(); i++) n = n * 2 + (str[i] - '0');

    return n;
}

string fromBinaryCode(string str) {
    string outStr = "";

    for (long long i = 0; i < str.length(); i += 8) {
        string binCode = "";
        int charCode = 0;

        for (int e = 0; e < 8; e++)charCode = charCode * 2 + (str[i + e] - '0');

        outStr += char(charCode);
    }

    return outStr;
}

string toRLE(string str) {
    string outStr = "";
    vector <string> v(str.length() / 8);

    for (long long i = 0; i < str.length(); i += 8) {
        for (int e = 0; e < 8; e++) {
            v[i / 8] += str[i + e];
        }
    }

    vector <vector <string>> data(1);

    data[0].push_back(v[0]);
    string prev = v[0];
    int t = 0; bool nowRepeat = true;

    for (long long i = 1; i < v.size(); i++) {
        if (nowRepeat) {
            if (v[i] == prev && data[t].size() < 127) data[t].push_back(v[i]);
            else {
                nowRepeat = false;
                t++;
                data.resize(data.size() + 1);
                data[t].push_back(v[i]);
                prev = v[i];
            }
        }else {
            if (v[i] != prev) {
                data[t].push_back(v[i]);
                prev = v[i];
                if (data[t].size() == 128) {
                    t++;
                    data.resize(data.size() + 1);
                    data[t].push_back(data[t - 1][data[t - 1].size() - 1]);
                    data[t - 1].resize(data[t - 1].size() - 1);
                }
            } else {
                nowRepeat = true;
                if (data[t].size() == 1) data[t].push_back(v[i]);
                else {
                    data[t].resize(data[t].size() - 1);
                    t++;
                    data.resize(data.size() + 1);
                    data[t].push_back(v[i]); data[t].push_back(v[i]);
                }
            }
        }
    }

    for (int y = 0; y < data.size(); y++) {
        if (data[y].size() == 1 || data[y][0] != data[y][1]) {
            outStr += "0" + intToBinary(data[y].size());
            for (int x = 0; x < data[y].size(); x++) outStr += data[y][x];
        } else {
            outStr += "1" + intToBinary(data[y].size());
            outStr += data[y][0];
        }
    }

    return outStr;
}

string fromRLE(string str) {
    string outStr = "";
    vector<string> v(str.length() / 8);

    for (int i = 0; i < str.length(); i += 8) {
        for (int e = 0; e < 8; e++)v[i / 8] += str[i + e];
    }

    int t = 0;

    while (t < str.length() / 8) {
        string testStr = v[t];
        if (testStr[0] == to_string(1)[0]) {
            int multiply = fromBinaryToInt(v[t]);

            for (int i = 0; i < multiply; i++)
                outStr += v[t + 1];

            t += 2;
        }else {
            int n = fromBinaryToInt(v[t]);

            for (int e = 0; e < n; e++) {
                outStr += v[t + e + 1];
            }

            t += n + 1;
        }
    }

    return outStr;
}

int main(){
    string inputStr; int n;
    setlocale(LC_ALL, "Russian");
    cout << "Можно сделать следующее:\n1. Перевести в двоичный\n2. Перевести из двоичного\n3. Зашифровать в RLE бинарными кодом\n4. Дешиифровать из RLE из бинарного кода\nДля использвания команд сначала вводится их номер, а потом, если требуется, текст\nДля завершения работы введите комбинацию Ctr + X\n\n";
    while (cin >> n) {
        if (n == 1) {
            cin >> inputStr;
            cout << toBinaryCode(inputStr) << "\n";
        }
        else if (n == 2) {
            cin >> inputStr;
            cout << fromBinaryCode(inputStr) << "\n";
        }
        else if (n == 3) {
            cin >> inputStr;
            cout << toRLE(toBinaryCode(inputStr)) << "\n";
        }else if(n == 4){
            cin >> inputStr;
            cout << fromBinaryCode(fromRLE(inputStr)) << "\n";
        }
    }
}