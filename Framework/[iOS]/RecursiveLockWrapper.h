//
//  RecursiveLockWrapper.h
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/1/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface RecursiveLockWrapper : NSObject
//@property (nonatomic, strong) NSRecursiveLock *lock;
@property (nonatomic, strong) NSLock *lock;

@end
