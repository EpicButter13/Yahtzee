let identificationDetails = "0a10aced202194944a069dc4";
let accessToken = "82610000acc77661b40a96934329224927716751";
let cloudVariableName_RollData = "roll";

const particle = new Particle();

function updateScores(scoreString) {
  if (!scoreString) return;

  const scores = scoreString.split(",");

  const ids = [
    "ones_score",
    "twos_score",
    "threes_score",
    "fours_score",
    "fives_score",
    "sixes_score",
    "three_kind_score",
    "four_kind_score",
    "full_house_score",
    "small_straight_score",
    "large_straight_score",
    "yahtzee_score",
    "chance_score"
  ];

  for (let i = 0; i < ids.length; i++) {
    const el = document.getElementById(ids[i]);

    if (el) {
      el.textContent = scores[i] ?? "--";
    }
  }
}

function updateFromCloud() {
  particle.getVariable({
    deviceId: identificationDetails,
    name: cloudVariableName_RollData,
    auth: accessToken
  })
  .then(function(data) {

    const rollString = data.body.result;

    console.log("Cloud response:", rollString);

    updateScores(rollString);

  })
  .catch(function(err) {
    console.log("Particle error:", err);
  });
}

// Start immediately
updateFromCloud();

// Poll every 2 seconds
setInterval(updateFromCloud, 2000);




// Function to add functionality to the buttons that select which dice to reroll
function rollThis(die)
{
  // Send a boolean data type, as this function determines whether a die is selected or not and sends that data back to the microcontroller
  // Change the color of the selected button to clearly show that the player successfully selected a die
  //console.log(document.getElementById(die.id));
  //console.log("THIS IS THE DIE ID: " + die.id);
  if(die.style.backgroundColor != "green") // Color to change to deselect die
  {
    die.style.backgroundColor = "green";
    return true;
  }
  else // Color to change to select the die
  {
    die.style.backgroundColor = "gray";
    return false;
  }

  // Note: Will probably need to utilize Particle functions to send/change data for cloud variables from the webPage
}