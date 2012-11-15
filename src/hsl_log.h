#ifndef HSL_LOG_H_
#define HSL_LOG_H_

#define LOG(format, args...)  printf("[D] " format "\n", ##args)
#define WARN(format, args...) printf("[W] " format "\n", ##args)
#define ERR(format, args...)  printf("[E] " format "\n", ##args)
#define TRACK()               LOG("%s+%d:%s", __FILE__, __LINE__, __func__)

#endif //HSL_LOG_H_
