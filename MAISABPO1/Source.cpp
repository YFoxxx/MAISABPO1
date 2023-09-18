#include "my_func.h"

using namespace std;

#pragma region BigInt
class BigInteger {
private:
    std::vector<int> digits;

public:
    BigInteger() {}

    BigInteger(const std::string& numStr) {
        for (int i = numStr.length() - 1; i >= 0; i--) {
            digits.push_back(numStr[i] - '0');
        }
    }

    void add(const BigInteger& other) {
        int carry = 0;
        int max_len = std::max(digits.size(), other.digits.size());

        for (int i = 0; i < max_len || carry; i++) {
            if (i == digits.size()) {
                digits.push_back(0);
            }
            digits[i] += carry + (i < other.digits.size() ? other.digits[i] : 0);
            carry = digits[i] / 10;
            digits[i] %= 10;
        }
    }

    void multiply(const BigInteger& other) {
        std::vector<int> result(digits.size() + other.digits.size(), 0);

        for (int i = 0; i < digits.size(); i++) {
            for (int j = 0, carry = 0; j < other.digits.size() || carry; j++) {
                long long cur = result[i + j] +
                    digits[i] * 1ll * (j < other.digits.size() ? other.digits[j] : 0) + carry;
                result[i + j] = cur % 10;
                carry = cur / 10;
            }
        }

        while (result.size() > 1 && result.back() == 0) {
            result.pop_back();
        }

        digits = result;
    }

    void modulo(const BigInteger& other) {
        BigInteger quotient;
        BigInteger dividend = *this;

        while (dividend >= other) {
            BigInteger temp = other;
            int factor = 1;

            while (dividend >= (temp * 10)) {
                temp.multiply(BigInteger("10"));
                factor *= 10;
            }

            while (dividend >= temp) {
                dividend -= temp;
                quotient.add(BigInteger(std::to_string(factor)));
            }
        }

        *this = dividend;
    }

    bool operator>=(const BigInteger& other) const {
        if (digits.size() != other.digits.size()) {
            return digits.size() > other.digits.size();
        }
        for (int i = digits.size() - 1; i >= 0; i--) {
            if (digits[i] != other.digits[i]) {
                return digits[i] > other.digits[i];
            }
        }
        return true;
    }

    bool operator<(const BigInteger& other) const {
        return !(*this >= other);
    }

    BigInteger operator*(const BigInteger& other) const {
        BigInteger result;
        result.digits.assign(digits.size() + other.digits.size(), 0);

        for (int i = 0; i < digits.size(); i++) {
            int carry = 0;
            for (int j = 0; j < other.digits.size() || carry; j++) {
                long long cur = result.digits[i + j] +
                    digits[i] * 1ll * (j < other.digits.size() ? other.digits[j] : 0) + carry;
                result.digits[i + j] = cur % 10;
                carry = cur / 10;
            }
        }

        while (result.digits.size() > 1 && result.digits.back() == 0) {
            result.digits.pop_back();
        }

        return result;
    }

    bool operator==(const BigInteger& other) const {
        return digits == other.digits;
    }

    bool operator!=(const BigInteger& other) const {
        return !(*this == other);
    }

    BigInteger operator+(const BigInteger& other) const {
        BigInteger result(*this);
        result.add(other);
        return result;
    }

    BigInteger operator-(const BigInteger& other) const {
        BigInteger result(*this);
        result -= other;
        return result;
    }

    BigInteger& operator+=(const BigInteger& other) {
        this->add(other);
        return *this;
    }

    BigInteger& operator-=(const BigInteger& other) {
        if (*this < other) {
            digits = { 0 };
            return *this;
        }

        int borrow = 0;
        for (size_t i = 0; i < digits.size(); ++i) {
            int sub = digits[i] - borrow;
            if (i < other.digits.size()) {
                sub -= other.digits[i];
            }
            if (sub < 0) {
                sub += 10;
                borrow = 1;
            }
            else {
                borrow = 0;
            }
            digits[i] = sub;
        }

        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }

