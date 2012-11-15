#include "hsl_location_array.h"
#include "hsl_location.h"
#include "hsl_log.h"

HSLLocationArray::HSLLocationArray() {
}

HSLLocationArray::HSLLocationArray(const std::string &xmldata) {
   parseFrom(xmldata);
}

bool HSLLocationArray::parseFrom (const std::string &xmldata) {

    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    xmlNodeSetPtr nodes = NULL;
    xmlChar *xpathExp = (xmlChar *)"/MTRXML/GEOCODE/LOC";
    int i;

TRACK();

    xmlInitParser();
    //doc = xmlParseDoc ((xmlChar *)xmldata.c_str());
    doc = xmlReadMemory (xmldata.c_str(), xmldata.size(), NULL, NULL, XML_PARSE_COMPACT);
    if (!doc) {
        WARN ("Could not create parse xml data");
        return false;
    }

    xpathCtx = xmlXPathNewContext(doc);
    if (!xpathCtx) {
        WARN ("Could not get xpath context for document.");
        xmlFreeDoc(doc);
        return false;
    }

    xpathObj = xmlXPathEvalExpression (xpathExp, xpathCtx);
    if (!xpathObj || !xpathObj->nodesetval) {
        WARN ("Could not evaluate xpath for : %s", (char *)xpathExp);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return false;
    }
    /*** Evaluate Locations ***/
    nodes = xpathObj->nodesetval;
    LOG ("No of xpath nodes found : %d", nodes->nodeNr);
    for (i=0; i < nodes->nodeNr; i++) {
        xmlNodePtr node = nodes->nodeTab[i];
        xmlAttrPtr attr;
        HSLLocation::Location map;

        if (node->type != XML_ELEMENT_NODE) continue;

        for (attr = node->properties; attr; attr = attr->next) {
            std::pair<std::string, std::string> element( std::string((char *)attr->name),
                                                         std::string((char *)attr->children->content));
            map.insert(element);
        }
        m_data.push_back(HSLLocation(map));
    }

    xmlXPathFreeContext(xpathCtx);

    return true;
}

const HSLLocation & HSLLocationArray::operator[] (int index) {
   return m_data[index];
}

size_t HSLLocationArray::length() {
   return m_data.size();
}

