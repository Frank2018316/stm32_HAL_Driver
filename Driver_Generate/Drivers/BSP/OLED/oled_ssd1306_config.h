#ifndef _SSD1306_CONFIG_H_
#define _SSD1306_CONFIG_H_


#include "stdint.h"

// ��������ö�� 
typedef enum {
    SSD1306_CMD_SINGLE = 1,         // ���ֽ����� 
    SSD1306_CMD_DOUBLE,             // ˫�ֽ����� 
    SSD1306_CMD_TRIPLE              // ���ֽ�����
} SSD1306_CmdType;

// ����ṹ�� 
typedef struct {
    uint8_t cmd;                     // ���������� 
    SSD1306_CmdType type;            // ����Ľṹ-�Ǽ����ֽ�����
    uint8_t param1;                  // ����������type=DOUBLEʱ��Ч��
    uint8_t param2;                  // ����������type=TRIPLEʱ��Ч�� 
} SSD1306_InitCmd;


//�豸��ַ
#define OLED_ADRESS         0x78
//дָ��ģʽ
#define WRITE_COMMAND_MODE  0x00
//д����ģʽ
#define WRITE_DATA_MODE     0x40

#define PAGE_SIZE           (1*8)
//���ҳ��
#define PAGE_MAX            8
//�������
#define ROW_MAX             (8*8)
//�������
#define COL_MAX             128

/*************************display��ʾ����***********************************************************************************/
// ��ʾ����
#define OLED_CMD_DISPLAY_OFF          0xAE                                // �ر���ʾ����������ģʽ�����͹��ģ�
#define OLED_CMD_DISPLAY_ON           0xAF                                // ������ʾ��������ʾģʽ��

// �Աȶȵ��ڣ���������������
#define OLED_CMD_SET_CONTRAST         0x81                                // ���öԱȶȣ����� 0x00~0xFF ������Ĭ�� 0x7F��

// ��ʾģʽ
#define OLED_CMD_DISPLAY_NORMAL       0xA4                                // ������ʾģʽ�������Դ�������Ⱦ��
#define OLED_CMD_DISPLAY_FORCE_ON     0xA5                                // ǿ��ȫ�������������Դ����ݣ����ڲ��ԣ�
#define OLED_CMD_COLOR_NORMAL         0xA6                                // ������ɫģʽ���ߵ�ƽ�������أ�
#define OLED_CMD_COLOR_INVERT         0xA7                                // ��ɫ��ʾģʽ���͵�ƽ�������أ�

// ��ʼ�����ã���Χ 0x40~0x7F��
#define OLED_CMD_SET_START_LINE(line) (0x40 | (line))                     // ������ʾ��ʼ�У�0~63�����ڴ�ֱ������

/*************************��ַ������***********************************************************************************/

// ��ַģʽ���ã���������������
#define OLED_CMD_SET_ADDRESS_MODE     0x20                                // ���õ�ַģʽ������ 0x00/0x01/0x02��
#define OLED_ADDR_MODE_HORIZONTAL     0x00                                // ˮƽ��ַģʽ���Զ����У��ʺ�����д�룩
#define OLED_ADDR_MODE_VERTICAL       0x01                                // ��ֱ��ַģʽ���������У��ʺ�ͼ��ˢ�£�
#define OLED_ADDR_MODE_PAGE           0x02                                // ҳ��ַģʽ�����ֶ��л�ҳ���ʺ���ҳ������

// ҳ��ַ���ã���Χ 0xB0~0xB7��
#define OLED_CMD_SET_PAGE(page)     do{\
                                          const uint8_t cmd = 0xB0 | (page);\
                                          oled_write_byte(cmd, OLED_8080_CMD);} while(0U)


// �е�ַ��4λ���ã���Χ 0x00~0x0F��
#define OLED_CMD_SET_COL_LOW(col)     (0x00 | ((col) & 0x0F))  // �����е�ַ��4λ��0~15��
 
// �е�ַ��4λ���ã���Χ 0x10~0x1F��
#define OLED_CMD_SET_COL_HIGH(col)    (0x10 | (((col) >> 4) & 0x0F))  // �����е�ַ��4λ��0~7����Ӧ0~127�У�
 
