#include "hsl_xml_parser.h"

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

HSLXMLParser::HSLXMLParser() {
   xmlInitParser();

}
~HSLXMLParser() {
}

std::vector<std::map<std::string,std::string> > HSLXMLParser::parseNodes (const std::string &data, const char *xpath) {
    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    xmlNodeSetPtr nodes = NULL;
    //xmlChar *xpathExp = (xmlChar *)"/MTRXML/GEOCODE/LOC";
    std::vector<std::map<std::string, std::string> > nodeArray;
    int i;

TRACK();

    doc = xmlReadMemory (data.c_str(), data.size(), NULL, NULL, XML_PARSE_COMPACT);
    if (!doc) {
        WARN ("Could not create parse xml data");
        return nodes;
    }

    xpathCtx = xmlXPathNewContext(doc);
    if (!xpathCtx) {
        WARN ("Could not get xpath context for document.");
        xmlFreeDoc(doc);
        return nodes;
    }

    xpathObj = xmlXPathEvalExpression ((xmlChar*)xpath, xpathCtx);
    if (!xpathObj || !xpathObj->nodesetval) {
        WARN ("Could not evaluate xpath for : %s", (char *)xpathExp);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return nodes;
    }
    /*** Evaluate Locations ***/
    nodes = xpathObj->nodesetval;
    LOG ("No of xpath nodes found : %d", nodes->nodeNr);
    for (i=0; i < nodes->nodeNr; i++) {
        xmlNodePtr node = nodes->nodeTab[i];
        xmlAttrPtr attr;
        std::map<std::string, std::string> map;

        if (node->type != XML_ELEMENT_NODE) continue;

        for (attr = node->properties; attr; attr = attr->next) {
            std::pair<std::string, std::string> element( std::string((char *)attr->name),
                                                         std::string((char *)attr->children->content));
            map.insert(element);
        }
        nodeArray.push_back(map);
    }

    xmlXPathFreeContext(xpathCtx);

    return nodeArray;
} 

