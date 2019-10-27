//
//  RecursiveLockWrapper.h
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/1/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include <Foundation/Foundation.h>

@interface RecursiveLockWrapper : NSObject
@property (nonatomic, strong) NSRecursiveLock *lock;
//@property (nonatomic, strong) NSLock *lock;



//@property (nonatomic, strong) dispatch_semaphore_t semaphore;


@end
