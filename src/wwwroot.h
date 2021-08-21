const char WEBPAGE_ROOT[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
  <script src="main.js"></script>
</head>
<body>
  <h1>PIR door control</h1>
  
  <h2>Settings</h2>
  <form action="/saveSettings" method="POST" id="settingsForm">
    <p><strong><label for="disableTime">Disable auto unlock at (strictly HH:MM:SS):</label></strong><br/>
    NOTE: Does not save when power lost</p>
    <p><input id="disableTime" name="disableTime" type="text" placeholder="HH:MM:SS"/></p> 
    <p><input type="submit" value="Save"/>&nbsp;<span id="submitResult">&nbsp;</span></p>
  </form>

  <h2>Status</h2>
  <p><strong>Device time:</strong> <span id="deviceTime">&nbsp;</span></p> 
  <p><strong>Last unlocked:</strong> <span id="lastUnlockTime">&nbsp;</span></p> 
  <p><strong>Auto unlock:</strong> <span id="autoUnlockStatus">&nbsp;</span></p> 
  <p><strong>Auto unlock last set:</strong> <span id="lastSetTime">&nbsp;</span></p> 

  <h2>Device actions</h2>
  <p><a href="/reset">Reset wifi</a></p>
  <p><a href="/reboot">Reboot device</a></p>
</body>

</html>
)=====";
