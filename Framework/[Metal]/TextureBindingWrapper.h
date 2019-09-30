//
//  TextureBindingWrapper.h
//
//  Created by Nicholas Raptis on 1/22/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/Metal.h>

@interface TextureBindingWrapper : NSObject
@property (nonatomic, strong) id <MTLTexture> texture;
@end
