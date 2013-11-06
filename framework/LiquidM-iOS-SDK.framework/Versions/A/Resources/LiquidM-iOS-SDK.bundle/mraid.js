/*global window */
(function initSDK(global) {
  /*
   * ###########################################################################
   * static information
   * ###########################################################################
   */
  var VERSION = "2.0";

  var GENERIC_STATIC_INFO = {
    contains: function contains(content) {
      var prop;
      for (prop in this) {
        if (this.hasOwnProperty(prop) &&
            typeof prop !== "function" &&
            this[prop] === content) {
          return true;
        }
      }
      return false;
    }
  };

  var STATES = {
    LOADING: 'loading',
    DEFAULT: 'default',
    EXPANDED: 'expanded',
    RESIZED: 'resized',
    HIDDEN: 'hidden',
    contains: GENERIC_STATIC_INFO.contains
  };

  var EVENTS = {
    ERROR: 'error',
    READY: 'ready',
    SIZE_CHANGE: 'sizeChange',
    STATE_CHANGE: 'stateChange',
    VIEWABLE_CHANGE: 'viewableChange',
    contains: GENERIC_STATIC_INFO.contains
  };

  var PLACEMENTS = {
    INLINE: 'inline',
    INTERSTITIAL: 'interstitial',
    contains: GENERIC_STATIC_INFO.contains
  };

  var CLOSE_POSITIONS = {
    TOP_LEFT: "top-left",
    TOP_RIGHT: "top-right",
    CENTER: "center",
    BOTTOM_LEFT: "bottom-left",
    BOTTOM_RIGHT: "bottom-right",
    TOP_CENTER: "top-center",
    BOTTOM_CENTER: "bottom-center",
    contains: GENERIC_STATIC_INFO.contains
  };

  var COMMAND_PREFIX = 'mraid';

  /*
   * ###########################################################################
   * Native Bridge
   * ###########################################################################
   */
  function NativeBridge() {
    /*
     * ########################################################################
     * private vars
     * ########################################################################
     */
    var callQueue = {};

    var generateUUID = function generateUUID() {
      var i;
      var uuid = [];

      for (i = 0; i < 36; i += 1) {
        if (i === 8 || i === 13 || i === 18 || i === 23) {
          uuid[i] = '-';
        } else {
          uuid[i] = Math.floor(Math.random() * 0x10).toString(16);
        }
      }
      return uuid.join('');
    };

    /*
     * #########################################################################
     * public API
     * #########################################################################
     */
    this.sendCommand = function sendCommand(command, parameters) {
      var call = COMMAND_PREFIX + ':' + command;
      var result;
      var i;
      var j;

      var encodeParameters = function encodeParameters(parameters) {
        var paramsString = "";
        var i = 0;
        var key;
        for (key in parameters) {
          if (parameters.hasOwnProperty(key) &&
              typeof parameters[key] !== "function") {
            if (i > 0) {
              paramsString += "&";
            } else {
              paramsString += "?";
            }
            paramsString += encodeURIComponent(key) +
                            "=" +
                            encodeURIComponent(parameters[key]);
            i += 1;
          }
        }
        return paramsString;
      };

      var callCommand = function callCommand(call) {
        var iframe = global.document.createElement('IFRAME');
        iframe.setAttribute('src', call);
        global.document.documentElement.appendChild(iframe);
        iframe.parentNode.removeChild(iframe);
        iframe = null;
      };

      var params = {};
      if (arguments.length > 2) {
        for (i = 1; i < arguments.length; i += 2) {
          var key = arguments[i];
          var value = arguments[i + 1];
          if (value !== null) {
            params[key] = value;
          }
        }
      } else if (arguments.length === 2) {
        if (typeof parameters === "object") {
          params = parameters;
        }
      }

      params.callID = generateUUID();

      callQueue[params.callID] = null;

      call += encodeParameters(params);

      callCommand(call);

      var WAITING_THRESHOLD = 1000000;
      j = 0;
      while (callQueue[params.callID] === null && j < WAITING_THRESHOLD) {
        // busy waiting : making an asynchronous call synchronous
        j += 1;
      }

      result = callQueue[params.callID] || null;
      delete callQueue[params.callID];
      return result;
    };

    this.getCommandResponse = function getCommandResponse(commandId, response) {
      callQueue[commandId] = response;
    };
  }

  /*
   * ###########################################################################
   * Mraid
   * ###########################################################################
   */
  function Mraid() {
    /*
     * #########################################################################
     * private vars
     * #########################################################################
     */
    var listeners = {};

    var bridge = new NativeBridge();

    var shouldUseCustomClose = false;

    var expandProperties = {};

    var orientationProperties = {
      "allowOrientationChange": true,
      "forceOrientation": "none"
    };

    var resizeProperties = {
      "customClosePosition": CLOSE_POSITIONS.TOP_RIGHT,
      "allowOffscreen": true
    };

    var broadcastEvent = function broadcastEvent(event) {
      var eventListeners;
      var listener;
      var i;
      if (EVENTS.contains(event)) {
        if (!listeners[event] || listeners[event].length < 1) {
          return;
        }
        eventListeners = listeners[event];
        var args = Array.prototype.slice.call(arguments);
        args.shift();
        for (i = 0; i < eventListeners.length; i += 1) {
          listener = eventListeners[i];
          listener.apply(null, args);
        }
        return;
      }
      // TODO warn that not supported
      return;
    };

    var state = (function () {
      var state = STATES.LOADING;
      return {
        get: function () {
          return state;
        },
        set: function (newState) {
          if (!STATES.contains(newState)) {
            // TODO fire error event that state is not supported
            return;
          }
          state = newState;
          broadcastEvent(EVENTS.STATE_CHANGE, state);
        }
      };
    }());

    var nativeEventHandlers = {};
    nativeEventHandlers[EVENTS.VIEWABLE_CHANGE] = function viewableChangeHandler(viewable) {
      broadcastEvent(EVENTS.VIEWABLE_CHANGE, viewable);
    };
    nativeEventHandlers[EVENTS.ERROR] = function errorHandler(message, origin) {
      broadcastEvent(EVENTS.ERROR, message, origin);
    };

    /*
     * #########################################################################
     * public API for native code to enter
     * #########################################################################
     */
    this.liquidMCommandResponse = function liquidMCommandResponse(commandId, data) {
      bridge.getCommandResponse(commandId, data);
    };

    this.liquidMNativeEvent = function liquidMNativeEvent(event) {
      var handler = nativeEventHandlers[event];
      var args = Array.prototype.slice.call(arguments);
      args.shift();
      if (handler !== null &&
          typeof handler === "function") {
        handler.apply(null, args);
      }
    };

    /*
     * #########################################################################
     * public API for the ad
     * #########################################################################
     */
    this.addEventListener = function addEventListener(event, listener) {
      var eventListeners;
      var registeredListener;
      var i;
      if (EVENTS.contains(event)) {
        listeners[event] = listeners[event] || [];
        eventListeners = listeners[event];
        for (i = 0; i < eventListeners.length; i += 1) {
          registeredListener = eventListeners[i];
          if (registeredListener === listener) {
            return;
          }
        }
        eventListeners.push(listener);
        return;
      }
      broadcastEvent(EVENTS.ERROR,
                     "The event \"" + event + "\" is not supported",
                     "addEventListener");
      return;
    };

    this.createCalendarEvent = function createCalendarEvent(parameters) {
      bridge.sendCommand("createCalendarEvent", parameters);
    };

    this.close = function close() {
      bridge.sendCommand("close");
      var currentState = state.get();
      if (currentState === STATES.EXPANDED ||
          currentState === STATES.RESIZED) {
        state.set(STATES.DEFAULT);
      } else if (currentState === STATES.DEFAULT) {
        var currentPlacement = this.getPlacementType();
        if (currentPlacement === PLACEMENTS.INTERSTITIAL) {
          state.set(STATES.HIDDEN);
        } else if (currentPlacement === PLACEMENTS.INLINE) {
          // TODO what should happen, discussion !
        }
      }
    };

    this.expand = function expand(URL) {
      if (state.get() !== STATES.EXPANDED) {
        if (URL !== null && URL !== undefined) {
          bridge.sendCommand("expand", "url", URL);
        }
        bridge.sendCommand("expand");
        state.set(STATES.EXPANDED);
      }
    };

    this.getCurrentPosition = function getCurrentPosition() {
      var data = bridge.sendCommand("getCurrentPosition");
      if (data === null) {
        broadcastEvent(EVENTS.ERROR, "No data received", "getCurrentPosition");
        return null;
      }
      var keyValuePairs = data.split("&");
      if (keyValuePairs.length < 4) {
        broadcastEvent(EVENTS.ERROR,
                       "Not all data received",
                       "getCurrentPosition");
        return null;
      }
      var parsedData = {};
      keyValuePairs.forEach(function (keyValuePair) {
        var keyAndValue = keyValuePair.split("=");
        parsedData[keyAndValue[0]] = parseInt(keyAndValue[1], 10);
      });
      return parsedData;
    };

    this.getDefaultPosition = function getDefaultPosition() {
      var data = bridge.sendCommand("getCurrentPosition");
      if (data === null) {
        broadcastEvent(EVENTS.ERROR, "No data received", "getDefaultPosition");
        return null;
      }
      var keyValuePairs = data.split("&");
      if (keyValuePairs.length < 4) {
        broadcastEvent(EVENTS.ERROR,
                       "Not all data received",
                       "getDefaultPosition");
        return null;
      }
      var parsedData = {};
      keyValuePairs.forEach(function (keyValuePair) {
        var keyAndValue = keyValuePair.split("=");
        parsedData[keyAndValue[0]] = parseInt(keyAndValue[1], 10);
      });
      return parsedData;
    };

    this.getExpandProperties = function getExpandProperties() {
      return {
        'width': expandProperties.width,
        'height': expandProperties.height,
        'useCustomClose': shouldUseCustomClose,
        'isModal': true
      };
    };

    this.getMaxSize = function getMaxSize() {
      var data = bridge.sendCommand("getMaxSize");
      if (data === null) {
        broadcastEvent(EVENTS.ERROR, "No data received", "getMaxSize");
        return null;
      }
      var keyValuePairs = data.split("&");
      if (keyValuePairs.length < 2) {
        broadcastEvent(EVENTS.ERROR, "Not all data received", "getMaxSize");
        return null;
      }
      var parsedData = {};
      keyValuePairs.forEach(function (keyValuePair) {
        var keyAndValue = keyValuePair.split("=");
        parsedData[keyAndValue[0]] = parseInt(keyAndValue[1], 10);
      });
      return parsedData;
    };

    this.getOrientationProperties = function getOrientationProperties() {
      return {
        "allowOrientationChange": orientationProperties.allowOrientationChange,
        "forceOrientation": orientationProperties.forceOrientation
      };
    };

    this.getPlacementType = function getPlacementType() {
      var data = bridge.sendCommand("getPlacementType");
      if (data === null) {
        broadcastEvent(EVENTS.ERROR, "No data received", "getPlacementType");
        return null;
      }
      return data;
    };

    this.getResizeProperties = function getResizeProperties() {
      var properties = {
        "customClosePosition": resizeProperties.customClosePosition,
        "allowOffscreen": resizeProperties.allowOffscreen
      };
      if (resizeProperties.width !== undefined) {
        properties.width = resizeProperties.width;
      }
      if (resizeProperties.height !== undefined) {
        properties.height = resizeProperties.height;
      }
      if (resizeProperties.offsetX !== undefined) {
        properties.offsetX = resizeProperties.offsetX;
      }
      if (resizeProperties.offsetY !== undefined) {
        properties.offsetY = resizeProperties.offsetY;
      }
      return properties;
    };

    this.getScreenSize = function getScreenSize() {
      var data = bridge.sendCommand("getScreenSize");
      if (data === null) {
        broadcastEvent(EVENTS.ERROR, "No data received", "getScreenSize");
        return null;
      }
      var keyValuePairs = data.split("&");
      if (keyValuePairs.length < 2) {
        broadcastEvent(EVENTS.ERROR, "Not all data received", "getScreenSize");
        return null;
      }
      var parsedData = {};
      keyValuePairs.forEach(function (keyValuePair) {
        var keyAndValue = keyValuePair.split("=");
        parsedData[keyAndValue[0]] = parseInt(keyAndValue[1], 10);
      });
      return parsedData;
    };

    this.getState = function getState() {
      return state.get();
    };

    this.getVersion = function getVersion() {
      return VERSION;
    };

    this.initialize = function initialize() {
      (function initializeExpandProperties(instance) {
        var screenSize = instance.getScreenSize();
        expandProperties.width = screenSize.width;
        expandProperties.height = screenSize.height;
      }(this));
      state.set(STATES.DEFAULT);
      bridge.sendCommand("jsControllerReady");
      broadcastEvent(EVENTS.READY);
    };

    this.isViewable = function isViewable() {
      var data = bridge.sendCommand("isViewable");
      if (data === null) {
        broadcastEvent(EVENTS.ERROR, "No data received", "isViewable");
        return null;
      }
      var viewable;
      if (data === 'true') {
        return true;
      }
      if (data === 'false') {
        return false;
      }
      broadcastEvent(EVENTS.ERROR, "Received data not parsable", "isViewable");
      return null;
    };

    this.open = function open(URL) {
      bridge.sendCommand("open", "url", URL);
    };

    this.playVideo = function playVideo(URI) {
      bridge.sendCommand("playVideo", "uri", URI);
    };

    this.removeEventListener = function removeEventListener(event, listener) {
      var eventListeners;
      var registeredListener;
      if (!event) {
        broadcastEvent(EVENTS.ERROR, "Event missing", "removeEventListener");
        return;
      }
      if (!listeners[event] || listeners[event].length < 1) {
        broadcastEvent(EVENTS.ERROR,
                       "No listener registered on event \" + event + \"",
                       "removeEventListener");
        return;
      }
      eventListeners = listener[event];
      for (registeredListener in eventListeners) {
        if (eventListeners.hasOwnProperty(registeredListener) &&
            registeredListener === listener) {
          var listenerIndex = eventListeners.indexOf(listener);
          eventListeners.splice(listenerIndex, 1);
          return;
        }
      }
      broadcastEvent(EVENTS.ERROR,
                     "This listener is not registered on event \" + event + \"",
                     "removeEventListener");
      return;
    };

    this.resize = function resize() {
      if (resizeProperties.width === undefined ||
          resizeProperties.height === undefined ||
          resizeProperties.offsetX === undefined ||
          resizeProperties.offsetY === undefined) {
        broadcastEvent(EVENTS.ERROR,
                       "Not all necessary resize properties set",
                       "resize");
        return;
      }
      if (state.get() === STATES.EXPANDED) {
        broadcastEvent(EVENTS.ERROR,
                       "The ad is already expanded and can therefore not be" +
                          " resized",
                       "resize");
        return;
      }
      bridge.sendCommand("resize");
      broadcastEvent(EVENTS.SIZE_CHANGE,
                     resizeProperties.width,
                     resizeProperties.height);
      state.set(STATES.RESIZED);
    };

    this.setExpandProperties = function setExpandProperties(properties) {
      if (properties.width !== undefined) {
        expandProperties.width = properties.width;
      }
      if (properties.height !== undefined) {
        expandProperties.height = properties.height;
      }
      if (properties.useCustomClose !== undefined) {
        shouldUseCustomClose = properties.useCustomClose;
      }
    };

    this.setOrientationProperties = function setOrientationProperties(properties) {
      if (properties.allowOrientationChange !== undefined) {
        orientationProperties.allowOrientationChange = properties.allowOrientationChange;
      }
      if (properties.forceOrientation !== undefined) {
        orientationProperties.forceOrientation = properties.forceOrientation;
      }
    };

    this.setResizeProperties = function setResizeProperties(properties) {
      if (properties.width !== undefined) {
        resizeProperties.width = properties.width;
      }
      if (properties.height !== undefined) {
        resizeProperties.height = properties.height;
      }
      if (properties.offsetX !== undefined) {
        resizeProperties.offsetX = properties.offsetX;
      }
      if (properties.offsetY !== undefined) {
        resizeProperties.offsetY = properties.offsetY;
      }
      if (properties.customClosePosition !== undefined) {
        if (!CLOSE_POSITIONS.contains(properties.customClosePosition)) {
          broadcastEvent(EVENTS.ERROR,
                         "Close position \"" +
                            properties.customClosePosition +
                            "\" is not supported",
                         "setResizeProperties");
        } else {
          resizeProperties.customClosePosition = properties.customClosePosition;
        }
      }
      if (properties.allowOffscreen !== undefined) {
        resizeProperties.allowOffscreen = properties.allowOffscreen;
      }

    };

    this.storePicture = function storePicture(URI) {
      bridge.sendCommand("storePicture", "uri", URI);
    };

    this.supports = function supports(feature) {
      var data = bridge.sendCommand("supports", "feature", feature);
      if (data === null) {
        broadcastEvent(EVENTS.ERROR, "No data received", "supports");
      }
      if (data === "true") {
        return true;
      }
      if (data === "false") {
        return false;
      }
      broadcastEvent(EVENTS.ERROR, "Received data not parsable", "supports");
      return null;
    };

    this.useCustomClose = function useCustomClose(doesUseCustomClose) {
      shouldUseCustomClose = doesUseCustomClose;
      bridge.sendCommand("useCustomClose");
    };
  }

  /*
   * ###########################################################################
   * Global Setup
   * ###########################################################################
   */
  global.mraid = new Mraid();
  global.mraid.initialize();
}(window));
