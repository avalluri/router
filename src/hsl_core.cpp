#include "hsl_core.h"
#include "hsl_priv.h"
#include "hsl_log.h"

#include <malloc.h>
#include <string.h>
#include <curl/curl.h>

/

#define API_BASE_URL "http://api.reittiopas.fi/public-ytv/fi/api/"

size_t gather_reply_cb( char *ptr, size_t size, size_t nmemb, void *userdata);

HSLCore::HSLCore() : m_curlHandle(NULL) {

  curl_global_init (CURL_GLOBAL_ALL);

  m_curlHandle = curl_easy_init ();

  if(!m_curlHandle) {
    ERR("Could not initialize curl.");
    return ;
  }

  curl_easy_setopt(m_curlHandle, CURLOPT_URL, API_BASE_URL);
  curl_easy_setopt(m_curlHandle, CURLOPT_WRITEDATA, &m_reply);
  curl_easy_setopt(m_curlHandle, CURLOPT_WRITEFUNCTION, gather_reply_cb);
}

HSLCore::~HSLCore() {
  curl_easy_cleanup(m_curlHandle);
}

size_t gather_reply_cb( char *ptr, size_t size, size_t nmemb, void *userdata) {

   std::string *buf = (std::string *)userdata;
  
   buf->append (ptr , size * nmemb);

   return size * nmemb;
}

const std::string & HSLCore::PushRequest () {
    m_reply.clear();

    if (!m_curlHandle) return m_reply;

    LOG("Request : %s?%s", API_BASE_URL, m_request);
    curl_easy_setopt(m_curlHandle, CURLOPT_POSTFIELDS, m_request);

    curl_easy_perform (m_curlHandle);

    return m_reply;
}

HSLLocationArray HSLCore::GetGeocodesFor (const std::string &location) {
    sprintf (m_request, "key=%s&user=%s&pass=%s", location.c_str(), USER, PASSWD);

    HSLLocationArray locations = HSLXMLParser().parseNodes(m_reply, "/MTRXML/GEOCODE/LOC");

    return locations;
}

HSLLocation HSLCore::GetLocationFor (const std::string &x, const std::string &y) {
    sprintf (m_request, "x=%s&y=%s&user=%s&pass=%s", x.c_str(), y.c_str(), USER, PASSWD);

    HSLLocationArray locations= HSLXMLParser().parseNodes(m_reply, "/MTRXML/GEOCODE/LOC");
    return locations.at(0);
}

/*
HSLRoute HSLCore::GetRoute (const std::string &from, const std::string &to) {

}
*/
