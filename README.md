# Pace-Man : A Pac-Man Clone

## Pace-Man is a passion project created using C++ SFML 
### "Pace" represents the uniqueness of this clone, this clone would allow the player character to speed up his pace

<h3> Map Design </h3>
<p>Pace-Man is capable of reading in custom symbol maps with the height and width specified at the top of the map<br>
as an example, the following is the default map supplied with the game. </p>

![image](https://github.com/realaryann/Pace-Man/assets/70107111/2c37f038-9b80-472e-8a17-99806f5452d3)   
![image](https://github.com/realaryann/Pace-Man/assets/70107111/7d54eb2d-7150-44e4-b29a-3dc04fca240b)

<h3>Symbol Table</h3>
<ul>
  <li>x - Wall</li>
  <li>o - Candy</li>
  <li>s - Empty Space/Tile</li>
  <li>b - Entry Point to the Ghost House</li>
  <li>1,2.. - Red Ghost, Blue Ghost...</li>
  <li>@ - Player/Pace-Man</li>
</ul>

<h3> In-Game Map Conversion </h3>

<h2>Movement Controls</h2>
<h3>W/Up Arrow - Up</h3>
<h3>A/Left Arrow - Left</h3>
<h3>S/Down Arrow - Down</h3>
<h3>D/Right Arrow - Right</h3>

<h2>Ghost Rules</h2>
<h3>Red Ghost - Randomly chooses any direction and moves to it</h3>
<h3>Blue Ghost - Calculates how far the player character is and chases the player, but sometimes chooses a random direction</h3>







