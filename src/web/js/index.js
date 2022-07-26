let host = 'broker.hivemq.com';
let port = 8000;
let macAdress = '96:EA:E8'
let topic = macAdress + '/et/smpl/tele/#';
let useTLS = false;
//let useTLS = true;
let cleansession = true;
let reconnectTimeout = 3000;
let tempData = new Array();
let humiData = new Array();
let mqtt;

function MQTTconnect() {
    if (typeof path == "undefined") {
        path = '/';
    }

    let clientId = "wc_" + parseInt(Math.random() * 10000, 10);
    mqtt = new Paho.MQTT.Client(host, port, clientId);
    let options = {
        timeout: 3,
        useSSL: useTLS,
        cleanSession: cleansession,
        onSuccess: onConnect,
        onFailure: function (message) {
            $('#status').html("Connection failed: " + message.errorMessage + "Retrying...")
                .attr('class', 'alert alert-danger');
            setTimeout(MQTTconnect, reconnectTimeout);
        }
    };

    mqtt.onConnectionLost = onConnectionLost;
    mqtt.onMessageArrived = onMessageArrived;
    console.log("Host: " + host + ", Port: " + port + ", Path: " + path + " TLS: " + useTLS);
    mqtt.connect(options);
};

function onConnect() {
    $('#status').html('Connected to ' + host + ':' + port + path)
        .attr('class', 'alert alert-success');
    mqtt.subscribe(topic, { qos: 0 });
    $('#topic').html(topic);
};

function onConnectionLost(response) {
    setTimeout(MQTTconnect, reconnectTimeout);
    $('#status').html("Connection lost. Reconnecting...")
        .attr('class', 'alert alert-warning');
};

function onMessageArrived(message) {
    let topic = message.destinationName;
    let payload = message.payloadString;
    console.log("Topic: " + topic + ", Message payload: " + payload);
    $('#message').html(topic + ', ' + payload);
    let topics = topic.split('/');
    let area = topics[4];

    if (area === 'sensor') {
      processSensor(payload);
    } else {
      console.log('Error: Data do not match the MQTT topic.');
    }
};

function processSensor(payload){
  let obj;
  try {
      obj = JSON.parse(payload);
  } catch (e) {
      return undefined; // Or whatever action you want here
  }

  // temperature
  $('#temperatureSensor').html('(Sensor value: ' + obj.temperature + ')');
  $('#temperatureLabel').text(obj.temperature + ' °C');
  $('#temperatureLabel').addClass('badge-default');

  tempData.push({
      "timestamp": Date().slice(16, 24),
      "value": parseInt(obj.temperature)
  });
  if (tempData.length >= 10) {
      tempData.shift()
  }
  drawChart("temperature", tempData);

  // humidty
  $('#humiditySensor').html('(Sensor value: ' + obj.humidity + ')');
  $('#humidityLabel').text(obj.humidity + ' %');
  $('#humidityLabel').addClass('badge-default');

  humiData.push({
      "timestamp": Date().slice(16, 24),
      "value": parseInt(obj.humidity)
  });
  if (humiData.length >= 10) {
      humiData.shift()
  }
  drawChart("humidity", humiData);
}

function drawChart(sensor, data) {
    let ctx;
    if (sensor === "temperature") {
        ctx = document.getElementById("tempChart").getContext("2d");
    } else if (sensor === "humidity") {
        ctx = document.getElementById("humiChart").getContext("2d");
    } else {
      return;
    };

    let values = []
    let timestamps = []

    data.map((entry) => {
        values.push(entry.value);
        timestamps.push(entry.timestamp);
    });

    let chart = new Chart(ctx, {
        type: 'line',
        data: {
            labels: timestamps,
            datasets: [{
                backgroundColor: 'rgb(255, 99, 132)',
                borderColor: 'rgb(255, 99, 132)',
                data: values
            }]
        },
        options: {
            legend: {
                display: false
            }
        }
    });
}

$(document).ready(function () {
    drawChart("temperature", tempData);
    MQTTconnect();
});
