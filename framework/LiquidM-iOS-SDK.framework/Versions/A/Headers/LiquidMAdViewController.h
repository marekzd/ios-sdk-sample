//
//  LiquidMAdViewController.h
//  LiquidM-iOS-SDK
//
//  Created by Conrad Calmez on 9/17/13.
//  Copyright (c) 2013 LiquidM. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <EventKitUI/EventKitUI.h>
#import "LiquidMBackfillingAdapter.h"
#import "LiquidMUtilities.h"

@class LiquidMAdViewController;

@protocol LiquidMAdViewControllerDelegate <NSObject>

/*!
 @name Loading
 */

@required

/*!
 @abstract Method called when the loading of the ad is finished.
 */
- (void)controllerDidReceiveAd:(LiquidMAdViewController *)controller;

/*!
 @abstract Method called when the loading of the ad failed.
 */
- (void)controller:(LiquidMAdViewController *)controller
        didFailedToReceiveAdWithError:(NSError*)error;

/*!
 @name Presentation
 */

@optional

/*!
 @abstract Method called just before the ad's view will appear on screen.
 */
- (void)controllerWillPresentAd:(LiquidMAdViewController *)controller;

/*!
 @abstract Method called after the ad's view appeared on screen.
 */
- (void)controllerDidPresentAd:(LiquidMAdViewController *)controller;

/*!
 @abstract Method called just before the ad's view will disappear from screen.
 */
- (void)controllerWillDismissAd:(LiquidMAdViewController *)controller;

/*!
 @abstract Method called after the ad's view disappeared from screen.
 */
- (void)controllerDidDismissAd:(LiquidMAdViewController *)controller;

@end

/*!
 @discussion This class provides an easy approach for integrating LiquidM ads into an
 iOS application. It's interface is intentionally kept simple to faciliate the
 integration.

 For a basic integration all it needs is just a UIViewController and a
 LiquidMAdClass to run. For further integration instructions please consult
 the integration tutorial.
 */
@interface LiquidMAdViewController : UIViewController
{

}

/*!
 @name Initialization
 */


/*!
 @name Serve by Ad Class
 */

/*!
 @abstract Convenience initializer which works just like
 `controllerWithRootViewController:adClass:options:`

 @discussion The token tag property will be initialized with the "default" tag.

 @param rvc the UIViewController that is used to present the ad and all its
 additional features.
 @param adClass A legacy ad class that determines the size of the placement.
 Possible values are:

 * MadvertiseAdClassMMA – 320 x 53
 * MadvertiseAdClassMediumRectangle – 300 x 250
 * MadvertiseAdClassLeaderboard – 728 x 90
 * MadvertiseAdClassFullscreen – 768 x 768
 * MadvertiseAdClassPortrait – 766 x 66
 * MadvertiseAdClassLandscape – 1024 x 66
 * MadvertiseAdClassRichMedia – 320 x 480
 * MadvertiseAdClassIphonePreloader – 320 x 460
 * MadvertiseAdClassIpadPreloader – 1024 x 748
 * MadvertiseAdClassIphonePreloaderLandscape – 480 x 300
 * MadvertiseAdClassIpadPreloaderPortrait – 768 x 1004

 @return a fully initialized instance of a LiquidMAdViewController

 @see controllerWithRootViewController:adClass:options:
 @see currentAdClass
 */
+ (LiquidMAdViewController *)controllerWithRootViewController:(UIViewController *)rvc
                                                      adClass:(LiquidMAdClass)adClass;

#define LiquidMAdViewControllerOptionReload @"reload"
#define LiquidMAdViewControllerOptionTokenTag @"tokenTag"

/*!
 @abstract Displays the ad view on the screen.
 
 @discussion This method should always be called after receiving the ad from the server.
 
 @see didReceiveAd
 */

- (void)presentAd;

/*!
 @abstract Manually reloads the ads.
 */

- (void)reloadAd;


/*!
 @abstract Initializes a LiquidMAdViewController with all needed information.
 
 @param rvc the UIViewController that is used to present the ad and all its
 additional features.
 @param adClass A legacy ad class that determines the size of the placement.
 Possible values are:
 
 * MadvertiseAdClassMMA – 320 x 53
 * MadvertiseAdClassMediumRectangle – 300 x 250
 * MadvertiseAdClassLeaderboard – 728 x 90
 * MadvertiseAdClassFullscreen – 768 x 768
 * MadvertiseAdClassPortrait – 766 x 66
 * MadvertiseAdClassLandscape – 1024 x 66
 * MadvertiseAdClassRichMedia – 320 x 480
 * MadvertiseAdClassIphonePreloader – 320 x 460
 * MadvertiseAdClassIpadPreloader – 1024 x 748
 * MadvertiseAdClassIphonePreloaderLandscape – 480 x 300
 * MadvertiseAdClassIpadPreloaderPortrait – 768 x 1004
 @param options A dictionary that contains optional parameters.
 
 @discussion The options dictionary can contain a key called
 `LiquidMAdViewControllerOptionTokenTag` whose value is the name (as `NSString`)
 of the tag to use to load the token for ad loading (default is `@"default"`),
 and a key called `LiquidMAdViewControllerOptionReload` which should have a
 boolean value that determines the manual reloading of ads (default is `YES`).
 Note that `NSDictionary` can only hold objects. The boolean value has therfore
 to be wrapped in a `NSNumber`.
 */
