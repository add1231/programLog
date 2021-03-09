/******************************************************************************
 *  LineTracer.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/26
 *  Implementation of the Class LineTracer
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "LineTracer.h"
#include <stdio.h>

uint16_t RED;
uint16_t GREEN;
uint16_t BLUE;
uint16_t RGBMAX;
uint16_t rgb[3];
int BlueCount[1]= {0};
int YellowCount[1] = {0};
int B = 0 ;
int Y = 0 ;
int countt=0;
/**
 * コンストラクタ
 * @param lineMonitor     ライン判定
 * @param walker 走行
 */
LineTracer::LineTracer(const LineMonitor* lineMonitor,
                       Walker* walker)
    : mLineMonitor(lineMonitor),
      mWalker(walker),
      mIsInitialized(false) {
}

/**
 * ライントレースする
 */
void LineTracer::run() {
    if (mIsInitialized == false) {
        mWalker->init();
        mIsInitialized = true;
    }
    mLineMonitor->suzuki(rgb);
    RED = rgb[0];
    GREEN = rgb[1];
    BLUE = rgb[2];
    RGBMAX = RED;
    if(RGBMAX < GREEN) RGBMAX = GREEN;
    if(RGBMAX < BLUE) RGBMAX = BLUE;
    //printf("%d,%d,%d\r\n",RED, GREEN,BLUE);

    // 走行体の向きを計算する
    int direction = calcDirection(RGBMAX, RED, GREEN, BLUE, BlueCount, YellowCount);

    B = BlueCount[0];
    Y = YellowCount[0];

    mWalker->setCommand(RGBMAX, direction, B, Y);

    // 走行を行う
    mWalker->run();
}

/**
 * 走行体の向きを計算する
 * @param isOnLine true:ライン上/false:ライン外
 * @retval RIGHT  ライン上にある場合(右旋回指示)
 * @retval LEFT ライン外にある場合(左旋回指示)
 */
int LineTracer::calcDirection(uint16_t RGBMAX, uint16_t RED, uint16_t GREEN, uint16_t BLUE, int BlueCount[1], int YellowCount[1]) {
    if(BLUE <= 30 && GREEN >=100 && RED >= 60) {
        YellowCount[0] = {1};
        printf("change mode Yellow\r\n");
    }else if (BLUE >= 100 && RED <= 30) {
        if(countt == 0 || countt == 60) {
           BlueCount[0] = BlueCount[0] + 1; 
           if(BlueCount[0]==1) printf("change mode BLUE:%d\r\n",BLUE);
        }
        //printf("B100-%d\r",countt);
        countt++;
        return Walker::LEFT;
    }else if (RGBMAX >= 92) {
        return Walker::RIGHT;
    } else {
        return Walker::LEFT;
    }
}
