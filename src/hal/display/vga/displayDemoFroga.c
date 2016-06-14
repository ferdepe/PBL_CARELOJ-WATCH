/*
 * displayDemoFroga.c
 *
 *  Created on: 14/07/2014
 *      Author: jaagirre
 */

#include "display_vga.h"
#include <math.h>
#include "xil_cache.h"

#include "font8x8.h"
#include "font16x16.h"

DisplayCtrl vgaCtrl;
u32 vgaBuf[3][DISPLAYDEMO_MAX_FRAME];
//ESTE SERA EL BUFFER AUXILIAR , ES EL DOBLE BUFFER
u32 frameBuffer[DISPLAYDEMO_MAX_FRAME];

void displayMenu()
{
	displayTestCirc(vgaCtrl.vMode.width/2,vgaCtrl.vMode.height/2,100);
}

int DisplayDemoFroga(){
//	displayInit();
//	//displayTest();
//	dibujar_linea(30);
//	dibujar_linea_vertical(130 , 0 , 30);
//	dibujar_linea_vertical(200 , 0 , 30);
//	displayTestRect(300, 10 , 50 , 30);
//	displayTestRect(300, 70 , 70 , 10);
//
//	displayTestCirc( 300, 300 , 30);
//
//	displayTestCirc_Perimetro( 400, 300 , 30);

	/*dibujar_linea_2_pto( 200, 200 , 250, 200 );
	dibujar_linea_2_pto( 200, 220 , 300, 220 );

	dibujar_linea_2_pto( 200, 220 , 300, 250 );
	dibujar_linea_2_pto( 200, 220 , 300, 180 );
	dibujar_linea_2_pto( 300, 150 , 200, 180 );

	dibujar_linea_2_pto( 450, 200 , 550, 150 );
	dibujar_linea_2_pto( 450, 200 , 550, 250 );
	dibujar_linea_2_pto( 450, 200 , 350, 150 );
	dibujar_linea_2_pto( 450, 200 , 350, 250 );*/

	 displayChar(400, 100 , 'A');

	 escribirTablaAscii();

	return 0;
}


void displayInit(){
	DisplayDemoInitializeFroga(&vgaCtrl, VGA_VDMA_ID, SCU_TIMER_ID, VGA_BASEADDR, DISPLAY_NOT_HDMI );
}

int DisplayDemoInitializeFroga(DisplayCtrl *dispPtr, u16 vdmaId, u16 timerId, u32 dispCtrlAddr, int fHdmi){
	int Status = 0;

	Status = DisplayInitialize(dispPtr, vdmaId, dispCtrlAddr, fHdmi,  vgaBuf, DISPLAYDEMO_STRIDE);
	if (Status != XST_SUCCESS)
	{
		xil_printf("Display Ctrl initialization failed during demo initialization%d\r\n", Status);
		return XST_FAILURE;
	}

	Status = DisplayStart(dispPtr);
	if (Status != XST_SUCCESS)
	{
		xil_printf("Couldn't start display during demo initialization%d\r\n", Status);
		return XST_FAILURE;
	}
	return 0;
}

