//
//  LiquidMBackfillingAdapter.h
//  LiquidM-iOS-SDK
//
//  Created by Conrad Calmez on 10/11/13.
//  Copyright (c) 2013 LiquidM. All rights reserved.
//

#ifndef LiquidM_iOS_SDK_LiquidMBackfillingAdapter_h
#define LiquidM_iOS_SDK_LiquidMBackfillingAdapter_h

#import <UIKit/UIKit.h>

/*!
 @discussion This class provides a protocol that can be used to incorporate
 the functionality of having backfilling with another ad network via its SDK.
 Backfilling is invoked when a LiquidM ad could not be served.
 */

@protocol LiquidMBackfillingAdapter;

@protocol LiquidMBackfillingAdapterDelegate <NSObject>

@optional

/*!
 @name Loading
 */

/*!
 @abstract Method called when the loading of the ad is finished.
 */
- (void)adapterDidReceiveAd:(id<LiquidMBackfillingAdapter>)adapter;

/*!
 @abstract Method called when the loading of the ad failed.
 */
- (void)adapter:(id<LiquidMBackfillingAdapter>)adapter
        didFailToReceiveAdWithError:(NSError*)error;

/*!
 @name Presentation
 */

/*!
 @abstract Method called just before the ad's view will appear on screen.
 */
- (void)adapterWillPresentAd:(id<LiquidMBackfillingAdapter>)adapter;

/*!
 @abstract Method called after the ad's view appeared on screen.
 */
- (void)adapterDidPresentAd:(id<LiquidMBackfillingAdapter>)adapter;

/*!
 @abstract Method called just before the ad's view will disappear from screen.
 */
- (void)adapterWillDismissAd:(id<LiquidMBackfillingAdapter>)adapter;

/*!
 @abstract Method called after the ad's view disappeared from screen.
 */
- (void)adapterDidDismissAd:(id<LiquidMBackfillingAdapter>)adapter;

@end

@protocol LiquidMBackfillingAdapter <NSObject>

@required

/*!
 @abstract Delegate object that should be informed about load and display
 related events produced by the backfilling adapter.
 */
@property (nonatomic, weak) id<LiquidMBackfillingAdapterDelegate> delegate;

/*!
 @name Loading
 */

/*!
 @abstract The tag used to lookup a certain token in the adapters token 
 dictionary configured in the app's plist.
 */
@property (nonatomic, copy) NSString *tokenTag;

/*!
 @abstract Initialization and loading of a banner ad
 
 @discussion The `token` property needs to be initiated on a plist dictionary called 
 AdMobBackfillingIDs with its tag as a key and the token itself as a value.
 
 @param size The size of the ad that matches the sizes established by Google AdMob.
 @param token The token tag that contains the value of the AdUnitID.

 */
- (void)loadBannerWithSize:(CGSize)size;

/*!
 @abstract Initialization and loading of an interstitial ad
 
 @discussion The passed `token` can be loaded via 
 
 @param token The token tag that contains the value of the AdUnitID.
 
 */
- (void)loadInterstitial;

/*!
 @name Presentation
 */

/*!
 @abstract Contains the banner view if it is loaded.
 */
@property (nonatomic, readonly) UIView *adView;

/*!
 @abstract If the banner is not loaded yet this method can be used to defer the
 displaying of the banner.

 @param readyAction A block that gets the banner view to add so that it gets
 displayed on screen.
 */
- (void)showBannerWhenReady:(void (^)(UIView *))readyAction;

/*!
 @abstract Method used to present the interstitial view on a selected view 
 controller.
 
 @discussion This method presents the interstitial as soon as it is loaded.
 
 @param vc The view controller that will present the adView.
 */
- (void)presentInterstitialOnViewController:(UIViewController *)vc;

@end

#endif
