// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

chrome.app.runtime.onLaunched.addListener(function() {
  chrome.test.getConfig(function(config) {
    var testName = config.customArg;
    if (!testName) {
      chrome.test.fail("Missing test name.");
      return;
    }
    chrome.chromeosInfoPrivate.get([
      'sessionType',
      'playStoreStatus',
      'managedDeviceStatus'
    ], chrome.test.callbackPass(function(values) {
          switch (testName) {
            case 'kiosk':
              chrome.test.assertEq('kiosk', values['sessionType']);
              break;
            case 'arc not-available':
              chrome.test.assertEq('not available', values['playStoreStatus']);
              break;
            case 'arc available':
              chrome.test.assertEq('available', values['playStoreStatus']);
              break;
            case 'arc enabled':
              chrome.test.assertEq('enabled', values['playStoreStatus']);
              break;
            case 'managed':
              chrome.test.assertEq('managed', values['managedDeviceStatus']);
          }
        }));
  });
});