void dibujar_linea(int grosor){
	int i;
		int height = 0;
		int width = 0;
		u32 wStride;
		u32 iPixelAddr;
		u32 wRed, wBlue, wGreen, wColor;
		u32 wCurrentInt;
		double fRed, fBlue, fGreen, fColor;
		u32 xLeft, xMid, xRight, xInt;
		u32 yMid, yInt;
		double xInc, yInc;
		u32 xcoi, ycoi;


		//Inicializacion
		height = vgaCtrl.vMode.height;
		width = vgaCtrl.vMode.width;
		wStride = vgaCtrl.stride / 4; /* Find the stride in 32-bit words */

		xInt = vgaCtrl.vMode.width / 4; //Four intervals, each with width/4 pixels
		xLeft = xInt;
		xMid = xInt * 2;
		xRight = xInt * 3;
		xInc = 256.0 / ((double) xInt); //256 color intensities are cycled through per interval (overflow must be caught when color=256.0)

		yInt = vgaCtrl.vMode.height / 2; //Two intervals, each with width/2 lines
		yMid = yInt;
		yInc = 256.0 / ((double) yInt); //256 color intensities are cycled through per interval (overflow must be caught when color=256.0)


		wStride = (vgaCtrl.stride) / 4; /* Find the stride in 32-bit words */

		xInt = width / 7; //Seven intervals, each with width/7 pixels
		xInc = 256.0 / ((double) xInt); //256 color intensities per interval. Notice that overflow is handled for this pattern.

		fBlue = 0.0;
		fRed = 255.0;
		fGreen = 0.0;
		//fColor = fBlue;
		wCurrentInt = 1;
		for(xcoi = 0; xcoi < grosor ; xcoi++){
			wColor = ((u32) fRed << BIT_DISPLAY_RED) | ((u32) fBlue << BIT_DISPLAY_BLUE) | ( (u32) fGreen << BIT_DISPLAY_GREEN);
			iPixelAddr = xcoi;
			for(ycoi = 0; ycoi < height; ycoi++){
				vgaBuf[0][iPixelAddr] = wColor;
				/*
				 * This pattern is printed one vertical line at a time, so the address must be incremented
				 * by the stride instead of just 1.
				 */
				iPixelAddr += wStride;
			}


		}
		/*
		* Flush the framebuffer memory range to ensure changes are written to the
		* actual memory, and therefore accessible by the VDMA.
		*/
		Xil_DCacheFlushRange( (unsigned int) vgaBuf, DISPLAYDEMO_MAX_FRAME * 4);

}


void displayBackground(){
	int i;
	int height = 0;
	int width = 0;
	u32 wStride;
	u32 iPixelAddr;
	u32 wRed, wBlue, wGreen, wColor;
	u32 wCurrentInt;
	double fRed, fBlue, fGreen, fColor;
	u32 xLeft, xMid, xRight, xInt;
	u32 yMid, yInt;
	double xInc, yInc;
	u32 xcoi, ycoi;


	//Inicializacion
	height = vgaCtrl.vMode.height;
	width = vgaCtrl.vMode.width;
	wStride = vgaCtrl.stride / 4; /* Find the stride in 32-bit words */

	xInt = vgaCtrl.vMode.width / 4; //Four intervals, each with width/4 pixels
	xLeft = xInt;
	xMid = xInt * 2;
	xRight = xInt * 3;
	xInc = 256.0 / ((double) xInt); //256 color intensities are cycled through per interval (overflow must be caught when color=256.0)

	yInt = vgaCtrl.vMode.height / 2; //Two intervals, each with width/2 lines
	yMid = yInt;
	yInc = 256.0 / ((double) yInt); //256 color intensities are cycled through per interval (overflow must be caught when color=256.0)

	wStride = (vgaCtrl.stride) / 4; /* Find the stride in 32-bit words */

	xInt = width / 1; //Seven intervals, each with width/7 pixels
	xInc = 256.0 / ((double) xInt); //256 color intensities per interval. Notice that overflow is handled for this pattern.

	fColor = 0.0;
	wCurrentInt = 0b010;
	for(xcoi = 0.4*width; xcoi < 0.6*width; xcoi++){
			/*if (wCurrentInt & 0b001)
				fRed = fColor;
			else
				fRed = 0.0;

			if (wCurrentInt & 0b010)
				fBlue = fColor;
			else
				fBlue = 0.0;

			if (wCurrentInt & 0b100)
				fGreen = fColor;
			else
				fGreen = 0.0;*/
///////////////////////////////////////////////////////////////
////////////Definicion de color de fondo de menu///////////////
			fRed=128;
			fBlue=250;
			fGreen=0;
///////////////////////////////////////////////////////////////
			/*
			 * Just draw white in the last partial interval (when width is not divisible by 7)
			 */
			if (wCurrentInt > 7)
			{
				wColor = 0x00FFFFFF;
			}
			else
			{
				wColor = ((u32) fRed << BIT_DISPLAY_RED) | ((u32) fBlue << BIT_DISPLAY_BLUE) | ( (u32) fGreen << BIT_DISPLAY_GREEN);
			}
			iPixelAddr = xcoi;

			for(ycoi = 0; ycoi < height; ycoi++)
			{
				frameBuffer[iPixelAddr] = wColor;
				/*
				 * This pattern is printed one vertical line at a time, so the address must be incremented
				 * by the stride instead of just 1.
				 */
				iPixelAddr += wStride;
			}

			//fColor += xInc;
			if (fColor >= 256.0)
			{
				fColor = 0.0;
				wCurrentInt++;
			}
		}
	dibujar_linea_vertical(0.4*width , 100 , 3);
	dibujar_linea_vertical(0.6*width , 100 , 3);
	displayTestCirc(320,240,100);//menu
	displayTestCirc_Perimetro(vgaCtrl.vMode.width/2,vgaCtrl.vMode.height/2, 100);
	displayTestCirc_Perimetro(vgaCtrl.vMode.width/2,vgaCtrl.vMode.height/2, 99);
	displayTestCirc_Perimetro(vgaCtrl.vMode.width/2,vgaCtrl.vMode.height/2, 98);
	displayCorazon(0,0);
	displayTestRect(350, 300 , 25, 25,'B');
	displayTestRect(350, 300 , 20 , 20,'N');
	displayTestRect(290, 300 , 25, 25,'B');
	displayTestRect(290, 300 , 20 , 20,'V');
	displayTestRect(320, 300 , 25, 25,'B');
	displayTestRect(320, 300 , 20 , 20,'R');
	//displayTestCirc(320, 20 , 10);
	//displayTestRect(vgaCtrl.vMode.width/2, vgaCtrl.vMode.height/2, 200 , 100);
	/*
	* Flush the framebuffer memory range to ensure changes are written to the
	* actual memory, and therefore accessible by the VDMA.
	*/
	//Xil_DCacheFlushRange( (unsigned int) vgaBuf, DISPLAYDEMO_MAX_FRAME * 4);

}

