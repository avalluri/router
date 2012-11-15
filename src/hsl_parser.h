#ifndef HSL_XML_PARSER_H_
#define HSL_XML_PARSER_H_

#include <string>
#include <map>
#include <vector>

class HSLXMLParser
{
public:
  HSLXMLParser();
  ~HSLXMLParser();
  std::vector<std::map<std::string, std::string> > parseNodes (const std::string &data, const char *xpath);
private:
   
};

#endif //HSL_XML_PARSER_H_



