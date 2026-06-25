// ================= MQTT CONFIG =================

const client = mqtt.connect(
    "wss://kelompok4mikrokontroller.cloud.shiftr.io:443",
    {
        username: "kelompok4mikrokontroller",
        password: "84wmjt1a5zRurEuh",
        reconnectPeriod: 3000
    }
);

// ================= ELEMENT =================

const statusBox = document.getElementById("status");
const suhuBox = document.getElementById("suhu");
const lembabBox = document.getElementById("lembab");

// ================= CONNECT =================

client.on("connect", () => {

    console.log("MQTT Connected");

    statusBox.innerHTML = "🟢 MQTT Connected";
    statusBox.style.background = "#28a745";
    statusBox.style.color = "#ffffff";

    client.subscribe("smarthome/sensor", (err) => {

        if (!err) {
            console.log("Subscribe berhasil");
        } else {
            console.error("Subscribe gagal:", err);
        }

    });
});

// ================= RECONNECT =================

client.on("reconnect", () => {

    console.log("MQTT Reconnecting...");

    statusBox.innerHTML = "🟡 MQTT Reconnecting...";
    statusBox.style.background = "#ffc107";
    statusBox.style.color = "#000000";
});

// ================= CLOSE =================

client.on("close", () => {

    console.log("MQTT Disconnected");

    statusBox.innerHTML = "🔴 MQTT Disconnected";
    statusBox.style.background = "#dc3545";
    statusBox.style.color = "#ffffff";
});

// ================= OFFLINE =================

client.on("offline", () => {

    console.log("MQTT Offline");

    statusBox.innerHTML = "🔴 MQTT Offline";
    statusBox.style.background = "#dc3545";
    statusBox.style.color = "#ffffff";
});

// ================= ERROR =================

client.on("error", (error) => {

    console.error("MQTT Error:", error);

    statusBox.innerHTML = "❌ MQTT Error";
    statusBox.style.background = "#dc3545";
    statusBox.style.color = "#ffffff";
});

// ================= RECEIVE MESSAGE =================

client.on("message", (topic, message) => {

    console.log(
        "Topic:",
        topic,
        "Message:",
        message.toString()
    );

    if (topic === "smarthome/sensor") {

        try {

            const data = JSON.parse(
                message.toString()
            );

            if (data.suhu !== undefined) {
                suhuBox.innerText = data.suhu;
            }

            if (data.lembab !== undefined) {
                lembabBox.innerText = data.lembab;
            }

        } catch (err) {

            console.error(
                "JSON Parse Error:",
                err
            );
        }
    }
});

// ================= CONTROL LED =================

function kontrolLED(status) {

    if (!client.connected) {

        alert("MQTT belum terhubung!");
        return;
    }

    client.publish(
        "smarthome/led",
        status
    );

    console.log(
        "LED:",
        status
    );
}

// ================= CONTROL FAN =================

function kontrolFan(status) {

    if (!client.connected) {

        alert("MQTT belum terhubung!");
        return;
    }

    client.publish(
        "smarthome/fan",
        status
    );

    console.log(
        "Fan:",
        status
    );
}