void dibujar_linea_vertical(int x , int y , int grosor){
	int i;
		int height = 0;
		int width = 0;
		u32 wStride;
		u32 iPixelAddr;
		u32 wRed, wBlue, wGreen, wColor;
		u32 wCurrentInt;
		double fRed, fBlue, fGreen;
		u32 xLeft, xMid, xRight, xInt;
		u32 yMid, yInt;
		double xInc, yInc;
		u32 xcoi, ycoi;


		//Inicializacion
		height = vgaCtrl.vMode.height;
		width = vgaCtrl.vMode.width;
		wStride = vgaCtrl.stride / 4; /* Find the stride in 32-bit words */

		xInt = vgaCtrl.vMode.width / 4; //Four intervals, each with width/4 pixels
		xLeft = xInt;
		xMid = xInt * 2;
		xRight = xInt * 3;
		xInc = 256.0 / ((double) xInt); //256 color intensities are cycled through per interval (overflow must be caught when color=256.0)

		yInt = vgaCtrl.vMode.height / 2; //Two intervals, each with width/2 lines
		yMid = yInt;
		yInc = 256.0 / ((double) yInt); //256 color intensities are cycled through per interval (overflow must be caught when color=256.0)


		wStride = (vgaCtrl.stride) / 4; /* Find the stride in 32-bit words */

		xInt = width / 7; //Seven intervals, each with width/7 pixels
		xInc = 256.0 / ((double) xInt); //256 color intensities per interval. Notice that overflow is handled for this pattern.

		fBlue = 255.0;
		fRed = 255.0;
		fGreen = 255.0;
	//	fColor = fBlue;
		wCurrentInt = 1;
		for(xcoi = x; xcoi < x+grosor ; xcoi++){
			wColor = ((u32) fRed << BIT_DISPLAY_RED) | ((u32) fBlue << BIT_DISPLAY_BLUE) | ( (u32) fGreen << BIT_DISPLAY_GREEN);
			iPixelAddr = xcoi;
			for(ycoi = 0; ycoi < height; ycoi++){
				frameBuffer[iPixelAddr] = wColor;
				/*
				 * This pattern is printed one vertical line at a time, so the address must be incremented
				 * by the stride instead of just 1.
				 */
				iPixelAddr += wStride;
			}


		}
		/*
		* Flush the framebuffer memory range to ensure changes are written to the
		* actual memory, and therefore accessible by the VDMA.
		*/

}

