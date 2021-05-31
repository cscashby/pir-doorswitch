const char WEBPAGE_ROOT[] PROGMEM = R"=====(
 <!DOCTYPE html>
<html>
<head>
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
  <script src="main.js"></script>
</head>
<body>
  <h1>IOTheatre home page</h1>

  <h2>Motor control</h2>
  <form action="/motor/move/1" method="post" name="motor_form" id="motor_form">
    <p><a href="/motor/enable/1">Enable motor</a></p>
    <p><a href="/motor/disable/1">Disable motor</a></p>
    <caption for="motor_mins">Minutes to move clock (can be fractional):&nbsp;</caption>
    <input type="text" id="motor_mins" value="60.0" name="unitcount"/><br/>
    <input type="radio" id="motor_forward" value="forward" name="direction"/>
    <caption for="motor_forward">Forward</caption><br/>
    <input type="radio" id="motor_backward" value="backward" name="direction"/>
    <caption for="motor_backward">Backward</caption><br/>
    <input type="button" value="Go" onclick="javascript:document.getElementById('motor_form').submit();"/>
  </form>

  <h2>Actions</h2>
  <p><a href="/reset">Reset wifi</a></p>
  <p><a href="/reboot">Reboot device</a></p>
</body>

</html>
)=====";
