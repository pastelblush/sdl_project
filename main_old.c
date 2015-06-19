#include <SDL.h>
#include <stdio.h>
#include <iostream.h>
#include <windows.h>
#include <conio.h>
#include <winbase.h>
#include <SDL_thread.h>

// ADS headers
#include "C:\TwinCAT\AdsApi\TcAdsDll\Include\TcAdsDef.h"
#include "C:\TwinCAT\AdsApi\TcAdsDll\Include\TcAdsApi.h"


void __stdcall bmp0(AmsAddr*, AdsNotificationHeader*, unsigned long);
void __stdcall bmp1(AmsAddr*, AdsNotificationHeader*, unsigned long);
void __stdcall bmp2(AmsAddr*, AdsNotificationHeader*, unsigned long);
void __stdcall bmp3(AmsAddr*, AdsNotificationHeader*, unsigned long);
void __stdcall bmp4(AmsAddr*, AdsNotificationHeader*, unsigned long);
void __stdcall bmp5(AmsAddr*, AdsNotificationHeader*, unsigned long);
void __stdcall bmp6(AmsAddr*, AdsNotificationHeader*, unsigned long);
void __stdcall bmp7(AmsAddr*, AdsNotificationHeader*, unsigned long);
void __stdcall bmp8(AmsAddr*, AdsNotificationHeader*, unsigned long);
void __stdcall bmp9(AmsAddr*, AdsNotificationHeader*, unsigned long);
void __stdcall recipewrite(AmsAddr*, AdsNotificationHeader*, unsigned long);
void __stdcall quit(AmsAddr*, AdsNotificationHeader*, unsigned long);
int my_thread( void *data );

char getstring(char ndata[80]);


    long                   nErr;
    AmsAddr                Addr;
    PAmsAddr               pAddr = &Addr;
    ULONG                  bmp0_note;
    ULONG                  bmp1_note;
    ULONG                  bmp2_note;
    ULONG                  bmp3_note;
    ULONG                  bmp4_note;
    ULONG                  bmp5_note;
    ULONG                  bmp6_note;
    ULONG                  bmp7_note;
    ULONG                  bmp8_note;
    ULONG                  bmp9_note;
    ULONG                  recipewrite_note;
    ULONG                  quit_note;

    boolean                q = FALSE,true_desu = TRUE,showbitmap = FALSE;

    AdsNotificationAttrib  adsNotificationAttrib;


	ULONG     bmphdl0,bmphdl1,bmphdl2,bmphdl3,bmphdl4,bmphdl5,bmphdl6,bmphdl7,bmphdl8,bmphdl9,rechdl,quithdl,bitdonehdl,repdonehdl;

    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *bmpSurface = NULL;

    SDL_Texture *bmpTex0 = NULL;
    SDL_Texture *bmpTex1 = NULL;
    SDL_Texture *bmpTex2 = NULL;
    SDL_Texture *bmpTex3 = NULL;
    SDL_Texture *bmpTex4 = NULL;
    SDL_Texture *bmpTex5 = NULL;
    SDL_Texture *bmpTex6 = NULL;
    SDL_Texture *bmpTex7 = NULL;
    SDL_Texture *bmpTex8 = NULL;
    SDL_Texture *bmpTex9 = NULL;

    SDL_Texture *bmpTexOpt = NULL;
    SDL_Texture *bmpTexTemp = NULL;

	SDL_Rect a, b;


	//thread
	//The event structure
    SDL_Event event;

    //The thread that will be used
    SDL_Thread *thread = NULL;

    SDL_Rect src;



