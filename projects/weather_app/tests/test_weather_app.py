"""
Unit tests for the WeatherApp and WeatherAPIClient
Notes:
First time messing with textual. Lots of the unit testing was
a result of thorough research online. Got most of it to work for
textual but not all.
"""

__author__ = "Jake Peterson"
__date__ = "2024/10/28"
__license__ = "MIT"
__version__ = "0.1.0"
__maintainer__ = "Jake Peterson"

import unittest
import asyncio
import os
from unittest import mock
from typing import Dict
from rich.text import Text
from weather_app import WeatherApp
from weather_api import WeatherAPIClient, WeatherData
from requests.exceptions import Timeout, RequestException


class TestWeatherApp(unittest.IsolatedAsyncioTestCase):
    """Unit Test Weather App"""

    async def asyncSetUp(self) -> None:
        """
        Setup the WeatherApp instance with a mock API key.
        """
        os.environ["TEXTUAL_TEST_ENV"] = "1"  # Set test environment variable
        self.api_key: str = "mock_api_key"
        self.app: WeatherApp = WeatherApp(api_key=self.api_key)
        self.app_task = asyncio.create_task(self.app.run_async())

    async def asyncTearDown(self) -> None:
        """
        Tear down the app instance by quitting.
        """
        await self.app.action_quit()
        await asyncio.sleep(0.1)
        del os.environ["TEXTUAL_TEST_ENV"]  # Clean up environment variable

    @mock.patch("weather_api.WeatherAPIClient.get_weather")
    async def test_input_submission_success(self,
                                            mock_get_weather: mock.Mock
                                            ) -> None:
        """
        Test that valid city input fetches weather data and updates the view.
        """
        mock_get_weather.return_value = WeatherData(
            temperature=75.0,
            description="Sunny",
            name="Test City",
            region="Test Region",
            country="Test Country",
            lat=45.0,
            lon=-120.0,
            localtime="2024-10-28 12:00"
        )
        self.app.city_input = "Test City"
        message = mock.Mock()
        message.value = "Test City"
        await self.app.on_input_submitted(message)
        weather_output_text = Text.from_markup(str(
            mock_get_weather.return_value))
        self.assertIn("Test City", weather_output_text.plain)
        self.assertIn("Sunny", weather_output_text.plain)

    @mock.patch("weather_api.WeatherAPIClient.get_forecast")
    async def test_forecast_button(self, mock_get_forecast: mock.Mock) -> None:
        """
        Test pressing the forecast button displays forecast data.
        """
        mock_get_forecast.return_value = "2024-10-29: 68.0°F, Rainy"
        self.app.city_input = "City"
        button_message = mock.Mock()
        button_message.button.id = "forecast_button"
        await self.app.on_button_pressed(button_message)
        self.assertIn("2024-10-29: 68.0°F, Rainy",
                      mock_get_forecast.return_value)

    async def test_quit_button(self) -> None:
        """
        Test that pressing the quit button stops the app.
        """
        button_message = mock.Mock()
        button_message.button.id = "quit_button"
        await self.app.on_button_pressed(button_message)
        await asyncio.sleep(0.5)
        if not self.app_task.done():
            self.app_task.cancel()

        self.assertTrue(self.app_task.done())


class TestWeatherData(unittest.TestCase):
    """
    Unit tests for the WeatherData class
    """

    def setUp(self) -> None:
        """
        Setup a sample WeatherData instance
        """
        self.weather_data: WeatherData = WeatherData(
            temperature=72.5,
            description="Partly cloudy",
            name="Sample City",
            region="Sample Region",
            country="Sample Country",
            lat=40.7128,
            lon=-74.0060,
            localtime="2024-10-28 12:00"
        )

    def test_get_weather_emoji(self) -> None:
        """
        Test the get_weather_emoji method with various descriptions
        """
        emoji_cases: Dict[str, str] = {
            "Sunny": "☀️",
            "Cloudy": "☁️",
            "Rainy": "🌧️",
            "Thunder": "🌩️",
            "Snow": "❄️",
            "Fog": "🌫️",
            "Mist": "🌫️",
            "Clear": "🌌",
            "Hurricane": "🌈"
        }

        for description, expected_emoji in emoji_cases.items():
            self.weather_data.description = description
            self.assertEqual(self.weather_data.get_weather_emoji(),
                             expected_emoji)

    def test_str_method(self) -> None:
        """
        Test the __str__ method output
        """
        expected_output: str = (
            "📍 Location: Sample City, Sample Region, Sample Country\n"
            "🗺️  Coordinates: 40.7128, -74.006\n"
            "🕒 Local Time: 2024-10-28 12:00\n"
            "☁️  Temperature: 72.5°F\n"
            "🌤️  Condition: Partly cloudy"
        )
        self.assertEqual(str(self.weather_data), expected_output)

    def test_temperature_property(self) -> None:
        """Test temperature property."""
        self.assertEqual(self.weather_data.temperature, 72.5)

    def test_description_property(self) -> None:
        """Test description property."""
        self.assertEqual(self.weather_data.description, "Partly cloudy")


