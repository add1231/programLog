/******************************************************************************
 *  Walker.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Implementation of the Class Walker
 *  Author: Kazuhiro.Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "Walker.h"
#include <stdio.h>
#include "etroboc_ext.h"
/*#include "iostream"
using namespace std; */




// 定数宣言
const int Walker::LOW = 30;
const int Walker::NORMAL = 50;    // 通常
const int Walker::HIGH   = 78;    // 高速
//static FILE *bt = NULL;
const int Walker::RIGHT  = 0;     // 左方向
const int Walker::LEFT   = 1;     // 右方向
//PID制御用の定数宣言
#define KP 0.7222
#define KI 0.0044
#define KD 0.7311
#define GKP 0.344 
#define GKI 0.003
#define GKD 0.01
//#define LIGHT_WHITE 40
//#define LIGHT_BLACK 20
#define SAIDO 92

// コース選択
// Lコース:0, Rコース:1
#define COURSE 0

//自作変数宣言（偏差とかに使うやつ）
static int b_diff = 0;
static int a_diff = 0;
static int ref = 0;
static int integral = 0;
static double MI;
static double MP;
static double MD;
//static double target = (LIGHT_BLACK + LIGHT_WHITE) / 2;
static double p;
static int32_t RM = 0;
static int32_t LM = 0;
static int SCENARIO = 0;
static int sa = 0;
static int LRM;
static int LLM;

static int PWMs[2];

int count = 0;
//int countA = 0;
//const int TE = 18060;
//const int STOP = 18900;


/**
 * コンストラクタ
 * @param leftWheel  左モータ
 * @param rightWheel 右モータ
 */
Walker::Walker(ev3api::Motor& leftWheel,
                                 ev3api::Motor& rightWheel)
    : mLeftWheel(leftWheel),
      mRightWheel(rightWheel),
      mForward(HIGH),
      mTurn(RIGHT) {
        /*bt = ev3_serial_open_file(EV3_SERIAL_BT);
        assert(bt != NULL);
        f*/ 
}

/**
 * 走行する
 */
void Walker::run() {
    // 左右モータに回転を指示する
    int rightPWM = 0;
    int leftPWM = 0;
    switch (SCENARIO) {
        case 0:
            a_diff = SAIDO - mRGBMAX;
            if (mBflag >=1 && mTurn == LEFT) {
                a_diff = SAIDO - (mRGBMAX - 60);
            } 
            if(a_diff < 0.0){
                a_diff = -1* a_diff;
                //なんかごくまれに符号チェックミスがあるからもし初動で不穏な動きがあればここを修正すること。
            }
            ref = b_diff - a_diff;
            if(count == 40){ //I制御の累積値を一定周期でリセットする（しないと死）
                integral =0;
                count = 0;
            }
            integral = integral + a_diff / 2 * 0.004;
            b_diff = a_diff;
            if(mBflag == 0) { //ゴール前までの高速状態でのPID制御
                MP = KP * a_diff;
                MI = KI * integral;
                MD = KD * ref;
                p =MP + MI - MD;
                if(mTurn == RIGHT) {
                    rightPWM = HIGH;
                    leftPWM = HIGH - p;
                } else if(mTurn == LEFT) {
                    rightPWM = HIGH - p;
                    leftPWM = HIGH;
                }else {
                    rightPWM =0;
                    leftPWM =0;
                }
            }
            else if(mBflag >= 1){ //ゴール後の低速状態でのPID制御、理由はreadmeにでも書いておく
                
                MP = GKP * (a_diff);
                MI = GKI * integral;
                MD = GKD * ref;
                p =MP + MI - MD;
                if(mTurn == RIGHT) {
                    rightPWM = LOW ;
                    leftPWM = LOW - p;
                } else if(mTurn == LEFT) {
                    rightPWM = LOW - p;
                    leftPWM = LOW ;
                }else {
                    rightPWM =0;
                    leftPWM =0;
                }
                if(mBflag >= 2){//青の検出回数で制御
                    rightPWM =0;
                    leftPWM =0;
                    SCENARIO = 1;
                    RM = mRightWheel.getCount();
                    LM = mLeftWheel.getCount();
                    
                    //ETRoboc_notifyCompletedToSimulator();
                }
            }
            /*if(countA == 4) {
                f
                countA =0;
            }*/
            mForward =p;
            break;
        case 1:
            RM = mRightWheel.getCount();
            LM = mLeftWheel.getCount();
            
            if(RM < 16600 && LM < 16600) {
                if (mYflag ==0){
                    if(mTurn == LEFT){
                        rightPWM = 10;
                        leftPWM = 20;
                    }
                    if(mTurn ==RIGHT){
                        rightPWM = 20;
                        leftPWM = 10;
                    }
                }else if(mYflag ==1) {
                    if(RM >= LM-3 && RM <= LM+3){
                        rightPWM =0;
                        leftPWM =5;
                    }
                    if(LM >=RM-3 && LM <= RM+3) {
                        rightPWM =0;
                        leftPWM =5;
                    }else{ 
                        rightPWM=20;
                        leftPWM=20;
                        LLM = LM;
                        LRM = RM;
                    }
                }
                
            }else{
                ETRoboc_notifyCompletedToSimulator();
            }
            break;
            
    }
    //a_diff = target - mBright;
            if(COURSE == 0)
            {
                PWMs[0] = rightPWM;
                PWMs[1] = leftPWM;
            }
            else
            {
                PWMs[0] = leftPWM;
                PWMs[1] = rightPWM;
            }
    
    mRightWheel.setPWM(PWMs[0]);
    mLeftWheel.setPWM(PWMs[1]);
    count++;
    //countA++;
}

/**
 * 走行に必要なものをリセットする
 */
void Walker::init() {
    // モータをリセットする
    mLeftWheel.reset();
    mRightWheel.reset();
}

/**
 * PWM値を設定する
 * @param forward 前進値
 * @param turn    旋回方向
 */
void Walker::setCommand(int RGBMAX, int turn ,int Bflag, int Yflag) {
    mRGBMAX = RGBMAX;
    mTurn    = turn;
    mBflag = Bflag; 
    mYflag = Yflag;
}
