#pragma once
#include "../pch.h"

extern PluginFuncs* g_Funcs;

#if defined(WIN32) || defined(_WIN32)
#include <Windows.h>
#endif

void raw_split(const std::string& s, char delim, std::vector<std::string>& elems)
{
	std::stringstream ss(s);
	std::string item;
	while(getline(ss, item, delim)) {
		if(!item.empty())
			elems.push_back(item);
	}
}

namespace std {

	std::vector<std::string> split(const std::string& s, char delim)
	{
		std::vector<std::string> elems;
		raw_split(s, delim, elems);
		return elems;
	}

}

namespace Plugin {
	namespace Log {
		enum Colors {
			LOG_NOR,
			LOG_INF,
			LOG_WRN,
			LOG_ERR
		};

		const char* GetLevelTag(Colors level) {
			switch (level) {
			case LOG_INF:
				return "[INF]";
				break;

			case LOG_WRN:
				return "[WRN]";
				break;

			case LOG_ERR:
				return "[ERR]";
				break;

			case LOG_NOR:
			default:
				return "[MSG]";
				break;
			}
		}

		#if defined(WIN32) || defined(_WIN32)
			WORD GetLevelColor(Colors type) { // From SqMod @Thanks S.L.C
				switch (type) {
				case LOG_INF:
					return FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE;
					break;

				case LOG_WRN:
					return FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN;
					break;

				case LOG_ERR:
					return FOREGROUND_INTENSITY | FOREGROUND_RED;
					break;

				case LOG_NOR:
				default:
					return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
					break;
				}
			}

			void MSG(const char* msg, Colors level) {
				HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
				CONSOLE_SCREEN_BUFFER_INFO csb_state;
				GetConsoleScreenBufferInfo(hstdout, &csb_state);
				SetConsoleTextAttribute(hstdout, GetLevelColor(level));
				printf_s("%s ", GetLevelTag(level));
				SetConsoleTextAttribute(hstdout, GetLevelColor(LOG_NOR));
				std::printf("%s\n", msg);
				SetConsoleTextAttribute(hstdout, csb_state.wAttributes);
			}
		#else
			const char* GetLevelColor(Colors type) {
				switch (type) {
				case LOG_INF:
					return "\033[21;96m[INF]\033[0m";
					break;

				case LOG_WRN:
					return "\033[21;93m[WRN]\033[0m";
					break;

				case LOG_ERR:
					return "\033[21;91m[ERR]\033[0m";
					break;

				default:
					return "\033[21;96m[MSG]\033[0m";
					break;
				}
			}

			void MSG(const char* msg, Colors level) {
				printf_s("%s%s %s\033[0m\n", GetLevelColor(level), GetLevelTag(level), msg);
			}
		#endif

		inline void MSG(const char* msg) { MSG(msg, LOG_NOR); }
		inline void INF(const char* msg) { MSG(msg, LOG_INF); }
		inline void WRN(const char* msg) { MSG(msg, LOG_WRN); }
		inline void ERR(const char* msg) { MSG(msg, LOG_ERR); }
	}

	namespace Player {
		void MessageToAll(const char* msg) {
			for (int32_t i = 0; i <= (int32_t) g_Funcs->GetMaxPlayers(); i++) {
				if (g_Funcs->IsPlayerConnected(i))
					g_Funcs->SendClientMessage(i, 1, "%s", msg);
			}
		}
	}
}