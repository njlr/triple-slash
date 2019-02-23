#include <string>
#include <vector>
#include <iostream>

using namespace std;

string takePattern(string& s) {
  string pattern = "";

  while (!s.empty()) {
    auto next = s[0];

    switch (next) {
      case '\\':
      {
        s.erase(0, 1);

        if (!s.empty()) {
          pattern += s[0];
          s.erase(0, 1);
        }

        break;
      }

      case '/':
      {
        s.erase(0, 1);

        return pattern;
      }

      default:
      {
        pattern += next;
        s.erase(0, 1);

        break;
      }
    }
  }

  return pattern;
}

int main(int argc, char **argv) {
  vector<string> args(argv, argv + argc);

  if (args.size() < 2) {
    cout << "Usage: " << args[0] << " <program>" << endl;

    return 1;
  }

  string s = args[1];

  while (!s.empty()) {
    switch (s[0]) {
      case '\\':
      {
        s.erase(0, 1);

        if (!s.empty()) {
          cout << s[0];
          s.erase(0, 1);
        }

        break;
      }

      case '/':
      {
        s.erase(0, 1);

        auto pattern = takePattern(s);

        if (s.empty()) {
          return 0;
        }

        auto replacement = takePattern(s);

        size_t pos = 0;
        while ((pos = s.find(pattern, pos)) != std::string::npos) {
          s.replace(pos, pattern.length(), replacement);
          pos += replacement.length();
        }

        break;
      }

      default:
      {
        cout << s[0];
        s.erase(0, 1);
        break;
      }
    }
  }

  cout << flush;

  return 0;
}
