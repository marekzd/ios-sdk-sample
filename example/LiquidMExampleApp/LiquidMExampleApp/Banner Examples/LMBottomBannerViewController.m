//
//  LMBottomBannerViewController.m
//  LiquidMExampleApp
//
//  Created by Conrad Calmez on 02/12/13.
//  Copyright (c) 2013 LiquidM. All rights reserved.
//

#import "LMBottomBannerViewController.h"
#import <LiquidM-iOS-SDK/LiquidM.h>

@interface LMBottomBannerViewController () <LiquidMAdViewControllerDelegate>
{
    LiquidMAdViewController *lmAd;
}

@end

@implementation LMBottomBannerViewController

- (void)viewDidLoad
{
    [super viewDidLoad];

    lmAd = [LiquidMAdViewController controllerWithRootViewController:self
                                                             adClass:LiquidMAdClassMMA];
    lmAd.delegate = self;
    CGRect frame = lmAd.view.frame;
    frame.origin = CGPointMake(0, self.view.frame.origin.y
                                  + self.view.frame.size.height
                                  - lmAd.view.frame.size.height);
    lmAd.view.frame = frame;
    [self.view addSubview:lmAd.view];
    [self.view bringSubviewToFront:lmAd.view];
    [lmAd reloadAd];
}

#pragma mark - LiquidMAdViewController delegate methods

- (void)controllerDidReceiveAd:(LiquidMAdViewController *)controller
{
    [controller presentAd];
}

- (void)controller:(LiquidMAdViewController *)controller didFailedToReceiveAdWithError:(NSError *)error
{
    NSLog(@"Failed to receive an ad.\nError: %@", error);
}

@end
