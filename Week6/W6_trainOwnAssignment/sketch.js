
/* DM3014 Interactive Devices, Jenn Teh 2026
 * Week 6 - Teachable Machine
 * Train Your Own Model
 * Week 6 - Teachable Machine
 * Edits:
 * Used Teachable Machine to train a model to classify hand gestures (Wink, Peace, Heart, Neutral) 
 * Best if body is mid to close to the camera,face in the middle of the screen
 * Wink: One side wink, left or right - if you cant wink pinch your thumb and index finger together and place it to one side of your eye 
 * - Go as close as you can to the camera for better detection. 
 * - 'wink gesture is abit finicky sometimes harder to detect if wink is not clear.
 * Heart: 
 * 1) Make a heart shape with your hands and place it in front of your chin/ neck area.
 * 2) Korean heart with thumb and index finger place it infront of your face at the side slighlty, let the hand cover your face abit on the screen closer to the camera.
 * 3) half heart on one side of your face
 * Peace: Do the peace sign with your index and middle finger, palm facing towards the camera.
 * Neutral: Keep your hands down, relax and still in front of the camera. there should be not sound.
 * Added effects when the model detects the gestures 
 * - Play different sounds based on the classification. 
 * - Change background color based on the classification.
 * - Apprently with Mac it also auto adds a visual effect to the video feed when it detects a gesture?? like heart, hearts will pop up on the video feed.
 * Changed the size of canvas, text position, text size and colour
 * {Check play final outcome and code more details}
 
 */

let classifier;
// model url link added after creating the model on Teachable Machine online
const imageModelURL = "https://teachablemachine.withgoogle.com/models/b3eRjF7Js/"; // Created my list of gestures on Teachable Machine and exported the model using google to get the link to the model.json file.

let video;
let flippedVideo;
let label = ""; // to store classifications
let soundA, soundB, soundC;


function preload() {
  classifier = ml5.imageClassifier(imageModelURL + "model.json");

  // Load the sound files for each gesture
  soundA = loadSound('wink.mp3');
  soundB = loadSound('happy.mp3');
  soundC = loadSound('heartbeat.mp3');
}

function setup() {
  //Changed the size of the canvas bigger to make it easier to see the video feed and the background colour change
  createCanvas(850, 500);
  video = createCapture(VIDEO);
  video.size(520, 440); // place the video to one side so that the text can be on the other side of the canvas and not under video feed
  video.hide();  
  flippedVideo = ml5.flipImage(video);
  classifyVideo();

  
}

// Change the colour of the background based on the classification 
function draw() {
if (label === 'Wink') {
    background(255, 255, 33);
  } else if (label === 'Heart') {
    background(255, 33, 133);
  } else if (label === 'Peace') {
    background(35, 247, 247);
  } else if (label === 'Neutral') {
    background(200);
  } else {
    background(0); // Default black background
  }

  // draw video
  image(flippedVideo, 40, 30);

  // rect(600,100);
  // draw label *** edit label here
  //Changed the text size, position and colour of the label
  fill(0);
  textSize(30);
  textAlign(CENTER);
  text(label, 700, 250);

//Play sound based on the classification
 if (label === "Wink") {
    if (!soundA.isPlaying()) {
      stopAllSounds();
      soundA.play();
      setTimeout(() => {
        soundA.stop();
      }, 1000); // 1000 ms = 1 second of the sound playing before it repeats as this is a short audio clip 
    }
  } else if (label === "Peace") {
    if (!soundB.isPlaying()) {
      stopAllSounds();
      soundB.play();
      setTimeout(() => {
        soundB.stop();
      }, 7000); // 7000 ms = 7 second of the sound playing before it repeats as this is a longer audio clip
    }
  }else if (label === "Heart") {
    if (!soundC.isPlaying()) {
      stopAllSounds();
      soundC.play();
      setTimeout(() => {
        soundB.stop();
      }, 3000);
    }
  }else if (label === "Neutral") {
      stopAllSounds(); // Neutral gesture stops all sounds
    }


// Stops all sounds so they don't play on top of each other
function stopAllSounds() {
  if (soundA && soundA.isPlaying()) soundA.stop();
  if (soundB && soundB.isPlaying()) soundB.stop();
  if (soundC && soundC.isPlaying()) soundC.stop();
}


}

// get prediction for the current video frame
function classifyVideo() {
  flippedVideo = ml5.flipImage(video);
  classifier.classify(flippedVideo, gotResult);
}


function gotResult(error, results) {
  if (error) {
    console.error(error);
    return;
  }

  label = results[0].label; // results in array ordered by confidence

  classifyVideo(); // classify again
}
