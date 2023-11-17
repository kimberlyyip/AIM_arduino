from django.shortcuts import render
from django.http import HttpRequest
import datetime
import time

from .helper.processUserInput import processPresets

from .helper.logging import (
    log_query_as_INFO,
    get_user_ip_address,
)

from .helper.weatherapi import (
    get_forecast_data, 
    get_forecast_data_current, 
    get_forecast_data_daily,
)

# Renders the index page.
def index(request):
    return render(request, 'weatherapp/index.html')

# Renders the presets page. Sends the appropriate data to the arduino based on the buttons pushed.
def presets(request: HttpRequest):
    if request.method == "POST":
        # Read the previous sent data to prevent double sending data for the same setting. 
        # For example, if the settings are currently set to 'sunny', do not set to 'sunny' again.
        file = open('general.log','r')
        data = file.read()
        words = [word for word in data.split()]
        task = words[-4]
        time_act = words[-1]

        # Change the background before you change the weather
        # If 'midday' button was pressed...
        if "midday" in request.POST:
            time_act = "midday"
            # If last setting was 'sunriseset', turn right.
            if words[-1] == "sunriseset":
                changeRight = True
                changeLeft = False
                print("change from sunrise to midday")
            # If last setting was 'night', turn left.
            elif words[-1] == "night":
                changeRight = False
                changeLeft = True
                print("changed from night to midday")
            # else keep backdrop on 'midday'
            else: 
                changeRight = False
                changeLeft = False
                print("still midday")
            processPresets(False, False, False, True, changeRight, changeLeft, True)
        # If 'sunriseset' button was pressed...
        elif "sunriseset" in request.POST:
            time_act = "sunriseset"
            # If last setting was 'midday', turn left.
            if words[-1] == "midday":
                changeRight = False
                changeLeft = True
                print("changed from midday to sunset")
            # If last setting was 'night', turn right.
            elif words[-1] == "night":
                changeRight = True
                changeLeft = False
                print("changed from night to sunrise")
            # else keep backdrop on 'sunriseset'
            else:
                changeRight = False
                changeLeft = False
                print("still sunrise/sunset")
            processPresets(False, False, False, True, changeRight, changeLeft, True)
        # If 'night' button was pressed...
        elif "night" in request.POST:
            time_act = "night"
            # If last setting was 'sunriseset', turn right.
            if words[-1] == "sunriseset":
                changeRight = False
                changeLeft = True
                print("changed from sunset to night")
            # If last setting was 'midday', turn left.
            elif words[-1] == "midday":
                changeRight = True
                changeLeft = False
                print("changed from midday to night")
            # else keep backdrop on 'night'
            else:
                changeRight = False
                changeLeft = False
                print("still night")
            processPresets(False, False, False, True, changeRight, changeLeft, True)
        
        # Change the weather
        # If 'sunny' button was pressed...
        if "sunny" in request.POST:
            task = "sunny"
            # If last setting was 'sunny', don't do anything
            if words[-4] == "sunny":
                upCloud = False
                downCloud = False
                print("still sunny")
            # else, last setting had the clouds down, so move the clouds back up
            else:
                upCloud = False
                downCloud = True
                print("now sunny")
            processPresets(upCloud, downCloud, False, True, False, False, True)
        # If 'cloudy' button was pressed...
        elif "cloudy" in request.POST:
            task = "cloudy"
            # If last setting was 'cloudy' or 'stormy', don't do anything
            if words[-4] == "cloudy" or words[-4] == "stormy":
                downCloud = False
                upCloud = False
                print("still cloudy")
            # else, last setting had clouds up, so move clouds down
            else:
                upCloud = True
                downCloud = False
                print("now cloudy")
            processPresets(upCloud, downCloud, False, True, False, False, True)
        # If 'stormy' button was pressed...
        elif "stormy" in request.POST:
            task = "stormy"
            # If last setting was 'cloudy' or 'stormy', don't do anything
            if words[-4] == "cloudy" or words[-4] == "stormy":
                downCloud = False
                upCloud = False
                print("still stormy")
            # else, last setting had clouds up, so move clouds down
            else:
                upCloud = True
                downCloud = False
                print("now stormy")
            processPresets(upCloud, downCloud, True, False, False, False, True)

        log_query_as_INFO(get_user_ip_address(request), task, time_act)
    return render(request, 'weatherapp/presets.html')

