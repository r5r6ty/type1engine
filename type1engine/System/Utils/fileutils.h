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
		va_list vArgList;                            //定义一个va_list型的变量,这个变量是指向参数的指针.
		va_start(vArgList, format);                 //用va_start宏初始化变量,这个宏的第二个参数是第一个可变参数的前一个参数,是一个固定的参数
		i = _vsnprintf_s(in, c, c, format, vArgList); //注意,不要漏掉前面的_
		va_end(vArgList);                            //用va_end宏结束可变参数的获取
		return i;                                    //返回参数的字符个数中间有逗号间隔
	}

	static std::string localeToUTF8(const char *src)
	{
		int nLen = MultiByteToWideChar(CP_ACP, 0, src, -1, NULL, 0);
		std::wstring unicode((size_t)nLen, L'\0');
		MultiByteToWideChar(CP_ACP, 0, src, -1, &unicode[0], nLen);
		int nRetLen = WideCharToMultiByte(CP_UTF8, 0, unicode.c_str(), -1, NULL, 0, NULL, NULL);
		std::string out((size_t)nRetLen, '\0');
		WideCharToMultiByte(CP_UTF8, 0, unicode.c_str(), -1, &out[0], nRetLen, NULL, NULL);
		out.resize(nRetLen > 0 ? (size_t)nRetLen - 1 : 0); // 去掉结尾的 \0
		return out;
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