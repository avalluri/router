#ifndef CORE_H_
#define CORE_H_


struct core_location {
    char *
struct core_location {
    char name[64];
    char number[8];
    char city[16]; //Helsinki, Espoo, Vantaa, Kirkkuonummi
    char code[16];
    char address[64];
    int type;
    char category[8]; //street, poi, stop
    char x[8];
    char y[8];
    char lon[16];
    char lat[16];
};


struct core_length {
    long time;
    float distance;
};

struct core_walk {
    char start[128];
    char destination[128];
};

struct core_line {
    int id;
    char code[16];
    int type;
    int mobility;
};

struct core_route {
    char uid[128];
    char from[64];
    char to[64];
    struct core_length length;
//    struct core_
};

int core_init ();
int get_geocodes_for (const char *location, struct core_location **locations);
int get_routes_for (const char *loc_a, const char *loc_b, struct core_route **routes);

#endif // CORE_H_
