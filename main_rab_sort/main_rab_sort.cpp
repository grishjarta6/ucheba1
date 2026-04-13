//типы сортировок: пузырьком(a) / подсчетом(d) / быстрая сортировка.

#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <chrono>
#include <fstream>
using namespace std;



void Print(int m[], int nm, int n, int time, size_t mem) {
	int i, vopr;

	switch (n) {
	case (1):
		cout << endl << endl;
		cout << "Bubble sort" << endl;
		break;
	case (2):
		cout << endl << endl;
		cout << "CountingSort" << endl;
		break;
	case (3):
		cout << endl << endl;
		cout << "Quic Sort" << endl;
		break;
	default:
		cout << endl;
		cout << "error" << endl;
		break;
	}
	cout << "run time: " << time << " ms" << endl;
	cout << "memory use: " << mem << " bytes" << endl;

	cout << "print array? 1/0" << endl;
	cin >> vopr;
	if (vopr == 1) { for (i = 0; i < nm; i += 1) { cout << m[i] << " "; } cout << endl << endl; }
}

int Bubblesort(int m[],int n, size_t& mem){
	int i, j, old, t, mem2 = 0;
	bool sw = false;
	mem = 0;

	int* mb = new int[n];
	mem += sizeof(int) * n;

	for (i = 0; i < n; i += 1) {
		mb[i] = m[i];
	}

	auto start = std::chrono::high_resolution_clock::now();


	for (i = 0; i < n - 1; i += 1) {
		sw = false;
		for (j = 0; j < n - i - 1; j += 1) {
			if (mb[j] > mb[j + 1]) {
				old = mb[j];
				mb[j] = mb[j + 1];
				mb[j + 1] = old;
			}
			sw = true;
		}

	}

	auto end = std::chrono::high_resolution_clock::now();
	auto tm = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	//mem2 += sizeof(int) * n;
	//mem = mem2 - mem;

	t = tm.count();

	Print(mb, n, 1, t, mem);

	//cout << "!!!!!!!!!!!!!!!!!BC" << endl;
	delete []mb;
	return 0;
}

int CountingSort(int m[], int n, size_t& mem) {
	int i, min, max, range, in = 0, t, mem2 = 0;
	mem = 0;
	int* mc = new int[n];
	mem += sizeof(int) * n;

	for (i = 0; i < n; i += 1) {
		mc[i] = m[i];
	}

	auto start = std::chrono::high_resolution_clock::now();

	min = mc[0];
	max = mc[0];
	for (i = 0; i < n; i += 1) {
		if (mc[i] < min) { min = mc[i]; }
		if (mc[i] > max) { max = mc[i]; }
	}

	range = max - min + 1;
	int* count = new int[range]();
	for (int i = 0; i < n; i += 1) {
		count[mc[i] - min] += 1;
	}

	for (i = 0; i < range; i += 1) {
		while (count[i] > 0) {
			mc[in] = i + min;
			in += 1;
			count[i] -= 1;
		}
	}
	delete []count;

	auto end = std::chrono::high_resolution_clock::now();
	auto tm = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	t = tm.count();

	//mem2 += sizeof(int) * n;
	//mem = mem2 - mem;

	Print(mc, n, 2, t, mem);
	delete []mc;
	//cout << "!!!!!!!!!!!!!!!!!QS con" << endl;
	return 0;
}

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
	//cout << "!!!!!!!!!!!!!!!!!swap" << endl;

}


int part(int mq[], int low, int high) {
	int pv, i, j;
	pv = mq[high];
	i = low - 1;
	//cout << "!!!!!!!!!!!!!!!!!part" << endl;
	for (j = low; j < high; j += 1) {
		if (mq[j] < pv) {
			i += 1;
			swap(mq[i], mq[j]);
		}
	}
	swap(mq[i + 1], mq[high]);
	cout << i << endl;
	return i + 1;
}

void RecQuicSort(int m[],int z, int n) {
	int i, min, max, pvin;
	
	if (z < n) {
		
		pvin = part(m, z, n);
		RecQuicSort(m, z, (pvin - 1));
		RecQuicSort(m, (pvin + 1), n);
	}
	
}

int QuicSort(int m[], int n, size_t& mem) {
	int i, t, mem2 = 0;
	mem = 0;
	int* mq = new int[n];
	mem += sizeof(int) * n;

	for (i = 0; i < n; i++)
		mq[i] = m[i];

	auto start = chrono::high_resolution_clock::now();

	RecQuicSort(mq, 0, n - 1);

	auto end = chrono::high_resolution_clock::now();

	auto tm = chrono::duration_cast<chrono::milliseconds>(end - start);

	t = tm.count();

	//mem2 += sizeof(int) * n;
	//mem = mem2 - mem;

	Print(mq, n, 3, t, mem);
	delete[] mq;
	return 0;
}

int main() {
	int n = 0, i, ask, temp;
	size_t mem_use;
	const char* filename = nullptr;

	cout << "choose file 1-5: " << endl;
	cout << "10_test.txt" << endl;
	cout << "100_test.txt" << endl;
	cout << "1000_test.txt" << endl;
	cout << "10000_test.txt" << endl;
	cout << "1000000_test.txt" << endl;
	cin >> ask;

	switch (ask) {
	case 1:
		filename = "10_test.txt";
		break;
	case 2:
		filename = "100_test.txt";
		break;
	case 3:
		filename = "1000_test.txt";
		break;
	case 4:
		filename = "10000_test.txt";
		break;
	case 5:
		filename = "1000000_test.txt";
		break;
	default:
		cout << "error" << endl;
		break;
	}
	ifstream file(filename);
	if (!file.is_open()) {
		cout << "cant open file " << filename << endl;
		return 1;
	}


	while (file >> temp) {
		n += 1;
	}

	if (n == 0) {
		cout << "file is clear" << endl;
		return 1;
	}

	file.clear();                
	file.seekg(0, ios::beg);    

	int* arr = new int[n];

	for (i = 0; i < n; i += 1) {
		if (!(file >> arr[i])) {
			cout << "error reading file" << endl;
			delete[] arr;
			return 1;
		}
	}
	file.close();

	cout << "start Bubblesort? 1/0" << endl;
	cin >> ask;
	if (ask == 1) { Bubblesort(arr, n, mem_use); }

	cout << "start CountingSort? 1/0" << endl;
	cin >> ask;
	if (ask == 1) { CountingSort(arr, n, mem_use); }

	cout << "start QuicSort? 1/0" << endl;
	cin >> ask;
	if (ask == 1) { QuicSort(arr, n, mem_use); }
	

	delete[] arr;
	return 0;
}