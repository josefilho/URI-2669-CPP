#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
#include <cstdio>  // Para scanf

#define PI 3.14159265358979323846

using namespace std;
typedef complex<double> base;

// Função para aplicar a FFT (in-place)
void fft(vector<base>& a, bool invert) {
    int n = a.size();
    if (n == 1) return;

    vector<base> a0(n / 2), a1(n / 2);
    for (int i = 0, j = 0; i < n; i += 2, ++j) {
        a0[j] = a[i];
        a1[j] = a[i + 1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    base w(1), wn(cos(ang), sin(ang));
    for (int i = 0; i < n / 2; ++i) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

// Função para multiplicar dois polinômios usando FFT
vector<int> multiply(const vector<int>& a, const vector<int>& b) {
    vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    size_t n = 1;
    while (n < max(a.size(), b.size())) n <<= 1;
    n <<= 1;
    fa.resize(n), fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (size_t i = 0; i < n; ++i)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<int> result(n);
    for (size_t i = 0; i < n; ++i)
        result[i] = int(fa[i].real() + 0.5);

    return result;
}

int main() {
    // Buffer para ler a string de entrada
    const int MAX_LENGTH = 100010;  // Tamanho máximo da string + margem
    char buffer[MAX_LENGTH];

    // Ler a string usando scanf
    scanf("%s", buffer);
    string s(buffer);

    // Pré-processamento: calcular os pesos dos caracteres e o prefix sum
    vector<int> prefix_sum(s.size() + 1, 0);
    for (size_t i = 1; i <= s.size(); ++i) {
        prefix_sum[i] = prefix_sum[i - 1] + (s[i - 1] - 'a' + 1);
    }

    // Encontrar o maior prefix sum (total_mass)
    int total_mass = prefix_sum.back();

    // Criar os polinômios P(x) e Q(x) com tamanho mínimo necessário
    vector<int> P(total_mass + 1, 0), Q(total_mass + 1, 0);
    for (size_t i = 0; i < prefix_sum.size(); ++i) {
        if (prefix_sum[i] <= total_mass) P[prefix_sum[i]]++;
        if (i < prefix_sum.size() - 1 && (total_mass - prefix_sum[i]) >= 0) {
            Q[total_mass - prefix_sum[i]]++;
        }
    }

    // Multiplicar os polinômios usando FFT
    vector<int> result = multiply(P, Q);

    // Coletar os submasses distintos
    int distinct_count = 0;
    for (size_t i = total_mass + 1; i < result.size(); ++i) {
        if (result[i] > 0) {
            distinct_count++;
        }
    }

    // Imprimir o número de submasses distintos
    cout << distinct_count << endl;

    return 0;
}