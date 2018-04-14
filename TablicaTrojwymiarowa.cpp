//Kamil Czajka
#include <iostream>
using namespace std;

bool zakres(int n, int x, int y, int z){
	return (x >= 0 && x < n) && (y >= 0 && y < n) && (z >= 0 && z < n);
}

bool direction(int n, int value){
	return (value < n / 2) ? true : false;
}

long long abs(int arg){

	if (arg < 0){
		return -1 * arg;
	}

	return arg;
}

long long operationT(const long long tab[][32][32], int n, int l, int v, int p, int e){
	int iteratorIP, iteratorIK, iteratorJP, iteratorJK, iteratorKP, iteratorKK;
	long long suma = 0;

	if (direction(n, l) == true){
		iteratorIP = l;
		iteratorIK = l + e;
	}
	else{
		iteratorIP = l - e;
		iteratorIK = l;
	}

	if (direction(n, v) == true){
		iteratorJP = v;
		iteratorJK = v + e;
	}
	else{
		iteratorJP = v - e;
		iteratorJK = v;
	}

	if (direction(n, p) == true){
		iteratorKP = p;
		iteratorKK = p + e;
	}
	else{
		iteratorKP = p - e;
		iteratorKK = p;
	}

	for (int i = iteratorIP; i <= iteratorIK; i++){
		for (int j = iteratorJP; j <= iteratorJK; j++){
			for (int k = iteratorKP; k <= iteratorKK; k++){
				if (zakres(n, i, j, k) == true){
					if (abs(i - l) + abs(j - v) + abs(k - p) <= e){
						suma += tab[i][j][k];
					}
				}
			}
		}
	}

	return suma;
}

long long operationC(const long long tab[][32][32], int n, int l, int v, int p, int h, int w, int d){
	int iteratorIP, iteratorIK, iteratorJP, iteratorJK, iteratorKP, iteratorKK;
	long long suma = 0;

	if (direction(n, l) == true){
		iteratorIP = l;
		iteratorIK = l + h;
	}
	else{
		iteratorIP = l - h;
		iteratorIK = l;
	}

	if (direction(n, v) == true){
		iteratorJP = v;
		iteratorJK = v + w;
	}
	else{
		iteratorJP = v - w;
		iteratorJK = v;
	}

	if (direction(n, p) == true){
		iteratorKP = p;
		iteratorKK = p + d;
	}
	else{
		iteratorKP = p - d;
		iteratorKK = p;
	}

	for (int i = iteratorIP; i <= iteratorIK; i++){
		for (int j = iteratorJP; j <= iteratorJK; j++){
			for (int k = iteratorKP; k <= iteratorKK; k++){
				if (zakres(n, i, j, k) == true){
					suma += tab[i][j][k];
				}
			}
		}
	}

	return suma;
}

long long odleglosc(int l, int v, int p, int x, int y, int z){
	return ((x - l) * (x - l)) + ((y - v) * (y - v)) + ((z - p) * (z - p));
}

long long operationO(const long long tab[][32][32], int n, int l, int v, int p, int r){
	int iteratorIP, iteratorIK, iteratorJP, iteratorJK, iteratorKP, iteratorKK;
	long long suma = 0;

	if (direction(n, l) == true){
		iteratorIP = l;
		iteratorIK = l + r;
	}
	else{
		iteratorIP = l - r;
		iteratorIK = l;
	}

	if (direction(n, v) == true){
		iteratorJP = v;
		iteratorJK = v + r;
	}
	else{
		iteratorJP = v - r;
		iteratorJK = v;
	}

	if (direction(n, p) == true){
		iteratorKP = p;
		iteratorKK = p + r;
	}
	else{
		iteratorKP = p - r;
		iteratorKK = p;
	}

	for (int i = iteratorIP; i <= iteratorIK; i++){
		for (int j = iteratorJP; j <= iteratorJK; j++){
			for (int k = iteratorKP; k <= iteratorKK; k++){
				if (zakres(n, i, j, k) == true){
					if (odleglosc(l, v, p, i, j, k) <= r * r){
						suma += tab[i][j][k];
					}
				}
			}
		}
	}

	return suma;
}

