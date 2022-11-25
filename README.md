# wioterminal-airquality

[![PlatformIO CI](https://github.com/kartben/wioterminal-airquality/actions/workflows/main.yml/badge.svg)](https://github.com/kartben/wioterminal-airquality/actions/workflows/main.yml)

This repository contains the source code for a Wio Terminal based Wi-Fi air quality monitoring device that integrates seamlessly with Home Assistant.

It supports the following sensors/peripherals:

- [Wio Terminal Battery Chassis][battery-chassis]: battery level and battery voltage.
- [Grove SCD30 CO2 sensor][co2-sensor]: CO2, temperature, humidity.
- [Grove Laser PM2.5 dust sensor][dust-sensor]: PM1, PM2.5, PM10.

The update period (MQTT publish interval) can be configured from the Home Assistant interface (default: 5s).

The LCD display is currently not used, but adding visual feedback shouldn't be too hard, and would make for a great pull request!

## Author <!-- omit in toc -->

👤 **Benjamin Cabé**

- Website: [https://blog.benjamin-cabe.com](https://blog.benjamin-cabe.com)
- Twitter: [@kartben](https://twitter.com/kartben)
- Github: [@kartben](https://github.com/kartben)
- LinkedIn: [@benjamincabe](https://linkedin.com/in/benjamincabe)

## 🤝 Contributing <!-- omit in toc -->

Contributions, issues and feature requests are welcome!

Feel free to check [issues page](https://github.com/kartben/wioterminal-airquality/issues).

## Show your support <!-- omit in toc -->

Give a ⭐️ if this project helped you!


## 📝 License <!-- omit in toc -->

Copyright &copy; 2022 [Benjamin Cabé](https://github.com/kartben).

This project is [MIT](/LICENSE) licensed.

***
_This README was generated with ❤️ by [readme-md-generator](https://github.com/kefranabg/readme-md-generator)_

[battery-chassis]: https://www.seeedstudio.com/Wio-Terminal-Chassis-Battery-650mAh-p-4756.html
[co2-sensor]: https://www.seeedstudio.com/Grove-CO2-Temperature-Humidity-Sensor-SCD30-p-2911.html
[dust-sensor]: https://www.seeedstudio.com/Grove-Laser-PM2-5-Sensor-HM3301.html
