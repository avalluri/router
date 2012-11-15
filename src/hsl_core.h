#ifndef HSL_CORE_H_
#define HSL_CORE_H_

#include <vector>
#include <string>
#include <curl/curl.h>

#include "hsl_location_array.h"

#define MAX_REQUEST_LEN 256

class HSLCore 
{
public:
  HSLCore();
  ~HSLCore();

  HSLLocationArray GetGeocodesFor (const std::string &location);
  HSLLocation      GetLocationFor (const std::string &x, const std::string &y);
private :
  const std::string & PushRequest ();

  CURL *m_curlHandle;
  char  m_request[MAX_REQUEST_LEN];
  std::string m_reply;

};

#endif //HSL_CORE_H_
