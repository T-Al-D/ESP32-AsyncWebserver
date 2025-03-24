#include <HTML.h>

String DesignButton(bool boolean, String unit)
{
    String result = "";
    if (unit == "button1") {
        if (boolean) {
            result = R"rawliteral(
            <p>BUTTON 1 Status: ON</p>
            <a id="button1" class="button button-on" href="/button1off">Turn off!</a>
            )rawliteral";
        } else {
            result = R"rawliteral(
            <p>BUTTON 1 Status: OFF</p>
            <a id="button1" class="button button-off" href="/button1on">Turn on!</a>
            )rawliteral";
        }
    }
    if (unit == "button2") {
        if (boolean) {
            result = R"rawliteral(
            <p>BUTTON 2 Status: ON</p>
            <a class="button button-on" href="/button2off">Turn off!</a>
            )rawliteral";
        } else {
            result = R"rawliteral(
            <p>BUTTON 2 Status: OFF</p>
            <a class="button button-off" href="/button2on">Turn on!</a>
            )rawliteral";
        }
    }
    return result;
}

// dynamic HTML Page
String SendHTML(bool button1status, bool button2status, String otherInfo)
{
    /* HTML text build in raw text*/
    // rawliteral = no escaped symbols
    String ptr = R"rawliteral(
    <!DOCTYPE html> <html>
    <head>
    <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
    <title>Button Control</title> 
    <style>
    html { font-family: Helvetica; display: block; margin: 0px auto; text-align: center;}
    body {
        font-size: 25px; margin-bottom: 10px; cursor: pointer; border-radius: 4px; 
    }
    .button {
        display: inline-block; height: 35px; width: 100px; font-size: 1.5rem; background-color: #351b54;
        color: white; padding: 15px 30px; border: 4px solid transparent;
    }
    .button:hover{ border: 4px solid black; } 
    .button-on { background-color: #055214; } 
    .button-off { background-color: #4f1109; }
    p { font-size: 1.5rem; color: #888; margin-bottom: 10px; }
    pre { font-size: 0.8rem;}
    </style>
    </head>
    <body>
    <h2>ESP32 Web Server</h2>
    <h4>Using Access Point (AP) Mode</h4>
    )rawliteral";

    // Button designs
    ptr += "<!-- Data Unit Separator -->";
    ptr += R"rawliteral(<div id="button1"> )rawliteral";
    ptr += DesignButton(button1status, "button1") + "</div>";
    ptr += "<!-- Data Unit Separator -->";
    ptr += R"rawliteral(<div id="button2"> )rawliteral";
    ptr += DesignButton(button2status, "button2") + "</div>";
    ptr += "<!-- Data Unit Separator -->";

    // Other Info in <pre>
    ptr += R"rawliteral(
    <h5>The input element</h5>
    <form action="/inputText">
    <label for="param"> Input: </label>
    <input type="text" id="param" name="param">
    <br><br>
    <input type="submit" value="Submit">
    </form>
    
    <p>Other Information:</p>
    <pre>
    )rawliteral";

    // pre text
    ptr += otherInfo + " </pre>";

    // script which asks for the current status of the "data unit" every setInterval(milliseconds)
    // and refreshes the "data unit" (even after reset) -> HTTP-Request
    // makes page dynamic
    ptr += R"rawliteral(
    <script>
    function fetchButtonStatus() {
        fetch('/refreshStatuses')
        .then(response => response.text())
        .then(data => {
            const parts = data.split("<!-- Data Unit Separator -->");
            document.getElementById('button1').innerHTML = parts[1];
            document.getElementById('button2').innerHTML = parts[2];
        });
    }

    setInterval(fetchButtonStatus, 2000);
    fetchButtonStatus();
    </script>

    </body>
    </html>
    )rawliteral";

    return ptr;
}