void displayTestRect(int x0, int y0 , int width , int height, char letra){

	int height_limit = 0;
	int width_limit = 0;
	u32 wStride;
	u32 iPixelAddr;
	u32 wColor;
	double fRed, fBlue, fGreen;
	u32 x, y;
	//Inicializacion
	height_limit = vgaCtrl.vMode.height;
	width_limit = vgaCtrl.vMode.width;
	wStride = vgaCtrl.stride / 4; /* Find the stride in 32-bit words */

	wStride = (vgaCtrl.stride) / 4; /* Find the stride in 32-bit words */

	if (letra=='V')
	{
		fBlue = 0.0;
		fRed = 0.0;
		fGreen = 255.0;
	}
	else if (letra=='N')
	{
		fBlue = 0.0;
		fRed = 0.0;
		fGreen = 0.0;
	}
	else if(letra=='R')
	{
		fBlue = 0.0;
		fRed = 255.0;
		fGreen = 0.0;
	}
	else
	{
		fBlue = 255.0;
		fRed = 255.0;
		fGreen = 255.0;
	}
	//fColor = fBlue;

	//comprobar los limites

	//establecer el color
	wColor = ((u32) fRed << BIT_DISPLAY_RED) | ((u32) fBlue << BIT_DISPLAY_BLUE) | ( (u32) fGreen << BIT_DISPLAY_GREEN);
	for(y = y0-height/2; y < y0+height/2; y++){
		for(x = x0-width/2; x < x0+width/2 ; x++){
			iPixelAddr = x + (y*wStride);
			frameBuffer[iPixelAddr] = wColor;
		}
	}

}

void displayTestCirc(int x0, int y0 , int r){
	int height_limit = 0;
	int width_limit = 0;
	int i = 0;
	u32 wStride;
	u32 iPixelAddr;
	u32 wColor;
	double fRed, fBlue, fGreen;
	u32 x;
	int y;
	int yOld;
	int aux = 0;

		//Inicializacion
		height_limit = vgaCtrl.vMode.height;
		width_limit = vgaCtrl.vMode.width;
		wStride = vgaCtrl.stride / 4; /* Find the stride in 32-bit words */

		wStride = (vgaCtrl.stride) / 4; /* Find the stride in 32-bit words */

		fBlue = 100.0;
		fRed = 0.0;
		fGreen = 255.0;
		//fColor = fBlue;

		//comprobar los limites

		//establecer el color
		wColor = ((u32) fRed << BIT_DISPLAY_RED) | ((u32) fBlue << BIT_DISPLAY_BLUE) | ( (u32) fGreen << BIT_DISPLAY_GREEN);
		yOld=0;
		for(x = x0-r; x <= x0+r; x++){
			y = (int) ( sqrt( (r*r)- ((x-x0)*(x-x0))  ) );
			//y = (int) ( Q_rsqrt( (r*r)- ((x-x0)*(x-x0))  ) );
			iPixelAddr = x + ((y0+y)*wStride);
			frameBuffer[iPixelAddr] = wColor;
			aux = yOld-y;
			if ( aux> 1  ) {
					for ( i = 1 ; i <= aux ; i++ ){
						iPixelAddr = x + ((y0+y-i)*wStride);
						frameBuffer[iPixelAddr] = wColor;
					}
			}else if (yOld -y < 1){
					for ( i = 1 ; i <= y-yOld ; i++ ){
						iPixelAddr = x + ((y0+y-i)*wStride);
						frameBuffer[iPixelAddr] = wColor;
					}
			}
			yOld = y;

			aux = yOld+y;
			if ( aux> 1  ) {
					for ( i = 1 ; i <= aux ; i++ ){
						iPixelAddr = x + ((y0+y-i)*wStride);
						frameBuffer[iPixelAddr] = wColor;
					}
			}else if (aux < 1){
				for ( i = 1 ; i <= y-yOld ; i++ ){
					iPixelAddr = x + ((y0+y-i)*wStride);
					frameBuffer[iPixelAddr] = wColor;
				}
			}

			iPixelAddr = x + ((y0-y)*wStride);
			frameBuffer[iPixelAddr] = wColor;
			//Xil_DCacheFlushRange( (unsigned int) vgaBuf, DISPLAYDEMO_MAX_FRAME * 4);
		}
			/*
		* Flush the framebuffer memory range to ensure changes are written to the
		* actual memory, and therefore accessible by the VDMA.
		*/
		//Xil_DCacheFlushRange( (unsigned int) vgaBuf, DISPLAYDEMO_MAX_FRAME * 4);
}
void updateFrame(){
	static int i = 0;
	Xil_DCacheFlushRange( (unsigned int) vgaBuf, DISPLAYDEMO_MAX_FRAME * 4);


}


