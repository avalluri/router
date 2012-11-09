#include "core.h"
#include "core_priv.h"

#include <curl/curl.h>
#include <stdio.h>

#define API_BASE_URL "http://api.reittiopas.fi/public-ytv/fi/api/"


CURL *curlHandle = NULL;

size_t parse_geocodes_cb( char *ptr, size_t size, size_t nmemb, void *userdata) {

    printf ("%s{\n", __FUNCTION__);
    if (ptr) {
        printf ("%s\n", ptr);
    }
    printf ("%s}\n", __FUNCTION__);

}

int get_geocodes_for (const char *location, struct core_location **locations) {
    char buf[1024] ;
    CURLcode res = 0;

    sprintf (buf, "key=%s&user=%s&pass=%s", location, USER, PASSWD);

    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, locations);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, parse_geocodes_cb);
    curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, buf);

    res = curl_easy_perform (curlHandle);

    return 0;
}

int get_routes_for (const char *loc_a, const char *loc_b, struct core_route **routes)
{
}

int core_init () {

    curl_global_init (CURL_GLOBAL_ALL);
    
    curlHandle = curl_easy_init ();

    if(!curlHandle) {
        fprintf (stderr, "Could not initialize curl.\n");
        return -1;
    }

    curl_easy_setopt (curlHandle, CURLOPT_URL, API_BASE_URL);

    return 0;
}
