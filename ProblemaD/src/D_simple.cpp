#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        string x;
        cin >> x;

        int carry = 0;
        for (int i = (int)x.size() - 1; i >= 0; --i) {
            int d = (x[i] - '0') * 2 + carry;
            x[i] = '0' + (d % 10);
            carry = d / 10;
        }
        if (carry) cout << 1;

        cout << x << '\n';
    }
}
