// Define the data associated with the utilized microcontroller and cloud variable
let identificationDetails = "0a10aced202194944a069dc4";
let accessToken = "82610000acc77661b40a96934329224927716751";
let cloudVariableName_RollData = "roll";


// initialize Particle API
const particle = new Particle();


// FUNCTION to update UI
function updateRoll() {
  particle.getVariable({
    deviceId: identificationDetails,
    name: cloudVariableName_RollData,
    auth: accessToken
  }).then(function(data) {

    console.log("Cloud response:", data);

    let rollString = data.body.result;

    document.getElementById("current_roll").textContent = rollString;

  }).catch(function(err) {
    console.log("Particle error:", err);
  });
}


// run once immediately
updateRoll();


// then poll every 2 seconds
setInterval(updateRoll, 2000);