void dibujar_linea_malda(int x0, int y0 , int m, int length )
{
	void line(int x0, int y0, int x1, int y1) {

	  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
	  int err = (dx>dy ? dx : -dy)/2, e2;

	  for(;;){
	    setPixel(x0,y0);
	    if (x0==x1 && y0==y1) break;
	    e2 = err;
	    if (e2 >-dx) { err -= dy; x0 += sx; }
	    if (e2 < dy) { err += dx; y0 += sy; }
	  }
	}
}

void dibujar_linea_2_pto(int x0, int y0 , int x1, int y1, double fRed, double fGreen, double fBlue ){
	int height_limit = 0;
	int width_limit = 0;
	u32 wStride;
	u32 iPixelAddr;
	u32 wColor;
	//double fRed, fBlue, fGreen;
	u32 x, y;
	float malda=0;
	int aux = 0;
	//Inicializacion
	height_limit = vgaCtrl.vMode.height;
	width_limit = vgaCtrl.vMode.width;
	wStride = vgaCtrl.stride / 4; /* Find the stride in 32-bit words */
	wStride = (vgaCtrl.stride) / 4; /* Find the stride in 32-bit words */
	//fBlue = 255.0;
	//fRed = 255.0;
	//fGreen = 255.0;
	//comprobar los limites
	//establecer el color
	wColor = ((u32) fRed << BIT_DISPLAY_RED) | ((u32) fBlue << BIT_DISPLAY_BLUE) | ( (u32) fGreen << BIT_DISPLAY_GREEN);
	//
	if (x1 < x0){
		aux = x0;
		x0=x1;
		x1=aux;
		aux = y0;
		y0=y1;
		y1=aux;
	}
	malda= (float)(y1-y0)/(float)(x1-x0);
	for(x = x0 ; x <x1; x++){
			iPixelAddr = x +  (  (y0 +  (int)( (x-x0) * malda ) ) * wStride ) ;
			vgaBuf[0][iPixelAddr] = wColor;
			//Xil_DCacheFlushRange( (unsigned int) vgaBuf, DISPLAYDEMO_MAX_FRAME * 4);

	}
			/*
		* Flush the framebuffer memory range to ensure changes are written to the
		* actual memory, and therefore accessible by the VDMA.
		*/
	Xil_DCacheFlushRange( (unsigned int) vgaBuf, DISPLAYDEMO_MAX_FRAME * 4);

}

void dibujar_punto(int x, int y , int size){

}



