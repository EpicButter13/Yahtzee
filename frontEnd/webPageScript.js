let identificationDetails = "0a10aced202194944a069dc4";
let accessToken = "82610000acc77661b40a96934329224927716751";
let cloudVariableName_RollData = "roll";

const particle = new Particle();
const lockInSound = new Audio('lockSFX.mp3');
//const fartSound = new Audio('unlockSFX.mp3');
const unlockSound = new Audio('unlockSFX.mp3');

// Sound functions
function playSound(sound) // Ensures audio plays no matter how fast button is clicked by duplicating/creating a new sound/instance object and then calling the play() method
{
  const s = sound.cloneNode(); // duplicate audio
  s.play();
}
function toggleMusic() 
{
  const music = document.getElementById("Sky_High");

  if(music.paused) 
  {
    music.play();
  } 
  else 
  {
    music.pause();
  }
}

// Dice reroll selector panel functions
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

// Poll every 1 second
setInterval(updateFromCloud, 1000);




// Adds button functionality
function rollThis(die, index)
{
  // Change the color of the selected button to show whether dice is locked in or not
  if(die.style.backgroundColor != "green") // Color to change to deselect die
  {
    particle.callFunction({
        deviceId: identificationDetails,
        name: 'UpdateSwitchState',  
        argument: `${index},1`,    // string parsed later     
        auth: accessToken
    })
    .then(data => {
        console.log('Function called, result:', data.body.return_value);
    })
    .catch(err => {
        console.error('Error calling function:', err);
    });
    die.style.backgroundColor = "green";
    playSound(lockInSound);
    return true;
  }
  else
  {
    particle.callFunction({
        deviceId: identificationDetails,
        name: 'UpdateSwitchState', 
        argument: `${index},0`,   // string parsed later
        auth: accessToken
    })
    .then(data => {
        console.log('Function called, result:', data.body.return_value);
    })
    .catch(err => {
        console.error('Error calling function:', err);
    });
    die.style.backgroundColor = "gray";
    playSound(unlockSound);
    return false;
  }
}