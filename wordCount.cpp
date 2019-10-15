// wordCount.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//#include "stdafx.h"
#include"pch.h"
#include <iostream>
#include <fstream>
#include "TextAnalysisUtil.h"
using namespace std;
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "未输入命令行参数" << endl;
		system("pause");
		return -1;
	}
	TextAnalysisUtil TA;
	ifstream infile;
	WordInf tempArr[10] = {

	};
	infile.open(argv[1], ifstream::binary | ifstream::in);
	if (!infile) {
		cout << "文件打开失败" << endl;
		system("pause");
		return 1;
	}
	infile.close();
	ofstream outFile;
	outFile.open("result.txt");
	if (!outFile) {
		cout << "文件打开失败" << endl;
		system("pause");
		return 1;
	}
	outFile << "characters: " << TA.asciiCount(argv[1]) << endl;

	outFile << "words: " << TA.wordAnalysis(argv[1], tempArr) << endl;
	outFile << "lines: " << TA.countLines(argv[1]) << endl;
	for (int d = 0; d < 10; d++)
	{
		if (tempArr[d].count > 0)
			outFile << "<" << tempArr[d].word << ">: " << tempArr[d].count << endl;
	}
	system("pause");
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
