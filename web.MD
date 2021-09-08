<!doctype html>

<html>
  <head>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.4/jquery.min.js"></script>
    <script src="lib/script.js"></script>
  </head>

  <body>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">

<form>
  <div class="form-group">
    <label for="ssid" class="control-label">SSID</label> 
    <input id="ssid" name="ssid" type="text" class="form-control">
  </div> 
  <div class="form-group">
    <button name="submit" type="submit" class="btn btn-primary">Submit</button>
  </div>
</form>
  </body>
</html>


// Add your code here
$(document).ready(function(){
  $.getJSON("config.json", function (data) {
    $.each(data, function (key, val) {
      $("#"+key).val(val);
    });
  });
});


{"ssid" : "John", "password" : "Doe"}