        return *this;
    }

    BigInteger operator*(int num) const {
        BigInteger result(*this);

        for (int i = 0, carry = 0; i < result.digits.size() || carry; i++) {
            if (i == result.digits.size()) {
                result.digits.push_back(0);
            }
            long long cur = result.digits[i] * 1ll * num + carry;
            result.digits[i] = cur % 10;
            carry = cur / 10;
        }

        while (result.digits.size() > 1 && result.digits.back() == 0) {
            result.digits.pop_back();
        }

        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const BigInteger& bigInt) {
        for (int i = bigInt.digits.size() - 1; i >= 0; i--) {
            os << bigInt.digits[i];
        }
        return os;
    }
};
#pragma endregion

int main()
{
    char chr;
    bool bMenu = true;
    string format, filePath, command;
    
    uint32_t ap, bp, Mp;

    BigInteger big_a("90832980532897532789123456789");
    BigInteger big_b("987659820349807432890732544321");
    BigInteger big_c("12326246243625353253252389372057892308790532");
    BigInteger big_d("5523091247812089741279847891278904");

    int num1, num2, m, a, b;
    int choice, N, num;
    while (bMenu)
    {
        cout << "***Choose***\n";
        cout << "1 - 1 task\n";
        cout << "2 - 2 task\n";
        cout << "3 - 3 task\n";
        cout << "4 - 3.2 task\n";
        cout << "5 - 4 task\n";
        cout << "6 - 5 task\n";
        cout << (chr = _getch()) << endl;
        switch (chr)
        {
        case '1':
            cout << "Choose format (hex8, dec8, hex16, dec16, hex32): ";
            cin >> format;

            cout << "Enter file path: ";
            cin >> filePath;

            printFile(format, filePath);

            break;
        case '2':

            std::cout << "Enter command: ";
            std::cin >> command;
            std::cout << "Enter 1st nuber: ";
            std::cin >> num1;
            std::cout << "enter 2nd number: ";
            std::cin >> num2;

            taskTwo(command, num1, num2);

            break;
        case '3':
            cout << "Enter modul m: ";
            cin >> m;
            cout << "Number a: ";
            cin >> a;
            cout << "Number b: ";
            cin >> b;

            cout << "a + b (mod m) = " << addMod(a, b, m) << endl;
            cout << "a - b (mod m) = " << subtractMod(a, b, m) << endl;
            cout << "a * b (mod m) = " << multiplyMod(a, b, m) << endl;
            cout << "a^b (mod m) = " << powerMod(a, b, m) << endl;
            if (divideMod(a, b, m) != -1) {
                cout << "a / b (mod m) = " << divideMod(a, b, m) << endl;
            }

            break;
        case '4':
            cout << "Enter modul M: ";
            cin >> Mp;
            cout << "Number a: ";
            cin >> ap;
            cout << "Number b: ";
            cin >> bp;

            std::cout << "a + b mod M = " << GF2nAdd(ap, bp) << std::endl;
            std::cout << "a - b mod M = " << GF2nSubtract(ap, bp) << std::endl;
            std::cout << "a * b mod M = " << GF2nMultiply(ap, bp, Mp) << std::endl;
            std::cout << "2^(-1) mod M = " << GF2nInverse(2, Mp) << std::endl;

            break;
        case '5':
            while (true) {
                cout << "Choose\n";
                cout << "1. Print N prime numbers\n";
                cout << "2. Prime test\n";
                cout << "3. Exit\n";
                cin >> choice;

                switch (choice) {
                case 1:
                    cout << "Enter N: ";
                    cin >> N;
                    printPrimes(N);
                    break;
                case 2:
                    cout << "Enter number for prime test";
                    cin >> num;
                    if (isPrime(num)) {
                        cout << num << " Prime \n";
                    }
                    else {
                        cout << num << " Not Prime \n";
                    }
                    break;
                case 3:
                    return 0;
                default:
                    cout << "Unsupported key is pressed\n";
                }
            }
            break;
        case '6':
            std::cout << "a + b = " << (big_a + big_b) << std::endl;
            std::cout << "a * b = " << (big_a * big_b) << std::endl;

            big_c.modulo(big_d);

            std::cout << "c % d = " << big_c << std::endl;
            break;
        default:
            cout << "\nUnsupported key is pressed\n";
            break;
        }
        cout << "\nPress 0 to continue\n";
        cout << "Any other to exit\n";
        cout << (chr = _getch()) << endl;
        if (chr != '0')
            bMenu = false;
        system("cls");
    }
}