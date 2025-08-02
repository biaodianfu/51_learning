#ifndef LED_MATRIX_8x8_MAX7219_H
#define LED_MATRIX_8x8_MAX7219_H

// 结构体定义
typedef struct {
    unsigned char data[8];
} Image;

// 图像常量声明
extern const Image HEART;
extern const Image HEART_SMALL;
extern const Image HAPPY;
extern const Image SMILE;
extern const Image SAD;
extern const Image CONFUSED;
extern const Image ANGRY;
extern const Image ASLEEP;
extern const Image SURPRISED;
extern const Image SILLY;
extern const Image FABULOUS;
extern const Image MEH;
extern const Image YES;
extern const Image NO;

// 箭头方向 (8种)
extern const Image ARROW_N;
extern const Image ARROW_NE;
extern const Image ARROW_E;
extern const Image ARROW_SE;
extern const Image ARROW_S;
extern const Image ARROW_SW;
extern const Image ARROW_W;
extern const Image ARROW_NW;

// 几何形状
extern const Image TRIANGLE;
extern const Image TRIANGLE_LEFT;
extern const Image CHESSBOARD;
extern const Image DIAMOND;
extern const Image DIAMOND_SMALL;
extern const Image SQUARE;
extern const Image SQUARE_SMALL;

// 动物和生物
extern const Image RABBIT;
extern const Image COW;
extern const Image DUCK;
extern const Image TORTOISE;
extern const Image BUTTERFLY;
extern const Image STICKFIGURE;
extern const Image GHOST;
extern const Image GIRAFFE;
extern const Image SKULL;
extern const Image SNAKE;

// 物品
extern const Image MUSIC_CROTCHET;
extern const Image MUSIC_QUAVER;
extern const Image MUSIC_QUAVERS;
extern const Image PITCHFORK;
extern const Image XMAS;
extern const Image PACMAN;
extern const Image TARGET;
extern const Image TSHIRT;
extern const Image ROLLERSKATE;
extern const Image HOUSE;
extern const Image SWORD;
extern const Image UMBRELLA;
extern const Image SCISSORS;

// 函数声明
void max7219_init(void);
void show_image(const Image *img);
void show_dot(unsigned char x, unsigned char y);
void show_h_line(unsigned char y);
void show_v_line(unsigned char x);
void animate_heart(void);
void animate_matrix(void);
void animate_square(void);
void show_char(char c);
void scroll_text(const char *text, unsigned int ms);

#endif
