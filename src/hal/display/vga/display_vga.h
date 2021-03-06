/*
 * display.h
 *
 *  Created on: 28/10/2015
 *      Author: jaagirre
 */

#ifndef DISPLAY_VGA_H_
#define DISPLAY_VGA_H_


#define DISPLAY_NUM_FRAMES 3

#define DISPLAYDEMO_MAX_FRAME (1920*1080)
/* ------------------------------------------------------------ */
/*				Include File Definitions						*/
/* ------------------------------------------------------------ */

#include "xil_types.h"
#include "vga_modes.h"
#include "xaxivdma.h"

#include "xil_types.h"
/*
 * This driver currently supports 3 frames.
 */
#define DISPLAY_NUM_FRAMES 3

/*
 * WEDGE and NOCOUNT can't both be high, so this is used to signal an error state
 */
#define ERR_CLKDIVIDER (1 << CLK_BIT_WEDGE | 1 << CLK_BIT_NOCOUNT)

/* ------------------------------------------------------------ */
/*					General Type Declarations					*/
/* ------------------------------------------------------------ */

typedef enum {
	DISPLAY_STOPPED = 0,
	DISPLAY_RUNNING = 1
} DisplayState;

typedef struct {
		u32 clk0L;
		u32 clkFBL;
		u32 clkFBH_clk0H;
		u32 divclk;
		u32 lockL;
		u32 fltr_lockH;
} ClkConfig;

typedef struct {
		double freq;
		u32 fbmult;
		u32 clkdiv;
		u32 maindiv;
} ClkMode;


typedef struct {
		u32 dispCtrlAddr; /*Physical Base address of the disp_ctrl core*/
		int fHdmi; /*flag indicating if the display controller is being used to drive an HDMI transmitter*/
		XAxiVdma vdma; /*VDMA driver struct*/
		XAxiVdma_DmaSetup vdmaConfig; /*VDMA channel configuration*/
		VideoMode vMode; /*Current Video mode*/
		u32 *framePtr[DISPLAY_NUM_FRAMES]; /* Array of pointers to the framebuffers */
		u32 stride; /* The line stride of the framebuffers, in bytes */
		double pxlFreq; /* Frequency of clock currently being generated */
		u32 curFrame; /* Current frame being displayed */
		DisplayState state; /* Indicates if the Display is currently running */
} DisplayCtrl;

/*
 * XPAR redefines
 */
#define VGA_BASEADDR XPAR_AXI_DISPCTRL_0_S_AXI_BASEADDR

#define VGA_VDMA_ID XPAR_AXIVDMA_0_DEVICE_ID
#define DISPLAYDEMO_STRIDE (1920 * 4)
#define SCU_TIMER_ID XPAR_SCUTIMER_DEVICE_ID
#define UART_BASEADDR XPAR_PS7_UART_1_BASEADDR

#define BTN_BASEADDR XPAR_BTNS_4BITS_BASEADDR

void mover_pelota();
void updateFrame();

/*
 * DOble Buffer
 */
void copiarFrameBuffer();
void borrarFrameBuffer();




void dibujar_linea_malda(int x0, int y0 , int m, int length );
void dibujar_linea_2_pto(int x0, int y0 , int x1, int y1, double fRed, double FGreen, double FBlue );
void dibujar_caracter(int x, int y , int size);
void dibujar_punto(int x, int y , int size);
void dibujar_linea_vertical(int x , int y , int grosor);
void dibujar_linea(int grosor);
void displayInit();
int DisplayDemoInitializeFroga(DisplayCtrl *dispPtr, u16 vdmaId, u16 timerId, u32 dispCtrlAddr, int fHdmi);
int DisplayDemoFroga();
void displayTest(void);
void displayChar(int x , int y , char kar);
void displayMenu(void);
void displayCorazon(int x0 , int y0);

void displayTestCirc_Perimetro(int x0, int y0 , int r);
void displayTestRect_Perimetro(int x0, int y0 , int width , int height);
void displayTestRect(int x0, int y0 , int width , int height, char letra);
void displayTestCirc(int x0, int y0 , int r);
float Q_rsqrt( float number );
void display_borrar_buffer();

void display_stop();
void display_start();
void escribirTablaAscii();



/* ------------------------------------------------------------ */
/*					Miscellaneous Declarations					*/
/* ------------------------------------------------------------ */

#define CLK_BIT_WEDGE 13
#define CLK_BIT_NOCOUNT 12

#define ERR_CLKCOUNTCALC 0xFFFFFFFF //This value is used to signal an error

#define OFST_DISPLAY_CTRL 0x0
#define OFST_DISPLAY_STATUS 0x4
#define OFST_DISPLAY_VIDEO_START 0x8
#define OFST_DISPLAY_CLK_L 0x1C
#define OFST_DISPLAY_FB_L 0x20
#define OFST_DISPLAY_FB_H_CLK_H 0x24
#define OFST_DISPLAY_DIV 0x28
#define OFST_DISPLAY_LOCK_L 0x2C
#define OFST_DISPLAY_FLTR_LOCK_H 0x30

