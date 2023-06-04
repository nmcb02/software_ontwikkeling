# Software ontwikkeling

- [Description](#description)
- [Three tier model](#three-tier-model)
- [Usage](#usage)

## Description

## Three tier model

The three tier model is shown in the below picture. The I/O layer also consist of the API functions.
![alt text](Images-readme\threetier.png "Three tier model")

The following model is designed by us. The front layer is for communication with UART. De logic layer to decipher ASCII scriptcommands and the I/O layer consist of the API functions and communication with the VGA screen.
![alt text](Images-readme\Func_ontwerp.drawio.png "Diagram three tier model")

## Usage

### Available colors

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

### Line command

The following script command is for drawing a line

``lijn, x, y, x’, y’, kleur, dikte``

``x, y`` are starting points

``x', y'`` are end points

``kleur`` is desired color

``dikte`` is the thickness of line

![alt text](Images-readme\lines.png "Drawable lines")

### Rectangle command
The following script command is for drawing a rectangle

``rechthoek, x_lup, y_lup, breedte, hoogte, kleur, gevuld``

``x_lup, y_lup`` are starting points

``breedte, hoogte`` width, height

``kleur`` is desired color

``gevuld`` filled (1) or not filled (0)

![alt text](Images-readme\rectangle.png "Drawable rectangle")

### Bitmap command

### Clearscreen command
