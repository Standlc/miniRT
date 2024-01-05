# miniRT
Single thread ray/path tracer in C.

## Usage

Compile miniRT with the provided Makefile:

```bash
make
```

Or for linux:

```bash
make linux
```

Run miniRT with the desired scene file:

```bash
./miniRT [scene_file]
```

## Mouse & keyboard
### Move
Click and drag to move in the scene. The further away you click from the center of the screen, the farther the pivot point of the camera will be.
### Zoom
Hold the ```command ⌘``` key then click and drag to zoom in or out.

## Some samples

```bash
./miniRT scenes/columns.rt
```
![Screenshot 2024-01-05 at 00 26 19](https://github.com/Standlc/miniRT/assets/92372490/24285d60-c040-4366-8890-53ca5345a951)

```bash
./miniRT scenes/checkers.rt
```
![Screenshot 2024-01-05 at 11 47 26](https://github.com/Standlc/miniRT/assets/92372490/3b3805dc-4c05-4d73-a897-cd4b65f1092f)
