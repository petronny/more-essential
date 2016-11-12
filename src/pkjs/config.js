module.exports = [{
	"type": "heading",
	"defaultValue": "Configurations"
}, {
	"type": "section",
	"items": [{
		"type": "heading",
		"defaultValue": "General"
	}, {
		"type": "select",
		"messageKey": "theme",
		"defaultValue": "default",
		"label": "Theme",
		"options": [{
			"label": "Custom",
			"value": "0"
		}, {
			"label": "Default",
			"value": "1"
		}, {
			"label": "France",
			"value": "2"
		}, {
			"label": "German",
			"value": "3"
		}, {
			"label": "Italy",
			"value": "4"
		}, {
			"label": "Russia",
			"value": "5"
		}]
	}, {
		"type": "toggle",
		"messageKey": "bluetooth_vibrate",
		"label": "Vibrate when disconnected",
		"defaultValue": true
	}, {
		"type": "toggle",
		"messageKey": "clock_hourly_vibrate",
		"label": "Vibrate hourly",
		"defaultValue": true
	}]
}, {
	"type": "section",
	"items": [{
		"type": "heading",
		"defaultValue": "Clock"
	}, {
		"type": "color",
		"messageKey": "clock_background_color",
		"defaultValue": "0xFFFFFF",
		"label": "Background color"
	}, {
		"type": "color",
		"messageKey": "clock_foreground_color",
		"defaultValue": "0x000000",
		"label": "Foreground color"
	}]
}, {
	"type": "section",
	"items": [{
		"type": "heading",
		"defaultValue": "Battery Bar"
	}, {
		"type": "text",
		"defaultValue": "It's the line under the clock."
	}, {
		"type": "toggle",
		"messageKey": "battery_display",
		"label": "Display",
		"defaultValue": true
	}, {
		"type": "color",
		"messageKey": "battery_color_high",
		"defaultValue": "0x005500",
		"label": "Color of the bar when battery level is high"
	}, {
		"type": "color",
		"messageKey": "battery_color_medium",
		"defaultValue": "0xFF5500",
		"label": "Color of the bar when battery level is medium"
	}, {
		"type": "color",
		"messageKey": "battery_color_low",
		"defaultValue": "0xAA0000",
		"label": "Color of the bar when battery level is low"
	}]
}, {
	"type": "section",
	"items": [{
		"type": "heading",
		"defaultValue": "Bluetooth Bar"
	}, {
		"type": "text",
		"defaultValue": "It's the line above the clock when bluetooth is connected."
	}, {
		"type": "toggle",
		"messageKey": "bluetooth_display",
		"label": "Display",
		"defaultValue": true
	}, {
		"type": "color",
		"messageKey": "bluetooth_color",
		"defaultValue": "0x000000",
		"label": "Color of the bar"
	}]
}, {
	"type": "section",
	"items": [{
		"type": "heading",
		"defaultValue": "Upper Panel"
	}, {
		"type": "text",
		"defaultValue": "It's the area above the clock."
	}, {
		"type": "color",
		"messageKey": "upper_panel_background_color",
		"defaultValue": "0x0000FF",
		"label": "Background Color"
	}, {
		"type": "color",
		"messageKey": "upper_panel_foreground_color",
		"defaultValue": "0xFFFFFF",
		"label": "Foreground Color"
	}, {
		"type": "toggle",
		"messageKey": "upper_panel_animations",
		"label": "Animations",
		"defaultValue": true
	}, {
		"type": "text",
		"defaultValue": "You can have up to 3 pins on a panel.Each pin will show more details if it's the only one on the panel."
	}, {
		"type": "select",
		"messageKey": "upper_panel_pin_1",
		"defaultValue": "none",
		"label": "Pin #1",
		"options": [{
			"label": "None",
			"value": "none"
		}, {
			"label": "Berry",
			"value": "berry"
		}, {
			"label": "Grape",
			"value": "grape"
		}, {
			"label": "Banana",
			"value": "banana"
		}]
	}, {
		"type": "select",
		"messageKey": "upper_panel_pin_2",
		"defaultValue": "none",
		"label": "Pin #2",
		"options": [{
			"label": "None",
			"value": "none"
		}, {
			"label": "Berry",
			"value": "berry"
		}, {
			"label": "Grape",
			"value": "grape"
		}, {
			"label": "Banana",
			"value": "banana"
		}]
	}, {
		"type": "select",
		"messageKey": "upper_panel_pin_3",
		"defaultValue": "none",
		"label": "Pin #3",
		"options": [{
			"label": "None",
			"value": "none"
		}, {
			"label": "Berry",
			"value": "berry"
		}, {
			"label": "Grape",
			"value": "grape"
		}, {
			"label": "Banana",
			"value": "banana"
		}]
	}]
}, {
	"type": "section",
	"items": [{
		"type": "heading",
		"defaultValue": "Bottom Panel"
	}, {
		"type": "text",
		"defaultValue": "It's the area under the clock."
	}, {
		"type": "color",
		"messageKey": "bottom_panel_background_color",
		"defaultValue": "0xFF0000",
		"label": "Background color"
	}, {
		"type": "color",
		"messageKey": "bottom_panel_foreground_color",
		"defaultValue": "0xFFFFFF",
		"label": "Foreground color"
	}, {
		"type": "toggle",
		"messageKey": "bottom_panel_animations",
		"label": "Animations",
		"defaultValue": true
	}, {
		"type": "text",
		"defaultValue": "You can have up to 3 pins on a panel.Each pin will show more details if it's the only one on the panel."
	}, {
		"type": "select",
		"messageKey": "bottom_panel_pin_1",
		"defaultValue": "none",
		"label": "Pin #1",
		"options": [{
			"label": "None",
			"value": "none"
		}, {
			"label": "Berry",
			"value": "berry"
		}, {
			"label": "Grape",
			"value": "grape"
		}, {
			"label": "Banana",
			"value": "banana"
		}]
	}, {
		"type": "select",
		"messageKey": "bottom_panel_pin_2",
		"defaultValue": "none",
		"label": "Pin #2",
		"options": [{
			"label": "None",
			"value": "none"
		}, {
			"label": "Berry",
			"value": "berry"
		}, {
			"label": "Grape",
			"value": "grape"
		}, {
			"label": "Banana",
			"value": "banana"
		}]
	}, {
		"type": "select",
		"messageKey": "bottom_panel_pin_3",
		"defaultValue": "none",
		"label": "Pin #3",
		"options": [{
			"label": "None",
			"value": "none"
		}, {
			"label": "Berry",
			"value": "berry"
		}, {
			"label": "Grape",
			"value": "grape"
		}, {
			"label": "Banana",
			"value": "banana"
		}]
	}]
}, {
	"type": "submit",
	"defaultValue": "Save Settings"
}];
