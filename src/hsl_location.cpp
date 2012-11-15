#include "hsl_location.h"

HSLLocation::HSLLocation() {
}

HSLLocation::HSLLocation(const HSLLocation::Location &map): m_data(map) {
}

HSLLocation::HSLLocation(const std::string &xmldata) {
   parseFrom(xmldata);
}

bool HSLLocation::parseFrom(const std::string &xmldata) {
}

