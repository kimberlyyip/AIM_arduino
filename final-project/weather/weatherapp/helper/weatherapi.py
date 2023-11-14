'''
Uses the free opensoure weather api: https://open-meteo.com/en/docs
Gathers current forecast data for the next 3 days.

A program to retrieve results from an HTTP-based API, parse the results (JSON in this case), 
and manage the potential errors.
'''

import sys
import argparse
import json
import urllib.request
import ssl
import ast

ssl._create_default_https_context = ssl._create_unverified_context

API_BASE_URL = 'https://api.open-meteo.com/v1/forecast'

# Obtains data for the following: latitude, longitude, generationtime_ms, utc_offset_seconds, 
# timezone, timezone_abbreviation, elevation, current_units, current, daily_units, daily
def get_forecast_data():
    url = f'{API_BASE_URL}?latitude=44.5588&longitude=-95.9856&current=is_day,precipitation,cloud_cover&daily=sunrise,sunset,precipitation_sum&timezone=America%2FChicago&forecast_days=3'
    data_from_server = urllib.request.urlopen(url).read()
    string_from_server = data_from_server.decode('utf-8')
    forecast_data_list = json.loads(string_from_server)
    return forecast_data_list

# Obtains data for the following: time, interval, is_day, precipitation, cloud_cover
def get_forecast_data_current(forecast_data_list):
    forecast_current_data = forecast_data_list["current"]
    return forecast_current_data

# Obtains data for the following: time, sunrise, sunset, precipitation_sum
def get_forecast_data_daily(forecast_data_list):
    forecast_daily_data = forecast_data_list["daily"]
    return forecast_daily_data