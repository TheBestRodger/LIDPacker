/*!
********************************************************
*
*   @file   Dimensions.cpp
*   @author Kalikin D.M.
*   @date   Январь  12/01/2023
*   @brief  Реализация методов Dimensions.h
*
**********************************************************
*/
#include "LIDPacker/maker/Brain/Dimensions.h"
/*!
*
* PRIVATE
*
*/
#pragma region R
std::string Dimensions::R1Cases(std::string format, int i) {
	std::string a1;

	a1 = std::to_string(i);

	format = a1 + ",";

	return format;
}
std::string Dimensions::R2Cases(std::string format, int i, int j) {
	std::string a1, a2;

	a1 = std::to_string(j);
	a2 = std::to_string(i);

	format = a1 + "," + a2 + ",";

	return format;
}
std::string Dimensions::R3Cases(std::string format, int i, int j, int k) {
	std::string a1, a2, a3;
	a1 = std::to_string(j);
	a2 = std::to_string(i);
	a3 = std::to_string(k);
	format = a1 + "," + a2 + "," + a3 + ",";
	return format;
}
std::string Dimensions::R4Cases(std::string format, int i, int j, int k, int z) {
	std::string a1, a2, a3, a4;
	a1 = std::to_string(j);
	a2 = std::to_string(i);
	a3 = std::to_string(k);
	a4 = std::to_string(z);
	format = a1 + "," + a2 + "," + a3 + "," + a4 + ",";
	return format;
}
std::string Dimensions::R5Cases(std::string format, int i, int j, int k, int z, int a) {
	std::string a1, a2, a3, a4, a5;
	a1 = std::to_string(j);
	a2 = std::to_string(i);
	a3 = std::to_string(k);
	a4 = std::to_string(z);
	a5 = std::to_string(a);
	format = a1 + "," + a2 + "," + a3 + "," + a4 + "," + a5 + ",";
	return format;
}
std::string Dimensions::R6Cases(std::string format, int i, int j, int k, int z, int a, int b) {
	std::string a1, a2, a3, a4, a5, a6;
	a1 = std::to_string(j);
	a2 = std::to_string(i);
	a3 = std::to_string(k);
	a4 = std::to_string(z);
	a5 = std::to_string(a);
	a6 = std::to_string(b);
	format = a1 + "," + a2 + "," + a3 + "," + a4 + "," + a5 + "," + a6 + ",";
	return format;
}
std::string Dimensions::R7Cases(std::string format, int i, int j, int k, int z, int a, int b, int c) {
	std::string a1, a2, a3, a4, a5, a6, a7;
	a1 = std::to_string(j);
	a2 = std::to_string(i);
	a3 = std::to_string(k);
	a4 = std::to_string(z);
	a5 = std::to_string(a);
	a6 = std::to_string(b);
	a7 = std::to_string(c);
	format = a1 + "," + a2 + "," + a3 + "," + a4 + "," + a5 + "," + a6 + "," + a7 + ",";
	return format;
}
std::string Dimensions::R8Cases(std::string format, int i, int j, int k, int z, int a, int b, int c, int d) {
	std::string a1, a2, a3, a4, a5, a6, a7, a8;
	a1 = std::to_string(j);
	a2 = std::to_string(i);
	a3 = std::to_string(k);
	a4 = std::to_string(z);
	a5 = std::to_string(a);
	a6 = std::to_string(b);
	a7 = std::to_string(c);
	a8 = std::to_string(d);
	format = a1 + "," + a2 + "," + a3 + "," + a4 + "," + a5 + "," + a6 + "," + a7 + "," + a8 + ",";
	return format;
}
std::string Dimensions::R9Cases(std::string format, int i, int j, int k, int z, int a, int b, int c, int d, int e) {
	std::string a1, a2, a3, a4, a5, a6, a7, a8, a9;
	a1 = std::to_string(j);
	a2 = std::to_string(i);
	a3 = std::to_string(k);
	a4 = std::to_string(z);
	a5 = std::to_string(a);
	a6 = std::to_string(b);
	a7 = std::to_string(c);
	a8 = std::to_string(d);
	a9 = std::to_string(e);
	format = a1 + "," + a2 + "," + a3 + "," + a4 + "," + a5 + "," + a6 + "," + a7 + "," + a8 + "," + a9 + ",";
	return format;
}
std::string Dimensions::R10Cases(std::string format, int i, int j, int k, int z, int a, int b, int c, int d, int e, int f) {
	std::string a1, a2, a3, a4, a5, a6, a7, a8, a9, a10;
	a1 = std::to_string(j);
	a2 = std::to_string(i);
	a3 = std::to_string(k);
	a4 = std::to_string(z);
	a5 = std::to_string(a);
	a6 = std::to_string(b);
	a7 = std::to_string(c);
	a8 = std::to_string(d);
	a9 = std::to_string(e);
	a10 = std::to_string(f);
	format = a1 + "," + a2 + "," + a3 + "," + a4 + "," + a5 + "," + a6 + "," + a7 + "," + a8 + "," + a9 + "," + a10 + ",";
	return format;
}
std::string Dimensions::R11Cases(std::string format, int i, int j, int k, int z, int a, int b, int c, int d, int e, int f, int g) {
	std::string a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11;
	a1 = std::to_string(j);
	a2 = std::to_string(i);
	a3 = std::to_string(k);
	a4 = std::to_string(z);
	a5 = std::to_string(a);
	a6 = std::to_string(b);
	a7 = std::to_string(c);
	a8 = std::to_string(d);
	a9 = std::to_string(e);
	a10 = std::to_string(f);
	a11 = std::to_string(g);
	format = a1 + "," + a2 + "," + a3 + "," + a4 + "," + a5 + "," + a6 + "," + a7 + "," + a8 + "," + a9 + "," + a10 + "," + a11 + ",";
	return format;
}
std::string Dimensions::R12Cases(std::string format, int i, int j, int k, int z, int a, int b, int c, int d, int e, int f, int g, int h) {
	std::string a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12;
	a1 = std::to_string(j);
	a2 = std::to_string(i);
	a3 = std::to_string(k);
	a4 = std::to_string(z);
	a5 = std::to_string(a);
	a6 = std::to_string(b);
	a7 = std::to_string(c);
	a8 = std::to_string(d);
	a9 = std::to_string(e);
	a10 = std::to_string(f);
	a11 = std::to_string(g);
	a12 = std::to_string(h);
	format = a1 + "," + a2 + "," + a3 + "," + a4 + "," + a5 + "," + a6 + "," + a7 + "," + a8 + "," + a9 + "," + a10 + "," + a11 + "," + a12 + ",";
	return format;
}
std::string Dimensions::R13Cases(std::string format, int i, int j, int k, int z, int a, int b, int c, int d, int e, int f, int g, int h, int m) {
	std::string a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13;
	a1 = std::to_string(j);
	a2 = std::to_string(i);
	a3 = std::to_string(k);
	a4 = std::to_string(z);
	a5 = std::to_string(a);
	a6 = std::to_string(b);
	a7 = std::to_string(c);
	a8 = std::to_string(d);
	a9 = std::to_string(e);
	a10 = std::to_string(f);
	a11 = std::to_string(g);
	a12 = std::to_string(h);
	a13 = std::to_string(m);
	format = a1 + "," + a2 + "," + a3 + "," + a4 + "," + a5 + "," + a6 + "," + a7 + "," + a8 + "," + a9 + "," + a10 + "," + a11 + "," + a12 + "," + a13 + ",";
	return format;
}
std::string Dimensions::R14Cases(std::string format, int i, int j, int k, int z, int a, int b, int c, int d, int e, int f, int g, int h, int m, int n) {
	std::string a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14;
	a1 = std::to_string(j);
	a2 = std::to_string(i);
	a3 = std::to_string(k);
	a4 = std::to_string(z);
	a5 = std::to_string(a);
	a6 = std::to_string(b);
	a7 = std::to_string(c);
	a8 = std::to_string(d);
	a9 = std::to_string(e);
	a10 = std::to_string(f);
	a11 = std::to_string(g);
	a12 = std::to_string(h);
	a13 = std::to_string(m);
	a14 = std::to_string(n);
	format = a1 + "," + a2 + "," + a3 + "," + a4 + "," + a5 + "," + a6 + "," + a7 + "," + a8 + "," + a9 + "," + a10 + "," + a11 + "," + a12 + "," + a13 + "," + a14 + ",";
	return format;
}
std::string Dimensions::R15Cases(std::string format, int i, int j, int k, int z, int a, int b, int c, int d, int e, int f, int g, int h, int m, int n, int l) {
	std::string a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15;
	a1 = std::to_string(j);
	a2 = std::to_string(i);
	a3 = std::to_string(k);
	a4 = std::to_string(z);
	a5 = std::to_string(a);
	a6 = std::to_string(b);
	a7 = std::to_string(c);
	a8 = std::to_string(d);
	a9 = std::to_string(e);
	a10 = std::to_string(f);
	a11 = std::to_string(g);
	a12 = std::to_string(h);
	a13 = std::to_string(m);
	a14 = std::to_string(n);
	a15 = std::to_string(l);
	format = a1 + "," + a2 + "," + a3 + "," + a4 + "," + a5 + "," + a6 + "," + a7 + "," + a8 + "," + a9 + "," + a10 + "," + a11 + "," + a12 + "," + a13 + "," + a14 + "," + a15 + ",";
	return format;
}
std::string Dimensions::R16Cases(std::string format, int i, int j, int k, int z, int a, int b, int c, int d, int e, int f, int g, int h, int m, int n, int l, int o) {
	std::string a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16;
	a1 = std::to_string(j);
	a2 = std::to_string(i);
	a3 = std::to_string(k);
	a4 = std::to_string(z);
	a5 = std::to_string(a);
	a6 = std::to_string(b);
	a7 = std::to_string(c);
	a8 = std::to_string(d);
	a9 = std::to_string(e);
	a10 = std::to_string(f);
	a11 = std::to_string(g);
	a12 = std::to_string(h);
	a13 = std::to_string(m);
	a14 = std::to_string(n);
	a15 = std::to_string(l);
	a16 = std::to_string(o);
	format = a1 + "," + a2 + "," + a3 + "," + a4 + "," + a5 + "," + a6 + "," + a7 + "," + a8 + "," + a9 + "," + a10 + "," + a11 + "," + a12 + "," + a13 + "," + a14 + "," + a15 + "," + a16 + ",";
	return format;
}
std::string Dimensions::R17Cases(std::string format, int i, int j, int k, int z, int a, int b, int c, int d, int e, int f, int g, int h, int m, int n, int l, int o, int p) {
	std::string a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17;
	a1 = std::to_string(j);
	a2 = std::to_string(i);
	a3 = std::to_string(k);
	a4 = std::to_string(z);
	a5 = std::to_string(a);
	a6 = std::to_string(b);
	a7 = std::to_string(c);
	a8 = std::to_string(d);
	a9 = std::to_string(e);
	a10 = std::to_string(f);
	a11 = std::to_string(g);
	a12 = std::to_string(h);
	a13 = std::to_string(m);
	a14 = std::to_string(n);
	a15 = std::to_string(l);
	a16 = std::to_string(o);
	a17 = std::to_string(p);
	format = a1 + "," + a2 + "," + a3 + "," + a4 + "," + a5 + "," + a6 + "," + a7 + "," + a8 + "," + a9 + "," + a10 + "," + a11 + "," + a12 + "," + a13 + "," + a14 + "," + a15 + "," + a16 + "," + a17 + ",";
	return format;
}
std::string Dimensions::R18Cases(std::string format, int i, int j, int k, int z, int a, int b, int c, int d, int e, int f, int g, int h, int m, int n, int l, int o, int p, int q) {
	std::string a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18;
	a1 = std::to_string(j);
	a2 = std::to_string(i);
	a3 = std::to_string(k);
	a4 = std::to_string(z);
	a5 = std::to_string(a);
	a6 = std::to_string(b);
	a7 = std::to_string(c);
	a8 = std::to_string(d);
	a9 = std::to_string(e);
	a10 = std::to_string(f);
	a11 = std::to_string(g);
	a12 = std::to_string(h);
	a13 = std::to_string(m);
	a14 = std::to_string(n);
	a15 = std::to_string(l);
	a16 = std::to_string(o);
	a17 = std::to_string(p);
	a18 = std::to_string(q);
	format = a1 + "," + a2 + "," + a3 + "," + a4 + "," + a5 + "," + a6 + "," + a7 + "," + a8 + "," + a9 + "," + a10 + "," + a11 + "," + a12 + "," + a13 + "," + a14 + "," + a15 + "," + a16 + "," + a17 + "," + a18 + ",";
	return format;
}
void Dimensions::Manager() {
	if (map_y.size() != 0)
		return;
	switch (amount)
	{
	case 1:
		R1();
		break;
	case 2:
		R2();
		break;
	case 3:
		R3();
		break;
	case 4:
		R4();
		break;
	case 5:
		R5();
		break;
	case 6:
		R6();
		break;
	case 7:
		R7();
		break;
	case 8:
		R8();
		break;
	case 9:
		R9();
		break;
	case 10:
		R10();
		break;
	case 11:
		R11();
		break;
	case 12:
		R12();
		break;
	case 13:
		R13();
		break;
	case 14:
		R14();
		break;
	case 15:
		R15();
		break;
	case 16:
		R16();
		break;
	case 17:
		R17();
		break;
	case 18:
		R18();
		break;
	default:
		break;
	}
}
void Dimensions::R1() {
	/*!
	* Первое измерение
	*/
	std::vector<std::string> A;
	A.clear();
	std::vector<std::string>::iterator it_A;
	std::string format = "0";
	for (int i = 0; i < lens[0]; ++i) {
		format = R1Cases(format, i);
		A.push_back(format);
	}
	map_y.insert(make_pair(0, A));
	A.clear();
}
void Dimensions::R2() {
	/*!
	* Второе измерение
	*/
	std::vector<std::string> A;
	A.clear();
	std::vector<std::string>::iterator it_A;
	std::string format = "0,0";
	for (int i = 0; i < lens[1]; ++i) {
		for (int j = 0; j < lens[0]; ++j) {
			format = R2Cases(format, i, j);
			A.push_back(format);
		}
		map_y.insert(make_pair(i, A));
		A.clear();
	}
}
void Dimensions::R3() {
	/*!
	* Третье измерение
	*/
	std::string format = "0,0,0";
	int ii = 0;
	std::vector<std::string> A;
	A.clear();
	std::vector<std::string>::iterator it_A;
	for (int k = 0; k < lens[2]; ++k) {
		for (int i = 0; i < lens[1]; ++i) {
			for (int j = 0; j < lens[0]; ++j) {
				format = R3Cases(format, i, j, k);
				A.push_back(format);
			}
			map_y.insert(std::make_pair(ii, A));
			A.clear();
			ii++;
		}
	}
}
void Dimensions::R4() {
	/*!
	* Четвертое измерение
	*/
	std::string format = "0,0,0,0";
	int ii = 0;
	std::vector<std::string> A;
	A.clear();
	std::vector<std::string>::iterator it_A;
	for (int z = 0; z < lens[3]; ++z) {
		for (int k = 0; k < lens[2]; ++k) {
			for (int i = 0; i < lens[1]; ++i) {
				for (int j = 0; j < lens[0]; ++j) {
					format = R4Cases(format, i, j, k, z);
					A.push_back(format);
				}
				map_y.insert(std::make_pair(ii, A));
				A.clear();
				ii++;
			}
		}
	}
}
void Dimensions::R5() {
	/*!
	* Пятое измерение
	*/
	std::string format = "0,0,0,0,0";
	int ii = 0;
	std::vector<std::string> A;
	A.clear();
	std::vector<std::string>::iterator it_A;
	for (int a = 0; a < lens[4]; ++a) {
		for (int z = 0; z < lens[3]; ++z) {
			for (int k = 0; k < lens[2]; ++k) {
				for (int i = 0; i < lens[1]; ++i) {
					for (int j = 0; j < lens[0]; ++j) {
						format = R5Cases(format, i, j, k, z, a);
						A.push_back(format);
					}
					map_y.insert(std::make_pair(ii, A));
					A.clear();
					ii++;
				}
			}
		}
	}
}
void Dimensions::R6() {
	/*!
	* Шестое измерение
	*/
	std::string format = "0,0,0,0,0,0";
	int ii = 0;
	std::vector<std::string> A;
	A.clear();
	std::vector<std::string>::iterator it_A;
	for (int b = 0; b < lens[5]; ++b) {
		for (int a = 0; a < lens[4]; ++a) {
			for (int z = 0; z < lens[3]; ++z) {
				for (int k = 0; k < lens[2]; ++k) {
					for (int i = 0; i < lens[1]; ++i) {
						for (int j = 0; j < lens[0]; ++j) {
							format = R6Cases(format, i, j, k, z, a, b);
							A.push_back(format);
						}
						map_y.insert(std::make_pair(ii, A));
						A.clear();
						ii++;
					}
				}
			}
		}
	}
}
void Dimensions::R7() {

	/*!
	* Седьмое измерение
	*/
	std::string format = "0,0,0,0,0,0,0";
	int ii = 0;
	std::vector<std::string> A;
	A.clear();
	std::vector<std::string>::iterator it_A;
	for (int c = 0; c < lens[6]; ++c) {
		for (int b = 0; b < lens[5]; ++b) {
			for (int a = 0; a < lens[4]; ++a) {
				for (int z = 0; z < lens[3]; ++z) {
					for (int k = 0; k < lens[2]; ++k) {
						for (int i = 0; i < lens[1]; ++i) {
							for (int j = 0; j < lens[0]; ++j) {
								format = R7Cases(format, i, j, k, z, a, b, c);
								A.push_back(format);
							}
							map_y.insert(std::make_pair(ii, A));
							A.clear();
							ii++;
						}
					}
				}
			}
		}
	}
}
void Dimensions::R8() {

	/*!
	* Восьмое измерение
	*/
	std::string format = "0,0,0,0,0,0,0,0";
	int ii = 0;
	std::vector<std::string> A;
	A.clear();
	std::vector<std::string>::iterator it_A;
	for (int d = 0; d < lens[7]; ++d) {
		for (int c = 0; c < lens[6]; ++c) {
			for (int b = 0; b < lens[5]; ++b) {
				for (int a = 0; a < lens[4]; ++a) {
					for (int z = 0; z < lens[3]; ++z) {
						for (int k = 0; k < lens[2]; ++k) {
							for (int i = 0; i < lens[1]; ++i) {
								for (int j = 0; j < lens[0]; ++j) {
									format = R8Cases(format, i, j, k, z, a, b, c, d);
									A.push_back(format);
								}
								map_y.insert(std::make_pair(ii, A));
								A.clear();
								ii++;
							}
						}
					}
				}
			}
		}
	}
}
void Dimensions::R9() {
	/*!
	* Девятое измерение
	*/
	std::string format = "0,0,0,0,0,0,0,0,0";
	int ii = 0;
	std::vector<std::string> A;
	A.clear();
	std::vector<std::string>::iterator it_A;
	for (int e = 0; e < lens[8]; ++e) {
		for (int d = 0; d < lens[7]; ++d) {
			for (int c = 0; c < lens[6]; ++c) {
				for (int b = 0; b < lens[5]; ++b) {
					for (int a = 0; a < lens[4]; ++a) {
						for (int z = 0; z < lens[3]; ++z) {
							for (int k = 0; k < lens[2]; ++k) {
								for (int i = 0; i < lens[1]; ++i) {
									for (int j = 0; j < lens[0]; ++j) {
										format = R9Cases(format, i, j, k, z, a, b, c, d, e);
										A.push_back(format);
									}
									map_y.insert(std::make_pair(ii, A));
									A.clear();
									ii++;
								}
							}
						}
					}
				}
			}
		}
	}
}
void Dimensions::R10() {
	/*!
	* Десятое измерение
	*/
	std::string format = "0,0,0,0,0,0,0,0,0,0";
	int ii = 0;
	std::vector<std::string> A;
	A.clear();
	std::vector<std::string>::iterator it_A;
	for (int f = 0; f < lens[9]; ++f) {
		for (int e = 0; e < lens[8]; ++e) {
			for (int d = 0; d < lens[7]; ++d) {
				for (int c = 0; c < lens[6]; ++c) {
					for (int b = 0; b < lens[5]; ++b) {
						for (int a = 0; a < lens[4]; ++a) {
							for (int z = 0; z < lens[3]; ++z) {
								for (int k = 0; k < lens[2]; ++k) {
									for (int i = 0; i < lens[1]; ++i) {
										for (int j = 0; j < lens[0]; ++j) {
											format = R10Cases(format, i, j, k, z, a, b, c, d, e, f);
											A.push_back(format);
										}
										map_y.insert(std::make_pair(ii, A));
										A.clear();
										ii++;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
void Dimensions::R11() {
	/*!
	* Одинадцатое измерение
	*/
	std::string format = "0,0,0,0,0,0,0,0,0,0,0";
	int ii = 0;
	std::vector<std::string> A;
	A.clear();
	std::vector<std::string>::iterator it_A;
	for (int g = 0; g < lens[10]; ++g) {
		for (int f = 0; f < lens[9]; ++f) {
			for (int e = 0; e < lens[8]; ++e) {
				for (int d = 0; d < lens[7]; ++d) {
					for (int c = 0; c < lens[6]; ++c) {
						for (int b = 0; b < lens[5]; ++b) {
							for (int a = 0; a < lens[4]; ++a) {
								for (int z = 0; z < lens[3]; ++z) {
									for (int k = 0; k < lens[2]; ++k) {
										for (int i = 0; i < lens[1]; ++i) {
											for (int j = 0; j < lens[0]; ++j) {
												format = R11Cases(format, i, j, k, z, a, b, c, d, e, f, g);
												A.push_back(format);
											}
											map_y.insert(std::make_pair(ii, A));
											A.clear();
											ii++;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
void Dimensions::R12() {
	/*!
	* Двенадцатое измерение
	*/
	std::string format = "0,0,0,0,0,0,0,0,0,0,0,0";
	int ii = 0;
	std::vector<std::string> A;
	A.clear();
	std::vector<std::string>::iterator it_A;
	for (int h = 0; h < lens[11]; ++h) {
		for (int g = 0; g < lens[10]; ++g) {
			for (int f = 0; f < lens[9]; ++f) {
				for (int e = 0; e < lens[8]; ++e) {
					for (int d = 0; d < lens[7]; ++d) {
						for (int c = 0; c < lens[6]; ++c) {
							for (int b = 0; b < lens[5]; ++b) {
								for (int a = 0; a < lens[4]; ++a) {
									for (int z = 0; z < lens[3]; ++z) {
										for (int k = 0; k < lens[2]; ++k) {
											for (int i = 0; i < lens[1]; ++i) {
												for (int j = 0; j < lens[0]; ++j) {
													format = R12Cases(format, i, j, k, z, a, b, c, d, e, f, g, h);
													A.push_back(format);
												}
												map_y.insert(std::make_pair(ii, A));
												A.clear();
												ii++;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
void Dimensions::R13() {
	/*!
	* Тринадцатое измерение
	*/
	std::string format = "0,0,0,0,0,0,0,0,0,0,0,0,0";
	int ii = 0;
	std::vector<std::string> A;
	A.clear();
	std::vector<std::string>::iterator it_A;
	for (int m = 0; m < lens[12]; ++m) {
		for (int h = 0; h < lens[11]; ++h) {
			for (int g = 0; g < lens[10]; ++g) {
				for (int f = 0; f < lens[9]; ++f) {
					for (int e = 0; e < lens[8]; ++e) {
						for (int d = 0; d < lens[7]; ++d) {
							for (int c = 0; c < lens[6]; ++c) {
								for (int b = 0; b < lens[5]; ++b) {
									for (int a = 0; a < lens[4]; ++a) {
										for (int z = 0; z < lens[3]; ++z) {
											for (int k = 0; k < lens[2]; ++k) {
												for (int i = 0; i < lens[1]; ++i) {
													for (int j = 0; j < lens[0]; ++j) {
														format = R13Cases(format, i, j, k, z, a, b, c, d, e, f, g, h, m);
														A.push_back(format);
													}
													map_y.insert(std::make_pair(ii, A));
													A.clear();
													ii++;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
void Dimensions::R14() {
	/*!
	* Четырнадцатое измерение
	*/
	std::string format = "0,0,0,0,0,0,0,0,0,0,0,0,0,0";
	int ii = 0;
	std::vector<std::string> A;
	A.clear();
	std::vector<std::string>::iterator it_A;
	for (int n = 0; n < lens[13]; ++n) {
		for (int m = 0; m < lens[12]; ++m) {
			for (int h = 0; h < lens[11]; ++h) {
				for (int g = 0; g < lens[10]; ++g) {
					for (int f = 0; f < lens[9]; ++f) {
						for (int e = 0; e < lens[8]; ++e) {
							for (int d = 0; d < lens[7]; ++d) {
								for (int c = 0; c < lens[6]; ++c) {
									for (int b = 0; b < lens[5]; ++b) {
										for (int a = 0; a < lens[4]; ++a) {
											for (int z = 0; z < lens[3]; ++z) {
												for (int k = 0; k < lens[2]; ++k) {
													for (int i = 0; i < lens[1]; ++i) {
														for (int j = 0; j < lens[0]; ++j) {
															format = R14Cases(format, i, j, k, z, a, b, c, d, e, f, g, h, m, n);
															A.push_back(format);
														}
														map_y.insert(std::make_pair(ii, A));
														A.clear();
														ii++;
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
void Dimensions::R15() {
	/*!
	* Пятнадцатое измерение
	*/
	std::string format = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
	int ii = 0;
	std::vector<std::string> A;
	A.clear();
	std::vector<std::string>::iterator it_A;
	for (int l = 0; l < lens[14]; ++l) {
		for (int n = 0; n < lens[13]; ++n) {
			for (int m = 0; m < lens[12]; ++m) {
				for (int h = 0; h < lens[11]; ++h) {
					for (int g = 0; g < lens[10]; ++g) {
						for (int f = 0; f < lens[9]; ++f) {
							for (int e = 0; e < lens[8]; ++e) {
								for (int d = 0; d < lens[7]; ++d) {
									for (int c = 0; c < lens[6]; ++c) {
										for (int b = 0; b < lens[5]; ++b) {
											for (int a = 0; a < lens[4]; ++a) {
												for (int z = 0; z < lens[3]; ++z) {
													for (int k = 0; k < lens[2]; ++k) {
														for (int i = 0; i < lens[1]; ++i) {
															for (int j = 0; j < lens[0]; ++j) {
																format = R15Cases(format, i, j, k, z, a, b, c, d, e, f, g, h, m, n, l);
																A.push_back(format);
															}
															map_y.insert(std::make_pair(ii, A));
															A.clear();
															ii++;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
void Dimensions::R16() {
	/*!
	* Шестнадцатое измерение
	*/
	std::string format = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
	int ii = 0;
	std::vector<std::string> A;
	A.clear();
	std::vector<std::string>::iterator it_A;
	for (int o = 0; o < lens[15]; ++o) {
		for (int l = 0; l < lens[14]; ++l) {
			for (int n = 0; n < lens[13]; ++n) {
				for (int m = 0; m < lens[12]; ++m) {
					for (int h = 0; h < lens[11]; ++h) {
						for (int g = 0; g < lens[10]; ++g) {
							for (int f = 0; f < lens[9]; ++f) {
								for (int e = 0; e < lens[8]; ++e) {
									for (int d = 0; d < lens[7]; ++d) {
										for (int c = 0; c < lens[6]; ++c) {
											for (int b = 0; b < lens[5]; ++b) {
												for (int a = 0; a < lens[4]; ++a) {
													for (int z = 0; z < lens[3]; ++z) {
														for (int k = 0; k < lens[2]; ++k) {
															for (int i = 0; i < lens[1]; ++i) {
																for (int j = 0; j < lens[0]; ++j) {
																	format = R16Cases(format, i, j, k, z, a, b, c, d, e, f, g, h, m, n, l, o);
																	A.push_back(format);
																}
																map_y.insert(std::make_pair(ii, A));
																A.clear();
																ii++;
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
void Dimensions::R17() {
	/*!
* Шестнадцатое измерение
*/
	std::string format = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
	int ii = 0;
	std::vector<std::string> A;
	A.clear();
	std::vector<std::string>::iterator it_A;
	for (int p = 0; p < lens[16]; ++p) {
		for (int o = 0; o < lens[15]; ++o) {
			for (int l = 0; l < lens[14]; ++l) {
				for (int n = 0; n < lens[13]; ++n) {
					for (int m = 0; m < lens[12]; ++m) {
						for (int h = 0; h < lens[11]; ++h) {
							for (int g = 0; g < lens[10]; ++g) {
								for (int f = 0; f < lens[9]; ++f) {
									for (int e = 0; e < lens[8]; ++e) {
										for (int d = 0; d < lens[7]; ++d) {
											for (int c = 0; c < lens[6]; ++c) {
												for (int b = 0; b < lens[5]; ++b) {
													for (int a = 0; a < lens[4]; ++a) {
														for (int z = 0; z < lens[3]; ++z) {
															for (int k = 0; k < lens[2]; ++k) {
																for (int i = 0; i < lens[1]; ++i) {
																	for (int j = 0; j < lens[0]; ++j) {
																		format = R17Cases(format, i, j, k, z, a, b, c, d, e, f, g, h, m, n, l, o, p);
																		A.push_back(format);
																	}
																	map_y.insert(std::make_pair(ii, A));
																	A.clear();
																	ii++;
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
void Dimensions::R18() {
	/*!
* Шестнадцатое измерение
*/
	std::string format = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
	int ii = 0;
	std::vector<std::string> A;
	A.clear();
	std::vector<std::string>::iterator it_A;
	for (int q = 0; q < lens[17]; ++q) {
		for (int p = 0; p < lens[16]; ++p) {
			for (int o = 0; o < lens[15]; ++o) {
				for (int l = 0; l < lens[14]; ++l) {
					for (int n = 0; n < lens[13]; ++n) {
						for (int m = 0; m < lens[12]; ++m) {
							for (int h = 0; h < lens[11]; ++h) {
								for (int g = 0; g < lens[10]; ++g) {
									for (int f = 0; f < lens[9]; ++f) {
										for (int e = 0; e < lens[8]; ++e) {
											for (int d = 0; d < lens[7]; ++d) {
												for (int c = 0; c < lens[6]; ++c) {
													for (int b = 0; b < lens[5]; ++b) {
														for (int a = 0; a < lens[4]; ++a) {
															for (int z = 0; z < lens[3]; ++z) {
																for (int k = 0; k < lens[2]; ++k) {
																	for (int i = 0; i < lens[1]; ++i) {
																		for (int j = 0; j < lens[0]; ++j) {
																			format = R18Cases(format, i, j, k, z, a, b, c, d, e, f, g, h, m, n, l, o, p, q);
																			A.push_back(format);
																		}
																		map_y.insert(std::make_pair(ii, A));
																		A.clear();
																		ii++;
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
#pragma endregion 
std::vector<int> Dimensions::makeAr(std::vector<int> Ar) {
	std::vector<int>::iterator it;
	std::vector<int> tmp;
	int k = 0;
	Ar.clear();
	tmp = ord;
	for (it = tmp.begin(); it != tmp.end(); ++it,++k) {
		if (k < 2)
			continue;
		else
			Ar.push_back(*it);
	}
	return Ar;
}
std::vector<int> Dimensions::makeAj(std::vector<int> Aj) {
	std::vector<int> tmp;
	std::vector<int>::iterator it;
	tmp = Aj;
	Aj.clear();
	int k = 0;
	for (it = tmp.begin(); it != tmp.end(); ++it,++k) {
		if (k < 2)
			continue;
		else
			Aj.push_back(*it + 1);
	}
	return Aj;
}
std::vector<int> Dimensions::makeSize(std::vector<int> siz) {
	std::vector<int> tmp = siz;
	std::vector <int>::iterator it;
	
	siz.clear();
	siz.push_back(1);
	int k = tmp.size();
	it = tmp.end();
	for (--it; it != tmp.begin(); --it, --k) {
		if (k <= 2) {
			a2 = *it;
			break;
		}
		siz.push_back(*it);
	}
	return siz;
}
/*!
*
* PUBLIC
*
*/
Dimensions::Dimensions(std::vector<int>allord, std::vector<int> siz) {
	amount  = 0;
	lens	= { 0 };
	ord		= allord;
	argsize = makeSize(siz);
}
Dimensions::Dimensions(size_t _amount, std::vector<int> _lens) {
	amount = _amount;
	lens   = _lens;
}
Dimensions::~Dimensions() {}
std::vector<int> Dimensions::ArgsByXY(int _x, int _y) {//x-colmn y-strok
	Manager();
	std::vector<int> _args;
	_args.clear();
	int stop = 0;
	int st = 0;
	it_y = map_y.find(_y);
	std::string format;
	std::string tmp;
	while (stop < it_y->second[_x].size()) {
		format = it_y->second[_x];
		while (format[stop] != ',') {
			tmp += format[stop];
			stop++;
			if (stop >= it_y->second[_x].size()) {
				break;
			}
		}
		if (stop >= it_y->second[_x].size()) {
			break;
		}
		_args.push_back(std::atoi(tmp.c_str()));
		tmp = "";
		stop++;
	}
	//map_y.clear();
	return _args;
}
std::map<int, std::vector<std::string>>	 Dimensions::AllArgsByXY() {
	Manager();
	return map_y;
}
std::vector<int> Dimensions::XYByArgs(std::vector<int> args) {
	std::vector<int> xy;
	/*
   *
   * numbers - порядковые номера узлов
   * nod     - номер узла и следующие порядковые номера узлов
   * nparam  - порядковый номер конкретного узла
   * nkey    - номер узла как ключ
   * len_1   - длинна узлов по умножению A[0] * A[1] * A[2] * A[0];
   * len_2   - длинна узлов по сложению  A[0] + A[1] + A[2] + A[3];
   * len     - общая сумма длинн узлов по умножению и по сложению
   * sum     - нарастающаяя сумма по углублению к низу графа
   * Ar      - хранит позицию выбранного аргумента после A3
   * Aj      - хранит координаты выбранные пользователем
   * Atmp    - копирует Аj
   *
   */
	std::list<int> numbers;
	std::list<int>::iterator it;

	std::map<int, std::list<int>> nod;
	std::map<int, std::list<int>>::iterator it_nod;

	int nparam = 2;
	int nkey = 1;
	int sum = 1;
	int len_2 = 1;
	std::vector<int> Ar;
	std::vector<int> Aj;
	std::vector<int> Atmp;
	Ar = args;
	Ar = makeAr(Ar);
	Aj = args;
	Atmp = Aj = makeAj(Aj);
	int k = 0;
	std::vector<int> A;// Хранит длинны аргументов с А3
	size_t tmpl = Ar.size();
	A = argsize;
	for (int i = 0; i < tmpl; ++i) {
		len_2 += A[i + 1];
	}
	while (true)
	{
		if (k >= A.size() - 1) break;
		if (k + 1 == A.size() - 1)nparam = 1;
		sum *= A[k];
		for (int i = 0; i < sum; ++i) {
			for (int j = 0; j < A[k + 1]; ++j) {
				numbers.push_back(nparam);
				nparam++;
			}
			nod.insert(std::make_pair(nkey, numbers));
			nkey++;
			numbers.clear();
		}
		k++;
	}

	Aj.push_back(1);
	Atmp.push_back(1);
	tmpl = Aj.size();
	for (int i = 0; i < A.size() - 1; ++i) {
		int tmp = Atmp[tmpl - i - 1];
		it_nod = nod.find(tmp);
		it = it_nod->second.begin();
		for (int j = 0; j < Aj[tmpl - (i + 2)]; ++j, ++it) {
			Atmp[tmpl - (i + 2)] = *it;
		}
	}
	int ans_t = Atmp[0];
	xy.push_back(args[0]);
	xy.push_back(ans_t * a2 - (a2 - args[1]));
	return xy;
}

