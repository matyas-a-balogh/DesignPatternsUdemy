#include <iostream>
#include <sstream>

using namespace std;

int main() {
   auto text = "Hello world";
   string output;

   // if u want to write eg. html page
   output += "<p>";
   output += text;
   output += "</p>";
   cout << output << endl;
   
   // something better : there is structure, but still putting a string together piece-by-piece
   string words[] = {"Hello", "world"};
   ostringstream oss;
   for (auto w: words){ oss << "<li>" << w << "</li>";}
   cout << "oss" << oss.str() << endl;
   
   return 0;
}
