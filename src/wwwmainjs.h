const char MAINJS_ROOT[] PROGMEM = R"=====(
$(document).ready(function() {
  setInterval(updateStatus, 1000);

  $.ajax({
    url: "/getAutoDisableTime",
    cache: false
  }).done(function (data) {
    $('#disableTime').val(data);
  });

  function updateStatus() {
    $.ajax({
     url: "/getTime",
     cache: false
    }).done(function (data) {
      $('#deviceTime').text(data);
    });
    $.ajax({
     url: "/getLastUnlockedTime",
     cache: false
    }).done(function (data) {
      $('#lastUnlockTime').text(data);
    });
    $.ajax({
     url: "/getStatus",
     cache: false
    }).done(function (data) {
      $('#autoUnlockStatus').text(data);
    });
    $.ajax({
     url: "/getLastSetTime",
     cache: false
    }).done(function (data) {
      $('#lastSetTime').text(data);
    });
  }

  $('#settingsForm').submit(function(e) {
    e.preventDefault();

    var form = $(this);
    var url = form.attr('action');

    $.ajax({
        type: "POST",
        url: url,
        data: form.serialize(),
        success: function(data) {
          $('#submitResult')
            .css("color", "green")
            .text(data);
          setTimeout(clearSaveStatus, 5000);
        },
        error: function (xhr, ajaxOptions, thrownError) {
          $('#submitResult')
            .css("color", "red")
            .text(xhr.responseText);
          setTimeout(clearSaveStatus, 5000);
        }
      });
  });

  function clearSaveStatus() {
    $('#submitResult').text("");
  }
});
)=====";
