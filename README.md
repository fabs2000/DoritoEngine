 Dorito Engine is an SFML engine written using part of the design patterns in the book "Game Programming Patterns".
 
 Towards the start of development, the debate on whether to use SDL or SFML to base the engine on was the main thing I thought about. 
 I ended up deciding on SFML since I believed that given the time I had put myself to complete the engine, the SFML API would be the one 
 to help me speed up development. This, however, did not mean it came without its problems.
 
 The engine, at its core, posseses a basic game loop based on time where objects are updated and rendered to the screen. Besides this, input is 
 also processed per frame, for this I believe the "Command" implementation was a bit cumbersome, so I opted for using callbacks on events added to a container of events, events 
 are also separated by keyboard and gamepad, split into SFML keyboard implementation and XINPUT gamepad implementation. I also use the "Observer" pattern to keep track of
 things like game stats and possibly audio.
 
 On the topic of objects rendered and updated, these are separated by scene, where only the "Active" scene can be rendered to the screen and updated. Each scene holds a container of 
 "GameObjects" and a container of "Colliders", where the collisions are checked/updated after the update of the GameObjects. Each GameObject is basically made up of a container of components
 Where the Game Object itsels owns a Transform and each Component also owns a Transform component. 
 
