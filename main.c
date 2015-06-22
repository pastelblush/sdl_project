#include <SDL.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <winbase.h>
#include <SDL_thread.h>
#include <string.h>


// ADS headers
#include "C:\TwinCAT\AdsApi\TcAdsDll\Include\TcAdsDef.h"
#include "C:\TwinCAT\AdsApi\TcAdsDll\Include\TcAdsApi.h"


void __stdcall recipewrite(AmsAddr*, AdsNotificationHeader*, unsigned long);
void __stdcall quit(AmsAddr*, AdsNotificationHeader*, unsigned long);
void __stdcall selectscreen(AmsAddr*, AdsNotificationHeader*, unsigned long);
int my_thread( void *data );
int recipe_thread( void *data );
char S[81];



    int                    index;
    long                   nErr;
    AmsAddr                Addr;
    PAmsAddr               pAddr = &Addr;
    ULONG                  recipewrite_note;
    ULONG                  quit_note;

    boolean                q = FALSE,true_desu = TRUE,showbitmap = FALSE,recwrite = FALSE,initflag = FALSE;


	ULONG     rechdl,quithdl,bitdonehdl,repdonehdl,bhdl1,bhdl2,bhdl3,bhdl4,bhdl5,bhdl6,bhdl7,bhdl8,bhdl9;

    AdsNotificationAttrib  adsNotificationAttrib,adsNotificationAttribselectscreen;
    ULONG   selectscreenhdl,selectscreennote;

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

    SDL_Texture **bmpTexOptARRAY[10];

    //The thread that will be used
    SDL_Thread *thread = NULL;
    SDL_Thread *thread2 = NULL;

    //argument setting
    int displayno,portno;

    char bmp1[30];
    char bmp2[30];
    char bmp3[30];
    char bmp4[30];
    char bmp5[30];
    char bmp6[30];
    char bmp7[30];
    char bmp8[30];
    char bmp9[30];

    char pbmp1[81];
    char pbmp2[81];
    char pbmp3[81];
    char pbmp4[81];
    char pbmp5[81];
    char pbmp6[81];
    char pbmp7[81];
    char pbmp8[81];
    char pbmp9[81];

    //int width,height;


