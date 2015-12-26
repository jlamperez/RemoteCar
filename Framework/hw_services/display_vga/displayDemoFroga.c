/*
 * displayDemoFroga.c
 *
 *  Created on: 14/07/2014
 *      Author: jaagirre
 */
//#include "timer_ps.h"
#include "display_vga.h"
#include <math.h>
#include "xil_cache.h"

#include "font8x8.h"


DisplayCtrl vgaCtrl;
u32 vgaBuf[3][DISPLAYDEMO_MAX_FRAME];


int DisplayDemoFroga(){
	displayInit();
	//displayTest();
	dibujar_linea(30);
	dibujar_linea_vertical(130 , 0 , 30);
	dibujar_linea_vertical(200 , 0 , 30);
	displayTestRect(300, 10 , 50 , 30);
	displayTestRect(300, 70 , 70 , 10);

	displayTestCirc( 300, 300 , 30);

	displayTestCirc_Perimetro( 400, 300 , 30);

	dibujar_linea_2_pto( 200, 200 , 250, 200 );
	dibujar_linea_2_pto( 200, 220 , 300, 220 );

	dibujar_linea_2_pto( 200, 220 , 300, 250 );
	dibujar_linea_2_pto( 200, 220 , 300, 180 );
	dibujar_linea_2_pto( 300, 150 , 200, 180 );

	dibujar_linea_2_pto( 450, 200 , 550, 150 );
	dibujar_linea_2_pto( 450, 200 , 550, 250 );
	dibujar_linea_2_pto( 450, 200 , 350, 150 );
	dibujar_linea_2_pto( 450, 200 , 350, 250 );

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


void displayTest(){
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

	fBlue = 0.0;
	fRed = 256.0;

	wStride = (vgaCtrl.stride) / 4; /* Find the stride in 32-bit words */

	xInt = width / 7; //Seven intervals, each with width/7 pixels
	xInc = 256.0 / ((double) xInt); //256 color intensities per interval. Notice that overflow is handled for this pattern.

	fColor = 0.0;
	wCurrentInt = 1;
	for(xcoi = 0; xcoi < width; xcoi++){
			if (wCurrentInt & 0b001)
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
				fGreen = 0.0;

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
				vgaBuf[0][iPixelAddr] = wColor;
				/*
				 * This pattern is printed one vertical line at a time, so the address must be incremented
				 * by the stride instead of just 1.
				 */
				iPixelAddr += wStride;
			}

			fColor += xInc;
			if (fColor >= 256.0)
			{
				fColor = 0.0;
				wCurrentInt++;
			}
		}
	/*
	* Flush the framebuffer memory range to ensure changes are written to the
	* actual memory, and therefore accessible by the VDMA.
	*/
	Xil_DCacheFlushRange( (unsigned int) vgaBuf, DISPLAYDEMO_MAX_FRAME * 4);

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

		fBlue = 0.0;
		fRed = 255.0;
		fGreen = 0.0;
		//fColor = fBlue;
		wCurrentInt = 1;
		for(xcoi = x; xcoi < x+grosor ; xcoi++){
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

void displayTestRect(int x0, int y0 , int width , int height){

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

	fBlue = 0.0;
	fRed = 255.0;
	fGreen = 0.0;
	//fColor = fBlue;

	//comprobar los limites

	//establecer el color
	wColor = ((u32) fRed << BIT_DISPLAY_RED) | ((u32) fBlue << BIT_DISPLAY_BLUE) | ( (u32) fGreen << BIT_DISPLAY_GREEN);
	for(y = y0; y < y0+height; y++){
		for(x = x0; x < x0+width ; x++){
			iPixelAddr = x + (y*wStride);
			vgaBuf[1][iPixelAddr] = wColor;
		}
	}
		/*
	* Flush the framebuffer memory range to ensure changes are written to the
	* actual memory, and therefore accessible by the VDMA.
	*/
	Xil_DCacheFlushRange( (unsigned int) vgaBuf, DISPLAYDEMO_MAX_FRAME * 3);

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

		fBlue = 0.0;
		fRed = 255.0;
		fGreen = 0.0;
		//fColor = fBlue;

		//comprobar los limites

		//establecer el color
		wColor = ((u32) fRed << BIT_DISPLAY_RED) | ((u32) fBlue << BIT_DISPLAY_BLUE) | ( (u32) fGreen << BIT_DISPLAY_GREEN);
		yOld=0;
		for(x = x0-r; x <= x0+r; x++){
			y = (int) ( sqrt( (r*r)- ((x-x0)*(x-x0))  ) );
			//y = (int) ( Q_rsqrt( (r*r)- ((x-x0)*(x-x0))  ) );
			iPixelAddr = x + ((y0+y)*wStride);
			vgaBuf[0][iPixelAddr] = wColor;
			aux = yOld-y;
			if ( aux> 1  ) {
					for ( i = 1 ; i <= aux ; i++ ){
						iPixelAddr = x + ((y0+y-i)*wStride);
						vgaBuf[0][iPixelAddr] = wColor;
					}
			}else if (yOld -y < 1){
					for ( i = 1 ; i <= y-yOld ; i++ ){
						iPixelAddr = x + ((y0+y-i)*wStride);
						vgaBuf[0][iPixelAddr] = wColor;
					}
			}
			yOld = y;

			aux = yOld+y;
			if ( aux> 1  ) {
					for ( i = 1 ; i <= aux ; i++ ){
						iPixelAddr = x + ((y0+y-i)*wStride);
						vgaBuf[0][iPixelAddr] = wColor;
					}
			}else if (aux < 1){
				for ( i = 1 ; i <= y-yOld ; i++ ){
					iPixelAddr = x + ((y0+y-i)*wStride);
					vgaBuf[0][iPixelAddr] = wColor;
				}
			}

			iPixelAddr = x + ((y0-y)*wStride);
			vgaBuf[0][iPixelAddr] = wColor;
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


void dibujar_linea_malda(int x0, int y0 , int m, int length ){

}

void dibujar_linea_2_pto(int x0, int y0 , int x1, int y1 ){
	int height_limit = 0;
	int width_limit = 0;
	u32 wStride;
	u32 iPixelAddr;
	u32 wColor;
	double fRed, fBlue, fGreen;
	u32 x, y;
	float malda=0;
	int aux = 0;
	//Inicializacion
	height_limit = vgaCtrl.vMode.height;
	width_limit = vgaCtrl.vMode.width;
	wStride = vgaCtrl.stride / 4; /* Find the stride in 32-bit words */
	wStride = (vgaCtrl.stride) / 4; /* Find the stride in 32-bit words */
	fBlue = 0.0;
	fRed = 255.0;
	fGreen = 0.0;
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

		fBlue = 0.0;
		fRed = 255.0;
		fGreen = 0.0;
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
			vgaBuf[0][iPixelAddr] = wColor;
			aux = y - yOldPos;
			if ( aux> 1  ) {
					for ( i = 1 ; i < aux ; i++ ){
						iPixelAddr = x + ((y0-yOldPos-i)*wStride);
						vgaBuf[0][iPixelAddr] = wColor;
					}
			}else if (aux < 1){
					for ( i = 1 ; i < (-aux) ; i++ ){
						iPixelAddr = x + ((y0-yOldPos+i)*wStride);
						vgaBuf[0][iPixelAddr] = wColor;
					}
			}
			yOldPos = y;

			aux = -y - yOldNeg;
			if ( aux < 1  ) {
					for ( i = 1 ; i < (-aux) ; i++ ){
						iPixelAddr = x + ( ( y0 - yOldNeg + i)*wStride);
						vgaBuf[0][iPixelAddr] = wColor;
					}
			}else if (aux > 1){
				for ( i = 1 ; i < (aux) ; i++ ){
					iPixelAddr = x + ((y0 - yOldNeg - i)*wStride);
					vgaBuf[0][iPixelAddr] = wColor;
				}
			}
			yOldNeg = -y;

			iPixelAddr = x + ((y0-y)*wStride);
			vgaBuf[0][iPixelAddr] = wColor;
			//Xil_DCacheFlushRange( (unsigned int) vgaBuf, DISPLAYDEMO_MAX_FRAME * 4);
		}
			/*
		* Flush the framebuffer memory range to ensure changes are written to the
		* actual memory, and therefore accessible by the VDMA.
		*/
		//Xil_DCacheFlushRange( (unsigned int) vgaBuf, DISPLAYDEMO_MAX_FRAME * 1);
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
	//Xil_DCacheFlushRange( (unsigned int) vgaBuf, DISPLAYDEMO_MAX_FRAME * 4);
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
		char line = 0;
		char auxByte = 0;
		char mask = 0x01;
		//Inicializacion
		height_limit = vgaCtrl.vMode.height;
		width_limit = vgaCtrl.vMode.width;
		wStride = vgaCtrl.stride / 4; /* Find the stride in 32-bit words */
		wStride = (vgaCtrl.stride) / 4; /* Find the stride in 32-bit words */
		fBlue = 0.0;
		fRed = 255.0;
		fGreen = 0.0;
		//comprobar los limites
		//establecer el color
		wColor = ((u32) fRed << BIT_DISPLAY_RED) | ((u32) fBlue << BIT_DISPLAY_BLUE) | ( (u32) fGreen << BIT_DISPLAY_GREEN);
		//
		for (i = 0 ; i < 8 ; i++){
			line = font8x8_basic[(int)kar][i];
			for(x = 0 ; x <8; x++){
				auxByte = line & (mask<<x);
				if ( auxByte > 0){
					iPixelAddr = (x0+x) +  (  (y0 + i ) * wStride ) ;
					vgaBuf[0][iPixelAddr] = wColor;
				}
			}
		}

				/*
			* Flush the framebuffer memory range to ensure changes are written to the
			* actual memory, and therefore accessible by the VDMA.
			*/
		//Xil_DCacheFlushRange( (unsigned int) vgaBuf, DISPLAYDEMO_MAX_FRAME * 4);


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





