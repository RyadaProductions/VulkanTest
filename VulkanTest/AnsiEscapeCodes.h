#ifndef AnsiEscapecodes_H
#define AnsiEscapecodes_H

// ANSI color escape sequences (works on windows since 10 aniversary edition)
namespace AnsiEscapeCodes {
	// Style
	static constexpr char RESET[] = "\u001b[0m";
	static constexpr char BOLD[] = "\u001b[1m";
	static constexpr char UNDERLINE[] = "\u001b[4m";
	static constexpr char Inverse[] = "\u001b[7m";

	// Foreground
	static constexpr char FOREGROUND_COLOR_BLACK[] = "\u001b[30m";
	static constexpr char FOREGROUND_COLOR_RED[] = "\u001b[31m";
	static constexpr char FOREGROUND_COLOR_GREEN[] = "\u001b[32m";
	static constexpr char FOREGROUND_COLOR_YELLOW[] = "\u001b[33m";
	static constexpr char FOREGROUND_COLOR_BLUE[] = "\u001b[34m";
	static constexpr char FOREGROUND_COLOR_MAGENTA[] = "\u001b[35m";
	static constexpr char FOREGROUND_COLOR_CYAN[] = "\u001b[36m";
	static constexpr char FOREGROUND_COLOR_WHITE[] = "\u001b[37m";

	// Background
	static constexpr char BACKGROUND_COLOR_BLACK[] = "\u001b[40m";
	static constexpr char BACKGROUND_COLOR_RED[] = "\u001b[41m";
	static constexpr char BACKGROUND_COLOR_GREEN[] = "\u001b[42m";
	static constexpr char BACKGROUND_COLOR_YELLOW[] = "\u001b[43m";
	static constexpr char BACKGROUND_COLOR_BLUE[] = "\u001b[44m";
	static constexpr char BACKGROUND_COLOR_MAGENTA[] = "\u001b[45m";
	static constexpr char BACKGROUND_COLOR_CYAN[] = "\u001b[46m";
	static constexpr char BACKGROUND_COLOR_WHITE[] = "\u001b[47m";

	// Strong foreground
	static constexpr char FOREGROUND_COLOR_STRONG_BLACK[] = "\u001b[90m";
	static constexpr char FOREGROUND_COLOR_STRONG_RED[] = "\u001b[91m";
	static constexpr char FOREGROUND_COLOR_STRONG_GREEN[] = "\u001b[92m";
	static constexpr char FOREGROUND_COLOR_STRONG_YELLOW[] = "\u001b[93m";
	static constexpr char FOREGROUND_COLOR_STRONG_BLUE[] = "\u001b[94m";
	static constexpr char FOREGROUND_COLOR_STRONG_MAGENTA[] = "\u001b[95m";
	static constexpr char FOREGROUND_COLOR_STRONG_CYAN[] = "\u001b[96m";
	static constexpr char FOREGROUND_COLOR_STRONG_WHITE[] = "\u001b[97m";
	
	// Strong background
	static constexpr char BACKGROUND_COLOR_STRONG_BLACK[] = "\u001b[100m";
	static constexpr char BACKGROUND_COLOR_STRONG_RED[] = "\u001b[101m";
	static constexpr char BACKGROUND_COLOR_STRONG_GREEN[] = "\u001b[102m";
	static constexpr char BACKGROUND_COLOR_STRONG_YELLOW[] = "\u001b[103m";
	static constexpr char BACKGROUND_COLOR_STRONG_BLUE[] = "\u001b[104m";
	static constexpr char BACKGROUND_COLOR_STRONG_MAGENTA[] = "\u001b[105m";
	static constexpr char BACKGROUND_COLOR_STRONG_CYAN[] = "\u001b[106m";
	static constexpr char BACKGROUND_COLOR_STRONG_WHITE[] = "\u001b[107m";

}

#endif // !AnsiEscapecodes_H