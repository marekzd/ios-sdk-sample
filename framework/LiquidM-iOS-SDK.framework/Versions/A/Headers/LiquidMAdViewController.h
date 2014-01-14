//
//  LiquidMAdViewController.h
//  LiquidM-iOS-SDK
//
//  Created by Conrad Calmez on 9/17/13.
//  Copyright (c) 2013 LiquidM. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <EventKitUI/EventKitUI.h>
#import "LiquidMAnimationClasses.h"
#import "LiquidMAdClasses.h"
#import "LiquidMAbstractController.h"
#import "LiquidMControllerOptions.h"

@class LiquidMAdViewController;

/*!
 This is the protocol that has to be implemented to set the
 [LiquidMAdViewController delegate] property.
 */

@protocol LiquidMAdViewControllerDelegate <LiquidMAbstractControllerDelegate>

/*!
 @name Presentation
 */

@optional

/*!
 @abstract Method called just before the ad's view will appear on screen.
 
 @param controller The LiquidMAdViewController that will present the ad
 */
- (void)controllerWillPresentAd:(LiquidMAdViewController *)controller;

/*!
 @abstract Method called after the ad's view appeared on screen.
 
 @param controller The LiquidMAdViewController that did present the ad
 */
- (void)controllerDidPresentAd:(LiquidMAdViewController *)controller;

/*!
 @abstract Method called just before the ad's view will disappear from screen.
 
 @param controller The LiquidMAdViewController that will dismiss the ad
 */
- (void)controllerWillDismissAd:(LiquidMAdViewController *)controller;

/*!
 @abstract Method called after the ad's view disappeared from screen.
 
 @param controller The LiquidMAdViewController that did dismiss the ad
 */
- (void)controllerDidDismissAd:(LiquidMAdViewController *)controller;

@end

/*!
 @discussion This class provides an easy approach for integrating LiquidM banner
 ads into an iOS application. It's interface is intentionally kept simple to
 facilitate the integration.

 For a basic integration all it needs is just an UIViewController and a
 LiquidMAdClass / ad size to run. For further integration instructions please
 consult the integration tutorial.

 **Additional Information**
 
 *Ad classes and sizes*: The following table lists all available ad sizes with
 its corresponding sizes. Also the sizes listed correspond to supported standard
 sizes.
 
 | AdClass                                | Size       |
 | -------------------------------------- | ---------- |
 | LiquidMAdClassMMA                      | 320 x 53   |
 | LiquidMAdClassMediumRectangle          | 300 x 250  |
 | LiquidMAdClassLeaderboard              | 728 x 90   |
 | LiquidMAdClassFullscreen               | 768 x 768  |
 | LiquidMAdClassPortrait                 | 766 x 66   |
 | LiquidMAdClassLandscape                | 1024 x 66  |
 | LiquidMAdClassRichMedia                | 320 x 480  |
 | LiquidMAdClassIphonePreloader          | 320 x 460  |
 | LiquidMAdClassIpadPreloader            | 1024 x 748 |
 | LiquidMAdClassIphonePreloaderLandscape | 480 x 300  |
 | LiquidMAdClassIpadPreloaderPortrait    | 768 x 1004 |
 
 *Options*: The following key-value pairs can be part of a dictionary that can
 be passed to some of the factory methods for creating a LiquidMAdViewController

 | Key                             | Value                                                                               |
 | ------------------------------- | ----------------------------------------------------------------------------------- |
 | LiquidMControllerOptionLocation | the user's location to be used for geo-targeting                                    |
 | LiquidMControllerOptionReload   | determines if automatic reloading should be used (BOOL).                            |
 | LiquidMControllerOptionToken    | actual token to be used for ad loading                                              |
 | LiquidMControllerOptionTokenTag | name (NSString) of the tag for looking up the initial token (default: `@"default"`) |

 **Note** that you will have to wrap the BOOL into a `NSNumber` for putting it
 into a `NSDictionary` (default is `YES`)
 */

@interface LiquidMAdViewController : LiquidMAbstractController
{

}

/*!
 @abstract The delegate that gets notified about loading and presentation
 events.

 @discussion It is adviced to use the delegate to be at least informed about the
 basic loading events in order to do proper presentation.
 
 @see LiquidMAdViewControllerDelegate
 */
@property (nonatomic, weak) id<LiquidMAdViewControllerDelegate> delegate;

/*!
 @name Serve by Ad Class
 */

