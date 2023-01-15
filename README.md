# Plant care system - CM3040

- `plant_care.ino` is the main Arduino file
- `lib` contains custom classes to simplify working with sensors, actuators, etc.
- `test` contains unit tests for the classes in `lib`

## Important note

It is necessary to create a header file `WifiCredentials.h` containing only the following definitions

```
#define SSID "NETWORK_NAME"
#define PASSWORD "NETWORK_PASSWORD"
```
