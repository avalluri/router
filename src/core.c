#include "core.h"
#include "hsl_priv.h"

#include <curl/curl.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <stdio.h>

#define API_BASE_URL "http://api.reittiopas.fi/public-ytv/fi/api/"


CURL *curlHandle = NULL;

// path: MTRXML/GEOCODE/LOC
size_t parse_geocodes_cb( char *ptr, size_t size, size_t nmemb, void *userdata) {
    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    xmlNodeSetPtr nodes = NULL;
    const xmlChar *xpathExp = "/MTRXML/GEOCODE/LOC";
    int i;

    if (!ptr) {
        printf ("NULL results\n");
        return 0;
    }
    printf ("%s\n", ptr);

    xmlInitParser();
    doc = xmlParseDoc ((const xmlChar *)ptr);
    if (!doc) {
        printf ("Could not create xmlDocPtr\n");
        return 0;
    }

    xpathCtx = xmlXPathNewContext(doc);
    if (!xpathCtx) {
       printf ("Could not get xpath context\n");
       xmlFreeDoc(doc);
       return 0;
    }

    xpathObj = xmlXPathEvalExpression (xpathExp, xpathCtx);
    if (!xpathObj || !xpathObj->nodesetval) {
        printf("Could not evaluate xpath for : %s\n", xpathExp);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return 0;
    }

    /*** Evaluate Locations ***/
    nodes = xpathObj->nodesetval;
    printf ("No of nodes found : %d\n", nodes->nodeNr);
    for (i=0; i < nodes->nodeNr; i++) {
        xmlNodePtr node = nodes->nodeTab[i];
        xmlAttrPtr attr;

        if (node->type != XML_ELEMENT_NODE) continue;

        printf (" Node Name : %s\n", node->name);
        for (attr = node->properties; attr; attr = attr->next) {
             printf ("   Attribute : %s: %s\n", attr->name, attr->children->content);
        }
    }

    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    return 0;
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
