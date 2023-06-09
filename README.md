# Software ontwikkeling

- [Description](#description)
- [Three tier model](#three-tier-model)
- [Usage](#usage)
- [ERRORS](#errors)

## Description

With this code scripts with commands can be read and the commands will be executed on a VGA screen.

## Three tier model

The three tier model is shown in the below picture. The I/O layer also consist of the API functions.

![alt text](/Images-readme/threetier.png "Three tier model")

The following model is designed by us. The front layer is for communication with UART. The logic layer to decipher ASCII scriptcommands and the I/O layer consist of the API functions and communication with the VGA screen.

![alt text](/Images-readme/Func_ontwerp.drawio.png "Diagram three tier model")

## Usage

### **Available colors**

- zwart
- blauw
- lichtblauw
- groen
- lichtgroen
- cyaan
- lichtcyaan
- rood
- lichtrood
- magenta
- lichtmagenta
- bruin
- geel
- grijs
- wit
- roze

### **Line command**

The following script command is for drawing a line

``lijn, x, y, x’, y’, kleur, dikte``

``x, y`` are starting points

``x', y'`` are end points

``kleur`` is desired color

``dikte`` is the thickness of line

![alt text](/Images-readme/lines.png "Drawable lines")

### **Rectangle command**

The following script command is for drawing a rectangle

``rechthoek, x_lup, y_lup, breedte, hoogte, kleur, gevuld``

``x_lup, y_lup`` are starting points of the upper left corner

``breedte, hoogte`` width, height

``kleur`` is desired color

``gevuld`` filled (1) or not filled (0)

![alt text](/Images-readme/rectangle.png "Drawable rectangle")

### **Bitmap command**

``bitmap, nr, x-lup, y-lup``

``nr``  number of the bitmap between 1 and 10

``x_lup, y_lup`` are starting points of the upper left corner

#### ***bitmap 1***

![alt text](/Images-readme/pijl-up.png "arrow up")

#### ***bitmap 2***

![alt text](/Images-readme/pijl-down.png "arrow down")

#### ***bitmap 3***

![alt text](/Images-readme/pijl-links.png "arrow left")

#### ***bitmap 4***

![alt text](/Images-readme/pijl-rechts.png "arrow right")

#### ***bitmap 5***

![alt text](/Images-readme/smiley-angry.png "Smiley angry")

#### ***bitmap 6***

![alt text](/Images-readme/smiley-angry-col.png "Smiley angry color")

#### ***bitmap 7***

![alt text](/Images-readme/smiley-happy.png "Smiley happy")

#### ***bitmap 8***

![alt text](/Images-readme/smiley-happy-col.png "Smiley happy color")

#### ***bitmap 9***

![alt text](/Images-readme/smiley-sad.png "Smiley sad")

#### ***bitmap 10***

![alt text](/Images-readme/smiley-sad-col.png "Smiley sad color")

### **Clearscreen command**

The following script command is for clearing the screen with a desired color

``clearscherm, kleur``

``kleur`` is desired color

## ERRORS

- COMMAND :
Er is een commando gegeven wat niet herkent wordt.
Ondersteunde commando's zijn: 'lijn', 'rechthoek', 'clearscherm' en 'bitmap'.

- OUT OF BOUNDS :
Er is een co-ordinaat gegeven wat zich buiten het scherm bevind.
De beschikbare co-ordinaten voor de X-as zijn 0 t/m 319, voor de Y-as 0 t/m 239.

- COLOR :
Er is een kleur opgegeven welke niet herkent wordt.
De beschikbare kleuren zijn: zwart, blauw, lichtblauw, groen, lichtgroen, cyaan, lichtcyaan, rood, lichtrood, magenta, lichtmagenta, bruin, geel, grijs, wit en roze.

- DATA :
Er is iets onbekends in de data reeks in gevuld.
De data wat herkent wordt zijn cijfers en letters, als er iets anders is ingevuld, zoals een '/'
dan wordt dit niet herkent.
