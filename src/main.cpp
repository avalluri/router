
#include <stdio.h>
#include <unistd.h> //getopts()
#include "hsl_core.h"
#include "hsl_location_array.h"
#include "hsl_location.h"
#include "hsl_log.h"

bool route_flag = false;
bool search_flag = false;

void print_help_string() {
  printf(
  "Usage: router [-s <key>] [-r <from> <to> ] [-l <x> <y>]\n" 
  "Options:\n"                                   
  "  -h : Usage string.\n"
  "  -s : Search locations for key.\n"
  "  -l : Get Location at position x, y"
  "  -r : Get route between two points from & to.\n");
}

void search_key ( const char *key) {
 
  HSLLocationArray locations = HSLCore().GetGeocodesFor(key);

  LOG ("Found Locations : %d", locations.length());
  
  for (unsigned int i=0; i<locations.length(); i++) {
     const HSLLocation &location = locations[i];
     LOG (" %s, %s[%s,%s]", location.name().c_str(), 
                            location.city().c_str(), 
                            location.longitude().c_str(), 
                            location.latitude().c_str());
  }
}

void location_at (const char *x, const char *y) {
  const HSLLocation &location = HSLCore()::GetLocationFor(x, y);
  LOG (" %s, %s[%s,%s]", location.name().c_str(), 
                         location.city().c_str(), 
                         location.longitude().c_str(), 
                         location.latitude().c_str());
  
}

void fetch_route(const char *from, const char *to) {
  printf ("__Not supported__\n");
}

int main (int argc, char *argv[]) {
  const char *options = "hs:r:";
  char c;

  while ((c = getopt (argc, argv, options)) != -1) {
  
    switch (c) {
    
    case 's': search_key (optarg); return 0;
    case 'l': (optind + 2 < argc) ? print_help_string() : location_at (argv[optind], argv[optind+1]);
    case 'r': (optind + 2 < argc) ? print_help_string() : fetch_route (argv[optind], argv[optind+1]); return 0;
    
    case 'h': 
    default: print_help_string(); return 0;
    
    }
  
  }
}
