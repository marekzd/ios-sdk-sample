//
//  LiquidMVideoViewController.h
//  LiquidM-iOS-SDK
//
//  Created by Khaterine Castellano on 12/9/13.
//  Copyright (c) 2013 LiquidM. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LiquidMAdClasses.h"
#import "LiquidMAbstractController.h"
#import "LiquidMControllerOptions.h"

@class LiquidMVideoViewController;

/*!
 This is the protocol that has to be implemented to set the
 [LiquidMVideoViewController delegate] property.
 */

@protocol LiquidMVideoViewControllerDelegate <LiquidMAbstractControllerDelegate>

@end

/*!
 @discussion This class provides an inline and fullscreen video player that is
 powered by LiquidM ads.
 
 **Additional Information**
 
 *Ad classes for video*:
 
 | AdClass                     | Description                                       |
 | --------------------------- | ------------------------------------------------- |
 | LiquidMAdClassVideoPreRoll  | Video will be played before the content           |
 | LiquidMAdClassVideoMidRoll  | Video will be played in the middle of the content |
 | LiquidMAdClassVideoPostRoll | Video will be played after the content            |
 
 *Options*: The following key-value pairs can be part of a dictionary that can
 be passed to some of the factory methods for creating a
 LiquidMVideoViewController
 
 | Key                               | Value                                                                               |
 | --------------------------------- | ----------------------------------------------------------------------------------- |
 | LiquidMControllerOptionLocation   | the location that can be used for geo-targeting                                     |
 | LiquidMControllerOptionFullscreen | determines if the video player should start in fullscreen mode (BOOL).              |
 | LiquidMControllerOptionTokenTag   | name (NSString) of the tag for looking up the initial token (default: `@"default"`) |
 
 **Note** that you will have to wrap the BOOL into a `NSNumber` for putting it
 into a `NSDictionary` (default is `YES`)
 */
@interface LiquidMVideoViewController : LiquidMAbstractController

/*!
 @abstract The delegate that gets notified about loading and presentation
 events.
 
 @discussion It is adviced to use the delegate to be at least informed about the
 basic loading events in order to do proper presentation.
 
 @see LiquidMVideoViewControllerDelegate
 */
@property (nonatomic, weak) id<LiquidMVideoViewControllerDelegate> delegate;


/*!
 @abstract Creates a LiquidMVideoViewController with all necessary information.
 
 @param adClass A legacy ad class that determines the size of the placement. Ad
 classes match the sizes in density independent pixels (points) listed in the
 overview section.
 
 @param videoURL The URL that is going to be used to load the main video.
 
 @return Fully initialized instance of a LiquidMVideoViewController
 */
+ (LiquidMVideoViewController *)controllerWithAdClass:(LiquidMAdClass)adClass
                                             videoURL:(NSString*)videoURL;

/*!
 @abstract Creates a LiquidMVideoViewController with all necessary information.
 
 @param adClass A legacy ad class that determines the size of the placement. Ad
 classes match the sizes in density independent pixels (points) listed in the
 overview section.
 
 @param videoURL The URL that is going to be used to load the main video.
 
 @param optionsDict A dictionary that contains optional parameters.  It can
 optionally contain the one or more of the key-value pairs listed in the
 overview section.

 
 @return Fully initialized instance of a LiquidMVideoViewController
 */
+ (LiquidMVideoViewController *)controllerWithAdClass:(LiquidMAdClass)adClass
                                             videoURL:(NSString*)videoURL
                                              options:(NSDictionary*)optionsDict;

- (void)play;
- (void)pause;
- (void)stop;

@end