int main(int argc, char *argv[]) {

   // SDL_Init( SDL_INIT_EVERYTHING );
              // Open communication port on the ADS router
              AdsPortOpen();
              nErr = AdsGetLocalAddress(pAddr);
			  printf("%i",nErr);


              // Select Port: TwinCAT2 PLC1
              pAddr->port = 801;


    nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(bmphdl0), &bmphdl0, sizeof("MAIN.bitmap0"), "MAIN.bitmap0");
	printf("%i",nErr);
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(bmphdl1), &bmphdl1, sizeof("MAIN.bitmap1"), "MAIN.bitmap1");
	printf("%i",nErr);
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(bmphdl2), &bmphdl2, sizeof("MAIN.bitmap2"), "MAIN.bitmap2");
	printf("%i",nErr);
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(bmphdl3), &bmphdl3, sizeof("MAIN.bitmap3"), "MAIN.bitmap3");
	printf("%i",nErr);
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(bmphdl4), &bmphdl4, sizeof("MAIN.bitmap4"), "MAIN.bitmap4");
	printf("%i",nErr);
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(bmphdl5), &bmphdl5, sizeof("MAIN.bitmap5"), "MAIN.bitmap5");
	printf("%i",nErr);
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(bmphdl6), &bmphdl6, sizeof("MAIN.bitmap6"), "MAIN.bitmap6");
	printf("%i",nErr);
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(bmphdl7), &bmphdl7, sizeof("MAIN.bitmap7"), "MAIN.bitmap7");
	printf("%i",nErr);
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(bmphdl8), &bmphdl8, sizeof("MAIN.bitmap8"), "MAIN.bitmap8");
	printf("%i",nErr);
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(bmphdl9), &bmphdl9, sizeof("MAIN.bitmap9"), "MAIN.bitmap9");
	printf("%i",nErr);
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(rechdl), &rechdl, sizeof("MAIN.recipewrite"), "MAIN.recipewrite");
	printf("%i",nErr);
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(rechdl), &quithdl, sizeof("MAIN.quit"), "MAIN.quit");
	printf("%i",nErr);
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(rechdl), &bitdonehdl, sizeof("MAIN.bitmapdone"), "MAIN.bitmapdone");
	printf("%i",nErr);
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(rechdl), &repdonehdl, sizeof("MAIN.recipedone"), "MAIN.recipedone");
    printf("%i",nErr);



              // Specify attributes of the notification
              adsNotificationAttrib.cbLength = sizeof(true_desu);
              adsNotificationAttrib.nTransMode = ADSTRANS_SERVERONCHA;
              adsNotificationAttrib.nMaxDelay = 10000; // 1ms
              adsNotificationAttrib.nCycleTime = 10000; // 1ms

              // Start notification for changes to the symbol table
              nErr = AdsSyncAddDeviceNotificationReq(pAddr, ADSIGRP_SYM_VALBYHND, bmphdl0, &adsNotificationAttrib, bmp0, 0, &bmp0_note);
              printf("%i",nErr);
              nErr = AdsSyncAddDeviceNotificationReq(pAddr, ADSIGRP_SYM_VALBYHND, bmphdl1, &adsNotificationAttrib, bmp1, 0, &bmp1_note);
              printf("%i",nErr);
              nErr = AdsSyncAddDeviceNotificationReq(pAddr, ADSIGRP_SYM_VALBYHND, bmphdl2, &adsNotificationAttrib, bmp2, 0, &bmp2_note);
              printf("%i",nErr);
              nErr = AdsSyncAddDeviceNotificationReq(pAddr, ADSIGRP_SYM_VALBYHND, bmphdl3, &adsNotificationAttrib, bmp3, 0, &bmp3_note);
              printf("%i",nErr);
              nErr = AdsSyncAddDeviceNotificationReq(pAddr, ADSIGRP_SYM_VALBYHND, bmphdl4, &adsNotificationAttrib, bmp4, 0, &bmp4_note);
              printf("%i",nErr);
              nErr = AdsSyncAddDeviceNotificationReq(pAddr, ADSIGRP_SYM_VALBYHND, bmphdl5, &adsNotificationAttrib, bmp5, 0, &bmp5_note);
              printf("%i",nErr);
              nErr = AdsSyncAddDeviceNotificationReq(pAddr, ADSIGRP_SYM_VALBYHND, bmphdl6, &adsNotificationAttrib, bmp6, 0, &bmp6_note);
              printf("%i",nErr);
              nErr = AdsSyncAddDeviceNotificationReq(pAddr, ADSIGRP_SYM_VALBYHND, bmphdl7, &adsNotificationAttrib, bmp7, 0, &bmp7_note);
              printf("%i",nErr);
              nErr = AdsSyncAddDeviceNotificationReq(pAddr, ADSIGRP_SYM_VALBYHND, bmphdl8, &adsNotificationAttrib, bmp8, 0, &bmp8_note);
              printf("%i",nErr);
              nErr = AdsSyncAddDeviceNotificationReq(pAddr, ADSIGRP_SYM_VALBYHND, bmphdl9, &adsNotificationAttrib, bmp9, 0, &bmp9_note);
              printf("%i",nErr);
              nErr = AdsSyncAddDeviceNotificationReq(pAddr, ADSIGRP_SYM_VALBYHND, rechdl, &adsNotificationAttrib, recipewrite, 0, &recipewrite_note);
              printf("%i",nErr);
              nErr = AdsSyncAddDeviceNotificationReq(pAddr, ADSIGRP_SYM_VALBYHND, quithdl, &adsNotificationAttrib, quit, 0, &quit_note);
			  printf("%i",nErr);

			  printf("%i",nErr);
			  //block the code

            //Create and run the thread
            thread = SDL_CreateThread( my_thread,"my_thread", (NULL) );
            printf("press enter to close");
             // q = FALSE;
			 //   do
			//	  {
			//		;
			//	  }
			 // while (!q);

			 getch();
			 q = TRUE;


              // Stop notification
              nErr = AdsSyncDelDeviceNotificationReq(pAddr, bmp0_note);
              nErr = AdsSyncDelDeviceNotificationReq(pAddr, bmp1_note);
              nErr = AdsSyncDelDeviceNotificationReq(pAddr, bmp2_note);
              nErr = AdsSyncDelDeviceNotificationReq(pAddr, bmp3_note);
              nErr = AdsSyncDelDeviceNotificationReq(pAddr, bmp4_note);
              nErr = AdsSyncDelDeviceNotificationReq(pAddr, bmp5_note);
              nErr = AdsSyncDelDeviceNotificationReq(pAddr, bmp6_note);
              nErr = AdsSyncDelDeviceNotificationReq(pAddr, bmp7_note);
              nErr = AdsSyncDelDeviceNotificationReq(pAddr, bmp8_note);
              nErr = AdsSyncDelDeviceNotificationReq(pAddr, bmp9_note);
              nErr = AdsSyncDelDeviceNotificationReq(pAddr, recipewrite_note);
              nErr = AdsSyncDelDeviceNotificationReq(pAddr, quit_note);

			  //relese handle
			  nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(bmphdl0), &bmphdl0);
			  nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(bmphdl1), &bmphdl1);
			  nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(bmphdl2), &bmphdl2);
			  nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(bmphdl3), &bmphdl3);
			  nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(bmphdl4), &bmphdl4);
			  nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(bmphdl5), &bmphdl5);
			  nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(bmphdl6), &bmphdl6);
			  nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(bmphdl7), &bmphdl7);
			  nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(bmphdl8), &bmphdl8);
			  nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(bmphdl9), &bmphdl9);
			  nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(rechdl), &rechdl);
			  nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(quithdl), &quithdl);
			  nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(bitdonehdl), &bitdonehdl);
			  nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(repdonehdl), &repdonehdl);



              // Close communication port
              nErr = AdsPortClose();



    SDL_DestroyTexture(bmpTex0);
    SDL_DestroyTexture(bmpTex1);
    SDL_DestroyTexture(bmpTex2);
    SDL_DestroyTexture(bmpTex3);
    SDL_DestroyTexture(bmpTex4);
    SDL_DestroyTexture(bmpTex5);
    SDL_DestroyTexture(bmpTex6);
    SDL_DestroyTexture(bmpTex7);
    SDL_DestroyTexture(bmpTex8);
    SDL_DestroyTexture(bmpTex9);
    SDL_DestroyTexture(bmpTexOpt);
    SDL_DestroyTexture(bmpTexTemp);


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);



    //SDL_KillThread( thread );
    SDL_Quit();

    return 0;

}

