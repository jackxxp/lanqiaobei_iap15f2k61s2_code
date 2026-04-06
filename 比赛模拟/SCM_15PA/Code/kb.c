#include "kb.h"

extern bdata unsigned char flag;

static unsigned char keyValue = 255;
//
static void clsC(void) { P42 = 0; P44 = 0; P32 = 1; P33 = 1;}
static void clsR(void) { P42 = 1; P44 = 1; P32 = 0; P33 = 0;}

unsigned char keyGet(void) {return keyValue;}
void keySet(unsigned char value) {keyValue = value;}

//
void keyScan(void)
{
    static unsigned char keyStatus = 0;
    static unsigned char col = 0;

    //KeyScan
    if ((flag & 0x01) == 0)
        return;
    flag &= ~0x01;

    switch(keyStatus)
    {
        case 0:
            clsR();
            if((P42 == 0) || (P44 == 0)){
                keyStatus = 1;
            }
            break;
        case 1:
            clsR();
            if(P44 == 0){
                col = 1;
                keyStatus = 2;
            }else if(P42 == 0){
                col = 2;
                keyStatus = 2;
            }else{
                keyStatus = 0;
            }
            break;
        case 2:
            clsC();
            keyStatus = 3;
            if((P32 == 0) && (col == 1)){
                keyValue = 5; 
            }else if((P33 == 0) && (col == 1)){
                keyValue = 4;
            }else if((P32 == 0) && (col == 2)){
                keyValue = 9;
            }else if((P33 == 0) && (col == 2)){
                keyValue = 8;
            }else{
                keyStatus = 0;
                col = 0;
            }
            break;
        case 3:
            clsC();
            if((P32 == 1) && (P33 == 1)){
                keyStatus = 0;
            }
            break;

    }
}
