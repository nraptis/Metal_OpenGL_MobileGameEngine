//
//  PhongConfiguration.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 2/27/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef PhongConfiguration_hpp
#define PhongConfiguration_hpp

#include "FUniforms.hpp"

class PhongConfiguration {
public:
    PhongConfiguration();
    ~PhongConfiguration();
    
    void                                Print();
    
    void                                Compute();
    
    FUniformsLightPhong                 mUniform;
    
    float                               mDirectionRotationPrimary;
    float                               mDirectionRotationSecondary;
};

#endif /* PhongConfiguration_hpp */