// �����е�ַ���ú꣨0~127�У�   ������ = LOW(col)+HIGH(col)*16
#define OLED_CMD_SET_COLUMN(col)     do{\
                                        oled_write_byte(OLED_CMD_SET_COL_LOW(col), OLED_8080_CMD); \
                                        oled_write_byte(OLED_CMD_SET_COL_HIGH(col), OLED_8080_CMD);}while(0U)

// �е�ַ��Χ�������������ʼ�кͽ����У�
#define OLED_CMD_SET_COLUMN_RANGE     0x21                                // �����е�ַ��Χ��������ʼ�кͽ����в�����

/*************************Ӳ�����ò���***********************************************************************************/

// ��ɱÿ��� 
#define OLED_CMD_CHARGE_PUMP_ON       0x8D                                // ������ɱÿ���ָ��������ã�
#define OLED_CMD_CHARGE_PUMP_ENABLE   0x14                                // ��ɱ�ʹ�ܲ�������� 0x8D ʹ�ã�

// COM����ɨ�跽�� 
#define OLED_CMD_SET_COM_PINS         0xDA                                // ���� COM ����Ӳ�����֣�����ɨ�跽�������
#define OLED_COM_SCAN_SEQUENTIAL      0x02                                // COM ˳��ɨ�裨������Ļ���֣�
#define OLED_COM_SCAN_ALTERNATE       0x12                                // COM ����ɨ�裨������Ļ���֣�

// ��·���ñ��ʣ������������������ô�ֱ�ֱ��� = ʵ������-1
#define OLED_CMD_SET_MUX_RATIO        0xA8                                // ������Ļ�߶ȸ��ñ��ʣ��� 0x3F ��Ӧ 64 �У�

// ʱ�ӷ�Ƶ��������������������ˢ��Ƶ��--����ΪĬ�ϵ����ˢ����0x80
#define OLED_CMD_SET_CLOCK_DIV        0xD5                                // ����ʱ�ӷ�Ƶ������ˢ���ʣ�

//��ֱ��ʾƫ��������������ʾ���ݵ���ʼ��λ��
#define OLED_CMD_SET_DISPLAY_OFFSET    0xD3                               // ���ô�ֱ��ʾƫ����������ƫ�Ʋ�����

// ����Ԥ�������ָ�����������
#define OLED_CMD_SET_PRECHARGE_PERIOD  0xD9                               // Phase1 �� Phase2 ��ȡֵ���� 0x0~0xF ֮�䣨��Ӧ 1~16 DCLK ���ڣ� 

// ����ʾ����Ĭ�����ã�Ĭ�ϣ�0x22��Phase1=2 DCLK��Phase2=2 DCLK��
#define OLED_PRECHARGE_PHASE1_DEFAULT  0x02                               // Phase1=2 DCLK �͹���ģʽ��Phase1=1, Phase2=1
#define OLED_PRECHARGE_PHASE2_DEFAULT  0x02                               // Phase2=2 DCLK ��ˢ���ʣ�Phase1=15, Phase2=1

// ���� VCOMH ��ѹ���ʣ�����������
#define OLED_CMD_SET_VCOMH             0xDB  
#define OLED_VCOMH_083_VCC             0x30                              // 0.83 �� VCC 0x30�������� 011����0.83 �� VCC��������ȣ�����������Ļ������
/*************************�������ܲ���***********************************************************************************/
// ˮƽ�������� 
#define OLED_CMD_SCROLL_RIGHT         0x26                                // ����ˮƽ���ҹ�����������ҳ��Χ���ٶȣ�
#define OLED_CMD_SCROLL_LEFT          0x27                                // ����ˮƽ������� 
 
// ��ֱ+ˮƽ���� 
#define OLED_CMD_SCROLL_VH_RIGHT      0x29                                // ������ֱ+ˮƽ���ҹ�����������ƫ������
#define OLED_CMD_SCROLL_VH_LEFT       0x2A                                // ������ֱ+ˮƽ������� 
 
