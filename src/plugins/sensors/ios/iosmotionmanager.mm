// Copyright (C) 2016 Lorn Potter
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#include "iosmotionmanager.h"

#import <CoreMotion/CoreMotion.h>

static CMMotionManager *sharedManager = nil;

@implementation QIOSMotionManager

+ (CMMotionManager *)sharedManager
{
    static dispatch_once_t staticToken;
    dispatch_once(&staticToken, ^{
        sharedManager = [[CMMotionManager alloc] init];
        sharedManager.showsDeviceMovementDisplay = YES;
    });
    return sharedManager;
}

@end
