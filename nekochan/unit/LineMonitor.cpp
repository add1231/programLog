/******************************************************************************
 *  LineMonitor.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Definition of the Class LineMonitor
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "LineMonitor.h"

// 定数宣言
const int8_t LineMonitor::INITIAL_THRESHOLD = 20;  // 黒色の光センサ値
//const uint16_t LineMonitor::INITIAL_CHROMA = 85;
rgb_raw_t RGB;
//uint16_t RED;
//uint16_t GREEN;
//uint16_t BLUE;
/*const int8_t LineMonitor::INITIAL_BLUE_R;
const int8_t LineMonitor::INITIAL_BLUE_G;
const int8_t LineMonitor::INITIAL_BLUE_B;
const int8_t LineMonitor::INITIAL_YELLOW;
*/
/**
 * コンストラクタ
 * @param colorSensor カラーセンサ
 */
LineMonitor::LineMonitor(const ev3api::ColorSensor& colorSensor)
    : mColorSensor(colorSensor),
      mThreshold(INITIAL_THRESHOLD)
      /*mChroma(INITIAL_CHROMA)*/ {
}

/**
 * ライン上か否かを判定する
 * @retval true  ライン上
 * @retval false ライン外
 */
void LineMonitor::suzuki(uint16_t rgb[3]) const {
    // 光センサからの取得値を見て
    // 黒以上であれば「true」を、
    // そうでなければ「false」を返す
    /*if (mColorSensor.getBrightness() >= mThreshold) {
        return true;
    } else {
        return false;
    }*/
    mColorSensor.getRawColor(RGB);
    rgb[0] = RGB.r;
    rgb[1] = RGB.g;
    rgb[2] = RGB.b;
}

/**
 * ライン閾値を設定する
 * @param threshold ライン閾値
 * @param chroma 彩度閾値
 */
void LineMonitor::setThreshold(int8_t threshold /*uint16_t chroma*/) {
    mThreshold = threshold;
    //mChroma  = chroma;

}