# Renders the weather forecasts page. Sends the appropriate data to the arduino based on the buttons pushed.
def forecast(request):
    if request.method == "POST":
        # Get all the required data
        forecast_current_data = get_forecast_data_current(get_forecast_data())
        forecast_daily_data = get_forecast_data_daily(get_forecast_data())
        time_data = forecast_daily_data["time"]
        sunrise_data = forecast_daily_data["sunrise"]
        sunset_data = forecast_daily_data["sunset"]
        precipitation_sum_data = forecast_daily_data["precipitation_sum"]
        now = datetime.datetime.now()
        past = now - datetime.timedelta(minutes=30)
        future = now + datetime.timedelta(minutes=30)

        # Read the previous sent data to prevent double sending data for the same setting. 
        # For example, if the settings are currently set to 'sunny', do not set to 'sunny' again.
        file = open('general.log','r')
        data = file.read()
        words = [word for word in data.split()]
        task = words[-4]
        time_act = words[-1]

        # If 'today' button was pressed...
        if "today" in request.POST:
            # Calculate the time of sunrise and sunset
            sunrise_time = datetime.datetime.strptime(sunrise_data[0], "%Y-%m-%dT%H:%M")
            sunset_time = datetime.datetime.strptime(sunset_data[0], "%Y-%m-%dT%H:%M")
            # if the current time is 30min between the sunrise or sunset time, change the backdrop to 'sunriseset'
            if (sunrise_time < future and sunrise_time > past) or (sunset_time < future and sunset_time > past):
                time_act = "sunriseset"
                if words[-1] == "midday":
                    changeRight = False
                    changeLeft = True
                    print("changed from midday to sunset")
                elif words[-1] == "night":
                    changeRight = True
                    changeLeft = False
                    print("changed from night to sunrise")
                else:
                    changeRight = False
                    changeLeft = False
                    print("still sunrise/sunset")
                processPresets(False, False, False, True, changeRight, changeLeft, True)
            # If the current time is between sunrise and sunset, change the backdrop to 'midday'
            elif (now > sunrise_time and now < sunset_time):
                time_act = "midday"
                if words[-1] == "sunriseset":
                    changeRight = True
                    changeLeft = False
                    print("change from sunrise to midday")
                elif words[-1] == "night":
                    changeRight = False
                    changeLeft = True
                    print("changed from night to midday")
                else: 
                    changeRight = False
                    changeLeft = False
                    print("still midday")
                processPresets(False, False, False, True, changeRight, changeLeft, True)
            # If the current time is before sunrise and after sunset, change the backdrop to 'night'
            elif (now < sunrise_time and now > sunset_time):
                time_act = "night"
                if words[-1] == "sunriseset":
                    changeRight = False
                    changeLeft = True
                    print("changed from sunset to night")
                elif words[-1] == "midday":
                    changeRight = True
                    changeLeft = False
                    print("changed from midday to night")
                else:
                    changeRight = False
                    changeLeft = False
                    print("still night")
                processPresets(False, False, False, True, changeRight, changeLeft, True)

            # If the reported precipitation is above 4, change the setting to 'stormy'
            # 1-5 mm of precipitation is considered light to moderate rain,
            # above 5 mm of precipitation is considered heavy
            if forecast_current_data["precipitation"] > 4:
                task = "stormy"
                if words[-4] == "cloudy" or words[-4] == "stormy":
                    downCloud = False
                    upCloud = False
                    print("still stormy")
                else:
                    upCloud = True
                    downCloud = False
                    print("now stormy")
                processPresets(upCloud, downCloud, True, False, False, False, True)
            # If the reported cloud coverage is above 50, change the setting to 'cloudy'
            # cloud coverage is based on a 0-100 scale where 0 is no clouds and 100 is completely cloudy
            elif forecast_current_data["cloud_cover"] > 50:
                task = "cloudy"
                if words[-4] == "cloudy" or words[-4] == "stormy":
                    downCloud = False
                    upCloud = False
                    print("still cloudy")
                else:
                    upCloud = True
                    downCloud = False
                    print("now cloudy")
                processPresets(upCloud, downCloud, False, True, False, False, True)
            # Else, its a relatively sunny day
            else: 
                task = "sunny"
                if words[-4] == "sunny":
                    upCloud = False
                    downCloud = False
                    print("still sunny")
                else:
                    upCloud = False
                    downCloud = True
                    print("now sunny")
                processPresets(upCloud, downCloud, False, True, False, False, True)
        # If 'tommorrow' button pressed...
        elif "tomorrow" in request.POST:
            # Change the background to midday
            # Assuming that people want to know the weather during the day
            time_act = "midday"
            if words[-1] == "sunriseset":
                changeRight = True
                changeLeft = False
                print("change from sunrise to midday")
            elif words[-1] == "night":
                changeRight = False
                changeLeft = True
                print("changed from night to midday")
            else: 
                changeRight = False
                changeLeft = False
                print("still midday")
            processPresets(False, False, False, True, changeRight, changeLeft, True)
            # sleep for 3 sec to allow the backdrop to change if needed
            time.sleep(5)

            # If the reported precipitation is above 4, change the setting to 'stormy'
            # 1-5 mm of precipitation is considered light to moderate rain,
            # above 5 mm of precipitation is considered heavy
            if precipitation_sum_data[1] > 4:
                task = "stormy"
                if words[-4] == "cloudy" or words[-4] == "stormy":
                    downCloud = False
                    upCloud = False
                    print("still stormy")
                else:
                    upCloud = True
                    downCloud = False
                    print("now stormy")
                processPresets(upCloud, downCloud, True, False, False, False, True)
            # Else, its a relatively sunny day
            # No stricly cloudy conditional since the API does not specify cloud coverage for
            # future forecasts
            else: 
                task = "sunny"
                if words[-4] == "sunny":
                    upCloud = False
                    downCloud = False
                    print("still sunny")
                else:
                    upCloud = False
                    downCloud = True
                    print("now sunny")
                processPresets(upCloud, downCloud, False, True, False, False, True)
        
        log_query_as_INFO(get_user_ip_address(request), task, time_act)
    return render(request, 'weatherapp/forecast.html')