bool wierszZer(long long tab[][32], int n){
	bool zero = true;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){	
			if (tab[i][j] != 0){
				zero = false;
			}
		}

		if (zero == true){
			return true;
		}
		else{
			zero = true;
		}
	}

	return false;
}

bool kolumnaZer(long long tab[][32], int n){
	bool zero = true;														
	for (int i = 0; i < n; i++){											
		for (int j = 0; j < n; j++){
			if (tab[j][i] != 0){
				zero = false;
			}
		}

		if (zero == true){
			return true;
		}
		else{
			zero = true;
		}
	}

	return false;
}

bool takieSameWiersze(long long tab[][32], int n){
	bool id = true;

	for (int i = 0; i < n - 1; i++){
		for (int j = i + 1; j < n; j++){
			for (int k = 0; k < n; k++){
				if (tab[i][k] != tab[j][k]){
					id = false;
				}
			}

			if (id == true){
				return true;
			}
			else{
				id = true;
			}
		}
	}

	return false;
}

bool takieSameKolumny(long long tab[][32], int n){
	bool id = true;

	for (int i = 0; i < n - 1; i++){
		for (int j = i + 1; j < n; j++){
			for (int k = 0; k < n; k++){
				if (tab[k][i] != tab[k][j]){
					id = false;
				}
			}

			if (id == true){
				return true;
			}
			else{
				id = true;
			}
		}
	}

	return false;
}

bool usuwanieZer(long long tab[][32], int n, bool minus, int s){
	int m = 0; 
	
	if (tab[s][s] == 0){
		while(tab[(s + m) % n][s] == 0){
			m++;
		}

		int pom[n];

		for (int i = 0; i < n; i++){
			pom[i] = tab[(s + m) % n][i];
		}
		for (int i = 0; i < n; i++){
			tab[(s + m) % n][i] = tab[s % n][i];
		}
		for (int i = 0; i < n; i++){
			tab[s % n][i] = pom[i];
		}
		
		minus = !minus;
	}
	
	return minus;
}


long long wspolnyDzielnik(long long a, long long b){
	while (true){
		if (a > b){
			a = a % b;
		}
		else{
			b = b % a;
		}
		
		if (a == 0){
			return b;
		}
		
		if (b == 0){
			return a;
		}
	}
}

long long nwdN(long long tab[32], int n){
	long long w;
	
	if (n == 1){
		return tab[0];
	}
	
	for (int i = 0; i < n; i++){
		if (tab[i] == 0){
			return 0;
		}
		if (tab[i] < 0){
			tab[i] *= -1; 
		}
	}
	
	for (int i = 1; i < n; i++){
		if (i == 1){
			w = wspolnyDzielnik(tab[0], tab[1]);
		}	
		else{
			w = wspolnyDzielnik(w, tab[i]);
		}
	}
	
	return w;
}