#define BIT_DISPLAY_RED 16
#define BIT_DISPLAY_BLUE 0
#define BIT_DISPLAY_GREEN 8

#define BIT_DISPLAY_START 0
#define BIT_DISPLAY_RUNNING 1

#define DISPLAY_NOT_HDMI 0
#define DISPLAY_HDMI 1


/* ------------------------------------------------------------ */
/*					Variable Declarations						*/
/* ------------------------------------------------------------ */

static const u64 lock_lookup[64] = {
   0b0011000110111110100011111010010000000001,
   0b0011000110111110100011111010010000000001,
   0b0100001000111110100011111010010000000001,
   0b0101101011111110100011111010010000000001,
   0b0111001110111110100011111010010000000001,
   0b1000110001111110100011111010010000000001,
   0b1001110011111110100011111010010000000001,
   0b1011010110111110100011111010010000000001,
   0b1100111001111110100011111010010000000001,
   0b1110011100111110100011111010010000000001,
   0b1111111111111000010011111010010000000001,
   0b1111111111110011100111111010010000000001,
   0b1111111111101110111011111010010000000001,
   0b1111111111101011110011111010010000000001,
   0b1111111111101000101011111010010000000001,
   0b1111111111100111000111111010010000000001,
   0b1111111111100011111111111010010000000001,
   0b1111111111100010011011111010010000000001,
   0b1111111111100000110111111010010000000001,
   0b1111111111011111010011111010010000000001,
   0b1111111111011101101111111010010000000001,
   0b1111111111011100001011111010010000000001,
   0b1111111111011010100111111010010000000001,
   0b1111111111011001000011111010010000000001,
   0b1111111111011001000011111010010000000001,
   0b1111111111010111011111111010010000000001,
   0b1111111111010101111011111010010000000001,
   0b1111111111010101111011111010010000000001,
   0b1111111111010100010111111010010000000001,
   0b1111111111010100010111111010010000000001,
   0b1111111111010010110011111010010000000001,
   0b1111111111010010110011111010010000000001,
   0b1111111111010010110011111010010000000001,
   0b1111111111010001001111111010010000000001,
   0b1111111111010001001111111010010000000001,
   0b1111111111010001001111111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001,
   0b1111111111001111101011111010010000000001
};

static const u32 filter_lookup_low[64] = {
	 0b0001011111,
	 0b0001010111,
	 0b0001111011,
	 0b0001011011,
	 0b0001101011,
	 0b0001110011,
	 0b0001110011,
	 0b0001110011,
	 0b0001110011,
	 0b0001001011,
	 0b0001001011,
	 0b0001001011,
	 0b0010110011,
	 0b0001010011,
	 0b0001010011,
	 0b0001010011,
	 0b0001010011,
	 0b0001010011,
	 0b0001010011,
	 0b0001010011,
	 0b0001010011,
	 0b0001010011,
	 0b0001010011,
	 0b0001100011,
	 0b0001100011,
	 0b0001100011,
	 0b0001100011,
	 0b0001100011,
	 0b0001100011,
	 0b0001100011,
	 0b0001100011,
	 0b0001100011,
	 0b0001100011,
	 0b0001100011,
	 0b0001100011,
	 0b0001100011,
	 0b0001100011,
	 0b0010010011,
	 0b0010010011,
	 0b0010010011,
	 0b0010010011,
	 0b0010010011,
	 0b0010010011,
	 0b0010010011,
	 0b0010010011,
	 0b0010010011,
	 0b0010010011,
	 0b0010100011,
	 0b0010100011,
	 0b0010100011,
	 0b0010100011,
	 0b0010100011,
	 0b0010100011,
	 0b0010100011,
	 0b0010100011,
	 0b0010100011,
	 0b0010100011,
	 0b0010100011,
	 0b0010100011,
	 0b0010100011,
	 0b0010100011,
	 0b0010100011,
	 0b0010100011,
	 0b0010100011
};

/* ------------------------------------------------------------ */
/*					Procedure Declarations						*/
/* ------------------------------------------------------------ */

u32 DisplayClkCountCalc(u32 divide);
u32 DisplayClkDivider(u32 divide);
u32 DisplayClkFindReg (ClkConfig *regValues, ClkMode *clkParams);
void DisplayClkWriteReg (ClkConfig *regValues, u32 dispCtrlAddr);
double DisplayClkFindParams(double freq, ClkMode *bestPick);

int DisplayStop(DisplayCtrl *dispPtr);
int DisplayStart(DisplayCtrl *dispPtr);
int DisplayInitialize(DisplayCtrl *dispPtr, u16 vdmaId, u32 dispCtrlAddr, int fHdmi, u32 framePtr[], u32 stride);
int DisplaySetMode(DisplayCtrl *dispPtr, const VideoMode *newMode);
int DisplayChangeFrame(DisplayCtrl *dispPtr, u32 frameIndex);

/* ------------------------------------------------------------ */

/************************************************************************/


#endif /* DISPLAY_H_ */
