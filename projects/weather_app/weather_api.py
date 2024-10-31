"""
API Module for weather app
    Key from: https://www.weatherapi.com/
"""
__author__ = "Jake Peterson"
__date__ = "2024/10/28"
__license__ = "MIT"
__version__ = "0.1.0"
__maintainer__ = "Jake Peterson"

from datetime import datetime
from typing import Optional
from typing import Mapping, Union
import requests

ParamsType = Mapping[str, Union[str, int, float, None]]


class WeatherData:
    """
    Represents weather data fetched from the API.
    """

    def __init__(self, temperature: float, description: str,
                 name: str, region: str, country: str, lat: float,
                 lon: float, localtime: str):
        self._temperature = temperature
        self._description = description
        self._name = name
        self._region = region
        self._country = country
        self._lat = lat
        self._lon = lon
        self._localtime = localtime

    @property
    def temperature(self) -> float:
        """Getter for temperature."""
        return self._temperature

    @property
    def description(self) -> str:
        """Getter for description."""
        return self._description

    @description.setter
    def description(self, description: str) -> None:
        self._description = description

    def get_weather_emoji(self) -> str:
        """Function to get specific emojis"""
        description_lower = self._description.lower()
        if "sunny" in description_lower:
            return "☀️"
        elif "cloudy" in description_lower:
            return "☁️"
        elif "rain" in description_lower:
            return "🌧️"
        elif "thunder" in description_lower:
            return "🌩️"
        elif "snow" in description_lower:
            return "❄️"
        elif "fog" in description_lower or "mist" in description_lower:
            return "🌫️"
        elif "clear" in description_lower:
            return "🌌"
        else:
            return "🌈"

    def __str__(self) -> str:
        weather_emoji = self.get_weather_emoji()
        return (
            f"📍 Location: {self._name}, {self._region}, {self._country}\n"
            f"🗺️  Coordinates: {self._lat}, {self._lon}\n"
            f"🕒 Local Time: {self._localtime}\n"
            f"{weather_emoji}  Temperature: {self._temperature}°F\n"
            f"🌤️  Condition: {self._description}"
        )


class WeatherAPIClient:
    """
    Handles API calls.
    """

    def __init__(self, api_key: str):
        self._api_key = api_key

    @property
    def api_key(self) -> str:
        """Getter for api key"""
        return self._api_key

    def get_weather(self, city: str) -> WeatherData:
        """
        Fetches weather data for the specified city.
        """
        url = "http://api.weatherapi.com/v1/current.json"
        params: ParamsType = {
            'key': self.api_key,
            'q': city
        }

        try:
            response = requests.get(url, params=params, timeout=10)

            if response.status_code == 200:
                data = response.json()
                temperature = data['current']['temp_f']
                description = data['current']['condition']['text']
                location = data['location']
                name = location['name']
                region = location.get('region', '')
                country = location['country']
                lat = location['lat']
                lon = location['lon']
                localtime = location['localtime']
                return WeatherData(temperature, description, name,
                                   region, country, lat, lon, localtime)
            else:
                error_message = response.json().get("error", {}).get(
                    "message", "Unknown error")
                raise ValueError(f"Failed to fetch data: \
                                 {response.status_code} - {error_message}")

        except requests.exceptions.Timeout as exc:
            raise ValueError("Request timed out. \
                             Please try again later.") from exc
        except requests.exceptions.RequestException as exc:
            raise ValueError(f"An error occurred: {exc}") from exc

    def get_forecast(self, city: str, days: int = 3) -> str:
        """
        Fetches forecast data for the specified city.
        """
        url = "http://api.weatherapi.com/v1/forecast.json"
        params: ParamsType = {
            'key': self.api_key,
            'q': city,
            'days': days
        }

        try:
            response = requests.get(url, params=params, timeout=10)

            if response.status_code == 200:
                data = response.json()
                forecast_data = data['forecast']['forecastday']
                forecast_summary = "📅 Weather Forecast:\n"
                for day in forecast_data:
                    date = day['date']
                    avg_temp = day['day']['avgtemp_f']
                    condition = day['day']['condition']['text']
                    forecast_summary += f"{date}: {avg_temp}°F, {condition}\n"
                return forecast_summary
            else:
                error_message = response.json().get("error", {}).get(
                    "message", "Unknown error")
                raise ValueError(f"Failed to fetch forecast: \
                                 {response.status_code} - {error_message}")

        except requests.exceptions.Timeout as exc:
            raise ValueError("Request timed out while fetching forecast. \
                             Please try again later.") from exc
        except requests.exceptions.RequestException as exc:
            raise ValueError(f"An error occurred while fetching forecast: \
                             {exc}") from exc

    def get_history(self, city: str, date: Optional[str] = None) -> str:
        """
        Fetches historical weather data for the specified city.
        """
        if not date:
            date = datetime.now().strftime("%Y-%m-%d")
        url = "http://api.weatherapi.com/v1/history.json"
        params: ParamsType = {
            'key': self.api_key,
            'q': city,
            'dt': date
        }
        try:
            response = requests.get(url, params=params, timeout=10)

            if response.status_code == 200:
                data = response.json()
                history_data = data['forecast']['forecastday'][0]
                date = history_data['date']
                avg_temp = history_data['day']['avgtemp_f']
                condition = history_data['day']['condition']['text']
                return f"📅 Historical Weather on {date}: {avg_temp}°F, \
                    {condition}"
            else:
                error_message = response.json().get("error", {}).get(
                    "message", "Unknown error")
                raise ValueError(f"Failed to fetch history: \
                                 {response.status_code} - {error_message}")

        except requests.exceptions.Timeout as exc:
            raise ValueError(
                "Request timed out while fetching history") from exc
        except requests.exceptions.RequestException as exc:
            raise ValueError(
                f"An error occurred while fetching history: {exc}") from exc


if __name__ == "__main__":  # pragma: no cover
    pass