+ (LiquidMAdViewController *)controllerWithRootViewController:(UIViewController *)rvc
                                                      adClass:(LiquidMAdClass)adClass
                                                     options:(NSDictionary *)optionsDict;

/*!
 @abstract Initializes a LiquidMAdViewController with all needed information.

 @param rvc the UIViewController that is used to present the ad and all its
 additional features.
 @param adClass A legacy ad class that determines the size of the placement.
 Possible values are:

 * MadvertiseAdClassMMA – 320 x 53
 * MadvertiseAdClassMediumRectangle – 300 x 250
 * MadvertiseAdClassLeaderboard – 728 x 90
 * MadvertiseAdClassFullscreen – 768 x 768
 * MadvertiseAdClassPortrait – 766 x 66
 * MadvertiseAdClassLandscape – 1024 x 66
 * MadvertiseAdClassRichMedia – 320 x 480
 * MadvertiseAdClassIphonePreloader – 320 x 460
 * MadvertiseAdClassIpadPreloader – 1024 x 748
 * MadvertiseAdClassIphonePreloaderLandscape – 480 x 300
 * MadvertiseAdClassIpadPreloaderPortrait – 768 x 1004
 @param adapter The adapter used for backfilling.

 @return a fully initialized instance of a LiquidMAdViewController

 @see currentAdClass
 */
+ (LiquidMAdViewController *)controllerWithRootViewController:(UIViewController *)rvc
                                                      adClass:(LiquidMAdClass)adClass
                                           backfillingAdapter:(id<LiquidMBackfillingAdapter>)adapter;


/*!
 @abstract Initializes a MadvertiseAdViewController with all needed information.

 @param rvc the UIViewController that is used to present the ad and all its
 additional features.
 @param adClass A legacy ad class that determines the size of the placement.
 Possible values are:

 * MadvertiseAdClassMMA – 320 x 53
 * MadvertiseAdClassMediumRectangle – 300 x 250
 * MadvertiseAdClassLeaderboard – 728 x 90
 * MadvertiseAdClassFullscreen – 768 x 768
 * MadvertiseAdClassPortrait – 766 x 66
 * MadvertiseAdClassLandscape – 1024 x 66
 * MadvertiseAdClassRichMedia – 320 x 480
 * MadvertiseAdClassIphonePreloader – 320 x 460
 * MadvertiseAdClassIpadPreloader – 1024 x 748
 * MadvertiseAdClassIphonePreloaderLandscape – 480 x 300
 * MadvertiseAdClassIpadPreloaderPortrait – 768 x 1004
 
 @param options A dictionary that contains optional parameters.
 
 @discussion The options dictionary can contain a key called
 `LiquidMAdViewControllerOptionTokenTag` whose value is the name (as `NSString`)
 of the tag to use to load the token for ad loading (default is `@"default"`),
 and a key called `LiquidMAdViewControllerOptionReload` which should have a
 boolean value that determines the manual reloading of ads (default is `YES`).
 Note that `NSDictionary` can only hold objects. The boolean value has therfore
 to be wrapped in a `NSNumber`.

 @return a fully initialized instance of a MadvertiseAdViewController

 @warning This initializer is deprecated. Usage of it is discouraged in favor of
 `initWithRootViewController:adSize:options:`

 */
+ (LiquidMAdViewController *)controllerWithRootViewController:(UIViewController *)rvc
                                                      adClass:(LiquidMAdClass)adClass
                                                      options:(NSDictionary *)optionsDict
                                           backfillingAdapter:(id<LiquidMBackfillingAdapter>)adapter;

/*!
 @name Serve by Dimension
 */

/*!
 @abstract Initializes a MadvertiseAdViewController with all needed information.

 @param rvc the UIViewController that is used to present the ad and all its
 additional features.
 @param adSize The size of the ad to load
 Standard sizes are

 * 320 x 53
 * 300 x 250
 * 728 x 90
 * 768 x 768
 * 766 x 66
 * 1024 x 66
 * 320 x 480
 * 320 x 460
 * 1024 x 748
 * 480 x 300
 * 768 x 1004

 @return a fully initialized instance of a MadvertiseAdViewController
 */
+ (LiquidMAdViewController *)controllerWithRootViewController:(UIViewController *)rvc
                                                       adSize:(CGSize)adSize;

