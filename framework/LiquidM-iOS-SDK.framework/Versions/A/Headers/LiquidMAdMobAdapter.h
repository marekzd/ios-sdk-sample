//
//  LiquidMAdMobAdapter.h
//  LiquidM-iOS-SDK
//
//  Created by Conrad Calmez on 10/11/13.
//  Copyright (c) 2013 LiquidM. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LiquidMBackfillingAdapter.h"

#define ADMOB_AD_UNIT_IDS_KEY @"AdMobBackfillingIDs"

/*!
 @discussion This class implements the `LiquidMBackfillingAdapter` protocol for
 AdMob backfilling in the LiquidM SDK.

 For making ad loading work with the AdMob SDK a dictionary similar to the one
 configured for the LiquidM SDK has to be added to the app's plist file under
 the key `AdMobBackfillingIDs`.
 
 Also the app needs to be linked against the AdMob SDK static library and the
 `-ObjC` flag has to be added to the linker flags.
 */

@interface LiquidMAdMobAdapter : NSObject <LiquidMBackfillingAdapter>

@end
