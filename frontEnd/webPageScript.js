// Define the data associated with the utilized microcontroller and cloud variable
let identificationDetails = "0a10aced202194944a069dc4";
let accessToken = "82610000acc77661b40a96934329224927716751";
let baseURL = "https://api.particle.io/v1/devices/";
let cloudVariableName_RollData = 'roll';


// ADD: initialize Particle API
const particle = new Particle();


// In the loop function, there will likely be a conditional to decide whether or not to send the current roll data (string data) to the cloud
// ,so the only thing that needs to be handled here is fetching that data from the cloud and displaying that on the webpage
//let rollString = "5 2 3 1 8";


// Establish an algorithim to fetch the string data held in the cloud variable that represents "rollString"

// (FIXED: correct parsing of returned object)
particle.getVariable({
  deviceId: identificationDetails,
  name: cloudVariableName_RollData,
  auth: accessToken
}).then(function(data) {

  console.log('Device variable retrieved successfully:', data);

  // original intent preserved, but corrected value extraction
  let rollString = data.body.result;

  document.getElementById("current_roll").innerHTML = rollString;

  // OPTIONAL ADD: if you later want to update the score table too
  // updateScores(rollString);

}, function(err) {
  console.log('An error occurred while getting attrs:', err);
});


setInterval(function () {
  particle.getVariable({
    deviceId: identificationDetails,
    name: cloudVariableName_RollData,
    auth: accessToken
  }).then(function(data) {

    let rollString = data.body.result;
    document.getElementById("current_roll").innerHTML = rollString;

    // OPTIONAL:
    // updateScores(rollString);

  });
}, 2000);



// Alternative, more general method (using the fetch method)
/*fetch(https://pokeapi.co/api/v2/pokemon/rayquaza)
    .then(Response => Response.jSon)
    .catch();*/


// Assign the new value to the HTML element that shall display that data to the player
//document.getElementById("current_roll").innerHTML = rollString; // HTML span tags have a manipulatable property called "innerHTML"