void displayTestCirc_Perimetro(int x0, int y0 , int r){
	int height_limit = 0;
	int width_limit = 0;
	int i = 0;
	u32 wStride;
	u32 iPixelAddr;
	u32 wColor;
	double fRed, fBlue, fGreen;
	u32 x;
	int y;
	int yOldNeg;
	int yOldPos;
	int aux = 0;

		//Inicializacion
		height_limit = vgaCtrl.vMode.height;
		width_limit = vgaCtrl.vMode.width;
		wStride = vgaCtrl.stride / 4; /* Find the stride in 32-bit words */

		wStride = (vgaCtrl.stride) / 4; /* Find the stride in 32-bit words */

		fBlue = 255.0;
		fRed = 255.0;
		fGreen = 255.0;
		//fColor = fBlue;

		//comprobar los limites

		//establecer el color
		wColor = ((u32) fRed << BIT_DISPLAY_RED) | ((u32) fBlue << BIT_DISPLAY_BLUE) | ( (u32) fGreen << BIT_DISPLAY_GREEN);
		yOldNeg=0;
		yOldPos=0;
		for(x = x0-r; x <= x0+r; x++){
			y = (int) ( sqrt( (r*r)- ((x-x0)*(x-x0))  ) );
			//y = (int) ( Q_rsqrt( (r*r)- ((x-x0)*(x-x0))  ) );
			iPixelAddr = x + ((y0+y)*wStride);
			frameBuffer[iPixelAddr] = wColor;
			aux = y - yOldPos;
			if ( aux> 1  ) {
					for ( i = 1 ; i < aux ; i++ ){
						iPixelAddr = x + ((y0-yOldPos-i)*wStride);
						frameBuffer[iPixelAddr] = wColor;
					}
			}else if (aux < 1){
					for ( i = 1 ; i < (-aux) ; i++ ){
						iPixelAddr = x + ((y0-yOldPos+i)*wStride);
						frameBuffer[iPixelAddr] = wColor;
					}
			}
			yOldPos = y;

			aux = -y - yOldNeg;
			if ( aux < 1  ) {
					for ( i = 1 ; i < (-aux) ; i++ ){
						iPixelAddr = x + ( ( y0 - yOldNeg + i)*wStride);
						frameBuffer[iPixelAddr] = wColor;
					}
			}else if (aux > 1){
				for ( i = 1 ; i < (aux) ; i++ ){
					iPixelAddr = x + ((y0 - yOldNeg - i)*wStride);
					frameBuffer[iPixelAddr] = wColor;
				}
			}
			yOldNeg = -y;

			iPixelAddr = x + ((y0-y)*wStride);
			frameBuffer[iPixelAddr] = wColor;
			//Xil_DCacheFlushRange( (unsigned int) vgaBuf, DISPLAYDEMO_MAX_FRAME * 4);
		}
			/*
		* Flush the framebuffer memory range to ensure changes are written to the
		* actual memory, and therefore accessible by the VDMA.
		*/
		//Xil_DCacheFlushRange( (unsigned int) vgaBuf, DISPLAYDEMO_MAX_FRAME * 1);
}




void displayChar(int x0 , int y0 , char kar){
		int height_limit = 0;
		int width_limit = 0;
		u32 wStride;
		u32 iPixelAddr;
		u32 wColor;
		double fRed, fBlue, fGreen;
		u32 x, y;
		int i = 0;
		u16 line = 0;
		u16 auxByte = 0;
		char mask = 0x01;
		//Inicializacion
		height_limit = vgaCtrl.vMode.height;
		width_limit = vgaCtrl.vMode.width;
		wStride = vgaCtrl.stride / 4; /* Find the stride in 32-bit words */
		wStride = (vgaCtrl.stride) / 4; /* Find the stride in 32-bit words */
		fBlue = 255.0;
		fRed = 255.0;
		fGreen = 255.0;

		//y0=height_limit/2;
		x0=(vgaCtrl.vMode.width/2)-x0;
		//comprobar los limites
		//establecer el color
		wColor = ((u32) fRed << BIT_DISPLAY_RED) | ((u32) fBlue << BIT_DISPLAY_BLUE) | ( (u32) fGreen << BIT_DISPLAY_GREEN);
		//
//		for (i = 0 ; i < 8; i++){
//			line = font8x8_basic[(int)kar][i];
//			for(x = 0 ; x < 8; x++){
//				auxByte = line & (mask<<x);
//				if ( auxByte > 0){
//					iPixelAddr = (x0+x) +  (  (y0 + i ) * wStride ) ;
//					frameBuffer[iPixelAddr] = wColor;
//				}
//			}
//		}
		for (i = 0 ; i < 32; i++){

					line = font16x16_basic[(int)kar][i];
					i++;
					line = (line<<8)|font16x16_basic[(int)kar][i];
					for(x = 0 ; x < 16; x++){
						auxByte = line & (mask<<x);
						if ( auxByte > 0){
							iPixelAddr = (x0-x+16) +  (  ((y0 + i )/2) * wStride ) ;
							frameBuffer[iPixelAddr] = wColor;
						}
					}
				}
				/*
			* Flush the framebuffer memory range to ensure changes are written to the
			* actual memory, and therefore accessible by the VDMA.
			*/
		//Xil_DCacheFlushRange( (unsigned int) vgaBuf, DISPLAYDEMO_MAX_FRAME * 1);


}

