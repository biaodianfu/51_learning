#ifndef LED_MATRIX_8x8_MAX7219_H
#define LED_MATRIX_8x8_MAX7219_H

/**
 * @brief 图像结构体，用于表示8x8 LED矩阵的图像数据
 *
 * data数组中的每个元素代表LED矩阵的一行，每个bit代表一个LED灯的状态（1为点亮，0为熄灭）
 */
typedef struct {
    unsigned char data[8];
} Image;

// 图像常量声明
extern const Image HEART;           ///< 心形图案
extern const Image HEART_SMALL;     ///< 小心形图案
extern const Image HAPPY;           ///< 开心表情
extern const Image SMILE;           ///< 微笑脸
extern const Image SAD;             ///< 伤心表情
extern const Image CONFUSED;        ///< 困惑表情
extern const Image ANGRY;           ///< 生气表情
extern const Image ASLEEP;          ///< 睡觉表情
extern const Image SURPRISED;       ///< 惊讶表情
extern const Image SILLY;           ///< 愚蠢表情
extern const Image FABULOUS;        ///< 极好表情
extern const Image MEH;             ///< 一般表情
extern const Image YES;             ///< 是（对勾）图案
extern const Image NO;              ///< 否（叉号）图案

// 箭头方向 (8种)
extern const Image ARROW_N;         ///< 北向箭头（上）
extern const Image ARROW_NE;        ///< 东北向箭头（右上）
extern const Image ARROW_E;         ///< 东向箭头（右）
extern const Image ARROW_SE;        ///< 东南向箭头（右下）
extern const Image ARROW_S;         ///< 南向箭头（下）
extern const Image ARROW_SW;        ///< 西南向箭头（左下）
extern const Image ARROW_W;         ///< 西向箭头（左）
extern const Image ARROW_NW;        ///< 西北向箭头（左上）

// 几何形状
extern const Image TRIANGLE;        ///< 三角形
extern const Image TRIANGLE_LEFT;   ///< 左向三角形
extern const Image CHESSBOARD;      ///< 棋盘图案
extern const Image DIAMOND;         ///< 菱形
extern const Image DIAMOND_SMALL;   ///< 小菱形
extern const Image SQUARE;          ///< 正方形
extern const Image SQUARE_SMALL;    ///< 小正方形

// 动物和生物
extern const Image RABBIT;          ///< 兔子
extern const Image COW;             ///< 奶牛
extern const Image DUCK;            ///< 鸭子
extern const Image TORTOISE;        ///< 乌龟
extern const Image BUTTERFLY;       ///< 蝴蝶
extern const Image STICKFIGURE;     ///< 火柴人
extern const Image GHOST;           ///< 幽灵
extern const Image GIRAFFE;         ///< 长颈鹿
extern const Image SKULL;           ///< 骷髅
extern const Image SNAKE;           ///< 蛇

// 物品
extern const Image MUSIC_CROTCHET;  ///< 音符（四分音符）
extern const Image MUSIC_QUAVER;    ///< 八分音符
extern const Image MUSIC_QUAVERS;   ///< 双八分音符
extern const Image PITCHFORK;       ///< 干草叉
extern const Image XMAS;            ///< 圣诞树
extern const Image PACMAN;          ///< 吃豆人
extern const Image TARGET;          ///< 目标靶心
extern const Image TSHIRT;          ///< T恤
extern const Image ROLLERSKATE;     ///< 溜冰鞋
extern const Image HOUSE;           ///< 房子
extern const Image SWORD;           ///< 剑
extern const Image UMBRELLA;        ///< 雨伞
extern const Image SCISSORS;        ///< 剪刀

/**
 * @brief 初始化MAX7219 LED驱动芯片
 *
 * 配置MAX7219的工作模式、亮度、扫描限制等参数，为显示做准备
 */
void max7219_init(void);

/**
 * @brief 在LED矩阵上显示指定的图像
 *
 * @param img 指向要显示的图像结构体的指针
 */
void show_image(const Image *img);

/**
 * @brief 在LED矩阵的指定位置点亮一个点
 *
 * @param x X坐标（0-7）
 * @param y Y坐标（0-7）
 */
void show_dot(unsigned char x, unsigned char y);

/**
 * @brief 在LED矩阵上显示一条水平线
 *
 * @param y 水平线的Y坐标（0-7）
 */
void show_h_line(unsigned char y);

/**
 * @brief 在LED矩阵上显示一条垂直线
 *
 * @param x 垂直线的X坐标（0-7）
 */
void show_v_line(unsigned char x);

/**
 * @brief 播放心跳动画效果
 *
 * 显示一个逐渐放大和缩小的心形图案，模拟心跳效果
 */
void animate_heart(void);

/**
 * @brief 播放矩阵动画效果
 *
 * 在LED矩阵上播放预定义的矩阵动画序列
 */
void animate_matrix(void);

/**
 * @brief 播放正方形动画效果
 *
 * 显示一个逐渐放大和缩小的正方形动画
 */
void animate_square(void);

/**
 * @brief 在LED矩阵上显示单个字符
 *
 * @param c 要显示的字符
 */
void show_char(char c);

/**
 * @brief 滚动显示文本字符串
 *
 * @param text 要滚动显示的字符串
 * @param ms 每个字符滚动停留的时间（毫秒）
 */
void scroll_text(const char *text, unsigned int ms);

#endif
