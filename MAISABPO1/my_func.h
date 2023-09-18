#ifndef MY_FUNC_H
#define MY_FUNC_H

#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <conio.h>
#include <array>
#include <vector>
#include <locale>
#include <fstream>
#include <bitset>
#include <streambuf>

void printFile(const std::string& format, const std::string& filePath);
void taskTwo(const std::string& command, int num1, int num2);
int gcd(int a, int b);
int modInverse(int a, int m);
int addMod(int a, int b, int m);
int subtractMod(int a, int b, int m);
int multiplyMod(int a, int b, int m);
int powerMod(int base, int exponent, int m);
int divideMod(int a, int b, int m);
uint32_t GF2nInverse(uint32_t a, uint32_t m);
uint32_t GF2nMultiply(uint32_t a, uint32_t b, uint32_t m);
uint32_t GF2nSubtract(uint32_t a, uint32_t b);
uint32_t GF2nAdd(uint32_t a, uint32_t b);
uint32_t PolynomialDegree(uint32_t num);
bool isPrime(int num);
void printPrimes(int N);

#endif