void displayCorazon(int x0 , int y0){

		char array[32]={0x1C,0x38,0x22,0x44,0x41,0x82,0x80,0x01,0x80,0x05,0x80,0x09,0x80,0x11,0x88,0x21,0x44,0x42,0x42,0x82,0x21,0x04,0x10,0x08,0x08,0x10,0x04,0x20,0x02,0x40,0x01,0x80};
		char array1[128]={0x03,0xf8,0x1f,0xc0,0x0c,0x04,0x20,0x30,0x30,0x02,0x40,0x0c,0x40,0x01,0x80,0x02,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x61,0x80,0x00,0x00,0xA1,0x80,0x00,0x01,0x41,0x80,0x00,0x02,0x81,0x80,0x00,0x05,0x01,0x80,0x30,0x0a,0x01,0x80,0x28,0x14,0x01,0x40,0x14,0x28,0x02,0x40,0x0a,0x50,0x02,0x40,0x05,0xa0,0x02,0x20,0x02,0x40,0x04,0x20,0x01,0x80,0x04,0x10,0x00,0x00,0x08,0x10,0x00,0x00,0x08,0x08,0x00,0x00,0x10,0x04,0x00,0x00,0x20,0x02,0x00,0x00,0x40,0x01,0x00,0x00,0x80,0x00,0x80,0x01,0x00,0x00,0x40,0x02,0x00,0x00,0x20,0x04,0x00,0x00,0x10,0x08,0x00,0x00,0x08,0x10,0x00,0x00,0x04,0x20,0x00,0x00,0x02,0x40,0x00,0x00,0x01,0x80,0x00};
		char array2[128]={0x03,0xf8,0x1f,0xc0,0x0f,0xfc,0x3f,0xf0,0x3f,0xfe,0x7f,0xfc,0x7f,0xff,0xff,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x9f,0xff,0xff,0xff,0x1f,0xff,0xff,0xfe,0x3f,0xff,0xff,0xfc,0x7f,0xff,0xff,0xf8,0xff,0xff,0xcf,0xf1,0xff,0xff,0xc7,0xe3,0xff,0x7f,0xe3,0xc7,0xfe,0x7f,0xf1,0x8f,0xfe,0x7f,0xf8,0x1f,0xfe,0x3f,0xfc,0x3f,0xfc,0x3f,0xfe,0x7f,0xfc,0x1f,0xff,0xff,0xf8,0x1f,0xff,0xff,0xf8,0x0f,0xff,0xff,0xf0,0x07,0xff,0xff,0xe0,0x03,0xff,0xff,0xc0,0x01,0xff,0xff,0x80,0x00,0xff,0xff,0x00,0x00,0x7f,0xfe,0x00,0x00,0x3f,0xfc,0x00,0x00,0x1f,0xf8,0x00,0x00,0x0f,0xf0,0x00,0x00,0x07,0xe0,0x00,0x00,0x03,0xc0,0x00,0x00,0x01,0x80,0x00};
		int height_limit = 0;
		int width_limit = 0;
		u32 wStride;
		u32 iPixelAddr;
		u32 wColor;
		double fRed, fBlue, fGreen;
		u32 x, y;
		int i = 0;
		u32 line = 0;
		u32 auxByte = 0;
		char mask = 0x01;
		//Inicializacion
		height_limit = vgaCtrl.vMode.height;
		width_limit = vgaCtrl.vMode.width;
		wStride = vgaCtrl.stride / 4; /* Find the stride in 32-bit words */
		wStride = (vgaCtrl.stride) / 4; /* Find the stride in 32-bit words */
		fBlue = 255.0;
		fRed = 255.0;
		fGreen = 255.0;

		y0=(4*height_limit/2)-300;
		x0=(width_limit/2)+15;
		//comprobar los limites
		//establecer el color
		wColor = ((u32) fRed << BIT_DISPLAY_RED) | ((u32) fBlue << BIT_DISPLAY_BLUE) | ( (u32) fGreen << BIT_DISPLAY_GREEN);
		for (i = 0 ; i < 128; i++){//32

					line = array2[i];
					i++;
					line = (line<<8)|array2[i];
					i++;
					line = (line<<8)|array2[i];
					i++;
					line = (line<<8)|array2[i];
					for(x = 0 ; x < 32; x++){//16
						auxByte = line & (mask<<x);
						if ( auxByte > 0){
							iPixelAddr = (x0-x) +  (  ((y0 + i )/4) * wStride ) ;
							frameBuffer[iPixelAddr] = wColor;
						}
					}
				}
}

