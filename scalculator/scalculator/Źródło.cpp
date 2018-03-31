#include <iostream>
#include <string>
#include <stack>
#include <math.h>
using namespace std;

class Kalkulator {
private:
	bool isDig(char c) {
		return (c >= '0' && c <= '9');
	}

	bool isDot(char c) {
		return (c == '.');
	}

	bool isOperator(char c) {
		return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%');
	}

	double licz(double v1, double v2, char op) {
		if (op == '+') return v1 + v2;
		if (op == '-') return v1 - v2;
		if (op == '*') return v1 * v2;
		if (op == '^') return pow(v1, v2);
		if (op == '/') {
			if (v2 == 0) {
				cout << "Nie dziel przez 0! Koniec programu!" << endl;
				system("pause");
				exit(0);
			}
			else {
				return v1 / v2;
			}
		}
		if (op == '%') {
			if ((int)v2 == 0) {
				cout << "Blad! Koniec programu!" << endl;
				system("pause");
				exit(0);
			}
			else {
				return (int)v1 % (int)v2;
			}
		}
	}

	int getImportance(char c) {
		switch (c) {
		case '+':
			return 1;
			break;
		case '-':
			return 1;
			break;
		case '*':
			return 2;
			break;
		case '/':
			return 2;
			break;
		case '%':
			return 2;
			break;
		case '^':
			return 3;
			break;
		default: return -1;
			break;
		}
	}

public:
	double calculate(string s) {
		stack<double> values;
		stack<char> ops;
		int flag = 0;
		int times = 0;
		double val = 0;
		int pos = 0;
		while (pos < s.length()) {
			char spot = s[pos];
			if (isDig(spot)) {
				val = (val * 10) + (double)(spot - '0');
				if (flag == 1) {
					times--;
				}

			}
			else if (isDot(spot)) {
				flag = 1;
			}
			else if (isOperator(spot)) {
				val = val * pow(10, times);
				flag = 0;
				times = 0;

				if (values.empty()) {
					values.push(val);
					ops.push(spot);
					val = 0;
				}
				else {
					char prev = ops.top();

					if (getImportance(spot) >= getImportance(prev)) {
						values.push(val);
						ops.push(spot);
						val = 0;
					}
					else {
						while (!ops.empty()) {
							double pvalue = values.top();
							values.pop();
							char prevop = ops.top();
							ops.pop();

							val = licz(pvalue, val, prevop);

						}
						values.push(val);
						ops.push(spot);
						val = 0;
					}
				}
			}
			pos++;
		}
		while (!ops.empty()) {
			val = val * pow(10, times);
			flag = 0;
			times = 0;
			double prev = values.top();
			values.pop();
			char spot = ops.top();
			ops.pop();

			val = licz(prev, val, spot);
		}
		return val;
	}

	void take() {
		string r;
		double wynik = 0;

		cout << "Podaj rownanie lub wpisz 'C' by zakocczyc program: " << endl;
		cin >> r;

		if (r == "C") {
			cout << "Koniec programu!" << endl;
			system("pause");
			exit(0);
		}
		else {
			wynik = calculate(r);
			cout << "Wynik: " << wynik << endl;
		}

	}

	Kalkulator() {}
};

int main() {
	Kalkulator *nowy = new Kalkulator;
	while (1) {
		nowy->take();
	}


	system("pause");
	return 0;
}