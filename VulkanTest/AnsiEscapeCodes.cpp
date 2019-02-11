// ANSI color escape sequences (works on windows since 10 aniversary edition)
class AnsiEscapeCodes {
public:
  // Style
  static constexpr const char* RESET = "[0m";
  static constexpr const char* BOLD = "[1m";
  static constexpr const char* UNDERLINE = "[4m";
  static constexpr const char* Inverse = "[7m";

  // Foreground
  static constexpr const char* FOREGROUNDCOLORBLACK = "[30m";
  static constexpr const char* FOREGROUNDCOLORRED = "[31m";
  static constexpr const char* FOREGROUNDCOLORGREEN = "[32m";
  static constexpr const char* FOREGROUNDCOLORYELLOW = "[33m";
  static constexpr const char* FOREGROUNDCOLORBLUE = "[34m";
  static constexpr const char* FOREGROUNDCOLORMAGENTA = "[35m";
  static constexpr const char* FOREGROUNDCOLORCYAN = "[36m";
  static constexpr const char* FOREGROUNDCOLORWHITE = "[37m";

  // Background
  static constexpr const char* BACKGROUNDCOLORBLACK = "[40m";
  static constexpr const char* BACKGROUNDCOLORRED = "[41m";
  static constexpr const char* BACKGROUNDCOLORGREEN = "[42m";
  static constexpr const char* BACKGROUNDCOLORYELLOW = "[43m";
  static constexpr const char* BACKGROUNDCOLORBLUE = "[44m";
  static constexpr const char* BACKGROUNDCOLORMAGENTA = "[45m";
  static constexpr const char* BACKGROUNDCOLORCYAN = "[46m";
  static constexpr const char* BACKGROUNDCOLORWHITE = "[47m";

  // Strong foreground
  static constexpr const char* FOREGROUNDCOLORSTRONGBLACK = "[90m";
  static constexpr const char* FOREGROUNDCOLORSTRONGRED = "[91m";
  static constexpr const char* FOREGROUNDCOLORSTRONGGREEN = "[92m";
  static constexpr const char* FOREGROUNDCOLORSTRONGYELLOW = "[93m";
  static constexpr const char* FOREGROUNDCOLORSTRONGBLUE = "[94m";
  static constexpr const char* FOREGROUNDCOLORSTRONGMAGENTA = "[95m";
  static constexpr const char* FOREGROUNDCOLORSTRONGCYAN = "[96m";
  static constexpr const char* FOREGROUNDCOLORSTRONGWHITE = "[97m";

  // Strong background
  static constexpr const char* BACKGROUNDCOLORSTRONGBLACK = "[100m";
  static constexpr const char* BACKGROUNDCOLORSTRONGRED = "[101m";
  static constexpr const char* BACKGROUNDCOLORSTRONGGREEN = "[102m";
  static constexpr const char* BACKGROUNDCOLORSTRONGYELLOW = "[103m";
  static constexpr const char* BACKGROUNDCOLORSTRONGBLUE = "[104m";
  static constexpr const char* BACKGROUNDCOLORSTRONGMAGENTA = "[105m";
  static constexpr const char* BACKGROUNDCOLORSTRONGCYAN = "[106m";
  static constexpr const char* BACKGROUNDCOLORSTRONGWHITE = "[107m";

};