int main(int argc, char *argv[]) {

    timeBeginPeriod(1);

    bmpTexOptARRAY[0] = &bmpTex0;
    bmpTexOptARRAY[1] = &bmpTex1;
    bmpTexOptARRAY[2] = &bmpTex2;
    bmpTexOptARRAY[3] = &bmpTex3;
    bmpTexOptARRAY[4] = &bmpTex4;
    bmpTexOptARRAY[5] = &bmpTex5;
    bmpTexOptARRAY[6] = &bmpTex6;
    bmpTexOptARRAY[7] = &bmpTex7;
    bmpTexOptARRAY[8] = &bmpTex8;
    bmpTexOptARRAY[9] = &bmpTex9;

    char rwrite[30] = "recipewrite";
    char bitdone[30] = "bitmapdone";
    char rdone[30] = "recipedone";
    char ss[30] = "selectscreen";
    char stemp[30];

    //atexit(SDL_QUIT);
    if (argc != 4)
    {
        printf("usage: %s <monitor_number(0,1..)> <adsportno> <prefix_for_variable(eg: GVL., or MAIN. , or MAIN.SC2_>",argv[0]);
        return;
    }
    else
    {
        displayno = atoi(argv[1]);
        portno = atoi(argv[2]);
        //width = atoi(argv[4]);
        //height = atoi(argv[5]);

        if(displayno == NULL)
        {
            displayno = 0;
        }
        if(portno == NULL)
        {
            portno = 801;
        }

        strcpy(pbmp1,"image1.bmp");
        strcpy(pbmp2,"image2.bmp");
        strcpy(pbmp3,"image3.bmp");
        strcpy(pbmp4,"image4.bmp");
        strcpy(pbmp5,"image5.bmp");
        strcpy(pbmp6,"image6.bmp");
        strcpy(pbmp7,"image7.bmp");
        strcpy(pbmp8,"image8.bmp");
        strcpy(pbmp9,"image9.bmp");

        strcpy(stemp,rwrite);
        strcpy(rwrite,argv[3]);
        strcat(rwrite,stemp);

        strcpy(stemp,bitdone);
        strcpy(bitdone,argv[3]);
        strcat(bitdone,stemp);

        strcpy(stemp,rdone);
        strcpy(rdone,argv[3]);
        strcat(rdone,stemp);

        strcpy(stemp,ss);
        strcpy(ss,argv[3]);
        strcat(ss,stemp);

        //bmp path
        strcpy(bmp1,argv[3]);
        strcat(bmp1,"bmp1");

        strcpy(bmp2,argv[3]);
        strcat(bmp2,"bmp2");

        strcpy(bmp3,argv[3]);
        strcat(bmp3,"bmp3");

        strcpy(bmp4,argv[3]);
        strcat(bmp4,"bmp4");

        strcpy(bmp5,argv[3]);
        strcat(bmp5,"bmp5");

        strcpy(bmp6,argv[3]);
        strcat(bmp6,"bmp6");

        strcpy(bmp7,argv[3]);
        strcat(bmp7,"bmp7");

        strcpy(bmp8,argv[3]);
        strcat(bmp8,"bmp8");

        strcpy(bmp9,argv[3]);
        strcat(bmp9,"bmp9");

        printf("screen is: %i \n",displayno);
        printf("port is: %i \n",portno);
        //printf("width is: %i \n",width);
        //printf("height is: %i \n",height);
        printf("your var configuration is: \n");
        printf("%s \n",rwrite);
        printf("%s \n",bitdone);
        printf("%s \n",rdone);
        printf("%s \n",ss);
        printf("%s \n",bmp1);
        printf("%s \n",bmp2);
        printf("%s \n",bmp3);
        printf("%s \n",bmp4);
        printf("%s \n",bmp5);
        printf("%s \n",bmp6);
        printf("%s \n",bmp7);
        printf("%s \n",bmp8);
        printf("%s \n",bmp9);
    }


              // Open communication port on the ADS router
              AdsPortOpen();
              nErr = AdsGetLocalAddress(pAddr);
			  printf("%i",nErr);


              // Select Port: TwinCAT2 PLC1
              pAddr->port = portno;

	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(rechdl), &rechdl, sizeof(rwrite), rwrite);
	printf("%i",nErr);
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(bitdonehdl), &bitdonehdl, sizeof(bitdone), bitdone);
	printf("%i",nErr);
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(repdonehdl), &repdonehdl, sizeof(rdone), rdone);
    printf("%i",nErr);
    nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(selectscreenhdl), &selectscreenhdl, sizeof(ss), ss);
    printf("%i",nErr);

    nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(bhdl1), &bhdl1, sizeof(bmp1), bmp1);
    printf("%i",nErr);
    nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(bhdl2), &bhdl2, sizeof(bmp2), bmp2);
    printf("%i",nErr);
    nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(bhdl3), &bhdl3, sizeof(bmp3), bmp3);
    printf("%i",nErr);
    nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(bhdl4), &bhdl4, sizeof(bmp4), bmp4);
    printf("%i",nErr);
    nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(bhdl5), &bhdl5, sizeof(bmp5), bmp5);
    printf("%i",nErr);
    nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(bhdl6), &bhdl6, sizeof(bmp6), bmp6);
    printf("%i",nErr);
    nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(bhdl7), &bhdl7, sizeof(bmp7), bmp7);
    printf("%i",nErr);
    nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(bhdl8), &bhdl8, sizeof(bmp8), bmp8);
    printf("%i",nErr);
    nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(bhdl9), &bhdl9, sizeof(bmp9), bmp9);
    printf("%i",nErr);





              // Specify attributes of the notification
              adsNotificationAttrib.cbLength = sizeof(true_desu);
              adsNotificationAttrib.nTransMode = ADSTRANS_SERVERONCHA;
              adsNotificationAttrib.nMaxDelay = 0; // 1ms
              adsNotificationAttrib.nCycleTime = 100000; // 1ms

              adsNotificationAttribselectscreen.cbLength = 2;
              adsNotificationAttribselectscreen.nTransMode = ADSTRANS_SERVERONCHA;
              adsNotificationAttribselectscreen.nMaxDelay = 0; // 1ms
              adsNotificationAttribselectscreen.nCycleTime = 10000; // 1ms


              nErr = AdsSyncAddDeviceNotificationReq(pAddr, ADSIGRP_SYM_VALBYHND, rechdl, &adsNotificationAttrib, recipewrite, 0, &recipewrite_note);
              printf("%i",nErr);
              nErr = AdsSyncAddDeviceNotificationReq(pAddr, ADSIGRP_SYM_VALBYHND, selectscreenhdl, &adsNotificationAttribselectscreen, selectscreen, 0, &selectscreennote);
			  printf("%i",nErr);

			  //block the code

            //Create and run the thread
            recwrite = TRUE;
            initflag = TRUE;
            thread = SDL_CreateThread( my_thread,"my_thread", (NULL) );
            thread = SDL_CreateThread( recipe_thread,"recipe_thread", (NULL) );
			 //getch();
			 while(!q)
             {
                 SDL_Delay(1000);
             }
			 q = TRUE;

			 SDL_WaitThread(thread, NULL);
			 SDL_WaitThread(thread2, NULL);


              // Stop notification
              nErr = AdsSyncDelDeviceNotificationReq(pAddr, recipewrite_note);
              nErr = AdsSyncDelDeviceNotificationReq(pAddr, selectscreennote);

			  //relese handle
			  nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(rechdl), &rechdl);
			  nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(bitdonehdl), &bitdonehdl);
			  nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(repdonehdl), &repdonehdl);
			  nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(selectscreenhdl), &selectscreenhdl);

            nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(bhdl1), &bhdl1);
            nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(bhdl2), &bhdl2);
            nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(bhdl3), &bhdl3);
            nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(bhdl4), &bhdl4);
            nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(bhdl5), &bhdl5);
            nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(bhdl6), &bhdl6);
            nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(bhdl7), &bhdl7);
            nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(bhdl8), &bhdl8);
            nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(bhdl9), &bhdl9);




              // Close communication port
              nErr = AdsPortClose();



    SDL_DestroyTexture(*bmpTexOptARRAY[0]);
    SDL_DestroyTexture(*bmpTexOptARRAY[1]);
    SDL_DestroyTexture(*bmpTexOptARRAY[2]);
    SDL_DestroyTexture(*bmpTexOptARRAY[3]);
    SDL_DestroyTexture(*bmpTexOptARRAY[4]);
    SDL_DestroyTexture(*bmpTexOptARRAY[5]);
    SDL_DestroyTexture(*bmpTexOptARRAY[6]);
    SDL_DestroyTexture(*bmpTexOptARRAY[7]);
    SDL_DestroyTexture(*bmpTexOptARRAY[8]);
    SDL_DestroyTexture(*bmpTexOptARRAY[9]);


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
    SDL_Event e;
    SDL_Rect secondscreen;
    SDL_GetDisplayBounds(displayno,&secondscreen);
    win = SDL_CreateWindow("Projector", secondscreen.x, secondscreen.y, NULL, NULL, SDL_WINDOW_MAXIMIZED|SDL_WINDOW_BORDERLESS|SDL_WINDOW_ALLOW_HIGHDPI);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderPresent(renderer);

    while( !q )
    {
        SDL_Delay(1);
        while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						q = TRUE;
					}
					else if( e.type == SDL_KEYDOWN )
                    {
                        if( e.key.keysym.sym == SDLK_q)
                        {
                            q = TRUE;
                        }
                    }
				}


        if(showbitmap)
        {
           showbitmap = FALSE;


            if(!initflag)
            {
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, *bmpTexOptARRAY[index] , NULL, NULL);
                SDL_RenderPresent(renderer);
                nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, bitdonehdl,1, &true_desu);
            }


        }
    }

    return 0;
}