/*!
 @abstract Initializes a MadvertiseAdViewController with all needed information.

 @param rvc the UIViewController that is used to present the ad and all its
 additional features.
 @param adSize The size of the ad to load
 Standard sizes are

 * 320 x 53
 * 300 x 250
 * 728 x 90
 * 768 x 768
 * 766 x 66
 * 1024 x 66
 * 320 x 480
 * 320 x 460
 * 1024 x 748
 * 480 x 300
 * 768 x 1004

 @param options A dictionary that contains optional parameters.
 
 @discussion The options dictionary can contain a key called
 `LiquidMAdViewControllerOptionTokenTag` whose value is the name (as `NSString`)
 of the tag to use to load the token for ad loading (default is `@"default"`),
 and a key called `LiquidMAdViewControllerOptionReload` which should have a
 boolean value that determines the manual reloading of ads (default is `YES`).
 Note that `NSDictionary` can only hold objects. The boolean value has therfore
 to be wrapped in a `NSNumber`.

 @return a fully initialized instance of a MadvertiseAdViewController
 */
+ (LiquidMAdViewController *)controllerWithRootViewController:(UIViewController *)rvc
                                                       adSize:(CGSize)adSize
                                                      options:(NSDictionary *)optionsDict;

/*!
 @abstract Initializes a MadvertiseAdViewController with all needed information.

 @param rvc the UIViewController that is used to present the ad and all its
 additional features.
 @param adSize The size of the ad to load
 Standard sizes are

 * 320 x 53
 * 300 x 250
 * 728 x 90
 * 768 x 768
 * 766 x 66
 * 1024 x 66
 * 320 x 480
 * 320 x 460
 * 1024 x 748
 * 480 x 300
 * 768 x 1004

 @return a fully initialized instance of a MadvertiseAdViewController
 */
+ (LiquidMAdViewController *)controllerWithRootViewController:(UIViewController *)rvc
                                                       adSize:(CGSize)adSize
                                           backfillingAdapter:(id<LiquidMBackfillingAdapter>)adapter;

/*!
 @abstract Initializes a MadvertiseAdViewController with all needed information.

 @param rvc the UIViewController that is used to present the ad and all its
 additional features.
 @param adSize The size of the ad to load
 Standard sizes are

 * 320 x 53
 * 300 x 250
 * 728 x 90
 * 768 x 768
 * 766 x 66
 * 1024 x 66
 * 320 x 480
 * 320 x 460
 * 1024 x 748
 * 480 x 300
 * 768 x 1004
 
 @param options A dictionary that contains optional parameters.
 
 @discussion The options dictionary can contain a key called
 `LiquidMAdViewControllerOptionTokenTag` whose value is the name (as `NSString`)
 of the tag to use to load the token for ad loading (default is `@"default"`),
 and a key called `LiquidMAdViewControllerOptionReload` which should have a
 boolean value that determines the manual reloading of ads (default is `YES`).
 Note that `NSDictionary` can only hold objects. The boolean value has therfore
 to be wrapped in a `NSNumber`.

 @return a fully initialized instance of a MadvertiseAdViewController

 */
+ (LiquidMAdViewController *)controllerWithRootViewController:(UIViewController *)rvc
                                                       adSize:(CGSize)adSize
                                                     options:(NSDictionary *)optionsDict
                                           backfillingAdapter:(id<LiquidMBackfillingAdapter>)adapter;

/*!
 @name Controlling Animations
 */

/*! 
 @abstract The duration length in seconds of the animation between two ads.
 */
@property (nonatomic) double animationDuration;

/*!
 @abstract The type of animation used for the transition between two ads.
 
 @discussion It must must be of the following predefined values:

 * **LiquidMAnimationClassCurlDown** (default): next ad curls down on the old
   one like a turning page
 * **LiquidMAnimationClassLeftToRight**: new ad pushed old one out from the
   left
 * **LiquidMAnimationClassTopToBottom**: new ad pushed old one out from the
   top
 * **LiquidMAnimationClassFade**: new ad fades in while the old ad fades out
 */
@property (nonatomic) LiquidMAnimationClass animationType;

/*!
 @name Controlling Ad Loading
 */

/*!
 @abstract Size of the ad to load
 */
@property (nonatomic) CGSize adSize;


/*!
 @abstract Ad class used for the ads to load and display an ad.
 
 @discussion it can have one of the following values:
 
 * LiquidMAdClassMMA
 * LiquidMAdClassMediumRectangle
 * LiquidMAdClassLeaderboard
 * LiquidMAdClassFullscreen
 * LiquidMAdClassPortrait
 * LiquidMAdClassLandscape
 * LiquidMAdClassRichMedia
 * LiquidMAdClassIphonePreloader
 * LiquidMAdClassIpadPreloader
 * LiquidMAdClassIphonePreloaderLandscape
 * LiquidMAdClassIpadPreloaderPortrait
 */
@property (nonatomic) LiquidMAdClass currentAdClass;

/*!
 @abstract The tag that is being used to search for an app token in the app's
 plist file.

 @discussion App tokens should be added to the plist file in a dictionary called
 `LiquidMAppIDs` with its tag as a key and the token itself as a value. For testing purposes you should 
 at least add the "default" tag's token to properly load an ad.
 */
@property (nonatomic, copy) NSString *tokenTag;

@property (nonatomic, weak) id<LiquidMAdViewControllerDelegate> delegate;

@end
