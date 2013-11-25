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

@protocol LiquidMBackfillingAdapter;

/*!
 This is the protocol that has to be implemented to set the
 [LiquidMBackfillingAdapter delegate] property.
 */

@protocol LiquidMBackfillingAdapterDelegate <NSObject>

@optional

/*!
 @name Loading
 */

/*!
 @abstract Method called when the loading of the ad is finished.
 
 @param adapter The LiquidMBackfillingAdapter that received an ad
 */
- (void)adapterDidReceiveAd:(id<LiquidMBackfillingAdapter>)adapter;

/*!
 @abstract Method called when the loading of the ad failed.
 
 @param adapter The LiquidMBackfillingAdapter that failed to receive an ad
 
 @param error The error that occured when loading an ad
 */
- (void)adapter:(id<LiquidMBackfillingAdapter>)adapter
        didFailToReceiveAdWithError:(NSError*)error;

/*!
 @name Presentation
 */

/*!
 @abstract Method called just before the ad's view will appear on screen.
 
 @param adapter The LiquidMBackfillingAdapter that will present an ad
 */
- (void)adapterWillPresentAd:(id<LiquidMBackfillingAdapter>)adapter;

/*!
 @abstract Method called after the ad's view appeared on screen.
 
 @param adapter The LiquidMBackfillingAdapter that did present an ad
 */
- (void)adapterDidPresentAd:(id<LiquidMBackfillingAdapter>)adapter;

/*!
 @abstract Method called just before the ad's view will disappear from screen.
 
 @param adapter The LiquidMBackfillingAdapter that will dismiss an ad
 */
- (void)adapterWillDismissAd:(id<LiquidMBackfillingAdapter>)adapter;

/*!
 @abstract Method called after the ad's view disappeared from screen.
 
 @param adapter The LiquidMBackfillingAdapter that did dismiss an ad
 */
- (void)adapterDidDismissAd:(id<LiquidMBackfillingAdapter>)adapter;

@end

/*!
 This protocol provides an interface that is needed to create an adapter for
 backfilling via another network's SDK. Backfilling is triggered when a LiquidM
 ad could not be served.
 */

@protocol LiquidMBackfillingAdapter <NSObject>

@required

/*!
 @abstract The object that should be informed about load and display related 
 events produced by the backfilling adapter.
 
 @see LiquidMBackfillingAdapterDelegate
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

 @param size The size of the ad to request
 
 @discussion This method will use the tokenTag to lookup a query key for loading
 an ad from the corresponding network.
 
 The requested size will match the size that was set in the
 LiquidMAdViewController
 */
- (void)loadBannerWithSize:(CGSize)size;

/*!
 @abstract Initialization and loading of an interstitial ad

 @discussion This method will use the tokenTag to lookup a query key for loading
 an ad from the corresponding network.
 */
- (void)loadInterstitial;

/*!
 @name Presentation
 */

/*!
 @abstract Contains the banner view
 
 @discussion The banner view is only present if loaded, otherwise this property
 should be `nil`.
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

 @param vc The view controller that will present the adView.

 @discussion This method presents the interstitial as soon as it is loaded.
 */
- (void)presentInterstitialOnViewController:(UIViewController *)vc;

@end

#endif
