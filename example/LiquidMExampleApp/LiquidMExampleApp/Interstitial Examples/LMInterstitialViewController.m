//
//  LMInterstitialViewController.m
//  LiquidMExampleApp
//
//  Created by Conrad Calmez on 02/12/13.
//  Copyright (c) 2013 LiquidM. All rights reserved.
//

#import "LMInterstitialViewController.h"
#import <LiquidM-iOS-SDK/LiquidM.h>

@interface LMInterstitialViewController () <LiquidMAdViewControllerDelegate>
{
    LiquidMAdViewController *lmAd;
}

@end

@implementation LMInterstitialViewController

- (void)viewDidLoad
{
    [super viewDidLoad];

    NSDictionary *options = @{
        LiquidMAdViewControllerOptionTokenTag: @"interstitial"
    };

    lmAd = [LiquidMAdViewController controllerWithRootViewController:self
                                                              adSize:[LiquidMUtilities getScreenResolution]
                                                             options:options];
    lmAd.delegate = self;
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
    [controller reloadAd];
}

@end