class TestWeatherAPIClient(unittest.TestCase):
    """
    Unit tests for the WeatherAPIClient class
    """

    def setUp(self) -> None:
        """
        Setup a WeatherAPIClient with a mock API key
        """
        self.api_client: WeatherAPIClient = WeatherAPIClient(
            api_key="mock_api_key")

    @mock.patch("requests.get")
    def test_get_weather(self, mock_get: mock.Mock) -> None:
        """
        Test get_weather method for valid response
        """
        mock_response = mock.Mock()
        mock_response.status_code = 200
        mock_response.json.return_value = {
            "current": {"temp_f": 70.0, "condition": {"text": "Sunny"}},
            "location": {
                "name": "City", "region": "Region", "country": "Country",
                "lat": 40.0, "lon": -75.0, "localtime": "2024-10-28 10:00"
            }
        }
        mock_get.return_value = mock_response

        weather_data: WeatherData = self.api_client.get_weather("City")
        self.assertEqual(weather_data.temperature, 70.0)
        self.assertEqual(weather_data.description, "Sunny")

    @mock.patch("requests.get")
    def test_get_weather_api_error(self, mock_get: mock.Mock) -> None:
        """
        Test get_weather method for a non-200 status code
        """
        mock_response = mock.Mock()
        mock_response.status_code = 404
        mock_response.json.return_value = {
            "error": {"message": "City not found"}}
        mock_get.return_value = mock_response

        with self.assertRaises(ValueError) as context:
            self.api_client.get_weather("InvalidCity")
        self.assertIn("404 - City not found", str(context.exception))

    @mock.patch("requests.get")
    def test_get_weather_timeout_error(self, mock_get: mock.Mock) -> None:
        """
        Test get_weather method handling Timeout exception
        """
        mock_get.side_effect = Timeout
        with self.assertRaises(ValueError) as context:
            self.api_client.get_weather("City")
        self.assertIn("Request timed out", str(context.exception))

    @mock.patch("requests.get")
    def test_get_weather_request_exception(self, mock_get: mock.Mock) -> None:
        """
        Test get_weather method handling general RequestException
        """
        mock_get.side_effect = RequestException("Connection error")
        with self.assertRaises(ValueError) as context:
            self.api_client.get_weather("City")
        self.assertIn("An error occurred: Connection error",
                      str(context.exception))

    @mock.patch("requests.get")
    def test_get_forecast(self, mock_get: mock.Mock) -> None:
        """
        Test get_forecast method for valid response
        """
        mock_response = mock.Mock()
        mock_response.status_code = 200
        mock_response.json.return_value = {
            "forecast": {
                "forecastday": [
                    {"date": "2024-10-29", "day": {
                        "avgtemp_f": 68.0, "condition": {"text": "Rainy"}
                    }}
                ]
            }
        }
        mock_get.return_value = mock_response

        forecast: str = self.api_client.get_forecast("City", days=3)
        self.assertIn("2024-10-29: 68.0°F, Rainy", forecast)

    @mock.patch("requests.get")
    def test_get_forecast_api_error(self, mock_get: mock.Mock) -> None:
        """
        Test get_forecast method for a non-200 status code
        """
        mock_response = mock.Mock()
        mock_response.status_code = 403
        mock_response.json.return_value = {"error": {"message": "Forbidden"}}
        mock_get.return_value = mock_response

        with self.assertRaises(ValueError) as context:
            self.api_client.get_forecast("City")
        self.assertIn("403 - Forbidden", str(context.exception))

    @mock.patch("requests.get")
    def test_get_history(self, mock_get: mock.Mock) -> None:
        """
        Test get_history method for valid response
        """
        mock_response = mock.Mock()
        mock_response.status_code = 200
        mock_response.json.return_value = {
            "forecast": {
                "forecastday": [
                    {"date": "2024-10-27", "day": {
                        "avgtemp_f": 65.0, "condition": {"text": "Clear"}
                    }}
                ]
            }
        }
        mock_get.return_value = mock_response

        history: str = self.api_client.get_history("City", "2024-10-27")
        self.assertIn("2024-10-27", history)
        self.assertIn("65.0°F", history)
        self.assertIn("Clear", history)

    @mock.patch("requests.get")
    def test_get_history_request_exception(self, mock_get: mock.Mock) -> None:
        """
        Test get_history method handling RequestException
        """
        mock_get.side_effect = RequestException("Connection error")
        with self.assertRaises(ValueError) as context:
            self.api_client.get_history("City", "2024-10-27")
        self.assertIn(
            "An error occurred while fetching history: Connection error",
            str(context.exception)
        )


if __name__ == "__main__":  # pragma: no cover
    unittest.main()
