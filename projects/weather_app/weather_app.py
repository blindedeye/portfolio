"""
Main module for weather app
"""
__author__ = "Jake Peterson"
__date__ = "2024/10/28"
__license__ = "MIT"
__version__ = "0.1.0"
__maintainer__ = "Jake Peterson"

import os
from dotenv import load_dotenv
from textual.app import App
from textual.app import ComposeResult
from textual.widgets import Header, Footer, Input, Static, Button
from textual.reactive import reactive
from weather_api import WeatherAPIClient
from rich.text import Text


class WeatherApp(App[None]):
    """
    A Textual app for displaying weather information.
    """
    CSS_PATH = "weather_app.css"
    city_input = reactive("")
    weather_info = reactive("")
    show_buttons = reactive(False)
    show_input = reactive(True)

    def __init__(self, api_key: str):
        super().__init__()
        self.api_client = WeatherAPIClient(api_key)

    def compose(self) -> ComposeResult:
        """
        Setup layout:
            Header - top
            Input - text box
            Static - weather output
            Button - quit button
            Footer - bottom
        """
        yield Header()
        yield Input(placeholder="Enter city name", id="city_input")
        yield Static("", id="weather_output", classes="bold")
        yield Footer()
        yield Button("Quit", id="quit_button", classes="red-button")

    async def on_input_submitted(self, message: Input.Submitted) -> None:
        """
        Handle input submission and fetch weather data.
        """
        self.city_input = message.value
        if self.city_input:
            try:
                weather_output = self.query_one("#weather_output", Static)
                weather_output.update("")
                weather_data = self.api_client.get_weather(self.city_input)
                self.weather_info = str(weather_data)
                self.show_buttons = True
                self.show_input = False
                formatted_text = Text.from_markup(
                    f"[bold]{self.weather_info}[/bold]\n\
                        \nPlease choose an option below.")
                weather_output.update(formatted_text)

                self.update_view()
            except ValueError as e:
                weather_output.update(Text.from_markup(
                    f"[bold red]Error: {e}[/bold red]"))

    async def on_button_pressed(self, message: Button.Pressed) -> None:
        """
        Handle button press events for forecast, history, and go back.
        """
        weather_output = self.query_one("#weather_output", Static)
        if message.button.id == "quit_button":
            await self.action_quit()
            return
        try:
            if self.city_input:
                weather_output.update("")

                if message.button.id == "forecast_button":
                    forecast_data = self.api_client.get_forecast(
                        self.city_input)
                    self.weather_info = forecast_data
                elif message.button.id == "history_button":
                    history_data = self.api_client.get_history(self.city_input)
                    self.weather_info = history_data
                elif message.button.id == "back_button":
                    self.show_buttons = False
                    self.show_input = True
                    self.update_view()
                    weather_output.update()
                    return

                # Format the weather info with Rich text
                formatted_text = Text.from_markup(
                    f"[bold]{self.weather_info}[/bold]")
                weather_output.update(formatted_text)
            else:
                weather_output.update(
                    Text.from_markup(
                        "[bold yellow]Enter a city name first.[/bold yellow]")
                )
        except ValueError as e:
            weather_output.update(Text.from_markup(
                f"[bold red]Error: {e}[/bold red]"))

    def update_view(self) -> None:
        """
        Update the view to show/hide buttons
        """
        if os.getenv("TEXTUAL_TEST_ENV") == "1":
            return  # Skip DOM manipulations during testing

        forecast_button = self.query("#forecast_button")
        history_button = self.query("#history_button")
        back_button = self.query("#back_button")
        quit_button = self.query("#quit_button")
        city_input = self.query("#city_input")

        if forecast_button:
            forecast_button.remove()
        if history_button:
            history_button.remove()
        if back_button:
            back_button.remove()
        if quit_button:
            quit_button.remove()
        if city_input:
            city_input.remove()

        if self.show_buttons:
            self.mount(Button("Get Forecast",
                              id="forecast_button",
                              classes="blue-button"))
            self.mount(Button("Get History",
                              id="history_button"))
            self.mount(Button("Go Back",
                              id="back_button",
                              classes="red-button"))
        else:
            if not self.query("#city_input"):
                self.mount(Input(placeholder="Enter city name",
                                 id="city_input"))
            if not self.query("#quit_button"):
                self.mount(Button("Quit",
                                  id="quit_button",
                                  classes="red-button"))


if __name__ == "__main__":  # pragma: no cover
    load_dotenv(dotenv_path=".env")
    api_key = os.getenv("WEATHER_API_KEY")
    WeatherApp(api_key).run()