int my_thread( void *data )
{
    //While the program is not over
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Rect secondscreen;
    SDL_GetDisplayBounds(1,&secondscreen);
    win = SDL_CreateWindow("Projector", secondscreen.x, secondscreen.y, 1366, 768, SDL_WINDOW_FULLSCREEN);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

    while( !q )
    {

        if(showbitmap)
        {
           showbitmap = FALSE;


            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, bmpTexOpt, NULL, NULL);
            SDL_RenderPresent(renderer);

        }
    }

    return 0;
}

// Callback function
void __stdcall bmp0(AmsAddr* pAddr, AdsNotificationHeader* pNotification, ULONG hUser)
{
if((*(boolean *)pNotification->data) == TRUE)
{

    bmpTexOpt = bmpTex0;
    showbitmap = TRUE;
    nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, bitdonehdl,1, &true_desu);
}
}
// Callback function
void __stdcall bmp1(AmsAddr* pAddr, AdsNotificationHeader* pNotification, ULONG hUser)
{
if((*(boolean *)pNotification->data) == TRUE)
{
    bmpTexOpt = bmpTex1;
    showbitmap = TRUE;
    nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, bitdonehdl,1, &true_desu);
}
}
// Callback function
void __stdcall bmp2(AmsAddr* pAddr, AdsNotificationHeader* pNotification, ULONG hUser)
{
if((*(boolean *)pNotification->data) == TRUE)
{
    bmpTexOpt = bmpTex2;
    showbitmap = TRUE;

	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, bitdonehdl,1, &true_desu);

}
}
// Callback function
void __stdcall bmp3(AmsAddr* pAddr, AdsNotificationHeader* pNotification, ULONG hUser)
{
if((*(boolean *)pNotification->data) == TRUE)
{
    bmpTexOpt = bmpTex3;
    showbitmap = TRUE;

	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, bitdonehdl,1, &true_desu);

}
}
// Callback function
void __stdcall bmp4(AmsAddr* pAddr, AdsNotificationHeader* pNotification, ULONG hUser)
{
if((*(boolean *)pNotification->data) == TRUE)
{
    bmpTexOpt = bmpTex4;
    showbitmap = TRUE;
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, bitdonehdl,1, &true_desu);

}
}
// Callback function
void __stdcall bmp5(AmsAddr* pAddr, AdsNotificationHeader* pNotification, ULONG hUser)
{
if((*(boolean *)pNotification->data) == TRUE)
{
    bmpTexOpt = bmpTex5;
    showbitmap = TRUE;
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, bitdonehdl,1, &true_desu);

}
}
// Callback function
void __stdcall bmp6(AmsAddr* pAddr, AdsNotificationHeader* pNotification, ULONG hUser)
{
if((*(boolean *)pNotification->data) == TRUE)
{
    bmpTexOpt = bmpTex6;
    showbitmap = TRUE;
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, bitdonehdl,1, &true_desu);

}
}
// Callback function
void __stdcall bmp7(AmsAddr* pAddr, AdsNotificationHeader* pNotification, ULONG hUser)
{
if((*(boolean *)pNotification->data) == TRUE)
{
    bmpTexOpt = bmpTex7;
    showbitmap = TRUE;
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, bitdonehdl,1, &true_desu);

}
}
// Callback function
void __stdcall bmp8(AmsAddr* pAddr, AdsNotificationHeader* pNotification, ULONG hUser)
{
if((*(boolean *)pNotification->data) == TRUE)
{
   bmpTexOpt = bmpTex8;
   showbitmap = TRUE;
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, bitdonehdl,1, &true_desu);

}
}
// Callback function
void __stdcall bmp9(AmsAddr* pAddr, AdsNotificationHeader* pNotification, ULONG hUser)
{
if((*(boolean *)pNotification->data) == TRUE)
{
    bmpTexOpt = bmpTex9;
    showbitmap = TRUE;
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, bitdonehdl,1, &true_desu);

}
}

