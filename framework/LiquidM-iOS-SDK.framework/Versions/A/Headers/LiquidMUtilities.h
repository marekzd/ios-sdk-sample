// Copyright 2012 LiquidM GmbH
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#import <Foundation/Foundation.h>
#import <sys/types.h>
#import <sys/socket.h>
#import <ifaddrs.h>
#import <netinet/in.h>
#import <CommonCrypto/CommonDigest.h>
#import <CommonCrypto/CommonHMAC.h>
#import <UIKit/UIKit.h>
#import <UIKit/UIDevice.h>
#include <sys/sysctl.h>
#include <net/if.h>
#include <net/if_dl.h>
#import <AdSupport/AdSupport.h>

#if DEBUG
#define LMLog(format, ...) [LiquidMUtilities logWithPath:__FILE__\
                                                        line:__LINE__\
                                                      string:(format), ## __VA_ARGS__]
#else
#define LMLog(format, ...)
#endif

#define NC [NSNotificationCenter defaultCenter]

#define LIQUIDM_APP_IDS_KEY @"LiquidMAppIDs"
#define LIQUIDM_DEFAULT_TAG @"default"

NSString *UserAgentString(void);

typedef enum tagLiquidMAnimationClass {
    LiquidMAnimationClassLeftToRight,
    LiquidMAnimationClassTopToBottom,
    LiquidMAnimationClassCurlDown,
    LiquidMAnimationClassFade,
    LiquidMAnimationClassNone
} LiquidMAnimationClass;

// enum of available banner formats
typedef enum {
    LiquidMAdClassNone,
    LiquidMAdClassMMA,
    LiquidMAdClassMediumRectangle,
    LiquidMAdClassLeaderboard,
    LiquidMAdClassFullscreen,
    LiquidMAdClassPortrait,
    LiquidMAdClassLandscape,
    LiquidMAdClassRichMedia,
    LiquidMAdClassIphonePreloader,
    LiquidMAdClassIpadPreloader,
    LiquidMAdClassIphonePreloaderLandscape,
    LiquidMAdClassIpadPreloaderPortrait
} LiquidMAdClass;

@interface LiquidMUtilities : NSObject

+ (NSString *)getIP;
+ (NSString *)getMacMD5Hash;
+ (NSString *)getMacSHA1Hash;
+ (NSString *)getTimestamp;
+ (NSString *)getAppName;
+ (NSString *)getAppVersion;
+ (CGSize)getScreenResolution;
+ (NSString *)getDeviceOrientation;
+ (NSString *)getIdentifierForAdvertiser;
+ (NSString *)urlEncodeUsingEncoding:(NSStringEncoding)encoding
                          withString:(NSString *)string;
+ (BOOL)isConnectionAvailable;

+ (void)logWithPath:(char *)path
               line:(NSUInteger)line
             string:(NSString *)format, ...;

/*  convenience methods */
+ (NSString *)liquidMAppID;
+ (NSString *)liquidMAppIDWithTag:(NSString *)tag;

+ (CGSize)liquidMAdClassSize:(LiquidMAdClass)adClass;
+ (NSString *)liquidMAdClassName:(LiquidMAdClass)adClass;

+ (BOOL)isAdSizeFullscreen:(CGSize)adSize;
+ (BOOL)isAdSizeCustom:(CGSize)adSize;
+ (BOOL)isAdSizePreloader:(CGSize)adSize;
+ (BOOL)isAdSizeIABMediumRectangle:(CGSize)adSize;
+ (BOOL)isAdSizeIABLeaderboard:(CGSize)adSize;

+ (NSString *)tokenFromDictionaryNamed:(NSString *)dictName withTag:(NSString *)tag;
+ (NSBundle *)frameworkBundle;
+ (NSString *)templateWithName:(NSString *)templateName;

+ (BOOL)hasRetinaDisplay;

@end

@interface UIWebView (MPAdditions)

- (void)mp_setScrollable:(BOOL)scrollable;

@end
