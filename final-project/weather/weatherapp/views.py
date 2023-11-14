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

# Create your views here.
def index(request):
    return render(request, 'weatherapp/index.html')

def presets(request: HttpRequest):
    if request.method == "POST":
        file = open('general.log','r')
        data = file.read()
        words = [word for word in data.split()]
        task = words[-4]
        time_act = words[-1]

        if ("midday" in request.POST or "sunriseset" in request.POST or "night" in request.POST) or ("midday" == time_act or "sunriseset" == time_act or "night" == time_act):
            if "midday" in request.POST:
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
            elif "sunriseset" in request.POST:
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
            elif "night" in request.POST:
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
        
        if ("sunny" in request.POST or "cloudy" in request.POST or "stormy" in request.POST) or ("sunny" == task or "cloudy" == task or "stormy" == task):
            if "sunny" in request.POST:
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
            elif "cloudy" in request.POST:
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
            elif "stormy" in request.POST:
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

        log_query_as_INFO(get_user_ip_address(request), task, time_act)
    return render(request, 'weatherapp/presets.html')

def forecast(request):
    if request.method == "POST":
        forecast_current_data = get_forecast_data_current(get_forecast_data())
        forecast_daily_data = get_forecast_data_daily(get_forecast_data())
        time_data = forecast_daily_data["time"]
        sunrise_data = forecast_daily_data["sunrise"]
        sunset_data = forecast_daily_data["sunset"]
        precipitation_sum_data = forecast_daily_data["precipitation_sum"]
        now = datetime.datetime.now()
        past = now - datetime.timedelta(minutes=30)
        future = now + datetime.timedelta(minutes=30)

        file = open('general.log','r')
        data = file.read()
        words = [word for word in data.split()]
        task = words[-4]
        time_act = words[-1]

        if "today" in request.POST:
            sunrise_time = datetime.datetime.strptime(sunrise_data[0], "%Y-%m-%dT%H:%M")
            sunset_time = datetime.datetime.strptime(sunset_data[0], "%Y-%m-%dT%H:%M")
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
        elif "tomorrow" in request.POST:
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
            time.sleep(3)

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

def world(request):
    return render(request, 'weatherapp/world.html')