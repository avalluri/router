#ifndef HSL_LOCATION_H_
#define HSL_LOCATION_H_

#include <string>
#include <map>

class HSLLocation
{
  #define NAME      "name1"
  #define NUMBER    "number"
  #define CITY      "city"
  #define CODE      "code"
  #define ADDRESS   "address"
  #define TYPE      "type"
  #define CATEGORY "category"
  #define X   "x"
  #define Y   "y"
  #define LON "lon"
  #define LAT "lat"
public:
  typedef std::map<std::string, std::string> Location;

  HSLLocation();
  HSLLocation(const std::string &xmldata);
  HSLLocation(const HSLLocation::Location &map);

  bool parseFrom(const std::string &xmldata);
  
  const std::string & operator[](const std::string &at) const {
    return m_data.find(at)->second;
  }

  const std::string & name() const {
    return m_data.find(std::string(NAME))->second;
  }

  const std::string & city() const {
    return m_data.find(std::string(CITY))->second;
  }

  const std::string & x() const {
    return m_data.find(std::string(X))->second;
  }

  const std::string & y() const {
    return m_data.find(std::string(Y))->second;
  }

  const std::string & type () const {
    return m_data.find(std::string(TYPE))->second;
  }

  const std::string & longitude () const {
    return m_data.find(std::string (LON))->second;
  }

  const std::string & latitude () const {
    return m_data.find(std::string(LAT))->second;
  }

private:

  Location m_data;
};

#endif //HSL_LOCATION_H_
