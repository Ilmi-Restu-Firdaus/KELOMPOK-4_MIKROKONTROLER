const statusDiv = document.getElementById("status");

const client = mqtt.connect(
    "wss://broker.hivemq.com:8884/mqtt"
);

client.on("connect", () => {

    console.log("MQTT Connected");

    statusDiv.innerHTML = "MQTT : Connected";
    statusDiv.className = "status online";

    client.subscribe("smarthome/suhu");
    client.subscribe("smarthome/kelembaban");
    client.subscribe("smarthome/jarak");
});

client.on("reconnect", () => {

    statusDiv.innerHTML = "MQTT : Reconnecting...";
    statusDiv.className = "status offline";
});

client.on("error", (err) => {
    console.log(err);
});

client.on("message", (topic, message) => {

    let value = message.toString();

    if(topic === "smarthome/suhu"){
        document.getElementById("suhu").innerText = value;
    }

    if(topic === "smarthome/kelembaban"){
        document.getElementById("kelembaban").innerText = value;
    }

    if(topic === "smarthome/jarak"){
        document.getElementById("jarak").innerText = value;
    }

});

function lampu1(status){
    client.publish("smarthome/lampu1", status);
}

function lampu2(status){
    client.publish("smarthome/lampu2", status);
}

function lampu3(status){
    client.publish("smarthome/lampu3", status);
}

function kipas(status){
    client.publish("smarthome/kipas", status);
}
