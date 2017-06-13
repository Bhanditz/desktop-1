// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

var tests = [
  function testAppBindings() {
    chrome.test.assertTrue(!!chrome.app, 'app');
    chrome.test.assertTrue(!!chrome.app.window, 'app.window');
    chrome.test.succeed();
  },
  function testCurrentWindow() {
    var currentWindow = chrome.app.window.current();
    // Current window is pretty funny and has a ton of custom JS bindings, also
    // utilizing an internal API (currentWindowInternal). Test a bunch of stuff.
    chrome.test.assertTrue(!!currentWindow, 'currentWindow');
    // An instance property.
    chrome.test.assertTrue(!!currentWindow.innerBounds, 'innerBounds');
    // A method from the internal API.
    chrome.test.assertTrue(!!currentWindow.drawAttention, 'drawAttention');
    // A method on the prototype.
    chrome.test.assertTrue(!!currentWindow.isFullscreen, 'isFullscreen');
    // A property on the prototype.
    chrome.test.assertTrue(!!currentWindow.contentWindow, 'contentWindow');
    chrome.test.succeed();
  },
  function testWebView() {
    var webview = document.createElement('webview');
    webview.src = 'data:text/html,<html><body>hello world</body></html>';
    document.body.appendChild(webview);
    // TODO(devlin): This is a pretty lame test currently, since we don't wait
    // for the webview to finish loading. We can't do that yet, since webview
    // events are all implemented as custom extension events (?!) under the
    // hood, and we haven't wired up custom events in binding hooks.
    chrome.test.succeed();
  },
];

chrome.test.runTests(tests);
