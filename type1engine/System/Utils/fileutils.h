#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <windows.h>
#include <glm\glm.hpp>

namespace Engine
{
	static std::string ReadFile(const char *pfile)
	{
#if 0
		std::string out;
		std::ifstream f(pfile);
		if (f.is_open())
		{
			std::string line;
			while (getline(f, line))
			{
				out.append(line);
				out.append("\n");
			}
			f.close();
			printf("Opened: %s\n", pfile);
		}
		else
		{
			printf("Could not open %s\n", pfile);
			exit(1);
		}
		return out;
#else
		std::ifstream in(pfile);
		if (in)
		{
			std::string contents;
			in.seekg(0, std::ios::end);
			contents.resize((unsigned int)in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&contents[0], contents.size());
			in.close();
			printf("Opened: %s\n", pfile);
			return contents;
		}
		else
		{
			printf("Could not open %s\n", pfile);
			exit(1);
		}
#endif
	}

	static std::string GetFileExtension(const char *file)
	{
		std::vector<std::string> elems;
		std::stringstream ss(file);
		std::string item;
		while (std::getline(ss, item, '.'))
		{
			elems.push_back(item);
		}
		return elems.back();
	}

	static int mon_log(char *in, size_t c, char* format, ...)
	{
		//char str_tmp[50];
		int i = 0;
		va_list vArgList;                            //����һ��va_list�͵ı���,���������ָ�������ָ��.
		va_start(vArgList, format);                 //��va_start���ʼ������,�����ĵڶ��������ǵ�һ���ɱ������ǰһ������,��һ���̶��Ĳ���
		i = _vsnprintf_s(in, c, c, format, vArgList); //ע��,��Ҫ©��ǰ���_
		va_end(vArgList);                            //��va_end������ɱ�����Ļ�ȡ
		return i;                                    //���ز������ַ������м��ж��ż��
	}

	static char *localeToUTF8(const char *src)
	{
		static char *buf = NULL;
		if (buf)
		{
			free(buf);
			buf = NULL;
		}
		wchar_t *unicode_buf;
		int nRetLen = MultiByteToWideChar(CP_ACP, 0, src, -1, NULL, 0);
		unicode_buf = (wchar_t*)malloc((nRetLen + 1) * sizeof(wchar_t));
		MultiByteToWideChar(CP_ACP, 0, src, -1, unicode_buf, nRetLen);
		nRetLen = WideCharToMultiByte(CP_UTF8, 0, unicode_buf, -1, NULL, 0, NULL, NULL);
		buf = (char*)malloc(nRetLen + 1);
		WideCharToMultiByte(CP_UTF8, 0, unicode_buf, -1, buf, nRetLen, NULL, NULL);
		free(unicode_buf);
		return buf;
	}

	static unsigned int Color_FloatToInt(glm::vec4 color)
	{
		int r = int(color.r * 255.0f);
		int g = int(color.g * 255.0f);
		int b = int(color.b * 255.0f);
		int a = int(color.a * 255.0f);

		return a << 24 | b << 16 | g << 8 | r;
	};
}