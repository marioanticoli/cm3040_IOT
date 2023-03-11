const char INDEX_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <meta http-equiv="refresh" content="5">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
  </head>
  <body>
    <h1>Plant Care Dashboard</h1>

    <h2>Environment readings</h2>
    <p>Temperature:&nbsp;<span id="temp"></span>&deg;C</p>
    <p>Humidity:&nbsp;<span id="hum"></span>%</p>
    <p>Luminosity:&nbsp;<span id="luminosity"></span>%</p>
    <p>Soil humidity:&nbsp;<span id="soil"></span>%</p>
    <hr />

    <h2>Actuators status</h2>
    <p>Water pump:&nbsp;<span id="pump"></span>&nbsp;<button type="button" id="togglePump">Toggle</button></p>
    <p>Light:&nbsp;<span id="light"></span>&nbsp;<button type="button" id="toggleLED">Toggle</button></p>
    <hr />

    <h2>Current settings</h2>
    <div>
      <select id="plant">
        <option value="0">Setting 1</option>
        <option value="1">Setting 2</option>
        <option value="2">Setting 3</option>
      </select>
      <label for="humidity">Humidity</label>
      <input type="number" name="humidity" id="plantHum" value="" step="5" min="0" max="100">
      <label for="luminosity">Light</label>
      <input type="number" name="luminosity" id="plantLight" value="" step="5" min="0" max="100">
      <button type="button" id="update-plant">Update</button>      
    </div>    

    <script>
      const setValue = async (endpoint, id) => {
        const res = await fetch(endpoint);
        document.getElementById(id).innerHTML = await res.text();
      };

      const setPlant = async () => {
        const endpoint = "/current-setting";
        const res = await fetch(endpoint);
        data = await res.json();
        document.getElementById("plant").value = data.i;
        document.getElementById("plantHum").value = data.h;
        document.getElementById("plantLight").value = data.l;
      }
      
      const toggleActuator = (endpoint) => {
        fetch(endpoint, { method: "POST" });
      }


      window.addEventListener("load", (e) => {
        setValue("/temperature", "temp");
        setValue("/humidity", "hum");
        setValue("/luminosity", "luminosity");
        setValue("/soil", "soil");
        setValue("/pump-status", "pump");
        setValue("/light-status", "light");
        setPlant();
      });

      document.getElementById("togglePump").addEventListener("click", () => {
        toggleActuator("/toggle-pump");
      });

      document.getElementById("toggleLED").addEventListener("click", () => {
        toggleActuator("/toggle-led");
      });

      document.getElementById("update-plant").addEventListener("click", (e) => {
        data = {
          i: document.getElementById("plant").value,
          h: document.getElementById("plantHum").value,
          l: document.getElementById("plantLight").value,                    
        };

        fetch("update-plant", {
          method: "POST",
          headers: {"Content-Type": "application/json"},
          body: JSON.stringify(data)
        });
      });

    </script>
  </body>
</html>
)=====";