void __stdcall recipewrite(AmsAddr* pAddr, AdsNotificationHeader* pNotification, ULONG hUser)
{

if((*(boolean *)pNotification->data) == TRUE)
{

    bmpSurface = SDL_LoadBMP("image0.bmp");
    bmpTex0 = SDL_CreateTextureFromSurface(renderer, bmpSurface);

   //         src.x = 0;
   //        src.y = 0;
   //         src.w = bmpSurface->w;
   //         src.h = bmpSurface->h;
    SDL_FreeSurface(bmpSurface);

    bmpSurface = SDL_LoadBMP("image1.bmp");
    bmpTex1 = SDL_CreateTextureFromSurface(renderer, bmpSurface);
    SDL_FreeSurface(bmpSurface);

    bmpSurface = SDL_LoadBMP("image2.bmp");
    bmpTex2 = SDL_CreateTextureFromSurface(renderer, bmpSurface);
    SDL_FreeSurface(bmpSurface);

     bmpSurface = SDL_LoadBMP("image.bmp");
    bmpTex3 = SDL_CreateTextureFromSurface(renderer, bmpSurface);
    SDL_FreeSurface(bmpSurface);

    bmpSurface = SDL_LoadBMP("image.bmp");
    bmpTex4 = SDL_CreateTextureFromSurface(renderer, bmpSurface);
    SDL_FreeSurface(bmpSurface);

    bmpSurface = SDL_LoadBMP("image.bmp");
    bmpTex5 = SDL_CreateTextureFromSurface(renderer, bmpSurface);
    SDL_FreeSurface(bmpSurface);

    bmpSurface = SDL_LoadBMP("image.bmp");
    bmpTex6 = SDL_CreateTextureFromSurface(renderer, bmpSurface);
    SDL_FreeSurface(bmpSurface);

    bmpSurface = SDL_LoadBMP("image.bmp");
    bmpTex7 = SDL_CreateTextureFromSurface(renderer, bmpSurface);
    SDL_FreeSurface(bmpSurface);

    bmpSurface = SDL_LoadBMP("image.bmp");
    bmpTex8 = SDL_CreateTextureFromSurface(renderer, bmpSurface);
    SDL_FreeSurface(bmpSurface);

    bmpSurface = SDL_LoadBMP("image.bmp");
    bmpTex9 = SDL_CreateTextureFromSurface(renderer, bmpSurface);
    SDL_FreeSurface(bmpSurface);

	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, repdonehdl,1, &true_desu);


}

}



// Callback function
void __stdcall quit(AmsAddr* pAddr, AdsNotificationHeader* pNotification, ULONG hUser)
{

if((*(BOOL *)pNotification->data) == TRUE)
{
    q = TRUE;
}
else
{
    q = FALSE;
}

}
