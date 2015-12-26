/*
 * display_vga.c
 *
 *  Created on: 26/12/2015
 *      Author: jlamp
 */

#include "display_vga.h"
#include <math.h>
#include "xil_cache.h"

#include "font8x8.h"

//ESTE ES EL BUFFER MEAPDEO A MEMEORIA. ESTO SE REALIZA EN LA FUNCIÓN DisplayDemoInitializeFroga
u32 vgaBuf[3][DISPLAYDEMO_MAX_FRAME];
//ESTE SERA EL BUFFER AUXILIAR , ES EL DOBLE BUFFER
u32 frameBuffer[DISPLAYDEMO_MAX_FRAME];

DisplayCtrl vgaCtrl;

void displayInit(){

	DisplayDemoInitialize(&vgaCtrl, VGA_VDMA_ID, SCU_TIMER_ID, VGA_BASEADDR, DISPLAY_NOT_HDMI );

}
int DisplayDemoInitialize(DisplayCtrl *dispPtr, u16 vdmaId, u16 timerId, u32 dispCtrlAddr, int fHdmi){
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
			vgaBuf[0][iPixelAddr] = wColor;
		}
	}
		/*
	* Flush the framebuffer memory range to ensure changes are written to the
	* actual memory, and therefore accessible by the VDMA.
	*/
	//Xil_DCacheFlushRange( (unsigned int) vgaBuf, DISPLAYDEMO_MAX_FRAME * 3);

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

	Xil_DCacheFlushRange( (unsigned int) vgaBuf, DISPLAYDEMO_MAX_FRAME * 4);
}

void borrarFrameBuffer() {

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
	wColor = ((u32) fRed << BIT_DISPLAY_RED) | ((u32) fBlue << BIT_DISPLAY_BLUE)
			| ((u32) fGreen << BIT_DISPLAY_GREEN);
	height_limit = vgaCtrl.vMode.height;
	width_limit = vgaCtrl.vMode.width;
	for (x = 0; x <= height_limit; x++) {
		for (y = 0; y < width_limit; y++) {
			iPixelAddr = x + ((y) * wStride);
			frameBuffer[iPixelAddr] = wColor;
		}
	}
}
void copiarFrameBuffer() {

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
	wColor = ((u32) fRed << BIT_DISPLAY_RED) | ((u32) fBlue << BIT_DISPLAY_BLUE)
			| ((u32) fGreen << BIT_DISPLAY_GREEN);
	height_limit = vgaCtrl.vMode.height;
	width_limit = vgaCtrl.vMode.width;
	for (x = 0; x <= height_limit; x++) {
		for (y = 0; y < width_limit; y++) {
			iPixelAddr = x + ((y) * wStride);
			vgaBuf[index][iPixelAddr] = frameBuffer[iPixelAddr];
		}
	}
}
