/******************************************************************************
 *  LineTracer.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Definition of the Class LineTracer
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef EV3_APP_LINETRACER_H_
#define EV3_APP_LINETRACER_H_

#include "LineMonitor.h"
#include "Walker.h"

class LineTracer {
public:
    LineTracer(const LineMonitor* lineMonitor,
               Walker* walker);

    void run();

private:
    const LineMonitor* mLineMonitor;
    Walker* mWalker;
    bool mIsInitialized;
    //int calcDirection();
    int calcDirection(uint16_t RGBMAX, uint16_t RED, uint16_t GREEN, uint16_t BLUE, int BlueCount[1], int YellowCount[1]);
};

#endif  // EV3_APP_LINETRACER_H_
