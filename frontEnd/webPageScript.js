// Define the data associated with the utilized microcontroller and cloud variable
let identificationDetails = "0a10aced202194944a069dc4";
let accessToken = "82610000acc77661b40a96934329224927716751";
let baseURL = "https://api.particle.io/v1/devices/";
let cloudVariableName_RollData = 'roll';


// In the loop function, there will likely be a conditional to decide whether or not to send the current roll data (string data) to the cloud
// ,so the only thing that needs to be handled here is fetching that data from the cloud and displaying that on the webpage
//let rollString = "5 2 3 1 8";


// Establish an algorithim to fetch the string data held in the cloud variable that represents "rollString"

// This (what to use when working with Particle Device Cloud API) can be found in https://docs.particle.io/reference/cloud-apis/javascript/
particle.getVariable({ deviceId: identificationDetails, name: cloudVariableName_RollData, auth: accessToken }).then(function(data) {
  console.log('Device variable retrieved successfully:', data);
  document.getElementById("current_roll").innerHTML = data;
}, function(err) {
  console.log('An error occurred while getting attrs:', err);
});



// Alternative, more general method (using the fetch method)
/*fetch(https://pokeapi.co/api/v2/pokemon/rayquaza)
    .then(Response => Response.jSon)
    .catch();*/


// Assign the new value to the HTML element that shall display that data to the player
//document.getElementById("current_roll").innerHTML = rollString; // HTML span tags have a manipulatable property called "innerHTML"