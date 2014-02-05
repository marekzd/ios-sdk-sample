//
//  LiquidMParentViewController.h
//  LiquidM-iOS-SDK
//
//  Created by Khaterine Castellano on 12/12/13.
//  Copyright (c) 2013 LiquidM. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>

#import "LiquidMAdClasses.h"

@class LiquidMAbstractController;

/*!
 This protocol gathers general definitions for LiquidM ad controller's
 delegates.
 */
@protocol LiquidMAbstractControllerDelegate <NSObject>

/*!
 @name Loading
 */

@required

/*!
 @abstract Method called when the loading of the ad is finished.
 
 @param controller The LiquidMAbstractController that received the ad
 */
- (void)controllerDidReceiveAd:(LiquidMAbstractController *)controller;

/*!
 @abstract Method called when the loading of the ad failed.
 
 @param controller The LiquidMAbstractController that failed to receive the ad
 
 @param error The error that occured when loading an ad
 */
- (void)controller:(LiquidMAbstractController *)controller
        didFailToReceiveAdWithError:(NSError*)error;

@end

/*!
 This controller gathers general behavior of LiquidM ad controllers.
 */
@interface LiquidMAbstractController : UIViewController

/*!
 @abstract Ad class used for the ads to load and display an ad.
 
 @discussion It can have one of the values listed in the ad class table in the
 overview section. Setting this property implies the related ad size.
 
 @warning For banner ads this property is discouraged in favor of
 [LiquidMAdViewController adSize].
 
 @see [LiquidMAdViewController adSize]
 */
@property (nonatomic) LiquidMAdClass currentAdClass;

/*!
 @abstract The actual token that is used to load an ad.
 
 @discussion If you leave this property untouched the SDK will try to load a
 token dictionary from the app's plist file. On the other hand if you set it the
 token you provided will be used directly for ad loading.
 You should choose to either use tokenTag or token for choosing a token for ad
 loading.
 
 @see tokenTag
 */
@property (nonatomic, copy) NSString *token;

/*!
 @abstract The tag that is being used to search for an app token in the app's
 plist file.
 
 @discussion App tokens should be added to the plist file in a dictionary called
 `LiquidMAppIDs` with its tag as a key and the token itself as a value. For
 testing purposes you should at least add the "default" tag's token to properly
 load an ad.
 */
@property (nonatomic, copy) NSString *tokenTag;

/*!
 @abstract The location that is used for location based ads.
 
 @discussion If the location gets not set it will not be used for the ad
 request. It can be set on creation of a banner controller via the
 `LiquidMControllerOptionLocation` option.
 
 @see [LiquidMAdViewController controllerWithRootViewController:adSize:options:]
 */
@property (nonatomic, copy) CLLocation *location;

/*!
 @name Keyword Management
 */

/*!
 @abstract Returns all currently set keywords used for ad loading.
 */
@property (nonatomic, readonly) NSArray *keywords;

/*!
 @abstract Adds a keyword to the list of keywords.
 
 @param keyword The keyword to add
 */
- (void)addKeyword:(NSString *)keyword;

/*!
 @abstract Adds all keywords of an array to the list of keywords.
 
 @param keywords An array of keywords to add
 */
- (void)addKeywords:(NSArray *)keywords;

/*!
 @abstract Removes a keyword from the list of keywords.
 
 @param keyword The keyword to remove
 */
- (void)removeKeyword:(NSString *)keyword;

/*!
 @abstract Removes all keywords of an array from the list of keywords.
 
 @param keywords An array of keywords to remove
 */
- (void)removeKeywords:(NSArray *)keywords;

/*!
 @abstract Empties the list of keywords.
 */
- (void)removeAllKeywords;


@end