int recipe_thread( void *data )
{
    while(!q){
            SDL_Delay(1);
        if(recwrite)
        {
            if(!initflag)
            {


                printf("\nPath Read Status\n");
                if(bhdl1 != NULL && bhdl1 != 0)
                {
                nErr = AdsSyncReadReq(pAddr,ADSIGRP_SYM_VALBYHND,bhdl1,sizeof(pbmp1),pbmp1);
                printf("%i",nErr);
                }

                if(bhdl2 != NULL && bhdl2 != 0)
                {
                nErr = AdsSyncReadReq(pAddr,ADSIGRP_SYM_VALBYHND,bhdl2,sizeof(pbmp2),pbmp2);
                printf("%i",nErr);
                }

                if(bhdl3 != NULL && bhdl3 != 0)
                {
                nErr = AdsSyncReadReq(pAddr,ADSIGRP_SYM_VALBYHND,bhdl3,sizeof(pbmp3),pbmp3);
                printf("%i",nErr);
                }

                if(bhdl4 != NULL && bhdl4 != 0)
                {
                nErr = AdsSyncReadReq(pAddr,ADSIGRP_SYM_VALBYHND,bhdl4,sizeof(pbmp4),pbmp4);
                printf("%i",nErr);
                }

                if(bhdl5 != NULL && bhdl5 != 0)
                {
                nErr = AdsSyncReadReq(pAddr,ADSIGRP_SYM_VALBYHND,bhdl5,sizeof(pbmp5),pbmp5);
                printf("%i",nErr);
                }

                if(bhdl6 != NULL && bhdl6 != 0)
                {
                nErr = AdsSyncReadReq(pAddr,ADSIGRP_SYM_VALBYHND,bhdl6,sizeof(pbmp6),pbmp6);
                printf("%i",nErr);
                }

                if(bhdl7 != NULL && bhdl7 != 0)
                {
                nErr = AdsSyncReadReq(pAddr,ADSIGRP_SYM_VALBYHND,bhdl7,sizeof(pbmp7),pbmp7);
                printf("%i",nErr);
                }

                if(bhdl8 != NULL && bhdl8 != 0)
                {
                nErr = AdsSyncReadReq(pAddr,ADSIGRP_SYM_VALBYHND,bhdl8,sizeof(pbmp8),pbmp8);
                printf("%i",nErr);
                }

                if(bhdl9 != NULL && bhdl9 != 0)
                {
                nErr = AdsSyncReadReq(pAddr,ADSIGRP_SYM_VALBYHND,bhdl9,sizeof(pbmp9),pbmp9);
                printf("%i",nErr);
                }

            }

            if(initflag)
            {
                SDL_Delay(3000);
            }

                bmpSurface = SDL_LoadBMP(pbmp1);
                *bmpTexOptARRAY[1]  = SDL_CreateTextureFromSurface(renderer, bmpSurface);
                bmpSurface = SDL_LoadBMP(pbmp2);
                *bmpTexOptARRAY[2]  = SDL_CreateTextureFromSurface(renderer, bmpSurface);
                bmpSurface = SDL_LoadBMP(pbmp3);
                *bmpTexOptARRAY[3]  = SDL_CreateTextureFromSurface(renderer, bmpSurface);
                bmpSurface = SDL_LoadBMP(pbmp4);
                *bmpTexOptARRAY[4]  = SDL_CreateTextureFromSurface(renderer, bmpSurface);
                bmpSurface = SDL_LoadBMP(pbmp5);
                *bmpTexOptARRAY[5]  = SDL_CreateTextureFromSurface(renderer, bmpSurface);
                bmpSurface = SDL_LoadBMP(pbmp6);
                *bmpTexOptARRAY[6]  = SDL_CreateTextureFromSurface(renderer, bmpSurface);
                bmpSurface = SDL_LoadBMP(pbmp7);
                *bmpTexOptARRAY[7]  = SDL_CreateTextureFromSurface(renderer, bmpSurface);
                bmpSurface = SDL_LoadBMP(pbmp8);
                *bmpTexOptARRAY[8]  = SDL_CreateTextureFromSurface(renderer, bmpSurface);
                bmpSurface = SDL_LoadBMP(pbmp9);
                *bmpTexOptARRAY[9]  = SDL_CreateTextureFromSurface(renderer, bmpSurface);
                SDL_FreeSurface(bmpSurface);

                if(initflag)
                {
                   printf("\nInit Done\n");
                   printf("\nPress any key to close\n");
                   initflag = FALSE;
                }
                else
                {
                    nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, repdonehdl,1, &true_desu);
                }
                recwrite = FALSE;
        }

    }
}


void __stdcall recipewrite(AmsAddr* pAddr, AdsNotificationHeader* pNotification, ULONG hUser)
{

if((*(boolean *)pNotification->data) == TRUE)
{
    recwrite = TRUE;
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

// Callback function
void __stdcall selectscreen(AmsAddr* pAddr, AdsNotificationHeader* pNotification, ULONG hUser)
{

index = (*(int *)pNotification->data);
if(index == 6464)
{
    index = 0;
    q = TRUE;
}
else if(index > 9 || index < 0)
{
    index = 0;
}
showbitmap = TRUE;

}