/*!
 @abstract Creates a LiquidMAdViewController with all necessary information.

 @param rvc the UIViewController that is used to present the ad and all its
 additional features.

 @param adClass A legacy ad class that determines the size of the placement. Ad
 classes match the sizes in density independent pixels (points) listed in the
 overview section.

 @warning This factory methods is deprecated. Usage of it is discouraged in
 favor of `controllerWithRootViewController:adSize:`

 @return Fully initialized instance of a LiquidMAdViewController
 */
+ (LiquidMAdViewController *)controllerWithRootViewController:(UIViewController *)rvc
                                                      adClass:(LiquidMAdClass)adClass;

/*!
 @abstract Creates a LiquidMAdViewController with all necessary information.

 @param rvc the UIViewController that is used to present the ad and all its
 additional features.

 @param adClass A legacy ad class that determines the size of the placement. Ad
 classes match the sizes in density independent pixels (points) listed in the
 overview section.

 @param optionsDict A dictionary that contains optional parameters.  It can
 optionally contain the one or more of the key-value pairs listed in the
 overview section.

 @warning This factory methods is deprecated. Usage of it is discouraged in
 favor of `controllerWithRootViewController:adSize:options:`

 @return Fully initialized instance of a LiquidMAdViewController
 */
+ (LiquidMAdViewController *)controllerWithRootViewController:(UIViewController *)rvc
                                                      adClass:(LiquidMAdClass)adClass
                                                      options:(NSDictionary *)optionsDict;

/*!
 @name Serve by Dimension
 */

/*!
 @abstract Initializes a LiquidMAdViewController with all needed information.

 @param rvc the UIViewController that is used to present the ad and all its
 additional features.

 @param adSize The size of the ad to load. The standard sizes can be found in
 the size column of the ad class table in the overview section.

 @return Fully initialized instance of a LiquidMAdViewController
 */
+ (LiquidMAdViewController *)controllerWithRootViewController:(UIViewController *)rvc
                                                       adSize:(CGSize)adSize;

/*!
 @abstract Initializes a LiquidMAdViewController with all needed information.

 @param rvc the UIViewController that is used to present the ad and all its
 additional features.

 @param adSize The size of the ad to load. The standard sizes can be found in
 the size column of the ad class table in the overview section.

 @param optionsDict A dictionary that contains optional parameters.  It can
 optionally contain the one or more of the key-value pairs listed in the
 overview section.

 @return Fully initialized instance of a LiquidMAdViewController
 */
+ (LiquidMAdViewController *)controllerWithRootViewController:(UIViewController *)rvc
                                                       adSize:(CGSize)adSize
                                                      options:(NSDictionary *)optionsDict;

/*!
 @name Controlling Presentation and Animations
 */

/*!
 @abstract Displays the ad view on the screen.

 @discussion This method should always be called after receiving the ad from the
 server. For fullscreen ads (interstitials) this will present the ad on screen
 as well. For banner ads though it is still required to add the controller's
 view to the view hierarchy that is on screen.

 @see [LiquidMAbstractControllerDelegate controllerDidReceiveAd:]
 */
- (void)presentAd;

/*! 
 @abstract The duration in seconds of the animation between two ads.
 */
@property (nonatomic) double animationDuration;

/*!
 @abstract The type of animation used for the transition between two ads.
 
 @discussion It must has to be of the following predefined animations.
 
 | Animation Name                   | Description                                                     |
 | -------------------------------- | --------------------------------------------------------------- |
 | LiquidMAnimationClassCurlDown    | next ad curls down on the old one like a turning page (default) |
 | LiquidMAnimationClassLeftToRight | new ad pushed old one out from the left                         |
 | LiquidMAnimationClassTopToBottom | new ad pushed old one out from the top                          |
 | LiquidMAnimationClassFade        | new ad fades in while the old ad fades out                      |
 | LiquidMAnimationClassNone        | no animation will be performed                                  |
 */
@property (nonatomic) LiquidMAnimationClass animationType;

/*!
 @name Controlling Ad Loading
 */

/*!
 @abstract Size of the ad to load
 
 @discussion This can be any desired size. However there are standard sizes that
 are widely used by ad designers which can be found in the size column of the
 ad class table in the overview section.
 
 @see [LiquidMAbstractController currentAdClass]
 */
@property (nonatomic) CGSize adSize;

/*!
 @abstract Manually reloads the ads.
 
 @discussion This method will do nothing if autoreload is turned on.
 */
- (void)reloadAd;


@end
