# Pace-Man : A Pac-Man Clone

## Pace-Man is a project created using C++ SFML 
### "Pace" represents the uniqueness of this clone, this clone would allow the player character to speed up his pace

<h3>General Discussion</h3>
<p>This project is a clone of the Pac-Man game created by Toru Iwatani and Atari in 1980. Being one of the staples of video games, I decided to create my version of this game and modify some aspects of the game. The project has an overarching World class that contains information about every aspect of the game. It stores essential details like the height and width of the board, current player score, Coordinates for the player and ghosts, and a two dimensional vector to hold tile pointers. This matrix is known as <i>(lowercase)</i> world</p>

<p>a Tile is a <i>mostly</i> abstract base class used to represent free space on the map. It contains the world (the matrix of tiles) by reference, as a Tile may need to perform swaps to move around in the world. This ability is granted by the move() and move(Coordinate) methods that are overloaded by classes Player, Red Ghost, and Blue Ghost. The overloaded move(Coordinate) takes in the coordinate of the player and is used by the Blue Ghost to follow the player around on the map of tiles.</p>

<p>The main loop is used for event handling and carrying out polling instructions to simulate steps on the world. The entire state of the game can be reset to default conditions by pressing the 'R' key anytime during the game. The Player's movements are handled by polling for WASD/Arrow Keys. Whenever the player moves to a Candy Tile, the score is updated in the World class and the Candy tile is turned into a space/empty tile. Moving the player once will move the player in that direction until a new direction is polled for.</p>

<p>If the Player or any of the Ghosts move in the direction of each other, the ghost will devour the player and reduce one of its lives. The player will then be reset to his spawn position and the game continues until all of the player lives deplete. </p>
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

<h3>Class Hierarchy Diagram</h3>

![image](https://github.com/realaryann/Pace-Man/assets/70107111/21e724db-a44c-422a-a174-592bf92ac61d)

<h2>Movement Controls</h2>
<h3>W/Up Arrow - Up</h3>
<h3>A/Left Arrow - Left</h3>
<h3>S/Down Arrow - Down</h3>
<h3>D/Right Arrow - Right</h3>

<h2>Ghost Rules</h2>
<h3>Red Ghost - Randomly chooses any direction and moves to it</h3>
<h3>Blue Ghost - Calculates how far the player character is and chases the player, but sometimes chooses a random direction</h3>







