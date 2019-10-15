//#include "stdafx.h"
#include"pch.h"
#include "TextAnalysisUtil.h"


TextAnalysisUtil::TextAnalysisUtil()
{
}


TextAnalysisUtil::~TextAnalysisUtil()
{
}

bool isWordGreater(string str1, int n1, string str2, int n2)
{
	bool flag;
	if (n1 > n2)
	{
		flag = true;
	}
	else if (n1 < n2)
	{
		flag = false;
	}
	else
	{
		flag = strcmp(str1.c_str(), str2.c_str()) < 0 ? true : false;
	}
	return flag;
}

int TextAnalysisUtil::asciiCount(char * fileName)
{
	//������
	ifstream fin(fileName);
	if (!fin)
	{
		cout << "�ļ���ʧ��";
		return -1;
	}
	char ch;
	int count = 0;
	while (fin.get(ch))
	{
		if (isAsascii(ch))
			count++;
	}
	fin.close();
	return count;
}

bool TextAnalysisUtil::isAsascii(char c)
{
	return ((unsigned char)c & 0x80) == 0x80 ? false : true;
}

int TextAnalysisUtil::countLines(char * fileName)
{
	ifstream ReadFile;
	int n = 0;
	string tmp;
	int len;
	ReadFile.open(fileName, ios::in);
	while (getline(ReadFile, tmp, '\n'))
	{
		len = tmp.length();
		for (int i = 0; i < len; i++)
		{
			if ((tmp[i] >= 0 && tmp[i] <= 32) || tmp[i] == 127)
			{
				continue;
			}
			else
			{
				n++;
				break;
			}

		}




	}
	ReadFile.close();
	return n;
}

int TextAnalysisUtil::wordAnalysis(char * fileName, WordInf * tempArr)
{
	ifstream fin(fileName);
	if (!fin)
	{
		cout << "�ļ���ʧ��";
		return -1;
	}
	char ch;
	string str;
	int state = 0;
	int nflag;
	int wordCount = 0;
	unordered_map<string, int> map;
	while (fin.get(ch))
	{
		if (ch < -1 || ch>255)
		{
			return -1;
		}
		switch (state)
		{
		case 0:
			//���ҵ����׵�״̬
			if (isdigit(ch))
			{
				//ת���ҵ����ֿ�ͷ�Ĺ���״̬
				state = 1;
			}
			else if (isalpha(ch))
			{
				//�ҵ����ʣ�ת����ȡ����״̬
				state = 2;
				str = ch;
				nflag = 1;//��¼���ʿ�ͷ��ĸ��
			}
			break;
		case 1:
			//ת���ҵ����ֿ�ͷ�򲻷��ϵ��ʿ�ͷ��4����ĸ�Ĺ���״̬
			if (!(isdigit(ch) || isalpha(ch)))
			{
				state = 0;
			}
			break;
		case 2:
			//��ȡ����״̬
			if (isalpha(ch))
			{
				++nflag;
				str += ch;
				if (nflag >= 4)
					//������ȡ����β��״̬
					state = 3;
			}
			else
			{
				//�����㵥�ʿ�ͷ��4����ĸ
				state = 1;
			}
			break;
		case 3:
			//��ȡ����β��״̬
			if (isdigit(ch) || isalpha(ch))
			{
				str += ch;
			}
			else
			{
				//����ʹ����ַ���
				transform(str.begin(), str.end(), str.begin(), ::tolower);
				state = 0;
				wordCount++;
				map[str]++;
			}
			break;
		default:
			break;
		}

	}
	if (state == 3)
		//�����������û���ļ�������ַ���
	{
		transform(str.begin(), str.end(), str.begin(), ::tolower);
		wordCount++;
		map[str]++;
	}
	//�����ҳ�Ƶ����ߵ�top10����
	for (auto iter = map.begin(); iter != map.end(); iter++)
	{
		if (isWordGreater(iter->first, iter->second, tempArr[9].word, tempArr[9].count))
		{
			tempArr[9].word = iter->first;
			tempArr[9].count = iter->second;
			for (int i = 9; i >= 1; i--)
			{
				if (isWordGreater(tempArr[i].word, tempArr[i].count, tempArr[i - 1].word, tempArr[i - 1].count))
				{
					swap(tempArr[i], tempArr[i - 1]);
				}
			}
		}
	}
	fin.close();
	return wordCount;
}