long long wyznacznik(long long tab[][32], int n){
	bool minus = false;

	if (wierszZer(tab, n) == true){
		return 0;
	}

	if (kolumnaZer(tab, n) == true){
		return 0;
	}

	if (takieSameWiersze(tab, n) == true){
		return 0;
	}

	if (takieSameKolumny(tab, n) == true){
		return 0;
	}

	long long wsp[n];																
	long long mnoznik, number;
	long long liczba[2];

	for (int i = 0; i < 2; i++){
		liczba[i] = 1;
	}
	
	for (int i = 0; i < n; i++){												
		wsp[i] = 1;
	}

	long long nwd[32];
	long long wynik[n], wynik2[n];

	int d;
	for (int a = 0, w = 0; a < n; a++, w++){
		d = 0;
		for (int b = 0; b < n; b++){
			if (tab[a][b] != 0){
				nwd[d] = tab[a][b];
				d++;
			}
		}

		wynik[w] = nwdN(nwd, d);
		if (wynik[w] != 0){
			for (int b = 0; b < n; b++){
				tab[a][b] /= wynik[w];
			}
		}
		else{
			wynik[w] = 1;
		}
	}

	for (int a = 0, w = 0; a < n; a++, w++){
		d = 0;
		for (int b = 0; b < n; b++){
			if (tab[b][a] != 0){
				nwd[d] = tab[b][a];
				d++;
			}
		}

		wynik2[w] = nwdN(nwd, d);
		if (wynik2[w] != 0){
			for (int b = 0; b < n; b++){
				tab[b][a] /= wynik2[w];
			}

			wynik[w] *= wynik2[w];
		}
	}

	long long x;
	for (int i = 0; i < n - 1; i++){
		minus = usuwanieZer(tab, n, minus, i);
		number = tab[i][i];
		for (int j = i + 1; j < n; j++){
			mnoznik = tab[j][i] * -1;			
			wsp[i] *= number;
			for (int k = i; k < n; k++){
				tab[j][k] = tab[j][k] * number + mnoznik * tab[i][k];
			}
		}

		for (int j = i + 1; j < n; j++){
			d = 0;
			if (wsp[i] != 0){
				nwd[d] = wsp[i];
				d++;
			}
			for (int k = i; k < n; k++){
				if (tab[j][k] != 0){
					nwd[d] = tab[j][k];
					d++;
				}
			}

			x = nwdN(nwd, d);
			if (x != 0){
				wsp[i] /= x;
				for (int k = i; k < n; k++){
					tab[j][k] /= x;
				}
			}
		}
	}

	for (int i = 0; i < n; i++){
		liczba[0] *= tab[i][i];
		liczba[0] *= wynik[i];
		liczba[1] *= wsp[i];

	//	x = nwdN(liczba, 2);
	//	if (x != 0){
	//		liczba[0] /= x;
	//		liczba[1] /= x;
	//	}
	}

	if (minus == true){
		liczba[1] *= -1;
	}

	if (liczba[1] == 0){													
		return 0;
	}
	else{
		return liczba[0] / liczba[1];
	}
}

long long operationD(const long long tab[][32][32], int n, char k, int i){
	long long wyz[32][32];

	if (k == 'l'){
		for (int a = 0; a < n; a++){
			for (int b = 0; b < n; b++){
				wyz[a][b] = tab[i][a][b];
			}
		}
	}
	if (k == 'v'){
		for (int a = 0; a < n; a++){
			for (int b = 0; b < n; b++){
				wyz[a][b] = tab[a][i][b];
			}
		}
	}
	if (k == 'p'){
		for (int a = 0; a < n; a++){
			for (int b = 0; b < n; b++){
				wyz[a][b] = tab[a][b][i];
			}
		}
	}

	long long w = wyznacznik(wyz, n);
	
	return w;
}

int main(){
	int n, f, l, v, p, e, h, w, d, r, i; char c, k; // INPUT
	bool next = false;
	long long wynik;
	cin >> n;

	long long szescian[32][32][32];

	for (int j = 0; j < n; j++){
		for (int a = 0; a < n; a++){
			for (int b = 0; b < n; b++){
				cin >> szescian[a][b][j];
			}
		}
	}

	while (true){
		cin >> c;

		if (next == true){
			cout << endl;
		}
		else{
			next = true;
		}

		if (c == 'T'){
			cin >> l >> v >> p >> e;
			wynik = operationT(szescian, n, l, v, p, e);
			cout << wynik;
		} 
		if (c == 'C'){
			cin >> l >> v >> p >> h >> w >> d;
			wynik = operationC(szescian, n, l, v, p, h, w, d);
			cout << wynik;
		} 
		if (c == 'O'){
			cin >> l >> v >> p >> r;
			wynik = operationO(szescian, n, l, v, p, r);
			cout << wynik;
		} 
		if (c == 'D'){
			cin >> k >> i;
			wynik = operationD(szescian, n, k, i);
			cout << wynik;
		} 
		if (c == 'E'){
			break;
		}
	}

	return 0;
}
