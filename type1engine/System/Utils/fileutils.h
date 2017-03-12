#pragma once
#include <fstream>
#include <string>

namespace Engine
{
	std::string ReadFile(const char *pfile)
	{
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
			printf("Opened %s\n", pfile);
		}
		else
		{
			printf("Could not open %s\n", pfile);
			exit(1);
		}
		return out;
	}
}