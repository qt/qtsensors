// Copyright (C) 2016 Lorn Potter
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#ifndef IOSMOTIONMANAGER_H
#define IOSMOTIONMANAGER_H

#import <Foundation/Foundation.h>

@class CMMotionManager;

@interface QIOSMotionManager : NSObject {
}

+ (CMMotionManager *)sharedManager;
@end

#endif //IOSMOTIONMANAGER_H

