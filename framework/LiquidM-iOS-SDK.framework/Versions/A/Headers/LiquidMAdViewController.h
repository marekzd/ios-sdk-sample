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

/*!
 This is the protocol that has to be implemented to set the
 [LiquidMAdViewController delegate] property.
 */

@protocol LiquidMAdViewControllerDelegate <NSObject>

/*!
 @name Loading
 */

@required

/*!
 @abstract Method called when the loading of the ad is finished.
 
 @param controller The LiquidMAdViewController that received the ad
 */
- (void)controllerDidReceiveAd:(LiquidMAdViewController *)controller;

/*!
 @abstract Method called when the loading of the ad failed.

 @param controller The LiquidMAdViewController that failed to receive the ad

 @param error The error that occured when loading an ad
 */
- (void)controller:(LiquidMAdViewController *)controller
        didFailedToReceiveAdWithError:(NSError*)error;

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
 @discussion This class provides an easy approach for integrating LiquidM ads into an
 iOS application. It's interface is intentionally kept simple to facilitate the
 integration.

 For a basic integration all it needs is just a UIViewController and a
 LiquidMAdClass to run. For further integration instructions please consult
 the integration tutorial.

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
 
 *Ad classes for video*:
 
 | AdClass                     | Description                                       |
 | --------------------------- | ------------------------------------------------- |
 | LiquidMAdClassVideoPreRoll  | Video will be played before the content           |
 | LiquidMAdClassVideoMidRoll  | Video will be played in the middle of the content |
 | LiquidMAdClassVideoPostRoll | Video will be played after the content            |

 *Options*: The following key-value pairs can be part of a dictionary that can
 be passed to some of the factory methods for creating a LiquidMAdViewController

 | Key                                     | Value                                                                               |
 | --------------------------------------- | ----------------------------------------------------------------------------------- |
 | `LiquidMAdViewControllerOptionToken`    | actual token to be used for ad loading                                              |
 | `LiquidMAdViewControllerOptionTokenTag` | name (NSString) of the tag for looking up the initial token (default: `@"default"`) |
 | `LiquidMAdViewControllerOptionReload`   | determines if automatic reloading should be used (BOOL).                            |
 | `LiquidMAdViewControllerOptionLocation` | the user's location to be used for geo-targeting                                    |

 **Note** that you will have to wrap the BOOL into a `NSNumber` for putting it
 into a `NSDictionary` (default is `YES`)
 */

@interface LiquidMAdViewController : UIViewController
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


#define LiquidMAdViewControllerOptionReload @"reload"
#define LiquidMAdViewControllerOptionToken @"token"
#define LiquidMAdViewControllerOptionTokenTag @"tokenTag"
#define LiquidMAdViewControllerOptionLocation @"location"

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
 @abstract Creates a LiquidMAdViewController with all necessary information.

 @param rvc the UIViewController that is used to present the ad and all its
 additional features.

 @param adClass A legacy ad class that determines the size of the placement. Ad
 classes match the sizes in density independent pixels (points) listed in the
 overview section.

 @param adapter An LiquidMBackfillingAdapter object that can be queried in case
 that no ad can be delivered.

 @warning This factory methods is deprecated. Usage of it is discouraged in
 favor of `controllerWithRootViewController:adSize:backfillingAdapter:`

 @return Fully initialized instance of a LiquidMAdViewController

 @see LiquidMAdMobAdapter
 */
+ (LiquidMAdViewController *)controllerWithRootViewController:(UIViewController *)rvc
                                                      adClass:(LiquidMAdClass)adClass
                                           backfillingAdapter:(id<LiquidMBackfillingAdapter>)adapter;

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

 @param adapter An LiquidMBackfillingAdapter object that can be queried in case
 that no ad can be delivered.

 @warning This factory methods is deprecated. Usage of it is discouraged in
 favor of `controllerWithRootViewController:adSize:options:backfillingAdapter:`

 @return Fully initialized instance of a LiquidMAdViewController
 
 @see LiquidMAdMobAdapter
 */