// �������� 
#define OLED_CMD_SCROLL_OFF           0x2E                                // �رչ������� 
#define OLED_CMD_SCROLL_ON            0x2F                                // ���������õĹ���Ч��

/*************************��ʾ���򲿷�***********************************************************************************/
// �е�ַ���� 
#define OLED_CMD_SEGMENT_REMAP_NORMAL  0xA0                               // �е�ַ�����ң�Ĭ�Ϸ���
#define OLED_CMD_SEGMENT_REMAP_REVERSE 0xA1                               // �е�ַ���ҵ���ˮƽ����
 
// ��ɨ�跽�� 
#define OLED_CMD_COM_SCAN_NORMAL       0xC0                               // ��ɨ�跽����ϵ��£�Ĭ�ϣ�
#define OLED_CMD_COM_SCAN_REVERSE      0xC8                               // ��ɨ�跽����µ��ϣ���ֱ����

/***********************************************************************************************************************/
// ��ʼ���������� 
const static SSD1306_InitCmd initCommands[] = { 
    // �ر���ʾ����������ģʽ�����͹��� 
    {OLED_CMD_DISPLAY_OFF, SSD1306_CMD_SINGLE, 0, 0}, 
    // ����ʱ�ӷ�Ƶ������ˢ���ʣ��˴�����ΪĬ�ϵ����ˢ���� 
    {OLED_CMD_SET_CLOCK_DIV, SSD1306_CMD_DOUBLE, 0x80, 0}, 
    // ������Ļ�߶ȸ��ñ��ʣ�0x3F ��Ӧ 64 �� 
    {OLED_CMD_SET_MUX_RATIO, SSD1306_CMD_DOUBLE, 0x3F, 0}, 
    // ���ô�ֱ��ʾƫ�������˴�ƫ����Ϊ 0 
    {OLED_CMD_SET_DISPLAY_OFFSET, SSD1306_CMD_DOUBLE, 0x00, 0}, 
    // ������ʾ��ʼ�У��˴��ӵ� 0 �п�ʼ 
    {OLED_CMD_SET_START_LINE(0), SSD1306_CMD_SINGLE, 0, 0}, 
    // �����е�ַ���ҵ���ʵ��ˮƽ���� 
    {OLED_CMD_SEGMENT_REMAP_REVERSE, SSD1306_CMD_SINGLE, 0, 0}, 
    // ������ɨ�跽����µ��ϣ�ʵ�ִ�ֱ���� 
    {OLED_CMD_COM_SCAN_REVERSE, SSD1306_CMD_SINGLE, 0, 0}, 
    // ���� COM ����Ӳ������Ϊ����ɨ�� 
    {OLED_CMD_SET_COM_PINS, SSD1306_CMD_DOUBLE, 0x12, 0}, 
    // ���öԱȶȣ��˴��Աȶ�Ϊ 0xCF 
    {OLED_CMD_SET_CONTRAST, SSD1306_CMD_DOUBLE, 0xCF, 0}, 
    // ����Ԥ������ڣ�Phase1 �� Phase2 ȡֵΪ 0xF1 
    {OLED_CMD_SET_PRECHARGE_PERIOD, SSD1306_CMD_DOUBLE, 0xF1, 0}, 
    // ���� VCOMH ��ѹ����Ϊ 0.83 �� VCC 
    {OLED_CMD_SET_VCOMH, SSD1306_CMD_DOUBLE, 0x30, 0}, 
    // ����������ʾģʽ�������Դ�������Ⱦ 
    {OLED_CMD_DISPLAY_NORMAL, SSD1306_CMD_SINGLE, 0, 0}, 
    // ����������ɫģʽ���ߵ�ƽ�������� 
    {OLED_CMD_COLOR_NORMAL, SSD1306_CMD_SINGLE, 0, 0}, 
    // ������ɱÿ��ƣ�ʹ�ܲ���Ϊ 0x14 
    {OLED_CMD_CHARGE_PUMP_ON, SSD1306_CMD_DOUBLE, 0x14, 0}, 
    // ������ʾ������������ʾģʽ 
    {OLED_CMD_DISPLAY_ON, SSD1306_CMD_SINGLE, 0, 0} 
}; 

#endif
