//
//  LMTopBannerViewController.m
//  LiquidMExampleApp
//
//  Created by Conrad Calmez on 02/12/13.
//  Copyright (c) 2013 LiquidM. All rights reserved.
//

#import "LMTopBannerViewController.h"
#import <LiquidM-iOS-SDK/LiquidM.h>

@interface LMTopBannerViewController () <LiquidMAdViewControllerDelegate>
{
    LiquidMAdViewController *lmAd;
}

@end

@implementation LMTopBannerViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    NSMutableDictionary *options = [NSMutableDictionary dictionary];
    [options setObject:@"6aCmmWgi"
                forKey:LiquidMAdViewControllerOptionToken];
    [options setObject:[NSNumber numberWithBool:NO]
                forKey:LiquidMAdViewControllerOptionReload];
    

    lmAd = [LiquidMAdViewController controllerWithRootViewController:self
                                                             adClass:LiquidMAdClassMMA
                                                             options:options];
    lmAd.delegate = self;
    CGRect frame = lmAd.view.frame;
    frame.origin = CGPointMake(0, 64);
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