+ (LiquidMAdViewController *)controllerWithRootViewController:(UIViewController *)rvc
                                                      adClass:(LiquidMAdClass)adClass
                                                      options:(NSDictionary *)optionsDict
                                           backfillingAdapter:(id<LiquidMBackfillingAdapter>)adapter;

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
 @abstract Initializes a LiquidMAdViewController with all needed information.

 @param rvc the UIViewController that is used to present the ad and all its
 additional features.

 @param adSize The size of the ad to load. The standard sizes can be found in
 the size column of the ad class table in the overview section.

 @param adapter An LiquidMBackfillingAdapter object that can be queried in case
 that no ad can be delivered.

 @return Fully initialized instance of a LiquidMAdViewController

 @see LiquidMAdMobAdapter
 */
+ (LiquidMAdViewController *)controllerWithRootViewController:(UIViewController *)rvc
                                                       adSize:(CGSize)adSize
                                           backfillingAdapter:(id<LiquidMBackfillingAdapter>)adapter;

/*!
 @abstract Initializes a LiquidMAdViewController with all needed information.

 @param rvc the UIViewController that is used to present the ad and all its
 additional features.

 @param adSize The size of the ad to load. The standard sizes can be found in
 the size column of the ad class table in the overview section.

 @param optionsDict A dictionary that contains optional parameters.  It can
 optionally contain the one or more of the key-value pairs listed in the
 overview section.

 @param adapter An LiquidMBackfillingAdapter object that can be queried in case
 that no ad can be delivered.

 @return Fully initialized instance of a LiquidMAdViewController

 @see LiquidMAdMobAdapter
 */
+ (LiquidMAdViewController *)controllerWithRootViewController:(UIViewController *)rvc
                                                       adSize:(CGSize)adSize
                                                     options:(NSDictionary *)optionsDict
                                           backfillingAdapter:(id<LiquidMBackfillingAdapter>)adapter;

/*!
 @name Controlling Presentation and Animations
 */

/*!
 @abstract Displays the ad view on the screen.

 @discussion This method should always be called after receiving the ad from the
 server. For fullscreen ads (interstitials) this will present the ad on screen
 as well. For banner ads though it is still required to add the controller's
 view to the view hierarchy that is on screen.

 @see [LiquidMAdViewControllerDelegate controllerDidReceiveAd:]
 */
- (void)presentAd;

/*! 
 @abstract The duration in seconds of the animation between two ads.
 */
@property (nonatomic) double animationDuration;

/*!
 @abstract The type of animation used for the transition between two ads.
 
 @discussion It must has to be of the following predefined animations

 | Animation Name                   | Description                                                     |
 | -------------------------------- | --------------------------------------------------------------- |
 | LiquidMAnimationClassCurlDown    | next ad curls down on the old one like a turning page (default) |
 | LiquidMAnimationClassLeftToRight | new ad pushed old one out from the left                         |
 | LiquidMAnimationClassTopToBottom | new ad pushed old one out from the top                          |
 | LiquidMAnimationClassFade        | new ad fades in while the old ad fades out                      |
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
 
 @see currentAdClass
 */
@property (nonatomic) CGSize adSize;


/*!
 @abstract Ad class used for the ads to load and display an ad.
 
 @discussion It can have one of the values listed in the ad class table in the
 overview section. Setting this property implies the related ad size.
 
 @warning This property is deprecated. Instead it is adviced to use adSize.
 
 @see adSize
 */
@property (nonatomic) LiquidMAdClass currentAdClass;

/*!
 @abstract The tag that is being used to search for an app token from the in the
 app's plist file preconfigured dictionary.

 @discussion App tokens can be added to the plist file in a dictionary called
 `LiquidMAppIDs` with its tag as a key and the token itself as a value. If you
 choose to use it you should at least add the "default" tag's token.
 You can leave the plist file unconfigured but you would have to provide an
 actual token at runtime.
 You should choose to either use tokenTag or token for choosing a token for ad
 loading.

 @see token
 */
@property (nonatomic, copy) NSString *tokenTag;

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
 @abstract The location that is used for location based ads.
 
 @discussion If the location gets not set it will not be used for the ad
 request.
 It can be set on creation of the controller via the
 `LiquidMAdViewControllerOptionLocation` option.
 
 @see controllerWithRootViewController:adSize:options:
 */
@property (nonatomic, copy) CLLocation *location;

/*!
 @abstract Manually reloads the ads.
 
 @discussion This method will do nothing if autoreload is turned on.
 */
- (void)reloadAd;


@end
