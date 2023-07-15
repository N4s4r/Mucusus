Devs:
Pol Ayala,231698, pol.ayala01@estudiant.upf.edu
Nasar Roca, 231676 nasar.roca01@estudiant.upf.edu


Optimicaciones:
	- Nuestro mundo esta dividido en celdas. Cada room es una celda en una grid de 7 x 7. En cada loop se detecta en que habitación se encuentra
	  el jugador y se calculan las colisiones solo con esa room.
	- Frustrum: solo se renderizan las meshes que se encuentran dentro de camara.
	- LODs: Las balas del juego cuentan con un sistema de LODs que hace que se renderice una mesh con mas o menos vértices en función de la distancia
	  a camara.
Implementaciones:
	- Se ha implementado un sistema de generación de mazmorra aleatorio. Para cada partida, la grid que conforma el mapa es generada aleatoriamente a
	  a partir del algoritmo de la función randomLoad() dentro de world.cpp. El algoritmo está basado en la generación de mapa del juego 
	  The Binding of Isaac a partir de la explicación que dan en este artículo: https://www.boristhebrave.com/2020/09/12/dungeon-generation-in-binding-of-isaac/
	- 


Shortcuts:
	- Para poder setear una sala como cleared, hay que pulsar 'u'. Entonces se limpia y se abren las puertas.
	- Para matar enemigos sin tener que disparar, pulsar 'k'. Un enemigo de la sala morira entonces.
	- Para simular ganar el juego instantaniamente, pulsar 'c'
	- Para simular perder el juego instantaniamente, pulsar 'l'



Partes del código de cada miembro:
Entidades:
	entityMesh: Nasar
	entityBullet: Pol
	entityDoor: Pol
	entityEnemy: Nasar
	entityMeshRoom: Pol
	entityPlayer: Pol
Stages:
	stageWin: Nasar
	stageGame: Pol, Nasar
	stageIntro: Pol
	stageTuto: Pol
camera: Pol
audio: Nasar
enemyManager: Nasar
gameHUD: Pol
world: Pol
menuGUI: Pol
Collisions: Pol i Nasar

Blender: Pol
Texturas: Pol | Nasar
