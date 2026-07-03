#include "../header.h"

struct Sentence
{
  struct WordToken
  {
    bool capitalize = false;
  };

  vector<string> words;
  map<size_t, WordToken> tokens;

  // no member initialization list needed ( : text(text))
  // bc their members are default constructed first (words, tokens)
  Sentence(const string& text)
  {
    istringstream iss(text);
    string word;
    while (iss >> word)
    {
      words.push_back(word);
    }
  }

  WordToken& operator[](size_t index)
  {
    return tokens[index];
  }

  string str() const
  {
    ostringstream oss;

    for (size_t i = 0; i < words.size(); ++i) {
      string word = words[i];
      auto it = tokens.find(i);

      if (it != tokens.end() && it->second.capitalize) {
        transform(word.begin(), word.end(), word.begin(), ::toupper);
      }
      if (i > 0) { oss << " "; }

      oss << word;
    }

    return oss.str();
  }
};

int main() {
    Sentence sentence("hello world"); // {} is the same as ()
    sentence[1].capitalize = true;
    // bc str is a member function of Sentence, we can call it on the object
    cout << sentence.str(); // prints "hello WORLD"
}
