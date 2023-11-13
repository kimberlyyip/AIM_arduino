from django.shortcuts import render
from django.http import HttpRequest

from .helper.processUserInput import processPresets

from .helper.logging import (
    log_query_as_INFO,
    get_user_ip_address,
)

# Create your views here.
def index(request):
    return render(request, 'weatherapp/index.html')

def presets(request: HttpRequest):
    if request.method == "POST":
        file = open('general.log','r')
        data = file.read()
        words = [word for word in data.split()]

        if "sunny" in request.POST:
            task = "sunny"
            if words[-1] == "sunny" or words[-1] == "midday" or words[-1] == "sunriseset" or words[-1] == "night":
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
            if words[-1] == "cloudy" or words[-1] == "stormy" or words[-1] == "midday" or words[-1] == "sunriseset" or words[-1] == "night":
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
            if words[-1] == "cloudy" or words[-1] == "stormy" or words[-1] == "midday" or words[-1] == "sunriseset" or words[-1] == "night":
                downCloud = False
                upCloud = False
                print("still stormy")
            else:
                upCloud = True
                downCloud = False
                print("now stormy")
            processPresets(upCloud, downCloud, True, False, False, False, True)
        elif "midday" in request.POST:
            task = "midday"
            if words[-1] == "midday" or words[-1] == "sunny" or words[-1] == "cloudy" or words[-1] == "stormy":
                changeRight = False
                changeLeft = False
                print("still midday")
            elif words[-1] == "sunriseset":
                changeRight = True
                changeLeft = False
                print("change from sunrise to midday")
            elif words[-1] == "night":
                changeRight = False
                changeLeft = True
                print("changed from night to midday")
            processPresets(False, False, False, True, changeRight, changeLeft, True)
        elif "sunriseset" in request.POST:
            task = "sunriseset"
            if words[-1] == "sunriseset" or words[-1] == "sunny" or words[-1] == "cloudy" or words[-1] == "stormy":
                changeRight = False
                changeLeft = False
                print("still sunrise/sunset")
            elif words[-1] == "midday":
                changeRight = True
                changeLeft = False
                print("changed from midday to sunset")
            elif words[-1] == "night":
                changeRight = False
                changeLeft = True
                print("changed from night to sunrise")
            processPresets(False, False, False, True, changeRight, changeLeft, True)
        elif "night" in request.POST:
            task = "night"
            if words[-1] == "night" or words[-1] == "sunny" or words[-1] == "cloudy" or words[-1] == "stormy":
                changeRight = False
                changeLeft = False
                print("still night")
            elif words[-1] == "sunriseset":
                changeRight = True
                changeLeft = False
                print("changed from sunset to night")
            elif words[-1] == "midday":
                changeRight = False
                changeLeft = True
                print("changed from midday to night")
            processPresets(False, False, False, True, changeRight, changeLeft, True)

        log_query_as_INFO(get_user_ip_address(request), task)
    return render(request, 'weatherapp/presets.html')

def forecast(request):
    return render(request, 'weatherapp/forecast.html')

def world(request):
    return render(request, 'weatherapp/world.html')