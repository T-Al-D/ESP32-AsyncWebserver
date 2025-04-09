#include <HTML.h>

extern String output;

String DesignButton(bool status, String unit)
{
    /*
    the resulting string should look like this (kind of):
    result = R"rawliteral( <p> BUTTON 1 Status: ON</p>
    <a id="button1" class="button button-on" href="/button1off">Turn off!</a>)rawliteral";
    */

    String miniHeader = "<p>" + unit + " Status: " + (status ? "ON" : "OFF") + "</p>";
    String Link = "<a id=\"" + unit + "\" class=\"button " + (status ? "button-on" : "button-off")
        + "\" href=\"/" + unit + (status ? "off" : "on") + "\">"
        + "Turn " + (status ? "off" : "on") + "!</a>";

    return miniHeader + Link;
}

String DesignActuator(short status, String unit)
{
    /*
    the resulting string should look like this (kind of):
    result = R"rawliteral( <div class="actuators" id="actuators2">
        <p>actuator 2: <span class="active-forward" id="status2">active-forward</span></p>
        </div>)rawliteral";
    */

    // staus of a actuator can be complex
    String statusStr = "inactive";
    switch (status) {
    case 0:
        statusStr = "inactive";
        break;
    case 1:
        statusStr = "active-forward";
        break;
    case 2:
        statusStr = "active-backward";
        break;
    default:
        break;
    }

    String part1 = R"rawliteral( <div class="actuators" id=" )rawliteral";
    String part2 = unit + "\" ><p> " + unit + " : <span class=\""
        + statusStr + " \" id =\"" + unit + "\">" + statusStr;
    String part3 = R"rawliteral(</span></p> </div> )rawliteral";

    String result = part1 + part2 + part3;
    return result;
}

// dynamic HTML Page
String SendHTML()
{
    /* HTML text build in raw text*/
    // rawliteral = no escaped symbols
    String ptr = R"rawliteral(
    <!DOCTYPE html> <html>
    <head>
    <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
    <title>Actuators Status Control</title> 
    <style>
    html { font-family: Helvetica; display: block; margin: 0px auto; text-align: center;}

    body {
    font-weight: bold;
    font-size: 20px;  background-color: #f4f4f4;
    height: 100vh;
    margin: 1;
    }

    .inactive {color: red;}

    .active-forward {color: green;}

    .active-backward {color: blue;}

    .container {
    text-align: center;
    background-color: #fff;
    padding: 10px;
    border-radius: 10px;
    }

    .actuators {
    margin-left: 10px;
    margin-top: 9px;
    border-radius: 8px;
    background-color: #e9ecef;
    box-shadow: 1px 4px 7px rgba(0, 0, 0, 0.25);
    }

    .button {
    display: inline-block; 
    height: 35px; width: 80px; font-size: 1.3rem; 
    background-color: #351b54; color: white; 
    padding: 10px 18px; margin-left: 2px;
    border: 4px solid transparent; border-radius: 20px;
    }

    .button:hover{ border: 4px solid black; } 
    .button-on { background-color: #055214; } 
    .button-off { background-color: #4f1109; }

    .reset{display: inline-block;}
    .reset-button{width: 120px; background-color:rgb(80, 80, 80); padding: 5px 8px;}
    .reset-button:hover{border: 4px solid black; }

    p {display: inline-block; font-size: 1.3rem; color: #000000; margin-bottom: 5px; }
    pre { font-size: 0.9rem;}

    </style>
    </head>
    <body>

    <h2>ESP32 Web Server</h2>
    <h3>Production Flow</h3>
    <div class="container">
    )rawliteral";

    // actuators in the production flow 
    ptr += "<!-- Data Unit Separator -->";
    ptr += R"rawliteral(<div id="conveyorBelt1"> )rawliteral";
    ptr += DesignActuator(conveyorBelt1Status, "conveyorBelt1") + "</div>";
    ptr += "<!-- Data Unit Separator -->";
    ptr += R"rawliteral(<div id="slideMotor1"> )rawliteral";
    ptr += DesignActuator(slideMotor1Status, "slideMotor1") + "</div>";
    ptr += "<!-- Data Unit Separator -->";
    ptr += R"rawliteral(<div id="conveyorBelt2"> )rawliteral";
    ptr += DesignActuator(conveyorBelt2Status, "conveyorBelt2") + "</div>";
    ptr += "<!-- Data Unit Separator -->";
    ptr += R"rawliteral(<div id="taskMotor1"> )rawliteral";
    ptr += DesignActuator(taskMotor1Status, "taskMotor1") + "</div>";
    ptr += "<!-- Data Unit Separator -->";
    ptr += R"rawliteral(<div id="conveyorBelt3"> )rawliteral";
    ptr += DesignActuator(conveyorBelt3Status, "conveyorBelt3") + "</div>";
    ptr += "<!-- Data Unit Separator -->";
    ptr += R"rawliteral(<div id="taskMotor2"> )rawliteral";
    ptr += DesignActuator(taskMotor2Status, "taskMotor2") + "</div>";
    ptr += "<!-- Data Unit Separator -->";
    ptr += R"rawliteral(<div id="slideMotor2"> )rawliteral";
    ptr += DesignActuator(slideMotor2Status, "slideMotor2") + "</div>";
    ptr += "<!-- Data Unit Separator -->";
    ptr += R"rawliteral(<div id="conveyorBelt4"> )rawliteral";
    ptr += DesignActuator(conveyorBelt4Status, "conveyorBelt4") + "</div>";

    // closing container
    ptr += "</div>";

    // Button designs
    ptr += "<!-- Data Unit Separator -->";
    ptr += R"rawliteral(<div id="button1"> )rawliteral";
    ptr += DesignButton(button1Status, "button1") + "</div>";
    ptr += "<!-- Data Unit Separator -->";
    ptr += R"rawliteral(<div id="button2"> )rawliteral";
    ptr += DesignButton(button2Status, "button2") + "</div>";
    ptr += "<!-- Data Unit Separator -->";

    // reset button
    ptr += R"rawliteral( <div id="reset">
        <p> Reset everything :<p> <a href="/reset" class="button reset-button">RESET ALL<a>
        <div> )rawliteral";

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
    ptr += output + " </pre>";

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
            document.getElementById("conveyorBelt1").innerHTML  = parts[1];
            document.getElementById("slideMotor1").innerHTML    = parts[2];
            document.getElementById("conveyorBelt2").innerHTML  = parts[3];
            document.getElementById("taskMotor1").innerHTML     = parts[4];
            document.getElementById("conveyorBelt3").innerHTML  = parts[5];
            document.getElementById("taskMotor2").innerHTML     = parts[6];
            document.getElementById("slideMotor2").innerHTML    = parts[7];
            document.getElementById("conveyorBelt4").innerHTML  = parts[8];

            document.getElementById('button1').innerHTML = parts[9];
            document.getElementById('button2').innerHTML = parts[10];
        });
    }

    setInterval(fetchButtonStatus, 1000);
    fetchButtonStatus();
    </script>

    </body>
    </html>
    )rawliteral";

    return ptr;
}