void escribirTablaAscii(){
	int i = 0, j = 0;
	int y0 = 108;
	for (i = 0 ; i < 16 ; i++){
		for (j = 0 ; j < 8 ; j++){
			displayChar( 400 + (j * 10 ) , y0 , (i*8)+j);
		}
		y0 = y0 + 10;


	}

}

float Q_rsqrt( float number )
{
	/*long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//      y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;*/

	    double mx = number;
	    double mn = 0;
	    while(mx - mn > 1e-9){
	        double md = (mx + mn) / 2;
	        if(md * md > number)
	            mx = md;
	        else
	            mn = md;
	    }
	    return mx;

}

void borrarFrameBuffer(){

	u32 x;
	int y;
	int height_limit = 0;
	int width_limit = 0;
	u32 wStride;
	u32 iPixelAddr;
	double fRed, fBlue, fGreen;
	u32 wColor;
	//
	int index = 0;
	fBlue = 0;
	fRed = 0;
	fGreen = 0;
	wStride = (vgaCtrl.stride) / 4; /* Find the stride in 32-bit words */
	wColor = ((u32) fRed << BIT_DISPLAY_RED) | ((u32) fBlue << BIT_DISPLAY_BLUE) | ( (u32) fGreen << BIT_DISPLAY_GREEN);
	height_limit = vgaCtrl.vMode.height;
	width_limit = vgaCtrl.vMode.width;
	for( x = 0 ; x <= height_limit; x++){
		for ( y = 0 ; y <  width_limit ; y++ ){
			iPixelAddr = x + ((y)*wStride);
			frameBuffer[iPixelAddr] = wColor;
			}
	}
}

void display_borrar_buffer(){
	u32 x;
	int y;
	int height_limit = 0;
	int width_limit = 0;
	u32 wStride;
	u32 iPixelAddr;
	double fRed, fBlue, fGreen;
	u32 wColor;
	//
	fBlue = 0;
	fRed = 0;
	fGreen = 0;
	wStride = (vgaCtrl.stride) / 4; /* Find the stride in 32-bit words */
	wColor = ((u32) fRed << BIT_DISPLAY_RED) | ((u32) fBlue << BIT_DISPLAY_BLUE) | ( (u32) fGreen << BIT_DISPLAY_GREEN);
	height_limit = vgaCtrl.vMode.height;
	width_limit = vgaCtrl.vMode.width;
	for( x = 0 ; x <= height_limit; x++){
		for ( y = 0 ; y <  width_limit ; y++ ){
			iPixelAddr = x + ((y)*wStride);
			vgaBuf[0][iPixelAddr] = wColor;
		}
	}
	Xil_DCacheFlushRange( (unsigned int) vgaBuf, DISPLAYDEMO_MAX_FRAME * 4);
}

void copiarFrameBuffer(){

	u32 x;
	int y;
	int height_limit = 0;
	int width_limit = 0;
	u32 wStride;
	u32 iPixelAddr;
	double fRed, fBlue, fGreen;
	u32 wColor;
	//
	int index = 0;
	fBlue = 128;
	fRed = 250;
	fGreen = 0;
	wStride = (vgaCtrl.stride) / 4; /* Find the stride in 32-bit words */
	wColor = ((u32) fRed << BIT_DISPLAY_RED) | ((u32) fBlue << BIT_DISPLAY_BLUE) | ( (u32) fGreen << BIT_DISPLAY_GREEN);
	height_limit = vgaCtrl.vMode.height;
	width_limit = vgaCtrl.vMode.width;
	for( x = 0 ; x <= height_limit; x++){
		for ( y = 0 ; y <  width_limit ; y++ ){
			iPixelAddr = x + ((y)*wStride);
			vgaBuf[index][iPixelAddr] = frameBuffer[iPixelAddr];
		}
	}
}






