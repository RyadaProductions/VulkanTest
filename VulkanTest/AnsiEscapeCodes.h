#ifndef AnsiEscapecodes_H
#define AnsiEscapecodes_H

// ANSI color escape sequences (works on windows since 10 aniversary edition)
class AnsiEscapeCodes {
public:
  // Style
  static constexpr const char* RESET = "[0m";
  static constexpr const char* BOLD = "[1m";
  static constexpr const char* UNDERLINE = "[4m";
  static constexpr const char* Inverse = "[7m";

  // Foreground
  static constexpr const char* FOREGROUND_COLOR_BLACK = "[30m";
  static constexpr const char* FOREGROUND_COLOR_RED = "[31m";
  static constexpr const char* FOREGROUND_COLOR_GREEN = "[32m";
  static constexpr const char* FOREGROUND_COLOR_YELLOW = "[33m";
  static constexpr const char* FOREGROUND_COLOR_BLUE = "[34m";
  static constexpr const char* FOREGROUND_COLOR_MAGENTA = "[35m";
  static constexpr const char* FOREGROUND_COLOR_CYAN = "[36m";
  static constexpr const char* FOREGROUND_COLOR_WHITE = "[37m";

  // Background
  static constexpr const char* BACKGROUND_COLOR_BLACK = "[40m";
  static constexpr const char* BACKGROUND_COLOR_RED = "[41m";
  static constexpr const char* BACKGROUND_COLOR_GREEN = "[42m";
  static constexpr const char* BACKGROUND_COLOR_YELLOW = "[43m";
  static constexpr const char* BACKGROUND_COLOR_BLUE = "[44m";
  static constexpr const char* BACKGROUND_COLOR_MAGENTA = "[45m";
  static constexpr const char* BACKGROUND_COLOR_CYAN = "[46m";
  static constexpr const char* BACKGROUND_COLOR_WHITE = "[47m";

  // Strong foreground
  static constexpr const char* FOREGROUND_COLOR_STRONG_BLACK = "[90m";
  static constexpr const char* FOREGROUND_COLOR_STRONG_RED = "[91m";
  static constexpr const char* FOREGROUND_COLOR_STRONG_GREEN = "[92m";
  static constexpr const char* FOREGROUND_COLOR_STRONG_YELLOW = "[93m";
  static constexpr const char* FOREGROUND_COLOR_STRONG_BLUE = "[94m";
  static constexpr const char* FOREGROUND_COLOR_STRONG_MAGENTA = "[95m";
  static constexpr const char* FOREGROUND_COLOR_STRONG_CYAN = "[96m";
  static constexpr const char* FOREGROUND_COLOR_STRONG_WHITE = "[97m";

  // Strong background
  static constexpr const char* BACKGROUND_COLOR_STRONG_BLACK = "[100m";
  static constexpr const char* BACKGROUND_COLOR_STRONG_RED = "[101m";
  static constexpr const char* BACKGROUND_COLOR_STRONG_GREEN = "[102m";
  static constexpr const char* BACKGROUND_COLOR_STRONG_YELLOW = "[103m";
  static constexpr const char* BACKGROUND_COLOR_STRONG_BLUE = "[104m";
  static constexpr const char* BACKGROUND_COLOR_STRONG_MAGENTA = "[105m";
  static constexpr const char* BACKGROUND_COLOR_STRONG_CYAN = "[106m";
  static constexpr const char* BACKGROUND_COLOR_STRONG_WHITE = "[107m";

};

#endif // !AnsiEscapecodes_H