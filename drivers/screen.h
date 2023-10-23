#define VIDEO_ADDRESS 0xb8000
#define MAX_ROW 25
#define MAX_COL 80

// default attribute
#define WHITE_ON_BLACK 0x0f

// Screen Device IO Ports
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

void clear_screen();
void kprint_at(char *str, int row, int col);
void kprint(char *str);
