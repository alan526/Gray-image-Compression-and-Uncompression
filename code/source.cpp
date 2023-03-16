#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <bitset>
#include "Minheap.h"

using namespace std;

bool isNumber(string temp);
void displayPixelFr(int count[]);

int main(int argc, char* argv[]) {
	string filename;
	string ofilename;
	bool mode;
	/* decide compress or uncompress */
	if (argc == 3) {
		if (strcmp(argv[1], "-c") == 0) {
			mode = true;
			filename = argv[2];
		}
		else {
			cout << "指令輸入錯誤";
			system("pause");
			exit(1);
		}
	}
	else if (argc == 4) {
		if (strcmp(argv[1], "-d") == 0) {
			mode = false;
			filename = argv[2];
			ofilename = argv[3];
		}
		else {
			cout << "指令輸入錯誤";
			system("pause");
			exit(1);
		}
	}
	else {
		cout << "指令輸入錯誤";
		system("pause");
		exit(1);
	}
	/* compress */
	if (mode) {
		/* open image file */
		ifstream fin;
		fin.open(filename);
		if (!fin.is_open()) {
			cout << "檔案開啟失敗";
			system("pause");
			exit(1);
		}
		/* temp variable */
		string temp;
		int a;
		/* pixel frequency variable */
		int countNumber[256] = { 0 };
		/* calculate pixel frequency */
		for (int i = 0; i < 4; i++) {
			getline(fin, temp);
		}
		while (fin >> temp) {
			if (isNumber(temp)) {
				a = stoi(temp);
				countNumber[a]++;
			}
		}
		/* display frequency */
		displayPixelFr(countNumber);
		fin.close();
		/* create min heap */
		Minheap mh;
		for (int i = 0; i < 256; i++) {
			TreeNode* temp = new TreeNode(i, countNumber[i]);
			mh.insert(temp);
		}
		/* create huffman tree */
		Minheap hf = mh;
		Minheap findmax = mh;
		while (hf.getNumber() > 1) {
			hf.createHF();
		}
		/* get huffman code and display(not contain 0 frequency) */
		string hfcode[256];
		cout << "-----------------------------------------" << endl;
		cout << "The pixel and huffman code (not contain 0 frequency)" << endl;
		hf.encode(hfcode);
		int hfcodesize[256];
		for (int i = 0; i < 256; i++) {
			TreeNode temp;
			temp = findmax.popmin();
			if (temp.getfr() == 0) {
				hfcodesize[i] = -1;
			}
			else {
				hfcodesize[i] = temp.getpixel();
			}
		}
		for (int i = 255; i >= 0; i--) {
			if (hfcodesize[i] >= 0) {
				cout << hfcodesize[i] << " => " << hfcode[hfcodesize[i]] << endl;
			}
		}
		/* output compress file */
		fin.open(filename);
		ofstream fout;
		string ofilename;
		int start = 0;
		int pos = filename.find_first_of(".", start);
		ofilename = filename.substr(start, pos - start);
		fout.open(ofilename + ".hc", ios::binary);

		for (int i = 0; i < 256; i++) {
			TreeNode temp;
			temp = mh.getNode(i);
			fout << temp.getpixel() << " " << temp.getfr() << endl;
		}

		for (int i = 0; i < 4; i++) {
			getline(fin, temp);
			fout << temp << endl;
		}
		string totalhfcode = "";
		while (getline(fin, temp)) {
			int current = 0;
			int next = 0;
			while (next != -1) {
				next = temp.find_first_of(" ", current);
				if (next != current) {
					string cuttemp = temp.substr(current, next - current);
					if (!cuttemp.empty()) {
						if (isNumber(cuttemp)) {
							a = stoi(cuttemp);
							totalhfcode += hfcode[a];

						}
					}
				}
				current = next + 1;
			}
		}
		/* package to byte */
		string totalbscode = "";
		bitset<8>bs;
		int bscount = 0;
		for (int i = 0; i < totalhfcode.length(); i++) {
			if (totalhfcode[i] =='0') {
				bs[bscount] = false;
				bscount++;
			}
			else if(totalhfcode[i] =='1') {
				bs[bscount] = true;
				bscount++;
			}
			if (bscount == 8) {
				fout.write((char*)&bs, 1);
				totalbscode += bs.to_string();
				bscount = 0;
			}
		}
		fout.write((char*)&bs, 1);
		totalbscode += bs.to_string();
		bscount = 0;
		fin.close();
		fout.close();
		/* display original image size and compressed image size */
		fin.open(filename);
		fin.seekg(0, ios::end);
		long long finlength = fin.tellg();
		fin.close();
		cout << "----------------------------------------------------------" << endl;
		cout << "The original image size => " << finlength << " bytes" << endl;
		fin.open(ofilename + ".hc");
		fin.seekg(0, ios::end);
		finlength = fin.tellg();
		fin.close();
		cout << "The compressend image size => " << finlength << " bytes" << endl;
	}
	/* uncompress */
	else {
		ifstream dfin;
		ofstream dfout;
		Minheap dhf;
		int pixel, fr;
		string temp;
		dfin.open(filename, ios::binary);
		if (!dfin.is_open()) {
			cout << "檔案開啟失敗";
			system("pause");
			exit(1);
		}
		dfout.open(ofilename);
		/* use information to create huffman tree */
		for (int i = 0; i < 256; i++) {
			dfin >> pixel >> fr;
			TreeNode* temp = new TreeNode(pixel, fr);
			dhf.insert(temp);
		}
		while (dhf.getNumber() > 1) {
			dhf.createHF();
		}

		getline(dfin, temp);
		for (int i = 0; i < 4; i++) {
			getline(dfin, temp);
			dfout << temp << endl;
		}
		/* decode */
		bitset<8>bs;
		string totalcode = "";
		while (!dfin.eof()) {
			dfin.read((char*)&bs, 1);
			string tempcode;
			tempcode = bs.to_string();
			reverse(tempcode.begin(), tempcode.end());
			totalcode += tempcode;
		}
		string totalpixel;
		totalpixel = dhf.searchpixel(totalcode);
		dfout << totalpixel;
	}
	system("pause");
	return(0);
}

bool isNumber(string temp) {
	for (int i = 0; i < temp.length(); i++) {
		int a = int(temp[i]) - 48;
		if (a > 9 || a < 0) {
			return(false);
		}
	}
	return(true);
}

void displayPixelFr(int count[]) {
	cout << "The pixel frequencies" << endl;
	for (int i = 0; i < 256; i++) {
		cout << i << " => " << count[i] << endl;
	}
}
