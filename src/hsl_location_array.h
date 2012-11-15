#ifndef HSL_LOCATION_ARRAY_H_
#define HSL_LOCATION_ARRAY_H_

#include <vector>

#include "hsl_location.h"

class HSLLocationArray {
public:
  HSLLocationArray();
  HSLLocationArray(const std::string &xmldata);

  bool parseFrom (const std::string &xmldata);

  const HSLLocation & operator[] (int index);
  size_t length();

private:
  std::vector<HSLLocation> m_data;
};

#endif //HSL_LOCATION_ARRAY_H_
