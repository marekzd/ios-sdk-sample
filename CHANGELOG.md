1.3.0 (2014-02-14)
==================

Bug Fixes
---------

- Fixed script tag rendering.
- Fixed ad presentation when changing between UIViewControllers.
- Fixed banner placement.
- Fixed rotation bug on video player.


Features
--------

- Added Google DFP mediation adapter and custom events.

1.2.1 (2014-02-05)
==================

Bug Fixes
---------

- Fixed bundle issue when signing the app.

1.2.0 (2014-01-17)
==================

Bug Fixes
---------

- improved token handling

Features
--------

- added video player featuring ad support

1.1.2 (2014-01-14)
==================

Bug Fixes
---------

- Removed AdMob Backfill.


1.1.1 (2013-12-16)
==================

Features
--------

- The token for actual loading of the ads can be added through the options dictionary.

1.0.1 (2013-11-25)
==================

Bug Fixes
---------

- Removed false positives of custom ad size warning.

Corrections on documentation
----------------------------

- Ad classes now are documented under their correct name.
- Backfilling instructions for AdMob were corrected.
- Repeated content in LiquidMAdViewController was reduced by general information in the overview section.
- Delegate properties and connected protocols are better linked together.

Location awareness
------------------

- LiquidMAdViewController now has a location property that can be used for location aware advertising.
- An option "LiquidMAdViewControllerOptionLocation" for the controller factory was added for the initial location.

AdMob mediation
---------------

- "GADMAdapterLiquidM" implements Google's SDK adapter interface.
- Google's custom events are implemented by the classes "GADMAdapterLiquidMCustomEventBanner" and "GADMAdapterLiquidMCustomEventInterstitial".

